
#ifndef _FITNESS_PLANE_CALCULATOR_H_
	#define _FITNESS_PLANE_CALCULATOR_H_

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
// #include <shark/Algorithms/AbstractSingleObjectiveOptimizer.h>
// #include <shark/Core/SearchSpaces/VectorSpace.h>

#include "../libSolve/ObjectFunctions.h"

#include<iostream>

namespace PRPSEvolution {
	namespace Support {

		template<std::size_t N>
		struct FitnessPlaneLimits
		{
			std::array<double,N> upper;
			std::array<double,N> lower;
			double increment;
			
			int	idx1;
			int idx2;
			
			void dump() {
				for(int i = 0; i < N; i++)
					std::cout << i
						<< "\tupper: " << upper[i]
						<< "\tlower: " << lower[i]
						<< std::endl;
				std::cout << "increment is " << increment << std::endl;
				std::cout << "idx1 is " << idx1 << std::endl;
				std::cout << "idx2 is " << idx2 << std::endl;
			}
			
		};

		template<std::size_t N>
		class FitnessPlaneCalculator {

			typedef AbstractOptimizer<shark::VectorSpace< double >,double,SingleObjectiveResultSet<typename shark::VectorSpace< double >::PointType> > base_type;
			typedef typename base_type::ObjectiveFunctionType ObjectiveFunctionType;
			typedef typename base_type::SearchPointType SearchPointType;

		public:
			std::vector<FitnessPlaneLimits<N>> limits;
			
			/**
			 * 
			 */
			FitnessPlaneCalculator( int offset ) : off( offset )
			{
				rPlaneLimitsFromFile();

// 				std::cout << "dumping limits to std " << std::endl;
// 				for( auto limit : limits )
// 					limit.dump();
				
			}

			/**
			 * 
			 */
			void rPlaneLimitsFromFile()
			{
				std::ifstream	file ( "input/PlaneLimits.dat" );
				std::string		line;
				int				valuesRead = 0;
				int				linesRead = 0;


				int configs, vars;
				double step;
				
				getline( file, line );

// 				std::cout << "1" << std::endl;
				
				std::stringstream   linestream( line );
				std::string         value;

				getline( linestream, value, ' ' );
				configs		= std::stoi( value );

				getline( linestream, value, ' ' );
				vars		= std::stoi( value );

				getline( linestream, value, ' ' );
				step		= std::stod( value );

// 				std::cout << "v "<< vars << " c "  << configs << std::endl;

				FitnessPlaneLimits<N> limit;

				linesRead = -1;
				
				while( getline( file, line ) ) {
					std::stringstream ls( line );
					
					valuesRead = 0;

					/* 1. line */
					if( linesRead == -1 ) {
// 						std::cout << " 333 "  << ls.str()<< std::endl;
						getline( ls, value, ' ' );
// 						std::cout << " 333 "  << value<< std::endl;
						limit.idx1 = std::stoi(value);

						getline( ls, value, ' ' );
						limit.idx2 = std::stoi(value);
						linesRead = 0;
						continue;
// 						std::stringstream ls( line );
						
					}

					
					while( getline( ls, value, ' ' ) ) {
						if( value == "#" ) {
// 							std::cout << " break " << std::endl;
							break;
						}
						
						limit.lower[ linesRead ] = (valuesRead == 0) ? std::stod( value ) : limit.lower[ linesRead ];
						limit.upper[ linesRead ] = (valuesRead == 1) ? std::stod( value ) : limit.upper[ linesRead ];

						valuesRead++;
						
					}
					linesRead++;
// 					std::cout << "4 "<< limit.lower[ linesRead ] << " " <<limit.upper[ linesRead ] << std::endl;
					
					if( linesRead > vars ) {
// 						std::cout << "4 " << std::endl;
						limit.increment = step;
						FitnessPlaneLimits<N> locallimit;
						locallimit = limit;
						
						limits.push_back( locallimit );
						linesRead = -1;
						
					}
					
				}
				std::cout << "limits.size() " << limits.size() << std::endl;
				
				return;
				
			}
			
			/**
			 * 
			 */
			void setLimits( FitnessPlaneLimits<N> Limits )
			{
				limits = Limits;
				std::cout << "FitnessPlaneCalculator:: limits set" << std::endl;
				limits.dump();
			}

			std::string f_pathBase = "output/fitness/data/plane";
			int f_count = 0;
			void calculate( ObjectiveFunctionType const& model )
			{
				for( auto limit : limits ) {
					std::ofstream f;
					std::ostringstream s;

					s << f_pathBase << "_" << off << "_" << f_count++ << ".dat";

					std::string f_path = s.str();

					if( f_path != "" )
						f.open( f_path );

					if( !f.is_open() )
						return;

					SearchPointType x;
					x.resize(limits[0].upper.size());

					int i = 0;
				
					for( auto lowerlimit : limit.lower ) {
						x[i++] = lowerlimit;

					}

					int step = 0;
					i = 0;
					int j = 0;

	// 				std::cout << "1" << std::cout;
					while( x[ limit.idx1 ] < limit.upper[ limit.idx1 ] ) {
						x[ limit.idx2 ] = limit.lower[ limit.idx2 ];
	// 					std::cout << "2" <<s td::cout;
						while( x[ limit.idx2 ] < limit.upper[ limit.idx2 ] ) {
							x[ limit.idx2 ] += limit.increment;

							double res = model.eval( x );
							f << res << " ";

// 							if( res < 0.02 ) {
// 								std::cout << res << " = ";
							
								for( auto val : x ) {
									f <<  val << " ";
// 									std::cout << val << " ";

								}
// 								std::cout << std::endl;
// 							}
							f << std::endl;

						}
						x[ limit.idx1 ] += limit.increment;

					}

					f.close();
				}
			}
			
		private:
			int off;
			
		};
		
	}
}
	
#endif /* _FITNESS_PLANE_CALCULATOR_H_ */