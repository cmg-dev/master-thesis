#ifndef _PROCESS_MK_II_H_
	#define _PROCESS_MK_II_H_

#define _USE_SHARK_3_0_
// 
#ifdef _USE_SHARK_3_0_

#include <shark/Algorithms/DirectSearch/CMA.h>
#include <shark/ObjectiveFunctions/Benchmarks/Benchmarks.h>

namespace PRPSEvolution {
	namespace ProcessMkII {

		struct mkII {
			static int ProcessMkIItest( ) {

				// Adjust the floating-point format to scientific and increase output precision.
				std::cout.setf( std::ios_base::scientific );
				std::cout.precision( 10 );

				// Instantiate both the problem and the optimizer.
				shark::Sphere sphere( 10 );
				sphere.setNumberOfVariables( 10 );
				shark::CMA cma;

				// Initialize the optimizer for the objective function instance.
				cma.init( sphere );

				// Iterate the optimizer until a solution of sufficient quality is found.
				do {

					cma.step( sphere );

					// Report information on the optimizer state and the current solution to the console.
					std::cout << sphere.evaluationCounter() << " "
						<< cma.solution().value << " "
						<< cma.solution().point << " "
						<< cma.sigma() << std::endl;
				
				}while(cma.solution().value > 1E-20 );
			}
		};
	}
}
#endif
#endif