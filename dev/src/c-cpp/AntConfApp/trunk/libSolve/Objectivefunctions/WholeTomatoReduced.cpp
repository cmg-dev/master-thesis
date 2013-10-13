#include <shark/Algorithms/DirectSearch/CMA.h>
#include <shark/Algorithms/AbstractOptimizer.h>
#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <math.h>

#include "../solve.h"

#include "WholeTomatoReduced.h"

#define _WT_CONSTRAIN_HARD_

namespace PRPSEvolution {
	namespace Models {
		using namespace shark;

		double WholeTomatoReduced::eval( const SearchPointType &p ) const
		{
			m_evaluationCounter++;

			std::vector<double> res;
			std::array<double,8> wavenumbers;
		
			int I = 0;

			double x[ 7 ];

			x[ 0 ] = p[ 0 ];
			x[ 1 ] = p[ 1 ];
			x[ 2 ] = p[ 2 ];

			wavenumbers = calcWavenumbers( x );
			
			bool doRecombination = true;
// 			if( As.size() == 1 )
// 				doRecombination = false;

			double pan = panalty(x);
			
			for( int i = 0; i < As.size(); i++ ) {
				auto idx = idxs[i];

// 				for( auto c : idx )
// 					std::cout << c;
// 				std::cout << std::endl;

				/* get the indeces for the solution */
				int j,k;
				j = k = 0;

				if( doRecombination ) {
					/* recompile chromosome x */
					x[ 3 ] = wavenumbers[  idx[ 0 ]  ];
					x[ 4 ] = wavenumbers[  idx[ 1 ]  ];
					x[ 5 ] = wavenumbers[  idx[ 2 ] ];
					x[ 6 ] = wavenumbers[  idx[ 3 ]  ];

				}

				double pan = panalty(x);

// 				std::cout << "panalty: " << pan ;
				
// 				if( !constrains(x) )
// 					return 10000;

				/* get a solution for all matrices in this group */
				res.push_back( this->reduced( As[i], x, bs[i] ) );

			}
			/***************************************************************/
			/* different return methodes are implemented here */
			/* calc mean */
			double ret = Solve::meanFromVector( res );

			/* Multiplizieren ???! */

			/* sort */
		// 			std::sort( res.begin(), res.end() );

			/* return highest value */
		// 			auto ret = res[0];

			/* return lowest value */
		//  			auto ret = res[ res.size() - 1 ];

			/* return median value */
		//  			auto ret = res[ (int)res.size()/2 ];

			return ret + pan ;

		}

		inline double WholeTomatoReduced::reduced( const NRmatrix<Doub> &A, const double* x, const NRvector<Doub> &b ) const
		{
			double res;
			double prod_Ax[3] = {0.,0.,0.};
			double x_[10];

			x_[0] = x[0];
			x_[1] = x[1];
			x_[2] = x[2];
			x_[3] = (x[3]*x[3])-(x[4]*x[4]);
			x_[4] = (x[3]*x[3])-(x[5]*x[5]);
			x_[5] = (x[3]*x[3])-(x[6]*x[6]);
			x_[6] = x[3];
			x_[7] = x[4];
			x_[8] = x[5];
			x_[9] = x[6];

			/* multiply the matrix with the vector */
			for( int i = 0; i < A.nrows(); i++ ) {
				for( int j = 0; j < A.ncols(); j++ ) {
					prod_Ax[i] += A[i][j]*x_[j];

				}
			}

			res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
			res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
			res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

			return res;

		}

		inline bool WholeTomatoReduced::constrains(const double* x) const
		{ 
#ifdef _WT_CONSTRAIN_HARD_
			for( int i = 0; i < 3; i++)
				if( x[i] > 5. || x[i] < -5. )
					return false;

// 			for( int i = 0; i < 3; i++)
// 				if( x[i] < 1. || x[i] > -1. )
// 					return false;

// 			auto v = std::sqrt( x[0]*x[0] + x[1]*x[1] + x[2]*x[2] );
// 			if( (double) v > 6. )
// 				return false;
#endif
			return true;

		}

		inline double WholeTomatoReduced::panalty(const double* x) const
		{
			double panalty = 0.0;

			for( int i = 0; i < 3; i++) {
				if( x[i] >= 3. || x[i] <= -3. ) {
// 					std::cout << "applying panalty";
					for( int j = 0; j < 3; j++) {
						panalty += std::pow( x[j], 2 );
					}
// 					panalty = std::sqrt( panalty );
					break;
				}
			}

// 			for( int i = 0; i < 3; i++)
// 				if( x[i] < 1. || x[i] > -1. )
// 					return false;

// 			auto v = std::sqrt( x[0]*x[0] + x[1]*x[1] + x[2]*x[2] );
// 			if( (double) v > 6. )
// 				return false;

			return panalty;

		}
		
		bool printYN = false;
		inline std::array<double, 8> WholeTomatoReduced::calcWavenumbers( const double *x ) const
		{
			std::array<double, 8> ret;

// 			std::cout << "1";
			
			if( continuesWavenumbers ) {
				int i = 0;

				/* for all antenna coords calc the wavenumbers */
				for( auto a : antennaCoords ) {
					double d = std::sqrt( pow( x[0]-a[0] , 2 )
							+ pow( x[1]-a[1] , 2 )
							+ pow( x[2]-a[2] , 2 ) );

// 					for( auto &wn : ret ) {
					ret[i++] = 2 * ( d/lambda );

// 					}
				}
				
			} else {
// 				std::cout << x[0] << " " << x[1] << " " << x[2] << std::endl;
				int i = 0;
				
				/* for all antenna coords calc the wavenumbers */
				for( auto a : antennaCoords ) {
					double d = std::sqrt( pow( x[0]-a[0] , 2 )
							+ pow( x[1]-a[1] , 2 )
							+ pow( x[2]-a[2] , 2 ) );

// 					for( auto &wn : ret ) {
					ret[i++] = std::floor( 2 * ( d/lambda ) );

// 					}
				}
	
			}
			
			if( printYN ) {
				for( auto wn : ret ) {
					std::cout << wn << " ";

				}
				std::cout<<std::endl;
			}
			
			return ret;
			
		}


		std::array<double, 8> WholeTomatoReduced::calcWavenumbers2( double x, double y, double z)
		{
			
			double xyz [] {x,y,z};

// 			printYN = true;
// 			auto ret = calcWavenumbers(xyz);
// 			printYN = false;
			
			return calcWavenumbers(xyz);;
		}

		
	}
}