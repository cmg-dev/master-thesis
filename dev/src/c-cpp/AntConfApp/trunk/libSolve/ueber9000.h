
#ifndef _UEBER_9000_H_
	#define _UEBER_9000_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <array>

namespace PRPSEvolution {
	namespace Solve {
		/**
		 * Collect the fitness functions.
		 * Make sure they are static so we can function-pointer to them.
		 *
		 */
		template < typename T >
		struct Ueber9000
		{
			double (Ueber9000<double>::*evaluate)( const ChromosomeT< double >& );
			int Dimension;

			/** */
			std::vector<NRmatrix< T >> A;
			/** */
			std::vector<NRvector< T >> b;

			/**
			 * Default constructor
			 */
			Ueber9000( ) : evaluate( &Ueber9000<double>::fitnessSphere ),
								Dimension( ProblemDimensions::Sphere ) { };

			/**
			 *
			 */
			Ueber9000(const Ueber9000 &me) : A(me.A), b(me.b), Dimension( ProblemDimensions::WholeTomatoeApproach ) {
				if( A && b )
					evaluate = &WholeTomatoeApproach;

			}

			/**
			 * Construct Ueber9000 to use the WholeTomatoeApproach as fitness function
			 * @param[in] A_selected The matrix A for this Solution
			 * @param[in] c_k0_selected The vector b for this Solution
			 *
			 */
			Ueber9000( const NRmatrix< T > A_selected,
					   const NRvector< T > b_selected ) /*: A( A_selected ), b( b_selected )*/ {

				std::vector<NRmatrix< T >> a;
				std::vector<NRvector< T >> B;

				a.push_back( A_selected );
				B.push_back( b_selected );
				
				A = a;
				b = B;

				Dimension = ProblemDimensions::WholeTomatoeApproach;

				/* the WholeTomatoeApproach is the model of choice if A_selected and c_k0_selected are given */
				evaluate = &Ueber9000<double>::WholeTomatoeApproach;

			}

			/**
			 * Construct Ueber9000 to use the WholeTomatoeApproach as fitness function
			 * @param[in] As The matrices A to get a solution from
			 * @param[in] bs The vectors b
			 *
			 */
			Ueber9000( const std::vector<NRmatrix< T >> As,
					   const std::vector<NRvector< T >> bs ) {

				if( As.size() != bs.size())
					return;

				Dimension = ProblemDimensions::WholeTomatoeApproachMkII;
				/* latch in the configurations */
				A = As;
				b = bs;

				/* the WholeTomatoeApproach is the model of choice if A_selected and c_k0_selected are given */
				evaluate = &Ueber9000<double>::WholeTomatoeApproachMkII;

			}

			/**
			 * This method basically wraps around the real WholeTomatoeApproach-function.
			 * Maps the function so that it can be used with the evaluate-method
			 * @param[in] x The vector x
			 *
			 */
			double
			WholeTomatoeApproach( const ChromosomeT< double > &x )
			{
				double res;

// 				std::cout << A.size() << " " << b.size() << std::endl;

				if( A.size() <= 0 || b.size() <= 0 )
					return -1;
				
				/* call function */
				res = WholeTomatoeApproach( A[0], x, b[0] );

				return res;

			}

			/**
			 *
			 * @param[in] x The vector x containing the
			 *
			 */
			double
			WholeTomatoeApproachMkII( const ChromosomeT< double > &x )
			{
				double res;

				/* call function */
				res = WholeTomatoeApproach( A, x, b );

				return res;

			}

			/**
			 * This approach will solve calculate the 10x3 matrix described
			 * in the Master-Thesis of C.Gnip
			 * Basically solves the linear equation @f[r=\mathbf{Ax}-\mathbf{b}@f]
			 * @param[in] A The 10x3 Matrix that ist used in this solution
			 * @param[in] x The vector containing the variables
			 * @param[in] b Representing the vector b
			 * @return The residuum of the equation system representing the "Fitness" of the given Solution in @see x
			 *
			 */
			inline double WholeTomatoeApproach( const NRmatrix<T> &A, const ChromosomeT< double > &x, const NRvector<T> &b )
			{
				double res;
				double prod_Ax[3] = {0.,0.,0.};
				double x_[10];

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

				/* multiply the matrix with the vector */
				for( int i = 0; i < A.nrows(); i++ )
					for( int j = 0; j < A.ncols(); j++ )
						prod_Ax[i] += A[i][j]*x_[j];

				/* sum up */
				res = (prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
				res += (prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
				res += (prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

				return res;

			}

			/***************************************************************/
			/***************************************************************/
			/***************************************************************/
			/**
			 * Approach 2 based on the thoughts of S. Winter.
			 * Here we want to optimize the wavenumbers
			 *
			 */
			double WavenumberVariation( const ChromosomeT< double > &n )
			{
				throw "Not implemented exeption";

			}

			/**
			 * Approach 3 based on the thoughts of by S. Winter
			 *
			 */
			double PositionVariation( const ChromosomeT< double > &pos )
			{
				throw "Not implemented exeption";

			}

			/**
			 * This ist the fitness function used in the EA algorithm
			 *
			 */
			double fitnessSphere( const ChromosomeT<double> &c )
			{
				double sum = Shark::sqr(c[0]);
				for(unsigned i=1; i<c.size(); i++) sum += Shark::sqr(c[i]);
				return sum;

			}

			/**
			 * The Rosenbrock implementation
			 *
			 */
			double fitnessRosenbrock( const ChromosomeT<double> &c )
			{
				double sum = 0.;

				for(unsigned i=0; i<c.size(); i++) {
					sum += ( 100 * Shark::sqr( c[i+1] - Shark::sqr(c[i]) )
								+ Shark::sqr(c[i]-1));

				}

				return sum;

			}

			/**
			 * The infamous Ackley-function
			 *
			 */
			double fitnessAckley( const std::vector< double >& x )
			{
				const double A = 20.;
				const double B = 0.2;
				const double C = M_2PI;

				unsigned i, n;
				double   a, b;

				for (a = b = 0., i = 0, n = x.size(); i < n; ++i) {
					a += x[ i ] * x[ i ];
					b += cos(C * x[ i ]);
				}

				return -A * exp(-B * sqrt(a / n)) - exp(b / n) + A + M_E;
			}

		};
	}
}

#endif /* !_UEBER_9000_H_ */