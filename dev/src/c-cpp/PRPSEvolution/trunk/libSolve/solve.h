/**
 * @file solve.h
 * @date 2013|Jun|25
 *
 *
 */
#ifndef __LIB_SOLVE_H
	#define __LIB_SOLVE_H

namespace PRPSEvolution {
	namespace Solve {
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
			MuCommaLambda,	/**< @f[[\mu,\lambda]-ES@f]*/
			MuCommaLambda_MkII,
			MuPlusLambda_MkII,
			CMA_ES_MkI,
			CMA_ES_MkII
			
		};

		/**
		 * Models are defined here
		 * 
		 */
		enum Models {
			WholeTomatoMkI,
			WholeTomatoMkII,
			TestSphere

		};
		
		/**
		 * This gathers the problemdimensions of the defined fitness functions
		 * 
		 */
		struct ProblemDimensions {
			static const int WholeTomato = 7;
			static const int WholeTomatoMkI = 10;
			static const int WholeTomatoMkI_A = 10;
			static const int WholeTomatoMkI_B = 7;

			/**
			 * The minimal dimension for this problem, depending on the
			 * amount of antennas used this number will increase
			 */
			static const int WholeTomatoMkII = 3;

			static const int Sphere = 10;

			static const int Rosenbrock = 15;

			static const int Calibration = 3;

			/* reduced problem dimension */
			static const int WholeTomatoReduced = 3;

		};

		inline double meanFromVector( std::vector<double> &res ) {
			if(res.size()<=0) return 0;
			double ret = 0.;
			for( auto val: res ) ret+=val;
			return (ret/=res.size());
			
		};
		
		const int nConfigsForProcessing = 1;
	}
}
#endif