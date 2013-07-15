/**
 * @file solveresult.h
 * @date 2013|Jul|5
 *
 *
 */
#ifndef __SOLVE_RESULT_H
	#define __SOLVE_RESULT_H

namespace PRPSEvolution {
	namespace Solve {
		/**
		 * Stores the final state of a solution
		 * 
		 */
		template <typename T_Store, typename T_Return>
		struct solveresult_t {
			/** Whrere the result is stored */
			T_Store values;
			/** The fitness value */
			T_Return fitness;
			/** The amount of iterations needed for this result */
			int iterations;
			/** The processing time for this solution */
			int duration;
			/** Indicates whether the build in convergence criterium was applied, or not */
			bool converged;
			
		};
	}
}

#endif