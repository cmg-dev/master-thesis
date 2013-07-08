/**
 * @file solve.h
 * @date 2013|Jun|25
 *
 *
 */
#ifndef __LIB_SOLVE_H
	#define __LIB_SOLVE_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <iterator>
// #include <iostream>
// #include <algorithm>
// #include <array>
// #include <chrono>
// #include <iostream>
// #include <string>
// #include <random>

// #include "../include/coords.h"
// #include "../include/PRPSEvolution.h"
// #include "../include/PRPSEvolutionSolveExceptions.h"
// #include "../include/PRPSEvolutionFIOExceptions.h"
// #include "../include/PRPSEvolutionGeneralExceptions.h"

// #include "../include/PRPSError.h"
// #include "../libPermutate/permutate.h"
// #include "../libPRPSSystem/prpsevolutionsystem.h"
// #include "../libNormalizer/normalizer.h"
/*
#include "nr3/nr3.h"
#include "nr3/svd.h"*/


namespace PRPSEvolution {
	namespace Solve {
/*
		using namespace PRPSEvolution::Permutate;
		using namespace std;
		
		using std::chrono::duration_cast;
		using std::chrono::microseconds;
		using std::chrono::milliseconds;
		using std::chrono::steady_clock;*/

		/*******************************************************************/
		/* Enums ***********************************************************/
		/*******************************************************************/

		/**
		 * Represents the selection method for the Matrix A that will be used
		 * for the solution
		 * 
		 */
		enum SelectBy {
			ConditionNumber, Random, AllPossible, Best10ByCN, AllFrom4Ant

		};

		/**
		 * Represents the ES-strategy to find a solution
		 * 
		 */
		enum ESStrategy {
			OnePlusOne,		/**< @f[[1+1]-ES@f]*/
			MuPlusLambda,	/**< @f[[\mu+\lambda]-ES@f]*/
			MuCommaLambda	/**< @f[[\mu,\lambda]-ES@f]*/

		};

		struct ProblemDimensions {
			static const int WholeTomatoeApproach = 7;
			static const int WholeTomatoeApproachMkII = 7;
			static const int Sphere = 10;
			static const int Rosenbrock = 15;

			
		};

		struct FitnessFunctions {
			
			
		};
		
		const int nConfigsForProcessing = 1;
	}
}
#endif