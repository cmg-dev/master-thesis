/**
 * @file solve.h
 * @date 2013|Jun|25
 *
 *
 */
#ifndef __LIB_SOLVE_H
	#define __LIB_SOLVE_H

#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

#include "../include/coords.h"
#include "../include/PRPSEvolution.h"
#include "../include/PRPSEvolutionSolveExeptions.h"
#include "../include/PRPSEvolutionFIOExeptions.h"
#include "../include/PRPSError.h"
#include "../libPermutate/permutate.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"

// #include "nr3/nr3.h"
// #include "nr3/svd.h"

#include <EALib/ChromosomeCMA.h>

namespace PRPSEvolution {
	namespace Solve {

		using namespace PRPSEvolution::Permutate;
		using namespace std;
		
		/*******************************************************************/
		/* Enums ***********************************************************/
		/*******************************************************************/
		enum SelectBy {
			ConditionNumber

		};

		const int nConfigsForProcessing = 5;
			
		/*******************************************************************/
		/* Classes *********************************************************/
		/*******************************************************************/
		
		template < std::size_t N_ANTA, typename T >
		class PreProcessing
		{
		/*******************************************************************/
		/*******************************************************************/
		/*******************************************************************/
		public:
			/** determines how many Configurations will solved for the Wavenumber */

			
			PreProcessing( ) {
				/* get measurement of point*/
				/* norm and scale thetas */
				/* choose reference antenna */
				/* select possible matrices for the given Values */
				/* Fill the precalculated matrix with the thetas */
				/* check condition numbers */

			}

		private:
			std::array<T,N_ANTA> measuredPhase;
			std::array<T,N_ANTA> measuredAmp;
			std::array<T,N_ANTA> normThetas;

			std::array<AntennaPermutations< N_ANTA, Doub >,nConfigsForProcessing>
				slectedConfs;
				
			/***************************************************************/
			/***************************************************************/
			/***************************************************************/
			int rMeasurementsFromFile( );
			
			std::array<T,N_ANTA> normalizeThetas( );

			int selectReferenceAntennaForProcessing( );

			/**
			 * This will select the matrices for the Processing and will return the array filed with them
			 * @param[in] method The selection Method
			 * 
			 */
			std::array<AntennaPermutations< N_ANTA, Doub >,nConfigsForProcessing>
				selectMatsForProcessing( PRPSEvolution::Solve::SelectBy method );

		};

		/**
		 * Find solutions for the possible matrices
		 * 
		 */
		class Process
		{
		public:
			/**
			 * This ist the fitness function used in the EA algorithm
			 * 
			 */
			double fitnessSphere(ChromosomeT<double> &c) {
				double sum = Shark::sqr(c[0]);
				for(unsigned i=1; i<c.size(); i++) sum += Shark::sqr(c[i]);
				return sum;

			}

			double fitnessRosenbrock(ChromosomeT<double> &c) {
				double sum = 0.;

				for(unsigned i=0; i<c.size()-1; i++)
					sum += ( 100 * Shark::sqr( Shark::sqr(c[i-1]) - Shark::sqr(c[i]) ) + Shark::sqr(Shark::sqr(c[i])-1));
// 				for(unsigned i=1; i<c.size(); i++) sum += Shark::sqr(c[i]);
				return sum;

			}
			
			
			Process( int i ){
				//
				// EA parameters
				//
				const unsigned Dimension      = 10;
				const unsigned Iterations     = 2000;
				const double   MinInit        = -3.;
				const double   MaxInit        = 7.;
				const double   GlobalStepInit = 1.;

				ChromosomeCMA parent(Dimension),
								offspring(Dimension);
								
				double fitnessParent, fitnessOffspring;

				parent.init(Dimension, GlobalStepInit, MinInit, MaxInit);
				
// 				fitnessParent=fitness( parent );
				fitnessParent = fitnessRosenbrock( parent );

				// loop over generations
				for (unsigned t = 0; t < Iterations; t++) {
					offspring = parent;
					offspring.mutate();
					
					fitnessOffspring = fitnessRosenbrock( offspring );
// 					fitnessOffspring = fitness( offspring );

					bool success = ( fitnessOffspring < fitnessParent );

					if( success ) {
						offspring.updateCovariance();
						parent = offspring;
						fitnessParent = fitnessOffspring;
					}
					parent.updateGlobalStepsize( success );

					std::cout << t << " " 	<< fitnessParent << endl;

				}
				for(unsigned i=0; i< parent.size(); i++)
					std::cout << i << " " << parent[i];
				
			}
			/* latch in model */
			/* compute solution */
			/* dump/ display results */
			
		};

		class PostProcessing
		{
		public:
			PostProcessing(){

			}
			/* check plausibility of result */
			/* compute Wavenumbers */
			/* report success/ failure */
			
		};
	}
}
#endif