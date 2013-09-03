
#include "EvolutionaryCalibration.h"

namespace PRPSEvolution {
	namespace Models {
	using namespace shark;

		double EvolutionaryCalibration::eval( const SearchPointType &p ) const
		{
			m_evaluationCounter++;

			std::vector<double> res;

			double x[ m_numberOfVariables ];

			x[ 0 ] = p[ 0 ];
			x[ 1 ] = p[ 1 ];
			x[ 2 ] = p[ 2 ];
			return mkII( A, x, b );

		}

		inline double EvolutionaryCalibration::mkII( const NRmatrix<Doub> &A, const double* x, const NRvector<Doub> &b ) const
		{
			double res;
			double prod_Ax[3] = {0.,0.,0.};
			double x_[m_numberOfVariables];

			x_[0]=x[0];
			x_[1]=x[1];
			x_[2]=x[2];

			/* multiply the matrix with the vector */
			for( int i = 0; i < A.nrows(); i++ )
				for( int j = 0; j < A.ncols(); j++ )
					prod_Ax[i] += A[i][j]*x_[j];

			/* sum up */
			res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
			res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
			res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

			return res;

		}
		
	} /* !namespace */
} /* !namespace */
