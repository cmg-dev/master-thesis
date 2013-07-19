
#ifndef _PROCESS_H_
	#define _PROCESS_H_

	#ifndef  _USE_SHARK_3_0_

#include <iostream>
#include <string>
#include <random>
#include <stdio.h>
#include <chrono>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <array>

#include "nr3/nr3.h"

// #include <shark/Algorithms/DirectSearch/CMA.h>
// #include <shark/ObjectiveFunctions/Benchmarks/Benchmarks.h>

#include <Shark2.3/EALib/ChromosomeCMA.h>
#include <Shark2.3/SharkDefs.h>
#include <Shark2.3/EALib/PopulationT.h>
#include <Shark2.3/EALib/ObjectiveFunction.h>
#include <Shark2.3/EALib/Population.h>
#include <Shark2.3/EALib/CMA.h>
   
// #include "../include/PRPSError.h"
// #include "../libPermutate/permutate.h"
// #include "../libPRPSSystem/prpsevolutionsystem.h"
// #include "../libNormalizer/normalizer.h"

#include "../include/PRPSEvolutionSolveExceptions.h"
#include "../include/PRPSEvolutionFIOExceptions.h"
#include "../include/PRPSEvolutionGeneralExceptions.h"

#include "solveresult.h"
#include "solve.h"
#include "ueber9000.h"
#include "ObjectFunctions.h"

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
			 *
			 */
			Process(  ) {

			}

			Process( const Process &p ) : solutionFitness( p.solutionFitness ), minSolutionFitness( p.minSolutionFitness ) {

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
			 * @todo document
			 * @return The solution
			 *
			 */
			template<typename T>
			T
			findSolutionCMA_ES_MkI()
			{
				Ueber9000<Doub> ueber(1);
				return solve<T>( &ueber, Solve::ESStrategy::CMA_ES_MkI, 12345 );

				
			}

			/**
			 * @todo document
			 * @return The solution
			 *
			 */
			template<typename T>
			T
			findSolutionCMA_ES_MkII()
			{
				Ueber9000<Doub> ueber(1);
				return solve<T>( &ueber, Solve::ESStrategy::CMA_ES_MkII, 12345 );


			}

			/**
			 * Find a Solution for a given pair of matrices
			 * @param[in] A_selected The matrix A to use in this solution
			 * @param[in] b_selected The c_k0' vector for this solution
			 * @return The solution
			 *
			 */
			template<typename T>
			T
			findSolutionSolveSingle
			(
				const NRmatrix< Doub > &A_selected,
				const NRvector< Doub > &b_selected,
				const std::vector<std::string> &names_selected,
				const int ants,
				const PRPSEvolution::Solve::ESStrategy strategy,
				const int seed
			)
			{
				std::vector<NRmatrix< Doub >> A_;
				std::vector<NRvector< Doub >> b_;
				A_.push_back(A_selected);
				b_.push_back(b_selected);
				
				/* create a new instance of Ueber9000 */
				Ueber9000<Doub> ueber( A_, b_, names_selected, ants, 1 );
// 				Ueber9000<Doub> ueber;
// 				ueber9000 = &t;

// 				T solution;

// 				switch( strategy ) {
// 					case (int) PRPSEvolution::Solve::ESStrategy::OnePlusOne:
// 						solution = OnePlusOneES( &ueber );
// 						break;
// 
// 					case (int) PRPSEvolution::Solve::ESStrategy::MuPlusLambda :
// 						solution = MuPlusLambdaES( &ueber, seed );
// 						break;
// 
// 					case (int) PRPSEvolution::Solve::ESStrategy::MuCommaLambda:
// 						solution = MuCommaLambdaES( &ueber, seed );
// 						break;
// 
// 				}
				return solve<T>( &ueber, strategy, seed );

			}

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
			(
				const std::vector<NRmatrix< Doub >> &A_selected,
				const std::vector<NRvector< Doub >> &b_selected,
				const std::vector<std::string> &names_selected,
				const int ants,
				const PRPSEvolution::Solve::ESStrategy strategy,
				const int seed
			)
			{

				/* Setup the Problem */
				Ueber9000<Doub> ueber( A_selected, b_selected, names_selected, ants, 1 );
// 				Ueber9000<Doub> ueber;
// 				ueber9000 = &t;

// 				throw Exceptions::General::NotImplemented();

				return solve<T>( &ueber, strategy, seed );

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

			template<typename T>
			inline
			T solve
			(  Ueber9000<double> *ueber, const PRPSEvolution::Solve::ESStrategy &strategy, const int seed )
			{
				T solution;

				switch( strategy ) {
					case (int) PRPSEvolution::Solve::ESStrategy::OnePlusOne:
						solution = OnePlusOneES<T>( ueber );
						break;

					case (int) PRPSEvolution::Solve::ESStrategy::MuPlusLambda :
						solution = MuPlusLambdaES<T>( ueber, seed );
						break;

					case (int) PRPSEvolution::Solve::ESStrategy::MuCommaLambda:
						solution = MuCommaLambdaES<T>( ueber, seed );
						break;

					case (int) PRPSEvolution::Solve::ESStrategy::MuCommaLambda_MkII:
						solution = MkIII<T>( ueber, seed );
						
						break;
					case (int) PRPSEvolution::Solve::ESStrategy::MuPlusLambda_MkII:
						solution = MkIII<T>( ueber, seed, false );
						break;

					case (int) PRPSEvolution::Solve::ESStrategy::CMA_ES_MkI:
						solution = CMA_ES_MkI<T>( ueber, seed );
						break;

					case (int) PRPSEvolution::Solve::ESStrategy::CMA_ES_MkII:
						solution = CMA_ES_MkII<T>( ueber, seed );
						break;
				}
				return solution;
				
			}
			
			/* The strategies **********************************************/
			/** Enter description */
			template<typename T>
			T
			OnePlusOneES( Ueber9000<double> *ueber9000 ) {
				steady_clock::time_point t_0 = steady_clock::now();
				// EA parameters
				const unsigned Dimension      = ueber9000->Dimension;
				const unsigned Iterations     = 30000;
				const double   MinInit        = -7.;
				const double   MaxInit        = 7.;
				const double   GlobalStepInit = 5.;

				ChromosomeCMA parent(Dimension), offspring(Dimension);

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

				T res;
// 				res.values.push_back( parent );
				res.fitness = fitnessParent;
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
				res.iterations = t;
				res.converged = Convergence;

				return res;

			}

			/** Enter description */
			template<typename T>
			T
			MuCommaLambdaES( Ueber9000<double> *ueber9000, double seed ) {
				steady_clock::time_point t_0 = steady_clock::now();

				const unsigned Mu           = 20;
				const unsigned Lambda       = 40;
				const unsigned Dimension    = ueber9000->Dimension;
				const unsigned Iterations   = 20000;
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

// 				Rng::seed(seed);

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

				T res;
// 				res.values.push_back( p[0] );
				res.fitness = p.fitnessValue();
				res.iterations = t;
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
				res.converged = Convergence;

				return res;

			}

			/** Enter description */
			template<typename T>
			T
			MkIII( Ueber9000<double> *ueber9000, double seed, const bool PlusStrategy = false ) {
				/* t_0 */
				steady_clock::time_point t_0 = steady_clock::now();

				const unsigned Mu           = 5;
				const unsigned Lambda       = 10;

				/* determine the problem dimensions */
				const unsigned Dimension    = ueber9000->Dimension;
				const unsigned DimensionCont	= 3;
				const unsigned DimensionDisc	= Dimension - 3;
				
				const unsigned Iterations   = 20000;
				const unsigned Interval     = 10;
				const unsigned NSigma       = 1;

				const double   GlobalStepInit = 5.;

				const int		MinInitDis		= 0;
				const int		MaxInitDis		= 20;
				const double	MinInitCont		= -3.;
				const double	MaxInitCont		= 3;
				
				const double   SigmaInit    = 3;

				/* activate elitist strategy */
				bool			Convergence = false;

				unsigned       i, t;

				// linear congruential generator
// 				std::mt19937 gen;

				// initialize the generator
// 				gen.seed((unsigned int)time(NULL));

// 				Rng::seed(seed);
// 				std::cerr << "1" << std::endl;
				// define populations
				Population parents(
									Mu,
									ChromosomeT<double>(DimensionCont),
									ChromosomeT< int >(DimensionDisc),
									ChromosomeT<double>(NSigma)
									);
				
				Population offsprings(
									Lambda,
									ChromosomeT<double>(DimensionCont),
									ChromosomeT< int >(DimensionDisc),
									ChromosomeT<double>(NSigma)
									);
// 				PopulationT<double> parents(Mu,     ChromosomeT< double >(Dimension),
// 								ChromosomeT< double >(NSigma));
// 				PopulationT<double> offsprings(Lambda, ChromosomeT< double >(Dimension),
// 									ChromosomeT< double >(NSigma));
// 
// 				std::cerr << "2" << std::endl;
				// minimization task
				parents.setMinimize();
				offsprings.setMinimize();

				// initialize parent population
				for (i = 0; i < parents.size(); ++i) {
					dynamic_cast< ChromosomeT< double >& >
						( parents[ i ][ 0 ] ).initialize( MinInitCont,   MaxInitCont ) ;
					dynamic_cast< ChromosomeT< int >& >
						( parents[ i ][ 1 ] ).initialize( MinInitDis, MaxInitDis );
					dynamic_cast< ChromosomeT< double >& >
						( parents[ i ][ 2 ] ).initialize( SigmaInit, SigmaInit );
				}

// 				std::cerr << "3" << std::endl;
// 				for (i = 0; i < children.size(); ++i) {
// 					dynamic cast( ChromosomeT< double >& >
// 						( children[ i ][ 0 ] ).initialize( MinInit,   MaxInit) );
// 					dynamic cast( ChromosomeT< int >& >
// 						( children[ i ][ 1 ] ).initialize( -10, 10 );
// 					dynamic cast( ChromosomeT< double >& >
// 						( children[ i ][ 2 ] ).initialize( SigmaInit, SigmaInit) );
// 
// 				}
				// selection parameters (number of elitists)
				unsigned numElitists = PlusStrategy ? Mu : 0;

				// standard deviations for mutation of sigma
				double     tau0 = 1. / sqrt(2. * Dimension);
				double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));

// std::cerr << "4" << std::endl;
				// evaluate parents (only needed for elitist strategy)
				if (PlusStrategy)
					for (i = 0; i < parents.size(); ++i)
						parents[ i ].setFitness(
							( ueber9000->*ueber9000->evaluateMkIII )
								(
									dynamic_cast< ChromosomeT< double >& >( parents[ i ][ 0 ] ),
									dynamic_cast< ChromosomeT< int >& >( parents[ i ][ 1 ] )
								)
							);

// std::cerr << "5" << std::endl;

				std::vector<double> fitness;
// 				fitness.reserve(20);

				// iterate
				for (t = 0; t < Iterations; ++t) {
					// generate new offsprings
					for (i = 0; i < offsprings.size(); ++i) {
						// select two random parents
						Individual& mom = parents.random();
						Individual& dad = parents.random();

						/* make it more convinient */
						ChromosomeT< double >& objvarContinuous =
							dynamic_cast< ChromosomeT< double >& >( offsprings[ i ][ 0 ] );
							
						ChromosomeT< int >& objvarDiscrete =
							dynamic_cast< ChromosomeT< int >& >( offsprings[ i ][ 1 ] );
							
						ChromosomeT< double >& stepSize =
							dynamic_cast< ChromosomeT< double >& >( offsprings[ i ][ 2 ] );
							

						/**/
						// recombine object variables discrete, step sizes intermediate
						objvarContinuous	.recombineDiscrete( mom[ 0 ], dad[ 0 ] );
						objvarDiscrete		.recombineDiscrete( mom[ 1 ], dad[ 1 ] );
						stepSize			.recombineGenIntermediate( mom[ 2 ], dad[ 2 ] );
// 						stepSize[1]	.recombineGenIntermediate( mom[ 2 ], dad[ 2 ] );
// 						stepSizeContinuous	.recombineGenIntermediate( mom[ 2 ], dad[ 2 ] );
// 						stepSizeDiscrete	.recombineGenIntermediate( mom[ 3 ], dad[ 3 ] );

						// mutate object variables normal distributed,
						// step sizes log normal distributed
// 						stepSizeContinuous			.mutateLogNormal(tau0,  tau1);
// 						stepSizeDiscrete			.mutateLogNormal(tau0,  tau1);
						stepSize			.mutateLogNormal(tau0,  tau1);
// 						std::cerr << "sS " << stepSize << std::endl;

// std::cerr << "9" << std::endl;
// 						int j;
// 						std::cout << "before" << std::endl;
// 						for( j = 0; j < objvarContinuous.size(); j++ )
// 							std::cout << objvarContinuous[j] << " ";
// 						std::cout << "" << std::endl;

						/* mutate */
						stepSize			.cutOff( 1, MaxInitCont );
// 						stepSizeContinuous		.cutOff( 1, MaxInitCont );
// 						stepSizeDiscrete		.cutOff( 1, MaxInitDis );
						objvarContinuous		.mutateNormal( stepSize, true );
						objvarDiscrete			.mutateDiffGeom( stepSize, true );

					}

					/* set the fitness */
					for ( i = 0; i < offsprings.size(); ++i )
						offsprings[ i ].setFitness(
							( ueber9000->*ueber9000->evaluateMkIII )
								(
									dynamic_cast< ChromosomeT< double >& > ( offsprings[ i ][ 0 ] ),
									dynamic_cast< ChromosomeT< int >& > ( offsprings[ i ][ 1 ] )
								)
							);

					// select (mu,lambda) or (mu+lambda)
					parents.selectMuLambda(offsprings, numElitists);
					
					if( parents.best().fitnessValue() < minSolutionFitness )
						break;

					/* convergenzkriterium */
					if( t > 20 ) {
						double sum = 0.;
						for( auto i : fitness ) {
							sum += i;

						}
						sum /= fitness[ fitness.size() - 1 ];
						sum = abs( sum );
// 						std::cout << sum <<std::endl;
						if( sum == fitness.size() ) { Convergence = true; break; }
						fitness.erase( fitness.begin(), fitness.begin() + 1 );

					}
// 					if( parents.best().fitnessValue() == 1000 )
					for( int j = 0; j < parents.size(); j++ )
						std::cout << parents[j].fitnessValue() << "\t";
					std::cout << "" << std::endl;
					std::cout << parents.best().fitnessValue() << std::endl;
					
					std::cout << "" << std::endl;
					
					fitness.push_back( parents.best().fitnessValue() );

				}

				Individual& best = parents.best();
				
				steady_clock::time_point t_1 = steady_clock::now();

				/* prepare result */
				T res;
				
				res.valCont		= static_cast< ChromosomeT< double >& >( best[0] );
				res.valDis		= static_cast< ChromosomeT< double >& >( best[1] );
				res.fitness = best.fitnessValue();
				res.iterations = t;
				res.duration = duration_cast<microseconds>( t_1 - t_0 ).count();
				res.converged = Convergence;

				return res;

			}
			
			/** Enter description */
			template<typename T>
			T
			MuPlusLambdaES( Ueber9000<double> *ueber9000, double seed ) {
				steady_clock::time_point t_0 = steady_clock::now();

				const unsigned Mu           = 5;
				const unsigned Lambda       = 25;
				const unsigned Dimension    = ueber9000->Dimension;
				const unsigned Iterations   = 3000;
				const unsigned Interval     = 10;
				const unsigned NSigma       = 1;

				const double   GlobalStepInit = 5.;

				const double   MinInit        = -7.;
				const double   MaxInit        = 7.;
				const double   SigmaInit    = 6;

				/* activate elitist strategy */
				const bool     PlusStrategy = true;
				bool			Convergence = false;

				unsigned       i, t;

				// initialize random number generator
// 				Rng::seed(seed);

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
				T res;
// 				res.values.push_back( p[0] );
				res.fitness = p.fitnessValue();
				res.iterations = t;
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
				res.converged = Convergence;

				return res;

			}

			template<typename T>
			T
			CMA_ES_MkI( Ueber9000<double> *ueber9000, double seed, const bool PlusStrategy = false ) {
				// EA parameters
				CMA cma;
				steady_clock::time_point t_0 = steady_clock::now();
				
				const unsigned Iterations = 1000;
				const double MinInit = 1.;
				const double MaxInit = 1.;
				const double GlobalStepInit = 1.;
				const int Dimension = ueber9000->Dimension;
				unsigned Lambda = cma.suggestLambda(Dimension);
				unsigned Mu = cma.suggestMu(Lambda);
				
				// define populations for minimization task
				Population parents (Mu,
									ChromosomeT< double >( Dimension ),
									ChromosomeT< double >( Dimension ));
				Population offsprings (Lambda,
									ChromosomeT< double >( Dimension ),
									ChromosomeT< double >( Dimension ));
				
				offsprings		.setMinimize( );
				parents			.setMinimize( );
				
				// initialize parent populations center of gravity
				for( int i = 0; i < parents.size( ); ++i )
					static_cast< ChromosomeT< double >& >( parents[i][0] ).
						initialize(MinInit, MaxInit);

				for( int j = 1; j < parents.size( ); ++j )
					static_cast< ChromosomeT< double >& >( parents[j][0] ) =
						static_cast< ChromosomeT< double >& >( parents[0][0] );

				// strategy parameters
				vector< double > variance( Dimension );

				for(int i = 0; i < Dimension; i++) variance[i] = 1.;
				
				cma.init(Dimension, variance, GlobalStepInit, parents,
							CMA::superlinear, CMA::rankmu);

				//
				// iterate
				//
				unsigned t ;
				for( t = 0; t < Iterations; ++t ) {
					for(unsigned k = 0; k < offsprings.size( ); k++ ) {
						cma.create(offsprings[k]);
						offsprings[k].setFitness(
								(ueber9000->*ueber9000->evaluate)(
// 									static_cast<ChromosomeT<double>>(offsprings[k])
									static_cast<ChromosomeT<double> &>(offsprings[k][0])
								)
						);

					}
					// select (mu,lambda) or (mu+lambda)
					parents.selectMuLambda(offsprings, 0u);
					// update strategy parameters
					cma.updateStrategyParameters(parents);

				
				}
				steady_clock::time_point t_1 = steady_clock::now();

				T res;

				Individual& best = parents.best();
				
// 				res.values.push_back( p[0] );
				res.fitness = best.fitnessValue();
				res.iterations = t;
				res.valCont		= static_cast< ChromosomeT< double >& >( best[0] );
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
// 				res.converged = Convergence;
				return res;
			}

			template<typename T>
			T
			CMA_ES_MkII( Ueber9000<double> *ueber9000, double seed, const bool PlusStrategy = false ) {
				// EA parameters
				CMA cma;
				steady_clock::time_point t_0 = steady_clock::now();

				const unsigned Iterations = 1000;
				const double MinInit = 1.;
				const double MaxInit = 1.;
				const double GlobalStepInit = 1.;
				const int Dimension = ueber9000->Dimension;
				unsigned Lambda = cma.suggestLambda(Dimension);
				unsigned Mu = cma.suggestMu(Lambda);

				// define populations for minimization task
				Population parents (Mu,
									ChromosomeT< double >( 5 ),
									ChromosomeT< double >( 5 ),
									ChromosomeT< double >( 5 ));
				
				Population offsprings (Lambda,
									ChromosomeT< double >( 5 ),
									ChromosomeT< double >( 5 ),
									ChromosomeT< double >( 5 ));

				offsprings		.setMinimize( );
				parents			.setMinimize( );

std::cout << "0" << std::endl;
				// initialize parent populations center of gravity
				for( int i = 0; i < 5; i++ )
					static_cast< ChromosomeT< double >& >( parents[i][0] ).
						initialize(MinInit, MaxInit);
						
std::cout << "0.1" << std::endl;

				for( int i = 0; i < (Dimension-5); i++ ) {
					std::cout << i << " " << std::endl;

					static_cast< ChromosomeT< double >& >( parents[i][1] ).
						initialize(MinInit, MaxInit);
				}
						
std::cout << "0.2" << std::endl;

				for( int j = 1; j < 5; ++j )
					static_cast< ChromosomeT< double >& >( parents[j][0] ) =
						static_cast< ChromosomeT< double >& >( parents[0][0] );
std::cout << "0.3" << std::endl;

				for( int j = 1; j < Dimension-5; ++j )
					static_cast< ChromosomeT< double >& >( parents[j][1] ) =
						static_cast< ChromosomeT< double >& >( parents[0][1] );

				// strategy parameters
				std::vector< double > variance( Dimension );

				for(int i = 0; i < Dimension; i++) variance[i] = 1.;

std::cout << "1" << std::endl;
				cma.init(Dimension, variance, GlobalStepInit, parents,
							CMA::superlinear, CMA::rankmu);
std::cout << "1.1" << std::endl;

				//
				// iterate
				//
				unsigned t ;
				for( t = 0; t < Iterations; ++t ) {
					for(unsigned k = 0; k < offsprings.size( ); k++ ) {
						std::cout << "1.1.0" << std::endl;
						
						cma.create(offsprings[k]);
						std::cout << "1.1.1" << std::endl;

						offsprings[k].setFitness(
								(ueber9000->*ueber9000->evaluateMkII)(
									static_cast<ChromosomeT<double> &>(offsprings[k][0]),
									static_cast<ChromosomeT<double> &>(offsprings[k][1])
								)
						);

					}
					// select (mu,lambda) or (mu+lambda)
					parents.selectMuLambda(offsprings, 0u);
std::cout << "1.2" << std::endl;
					// update strategy parameters
					cma.updateStrategyParameters(parents);
std::cout << "1.3" << std::endl;


				}
				steady_clock::time_point t_1 = steady_clock::now();

				T res;

				Individual& best = parents.best();

// 				res.values.push_back( p[0] );
				res.fitness = best.fitnessValue();
				res.iterations = t;
				res.valCont		= static_cast< ChromosomeT< double >& >( best[0] );
				res.duration = duration_cast<microseconds>(t_1-t_0).count();
// 				res.converged = Convergence;
				return res;
			}

			template<typename T>
			T
			CMA_ES_MkII_A( Ueber9000<double> *ueber9000, double seed, const bool PlusStrategy = false )
			{
// 				// Adjust the floating-point format to scientific and increase output precision.
// 				std::cout.setf( std::ios_base::scientific );
// 				std::cout.precision( 10 );
// 
// 				// Instantiate both the problem and the optimizer.
// 				shark::Sphere sphere( 2 );
// 				sphere.setNumberOfVariables( 2 );
// 				shark::CMA cma;
// 
// 				// Initialize the optimizer for the objective function instance.
// 				cma.init( sphere );
// 
// 				// Iterate the optimizer until a solution of sufficient quality is found.
// 				do {
// 
// 					cma.step( sphere );
// 
// 					// Report information on the optimizer state and the current solution to the console.
// 					std::cout << sphere.evaluationCounter() << " "
// 						<< cma.solution().value << " "
// 						<< cma.solution().point << " "
// 						<< cma.sigma() << std::endl;
// 				} while ( cma.solution().value > 1E-20 );

/***************************************************************************/
   
// 				//
// 				// EA parameters
// 				//
// 				const unsigned Dimension      = 10;
// 				const unsigned Iterations     = 2000;
// 				const double   MinInit        = -3.;
// 				const double   MaxInit        = 7.;
// 				const double   GlobalStepInit = 1.;
// 
// 				ChromosomeCMA parent   (Dimension), offspring(Dimension);
// 				double fitnessParent, fitnessOffspring;
// 
// 				parent.init(Dimension, GlobalStepInit, MinInit, MaxInit);
// 				fitnessParent=fitness(parent);
// 
// 				// loop over generations
// 				for (unsigned t = 0; t < Iterations; t++) {
// 					offspring = parent;
// 					offspring.mutate();
// 					fitnessOffspring = fitness(offspring);
// 
// 					bool success = (fitnessOffspring < fitnessParent);
// 
// 					if(success) {
// 						offspring.updateCovariance();
// 						parent = offspring;
// 						fitnessParent = fitnessOffspring;
// 					}
// 					parent.updateGlobalStepsize(success);
// 
// 					cout << t << " " 	<< fitnessParent << endl;
// 				}
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

	#endif /* !_USE_SHARK_3_0_ */
#endif /* _PROCESS_H_ */ 
