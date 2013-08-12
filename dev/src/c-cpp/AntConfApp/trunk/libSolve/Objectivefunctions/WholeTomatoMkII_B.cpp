#include <shark/Algorithms/DirectSearch/CMA.h>
#include <shark/Algorithms/AbstractOptimizer.h>
#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>

#include "../solve.h"

#include "WholeTomatoMkII_B.h"

namespace PRPSEvolution {
	namespace Models {
		using namespace shark;

		double WholeTomatoMkII_B::eval( const SearchPointType &p) const
		{
			m_evaluationCounter++;

			std::vector<double> res;

			int I = 0;

			/* crea*/
			double x[ 7 ];

			/* copy the nessary variales */
			x[ 0 ] = p[ 0 ];
			x[ 1 ] = p[ 1 ];
			x[ 2 ] = p[ 2 ];

// 			for(int i = 3; i < m_numberOfVariables; i++ )
// 				p[i] = std::round( p[i] );
			

		// 	std::cout << m_numberOfVariables << std::endl;

			for( int i = 3; i < m_numberOfVariables; i++)
				if( p[i] < 0 )
					return 10000;

			bool doRecombination = ( As.size() != 1 ) ? true : false;
// 			bool doRecombination = true;
// 			if( As.size() == 1 )
// 				doRecombination = false;

			for( int i = 0; i < As.size(); i++ ) {
				auto idx = idxs[i];

				/* get the indeces for the solution */
				int j,k;
				j = k = 0;

				if( doRecombination ) {
					/* recompile chromosome x */
					x[ 3 ] = std::round( p[ idx[ 0 ] ] );
					x[ 4 ] = std::round( p[ idx[ 1 ] ] );
					x[ 5 ] = std::round( p[ idx[ 2 ] ] );
					x[ 6 ] = std::round( p[ idx[ 3 ] ] );
 
				}

				/* get a solution for all matrices in this group */
				res.push_back( this->mkII( As[i], x, bs[i] ) );

			}
			return Solve::meanFromVector( res );

		}

		inline double WholeTomatoMkII_B::mkII( const NRmatrix<Doub> &A, const double* x, const NRvector<Doub> &b ) const
		{
			double res;
			double prod_Ax[3] = {0.,0.,0.};
			double x_[10];

		#ifdef _DROP_BAD_

		#endif
			x_[0]=x[0];
			x_[1]=x[1];
			x_[2]=x[2];
			x_[3]=(x[3]*x[3])-(x[4]*x[4]);
			x_[4]=(x[3]*x[3])-(x[5]*x[5]);
			x_[5]=(x[3]*x[3])-(x[6]*x[6]);
			x_[6]=x[3];
			x_[7]=x[4];
			x_[8]=x[5];
			x_[9]=x[6];

		// 	for( int i = 0; i < 10; i++)
		// 		std::cout << "	" << x_[i] << std::endl;

			/* multiply the matrix with the vector */
			for( int i = 0; i < A.nrows(); i++ )
				for( int j = 0; j < A.ncols(); j++ )
					prod_Ax[i] += A[i][j]*x_[j];

		// 	for( int i = 0; i < 3; i++)
		// 		std::cout << prod_Ax[i] << "	" << b[i] << std::endl;

			/* sum up */
			res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
			res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
			res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

		// 	std::cout << "	" << res << std::endl;
			return res;

		}
	}
}