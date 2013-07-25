// #include <boost/signals2.hpp>
// #include <iostream>
#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

#include <shark/Algorithms/DirectSearch/CMA.h>
#include <shark/ObjectiveFunctions/Benchmarks/Benchmarks.h>

#include <nr3/nr3.h>

int main( int argc, char ** argv ) {

// 	NRmatrix <double> mat;
	
    // Adjust the floating-point format to scientific and increase output precision.
    std::cout.setf( std::ios_base::scientific );
    std::cout.precision( 10 );

    // Instantiate both the problem and the optimizer.
    shark::Sphere sphere( 2 );
    sphere.setNumberOfVariables( 2 );
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