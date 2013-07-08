
#ifndef _PROCESS_H_
	#define _PROCESS_H_

#include <iostream>
#include <string>
#include <random>
#include <stdio.h>
#include <chrono>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <array>

#include <EALib/ChromosomeCMA.h>
#include <SharkDefs.h>
#include <EALib/PopulationT.h>
#include <EALib/ObjectiveFunction.h>

// #include "../include/PRPSError.h"
// #include "../libPermutate/permutate.h"
// #include "../libPRPSSystem/prpsevolutionsystem.h"
// #include "../libNormalizer/normalizer.h"

#include "solveresult.h"
#include "solve.h"
#include "ueber9000.h"

namespace PRPSEvolution {
	namespace Solve {
		using std::chrono::duration_cast;
		using std::chrono::microseconds;
		using std::chrono::milliseconds;
		using std::chrono::steady_clock;
		
		/******************************************************************/
		/* Process Class **************************************************/
		/******************************************************************/

		/**
		 * Find solutions for the possible matrices
		 *
		 */
		class Process
		{
		public:
			/*	the strategy to find a solution */
// 			ESStrategy strategy;

			/* */

			/**
			 * Constructor

			 */
			Process(  ) {

			}

			Process(const Process &p) :solutionFitness( p.solutionFitness ), minSolutionFitness( p.minSolutionFitness ) {


			}

			double getLastSolutionFitness() { return solutionFitness; }

			/**
			 * Set the ES-Strategy
			 * @param[in] Strategy The selected strategy
			 *
			 */
// 			void setESStrategy( ESStrategy Strategy ) {
// 				strategy = Strategy;
//
// 			}

			/**
			 * Find a Solution for a given pair of matrices
			 * @param[in] A_selected The matrix A to use in this solution
			 * @param[in] b_selected The c_k0' vector for this solution
			 * @return The solution
			 *
			 */
			template<typename T>
			T
			findSolution
			( const NRmatrix< Doub > &A_selected, const NRvector< Doub > &b_selected, PRPSEvolution::Solve::ESStrategy strategy, int seed )
			{
				/* create a new instance of Ueber9000 */
				Ueber9000<Doub> ueber( A_selected, b_selected );
// 				Ueber9000<Doub> ueber;
// 				ueber9000 = &t;

				T solution;

				switch( strategy ) {
					case (int) PRPSEvolution::Solve::ESStrategy::OnePlusOne:
						solution = OnePlusOneES( &ueber );
						break;

					case (int) PRPSEvolution::Solve::ESStrategy::MuPlusLambda :
						solution = MuPlusLambdaES( &ueber, seed );
						break;

					case (int) PRPSEvolution::Solve::ESStrategy::MuCommaLambda:
						solution = MuCommaLambdaES( &ueber, seed );
						break;

				}
				return solution;

			}

			int sq( int i ) {return i*i; }

			/**
			 * Sets the min. solution fitness we want to achieve.
			 * @param[in] value The new value for the solution fitness
			 *
			 */
			void setMinSolutionFitness( double value ) { minSolutionFitness = value; }

			/**
			 *
			 */
			void setSeed( unsigned int value ) { Rng::seed(value); }

		private:

			double solutionFitness;
			double minSolutionFitness;

			/* The strategies **********************************************/
			/** Enter description */
			solveresult_t<ChromosomeT<double>, Doub>
			OnePlusOneES( Ueber9000<double> *ueber9000 ) {
				steady_clock::time_point t_0 = steady_clock::now();
				// EA parameters
				const unsigned Dimension      = ueber9000->Dimension;
				const unsigned Iterations     = 3000;
				const double   MinInit        = -3.;
				const double   MaxInit        = 7.;
				const double   GlobalStepInit = 5.;

				ChromosomeCMA parent(Dimension),
								offspring(Dimension);

				double fitnessParent, fitnessOffspring;
				bool			Convergence = false;

				parent.init( Dimension, GlobalStepInit, MinInit, MaxInit );

				fitnessParent = (ueber9000->*ueber9000->evaluate)( parent );
				unsigned int t;
				// loop over generations
				for ( t = 0; t < Iterations; t++) {
					offspring = parent;
					offspring.mutate();

					fitnessOffspring =  (ueber9000->*ueber9000->evaluate)( offspring );

					bool success = ( fitnessOffspring < fitnessParent );

					if( success ) {
						offspring.updateCovariance();
						parent = offspring;
						fitnessParent = fitnessOffspring;
					}
					parent.updateGlobalStepsize( success );

					if( fitnessParent < minSolutionFitness )
						break;

				}
// 				solutionFitness = fitnessParent;

// 				if( t >= Iterations )
// 					std::cout << t << " 1+1 Done " << std::endl;
// 				std::cout << t << " Done \tFinal Fitness: " << fitnessParent << endl;
// 				for(unsigned i=0; i < Dimension; i++)
// 					std::cout << i << " " << parent[i] << " " ;

// 				std::cout << std::endl;
				steady_clock::time_point t_1 = steady_clock::now();

				solveresult_t<ChromosomeT<double>, Doub> res;
				res.values = parent;
				res.fitness = fitnessParent;
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
				res.iterations = t;
				res.converged = Convergence;

				return res;

			}

			/** Enter description */
			solveresult_t<ChromosomeT<double>, Doub>
			MuCommaLambdaES( Ueber9000<double> *ueber9000, double seed ) {
				steady_clock::time_point t_0 = steady_clock::now();

				const unsigned Mu           = 20;
				const unsigned Lambda       = 40;
				const unsigned Dimension    = ueber9000->Dimension;
				const unsigned Iterations   = 2000;
				const unsigned Interval     = 10;
				const unsigned NSigma       = 3;

				const double   GlobalStepInit = 5.;

				const double   MinInit        = -3.;
				const double   MaxInit        = 7.;
				const double   SigmaInit    = 3;

				/* activate elitist strategy */
				const bool     PlusStrategy = false;
				bool			Convergence = false;

				unsigned       i, t;

				// linear congruential generator
// 				std::mt19937 gen;

				// initialize the generator
// 				gen.seed((unsigned int)time(NULL));

				Rng::seed(seed);

				// define populations
				PopulationT<double> parents(Mu,     ChromosomeT< double >(Dimension),
								ChromosomeT< double >(NSigma));
				PopulationT<double> offsprings(Lambda, ChromosomeT< double >(Dimension),
									ChromosomeT< double >(NSigma));

				// minimization task
				parents.setMinimize();
				offsprings.setMinimize();

				// initialize parent population
				for (i = 0; i < parents.size(); ++i) {
					parents[ i ][ 0 ].initialize(MinInit,   MaxInit);
					parents[ i ][ 1 ].initialize(SigmaInit, SigmaInit);
				}

				// selection parameters (number of elitists)
				unsigned numElitists = PlusStrategy ? Mu : 0;

				// standard deviations for mutation of sigma
				double     tau0 = 1. / sqrt(2. * Dimension);
				double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));

				// evaluate parents (only needed for elitist strategy)
				if (PlusStrategy)
					for (i = 0; i < parents.size(); ++i)
						parents[ i ].setFitness((ueber9000->*ueber9000->evaluate)(parents[ i ][ 0 ]));

				std::vector<double> fitness;
				fitness.reserve(10);

				// iterate
				for (t = 0; t < Iterations; ++t) {
					// generate new offsprings
					for (i = 0; i < offsprings.size(); ++i) {
						// select two random parents
						Individual& mom = parents.random();
						Individual& dad = parents.random();

						// recombine object variables discrete, step sizes intermediate
						offsprings[ i ][ 0 ].recombineDiscrete(mom[ 0 ], dad[ 0 ]);
						offsprings[ i ][ 1 ].recombineGenIntermediate(mom[ 1 ], dad[ 1 ]);

						// mutate object variables normal distributed,
						// step sizes log normal distributed
						offsprings[ i ][ 1 ].mutateLogNormal(tau0,  tau1);
						offsprings[ i ][ 0 ].mutateNormal(offsprings[ i ][ 1 ], true);
					}

					// evaluate objective function (parameters in chromosome #0)
					for (i = 0; i < offsprings.size(); ++i)
						offsprings[ i ].setFitness((ueber9000->*ueber9000->evaluate)(offsprings[ i ][ 0 ]));

					// select (mu,lambda) or (mu+lambda)
					parents.selectMuLambda(offsprings, numElitists);

					// print out best value found so far
					if( parents.best().fitnessValue() < minSolutionFitness )
						break;

				}

				auto p = parents.best();

				solutionFitness = parents.best().fitnessValue();

// 				if( t >= Iterations )
// 					std::cout << t << " mu,lambda Done  " << std::endl;

// 				std::cout << t << " Done \tFinal Fitness: " << parents.best().fitnessValue() << endl;
/*
				for( int i = 0; i < 10; i++ )
					std::cout << i << " " << p[0][i] << " " ;
				std::cout << std::endl;*/
				steady_clock::time_point t_1 = steady_clock::now();

				solveresult_t<ChromosomeT<double>, Doub> res;
				res.values = p[0];
				res.fitness = p.fitnessValue();
				res.iterations = t;
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
				res.converged = Convergence;

				return res;

			}

			/** Enter description */
			solveresult_t<ChromosomeT<double>, Doub>
			MuPlusLambdaES( Ueber9000<double> *ueber9000, double seed ) {
				steady_clock::time_point t_0 = steady_clock::now();

				const unsigned Mu           = 5;
				const unsigned Lambda       = 25;
				const unsigned Dimension    = ueber9000->Dimension;
				const unsigned Iterations   = 3000;
				const unsigned Interval     = 10;
				const unsigned NSigma       = 1;

				const double   GlobalStepInit = 5.;


				const double   MinInit        = -3.;
				const double   MaxInit        = 7.;
				const double   SigmaInit    = 3;

				/* activate elitist strategy */
				const bool     PlusStrategy = true;
				bool			Convergence = false;

				unsigned       i, t;

				// initialize random number generator
				Rng::seed(seed);

				// define populations
				PopulationT<double> parents(Mu,     ChromosomeT< double >(Dimension),
								ChromosomeT< double >(NSigma));

				PopulationT<double> offsprings(Lambda, ChromosomeT< double >(Dimension),
									ChromosomeT< double >(NSigma));

				// minimization task
				parents   .setMinimize();
				offsprings.setMinimize();

				// initialize parent population
				for (i = 0; i < parents.size(); ++i) {
					parents[ i ][ 0 ].initialize(MinInit,   MaxInit);
					parents[ i ][ 1 ].initialize(SigmaInit, SigmaInit);
				}

				// selection parameters (number of elitists)
				unsigned numElitists = PlusStrategy ? Mu : 0;

				// standard deviations for mutation of sigma
				double     tau0 = 1. / sqrt(2. * Dimension);
				double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));

				// evaluate parents (only needed for elitist strategy)
				if (PlusStrategy)
					for (i = 0; i < parents.size(); ++i)
						parents[ i ].setFitness((ueber9000->*ueber9000->evaluate)(parents[ i ][ 0 ]));

				std::vector<double> fitness;
				fitness.reserve(10);

				// iterate
				for (t = 0; t < Iterations; ++t) {
					// generate new offsprings
					for (i = 0; i < offsprings.size(); ++i) {
						// select two random parents
						Individual& mom = parents.random();
						Individual& dad = parents.random();

						// recombine object variables discrete, step sizes intermediate
						offsprings[ i ][ 0 ].recombineDiscrete(mom[ 0 ], dad[ 0 ]);
						offsprings[ i ][ 1 ].recombineGenIntermediate(mom[ 1 ], dad[ 1 ]);

						// mutate object variables normal distributed,
						// step sizes log normal distributed
						offsprings[ i ][ 1 ].mutateLogNormal(tau0,  tau1);
						offsprings[ i ][ 0 ].mutateNormal(offsprings[ i ][ 1 ], true);
					}

					// evaluate objective function (parameters in chromosome #0)
					for (i = 0; i < offsprings.size(); ++i)
						offsprings[ i ].setFitness((ueber9000->*ueber9000->evaluate)(offsprings[ i ][ 0 ]));

					// select (mu,lambda) or (mu+lambda)
					parents.selectMuLambda(offsprings, numElitists);

					// print out best value found so far
					if( parents.best().fitnessValue() < minSolutionFitness )
						break;

					/* convergenzkriterium */
					if( t > 20 ) {
						double sum = 0.;
						for( auto i : fitness ) {
							sum += i;

						}
						sum /= fitness[fitness.size()-1];
						sum = abs( sum );
// 						std::cout << sum <<std::endl;
						if( sum == fitness.size() ) { Convergence = true; break; }
						fitness.erase( fitness.begin(), fitness.begin() + 1 );

					}
					fitness.push_back( parents.best().fitnessValue() );

				}

				steady_clock::time_point t_1 = steady_clock::now();

				auto p = parents.best();
				solutionFitness = parents.best().fitnessValue();

// 				if( t >= Iterations )
// 					std::cout << t << " mu+lambda Done " << p.fitnessValue() << std::endl;

				/* create result statistic */
				solveresult_t<ChromosomeT<double>, Doub> res;
				res.values = p[0];
				res.fitness = p.fitnessValue();
				res.iterations = t;
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
				res.converged = Convergence;

				return res;

			}


// 			void Another( &ueber ) {
// 				const unsigned Mu           = 5;
// 				const unsigned Lambda       = 10;
// 				const unsigned Dimension    = 10;
// 				const unsigned Iterations   = 2000;
// 				const unsigned Interval     = 10;
// 				const unsigned NSigma       = 1;
//
// 				const double   GlobalStepInit = 5.;
//
//
// 				const double   MinInit        = -3.;
// 				const double   MaxInit        = 7.;
// 				const double   SigmaInit    = 6;
//
// 				/* activate elitist strategy */
// 				const bool     PlusStrategy = true;
//
// 				unsigned       i, t;
//
// 				// initialize random number generator
// 				Rng::seed(1234);
//
// 				// define populations
// 				PopulationT<double> parents(Mu,     ChromosomeT< double >(Dimension),
// 								ChromosomeT< double >(NSigma));
// 				PopulationT<double> offsprings(Lambda, ChromosomeT< double >(Dimension),
// 									ChromosomeT< double >(NSigma));
//
// 				// minimization task
// 				parents   .setMinimize();
// 				offsprings.setMinimize();
//
// 				// initialize parent population
// 				for (i = 0; i < parents.size(); ++i) {
// 					parents[ i ][ 0 ].initialize(MinInit,   MaxInit);
// 					parents[ i ][ 1 ].initialize(SigmaInit, SigmaInit);
// 				}
//
// 				// selection parameters (number of elitists)
// 				unsigned numElitists = PlusStrategy ? Mu : 0;
//
// 				// standard deviations for mutation of sigma
// 				double     tau0 = 1. / sqrt(2. * Dimension);
// 				double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));
//
// 				// evaluate parents (only needed for elitist strategy)
// 				if (PlusStrategy)
// 					for (i = 0; i < parents.size(); ++i)
// 						parents[ i ].setFitness((ueber9000->*ueber9000->evaluate)(parents[ i ][ 0 ]));
//
// 				std::vector<double> fitness;
// 				fitness.reserve(10);
//
// 				// iterate
// 				for (t = 0; t < Iterations; ++t) {
// 					// generate new offsprings
// 					for (i = 0; i < offsprings.size(); ++i) {
// 						// select two random parents
// 						Individual& mom = parents.random();
// 						Individual& dad = parents.random();
//
// 						// recombine object variables discrete, step sizes intermediate
// 						offsprings[ i ][ 0 ].recombineDiscrete(mom[ 0 ], dad[ 0 ]);
// 						offsprings[ i ][ 1 ].recombineGenIntermediate(mom[ 1 ], dad[ 1 ]);
//
// 						// mutate object variables normal distributed,
// 						// step sizes log normal distributed
// 						offsprings[ i ][ 1 ].mutateLogNormal(tau0,  tau1);
// 						offsprings[ i ][ 0 ].mutateNormal(offsprings[ i ][ 1 ], true);
// 					}
//
// 					// evaluate objective function (parameters in chromosome #0)
// 					for (i = 0; i < offsprings.size(); ++i)
// 						offsprings[ i ].setFitness((ueber9000->*ueber9000->evaluate)(offsprings[ i ][ 0 ]));
//
// 					// select (mu,lambda) or (mu+lambda)
// 					parents.selectMuLambda(offsprings, numElitists);
//
// 					// print out best value found so far
// 					if( parents.best().fitnessValue() < 1e-18 )
// 						break;
//
// // 					/* convergenzkriterium */
// // 					if( t > 10 ) {
// // 						double sum = 0.;
// // 						for( auto i : fitness ) {
// // 							sum += i;
// // //
// // 						}
// // 						sum -= fitness.size()*fitness[0];
// // 						sum = abs( sum );
// //
// // 						if( sum < .1) break;
// // 						fitness.erase( fitness.begin(), fitness.begin() + 1 );
// //
// // 					}
// // // 					fitness.resize(9);
// // 					fitness.push_back( parents.best().fitnessValue() );
//
// 				}
//
// 				auto p = parents.best();
// 				std::cout << t << " Done \tFinal Fitness: " << parents.best().fitnessValue() << endl;
//
// 				for( int i = 0; i < 10; i++ )
// 					std::cout << i << " " << p[0][i] << " " ;
// 				std::cout << std::endl;
//
// 			}

		};

		/******************************************************************/
		/* Process Class Function implementation **************************/
		/******************************************************************/

	}
}
#endif /* _PROCESS_H_ */ 
