#ifndef _PROCESS_MK_II_H_
	#define _PROCESS_MK_II_H_

#include <chrono>
#include <shark/Algorithms/DirectSearch/CMA.h>
#include <shark/Algorithms/AbstractOptimizer.h>
#include <shark/ObjectiveFunctions/Benchmarks/Benchmarks.h>
#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <nr3/nr3.h>
#include "solve.h"
#include "../libCalibration/calib.h"
#include "ObjectFunctions.h"

#include <nr3/nr3.h>

/** */
#define STUFF(Function,Vars)\
	Function model(Vars);													\
	model.setNumberOfVariables(Vars);										\
	shark::CMA cma;															\
	cma.init( model );														\
	do { cma.step( model ); } while(cma.solution().value > epsilon );	\

#define SOLVE(MODEL)\
	shark::CMA cma;															\
	cma.init( MODEL );														\
	do { cma.step( MODEL ); } while(cma.solution().value > epsilon );	\

#define SOLVE_AND_WRITE(MODEL)\
	shark::CMA cma;															\
	cma.init( MODEL );														\
	do {																	\
		cma.step( MODEL );													\
		f << model.evaluationCounter() << " "								\
						<< cma.solution().value << " "						\
						<< cma.solution().point << " "						\
						<< cma.sigma()										\
						<< std::endl;										\
	} while(cma.solution().value > epsilon									\
		&& model.evaluationCounter() < maxEvaluations);					\

namespace PRPSEvolution {
	namespace Solve {

		/*=============================================================*/
		/**
		 * 
		 */
		class Process_MkII
		{

		public:

			/*=============================================================*/
			/**
			 * Set up basic stuff...
			 */
			Process_MkII( )
			{
				// Adjust the floating-point format to scientific and increase output precision.
				std::cout.setf( std::ios_base::scientific );
				std::cout.precision( 10 );
				
				std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

				auto duration = now.time_since_epoch();
				/* init the seed */
				auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

				shark::Rng::seed( seed );
				
			}

			/*=============================================================*/
			/**
			 *
			 */
			Process_MkII(
				NRmatrix< Doub > Mat,
				NRvector< Doub > Vect,
				std::string Name
			)
			{
				A.push_back( Mat );
				b.push_back( Vect );
				names.push_back( Name );
				Process_MkII();
			}
			
			/*=============================================================*/
			/**
			 * 
			 */
			Process_MkII(
				NRmatrix< Doub > Mat,
				NRvector< Doub > Vect,
				std::string Name,
				const int mu,
				const int lambda
			): Mu( mu ), Lambda( lambda )
			{
				A.push_back( Mat );
				b.push_back( Vect );
				names.push_back( Name );
				Process_MkII();
			}
			
			/*=============================================================*/
			/**
			 * 
			 */
			Process_MkII(
				std::vector<NRmatrix< Doub >> Mats,
				std::vector<NRvector< Doub >> Vects,
				std::vector<std::string> Names
			) : A( Mats ), b( Vects ), names( Names )
			{
				Process_MkII();
			}
			
			/*=============================================================*/
			/**
			 *
			 */
			Process_MkII(
				std::vector<NRmatrix< Doub >> Mats,
				std::vector<NRvector< Doub >> Vects,
				std::vector<std::string> Names,
				const int mu,
				const int lambda
			) : A( Mats ), b( Vects ), names( Names ), Mu( mu ), Lambda( lambda )
			{
				Process_MkII();
			}
			
			/*=============================================================*/
			/**
			 * 
			 */
			Process_MkII(
				std::vector<NRmatrix< Doub >> Mats,
				std::vector<NRvector< Doub >> Vects,
				std::vector<std::string> Names,
				std::vector<std::vector<int>> IDs,
				double Epsilon
			) : A( Mats ), b( Vects ), names( Names ), idxs( IDs ), epsilon( Epsilon )
			{
				Process_MkII();
			}

			/*=============================================================*/
			/**
			 * 
			 */
			int WholeTomatoMkII( int dimension ) {
#ifdef _Write_Result
				std::ofstream f;
				std::ostringstream s;
				if( f_path == "")
					s << f_pathBase << "_" << f_count << ".dat";

				f_path = s.str();

				if( f_path != "" )
					f.open( f_path );

				if( !f.is_open() )
					return -1;

				f_path = "";
				
				for( auto name : names )
					f << name << " ";
				f << dimension << std::endl;

#endif
				auto dim = Solve::ProblemDimensions::WholeTomatoMkII;
				dim += dimension;
				PRPSEvolution::WholeTomatoMkII model( dim );
				model.setNumberOfVariables( dim );

				model.setParams( A, b, names );

#ifdef _Write_Result
				/* init the algorithm */
				shark::CMA cma;
				/* if we specify the Mu and Lamdba ourself */
				if( Mu != 0 && Lambda != 0) {
					RealVector p;
					model.proposeStartingPoint( p );
					cma.init(p.size(), Lambda, Mu, p, 1.0 );
					
				} else {
					cma.init( model );

					
				}
				/* print out selection of mu and lambda */
// 				std::cout << "Mu:" << cma.mu() << " Lambda: " << cma.lambda() << std::endl;

				/* solve.. */
				do {
					cma.step( model );
					f << model.evaluationCounter() << " "
									<< cma.solution().value << " "
									<< cma.solution().point << " "
									<< cma.sigma() << " "
									<< cma.solution().value * 1e10 << " "
									<< cma.solution().value / epsilon << " "
									<< (1e-20) * epsilon / cma.solution().value 
									<< std::endl;

// 					if( cma.solution().value == 10000 );
// 						break;
					
				} while(cma.solution().value > epsilon	
					&& model.evaluationCounter() < maxEvaluations);
#else
				SOLVE(model);
#endif

			}

			/*=============================================================*/
			/**
			 * 
			 */
			int WholeTomatoMkI_A( ) {

#ifdef _Write_Result
				std::ofstream f;
				std::ostringstream s;
				if( f_path == "")
					s << f_pathBase << "_" << f_count << ".dat";

				f_path = s.str();

				if( f_path != "" )
					f.open( f_path );

				if( !f.is_open() )
					return -1;

				f_path = "";
				f << names[0] << std::endl;
				
#endif
				auto dim = Solve::ProblemDimensions::WholeTomatoMkI;
				
				auto model = PRPSEvolution::WholeTomatoMkI_A( dim );
				
				model.setNumberOfVariables( dim );

				model.setParams( A[0], b[0] );

#ifdef _Write_Result
				SOLVE_AND_WRITE(model);
#else
				SOLVE(model);
#endif

			}
			
			/*=============================================================*/
			/**
			 *
			 */
			int WholeTomatoMkI_B( ) {

#ifdef _Write_Result
				std::ofstream f;
				std::ostringstream s;
				if( f_path == "")
					s << f_pathBase << "_" << f_count << ".dat";

				f_path = s.str();

				if( f_path != "" )
					f.open( f_path );

				if( !f.is_open() )
					return -1;

				f_path = "";
				f << names[0] << std::endl;

#endif
				auto dim = Solve::ProblemDimensions::WholeTomatoMkI_B;

				auto model = PRPSEvolution::WholeTomatoMkI_B( dim );

				model.setNumberOfVariables( dim );

				model.setParams( A[0], b[0] );

#ifdef _Write_Result
				SOLVE_AND_WRITE(model);
#else
				SOLVE(model);
#endif

			}
			
			/*=============================================================*/
			/**
			 *
			 */
			int Process_MkII_test( ) {

#ifdef _Write_Result
				std::ofstream f;
				std::ostringstream s;
				if( f_path == "")
					s << f_pathBase << "_" << f_count << ".dat";

				f_path = s.str();

				if( f_path != "" )
					f.open( f_path );

				if( !f.is_open() )
					return -1;

				f_path = "";
#endif
				// Adjust the floating-point format to scientific and increase output precision.
				std::cout.setf( std::ios_base::scientific );
				std::cout.precision( 10 );

				std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

				auto duration = now.time_since_epoch();
				auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

				Rng::seed(millis);

				// Instantiate both the problem and the optimizer.
				shark::Sphere model( ProblemDimensions::Sphere );
				model.setNumberOfVariables( ProblemDimensions::Sphere );
				shark::CMA cma;

				// Initialize the optimizer for the objective function instance.
				cma.init( model );

				// Iterate the optimizer until a solution of sufficient quality is found.
				do {
					cma.step( model );

					if( !printLastSolutionOnly ) {
					// Report information on the optimizer state and the current solution to the console.
						f << model.evaluationCounter() << " "
							<< cma.solution().value << " "
							<< cma.solution().point << " "
							<< cma.sigma() << std::endl;
					}
				} while(cma.solution().value > epsilon );

				if( printLastSolutionOnly ) {
					f << model.evaluationCounter() << " "
						<< cma.solution().value << " "
						<< cma.solution().point << " "
						<< cma.sigma() << std::endl;
				}

				f.close();
				
			}

			/**
			 * 
			 */
			int EvolutionaryCalibration(  ) {

#ifdef _Write_Result
				std::ofstream f;
				std::ostringstream s;
				if( f_path == "")
					s << f_pathBase << "_" << f_count << ".dat";

				f_path = s.str();

				if( f_path != "" )
					f.open( f_path );

				if( !f.is_open() )
					return -1;

				f_path = "";
#endif
				// Adjust the floating-point format to scientific and increase output precision.
				std::cout.setf( std::ios_base::scientific );
				std::cout.precision( 10 );

				std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

				auto duration = now.time_since_epoch();
				auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

				Rng::seed(millis);

				// Instantiate both the problem and the optimizer.
				PRPSEvolution::Models::EvolutionaryCalibration model;

				model.setParams( A[0], b[0] );
				
				shark::CMA cma;

				// Initialize the optimizer for the objective function instance.
				cma.init( model );

				// Iterate the optimizer until a solution of sufficient quality is found.
				do {
					cma.step( model );

					if( !printLastSolutionOnly ) {
					// Report information on the optimizer state and the current solution to the console.
						f << model.evaluationCounter() << " "
							<< cma.solution().value << " "
							<< cma.solution().point << " "
							<< cma.sigma() << std::endl;
					}
				} while(cma.solution().value > epsilon );

				if( printLastSolutionOnly ) {
					f << model.evaluationCounter() << " "
						<< cma.solution().value << " "
						<< cma.solution().point << " "
						<< cma.sigma() << std::endl;
				}

				f.close();

			}
			
			/**
			 * 
			 */
			void setEpsilon( double Value) { epsilon = Value; }

			/**
			 * 
			 */
			void setOutputFilePath( std::string file ) { f_path = file; }

			void setOutputFilePathBase( std::string file ) { f_pathBase = file; }
			
			/**
			 * 
			 */
			void setPrintLastOnly( void ) { printLastSolutionOnly = !printLastSolutionOnly; }

			/**
			 * increment the File counter 
			 */
			void incrementFileCounter( void ) { f_count++; }
			
			void resetFileCounter() { f_count = 0; }

			void toggleVariant() { VariantA = !VariantA; }

			/**
			 * @param[in] evaluations The new value for the evaluations
			 * @todo remove typo
			 */
			void setMaxEvauations( const int evaluations) { maxEvaluations = evaluations; }

		private:
			/** The Matrices we need to solve the Problem */
			std::vector<NRmatrix< Doub >> A;

			/** The b-vector needed to find a Solution */
			std::vector<NRvector< Doub >> b;

			std::vector<std::string> names;

			std::vector<std::vector<int>> idxs;

			/* init with base epsilon */
			double epsilon = 1e-20;

			std::string f_path;
			
			std::string f_pathBase;
			
			bool printLastSolutionOnly = false;

			int f_count = 0;

			int maxEvaluations = 30000;

			int VariantA = true;

			int Lambda = 0;
			
			int Mu = 0;

		};
	}
}

#endif