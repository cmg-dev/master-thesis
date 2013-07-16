
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

		std::mutex wMutex;
		int _i_ = 0;
		
		/**
		 * Collect the fitness functions.
		 * Make sure they are static so we can function-pointer to them.
		 *
		 */
		template < typename T >
		struct Ueber9000
		{
			/** @todo document */
			double (Ueber9000<double>::*evaluate)( const ChromosomeT< double >& );
			/** @todo document */
			double (Ueber9000<double>::*evaluateMKIII)( const ChromosomeT< double >&, const ChromosomeT< int >& );

			
			/** The Dimension of the Problem */
			int Dimension;

			/** The Matrices we need to solve the Problem */
			std::vector<NRmatrix< T >> A;
			
			/** The b-vector needed to find a Solution */
			std::vector<NRvector< T >> b;

			/** The names for the Solution (contains the contributing antennas )*/
			std::vector<std::string> names;

			std::vector<std::vector<int>> idxs;
			
			/**
			 * Default constructor
			 */
			Ueber9000( ) : evaluate( &Ueber9000<double>::fitnessSphere ),
								Dimension( ProblemDimensions::Sphere ) { };

			Ueber9000( int i ) : evaluate( &Ueber9000<double>::fitnessSphere ),
								Dimension( ProblemDimensions::Sphere ) { };

			/**
			 *
			 */
			Ueber9000(const Ueber9000 &me) : A(me.A), b(me.b), Dimension( ProblemDimensions::WholeTomato ) {
				if( A && b )
					evaluate = &WholeTomato;

			}

			/**
			 * Construct Ueber9000 to use the WholeTomato as fitness function
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

				Dimension = ProblemDimensions::WholeTomato;

				/* the WholeTomato is the model of choice if A_selected and c_k0_selected are given */
				evaluate = &Ueber9000<double>::WholeTomato;

			}

			/**
			 * Construct Ueber9000 to use the WholeTomato as fitness function
			 * @param[in] As The matrices A to get a solution from
			 * @param[in] bs The vectors b
			 * @param[in] namess The Names of the matrices in As
			 * @param[in] numOAnts The number of antennas used in the matrices in As
			 * @param[in] select Selects the WholeTomato-Version
			 *
			 */
			Ueber9000( const std::vector<NRmatrix< T >> As,
						const std::vector<NRvector< T >> bs,
						const std::vector<std::string> namess,
						const int numOAnts,
						const int select
 					) {

				if( As.size() != bs.size())
					return;
				
				std::vector<std::vector<int>> idx = parseIdxFromNames( namess );
				
				/* latch in the configurations */
				A = As;
				b = bs;
				names = namess;
				idxs = idx;


				/* determine the amount of participating antennas */
				Dimension = ProblemDimensions::WholeTomatoMkII;
				Dimension += numOAnts;
				
// 				std::cout << "Mark II: " << Dimension << std::endl;

				if( select == 0 ) {
				/* the WholeTomato is the model of choice if A_selected and c_k0_selected are given */
					evaluate = &Ueber9000<double>::WholeTomatoMkII;
				
				} else if( select == 1 ) {
// 					std::cout << "Evaluating MKIII" << std::endl;
					evaluateMKIII = &Ueber9000<double>::WholeTomatoMkII;
					
				}

			}

			/**
			 * This function will parse the indeces used for a solution
			 * @param[in] namess Contains the "Name" of each matrix we want to use in this solution
			 * @return A two dimensional vector with the indeces of each antenna for each matrix
			 * 
			 */
			std::vector<std::vector<int>>
			parseIdxFromNames
			( const std::vector<std::string> &namess ) {
				std::vector<std::vector<int>> res;
				
				for( auto names: namess ) {
					std::vector<int> idxs;
					for( int i = 0; i < names.size(); i++ ) {
						idxs.push_back( std::stoi( names.substr(i,1)) );
						
					}
					res.push_back( idxs );
				}

#ifdef OUTPUT
				for( auto idx: res ) {
					for( auto i: idx ) {
						std::cout << i << " ";
					}
					std::cout << std::endl;
				}
#endif
				return res;
			}
			
			/**
			 * This method basically wraps around the real WholeTomato-function.
			 * Maps the function so that it can be used with the evaluate-method
			 * @param[in] x The vector x
			 *
			 */
			double
			WholeTomato( const ChromosomeT< double > &x )
			{
				double res;

// 				std::cout << A.size() << " " << b.size() << std::endl;

				if( A.size() <= 0 || b.size() <= 0 )
					return -1;
				
				/* call function, always solve the first matrix */
				res = WholeTomato( A[0], x, b[0] );

				return res;

			}

			/**
			 * @todo document
			 * @param[in] x The vector x containing the
			 *
			 */
			double
			WholeTomatoMkII( const ChromosomeT< double > &x )
			{
				/* the result */
				std::vector<double> res;
				
				ChromosomeCMA x_( 7 );

				x_[0] = x[0];
				x_[1] = x[1];
				x_[2] = x[2];

				for( int i = 0; i < A.size(); i++ ) {
					auto idx = idxs[i];
					/* get the indeces for the solution */
					int j,k;
					j = k = 0;
					/* recompile chromosome x */
					x_[ 3 ] = x[3+idx[0]];
					x_[ 4 ] = x[3+idx[1]];
					x_[ 5 ] = x[3+idx[2]];
					x_[ 6 ] = x[3+idx[3]];

// 					for( auto & c : x_ ) {
// 						std::cout << c << " ";
// 
// 					}
// 					std::cout << "" << std::endl;

					res.push_back( WholeTomatoMkII( A[i], x_, b[i] ) );
				}

// 				wMutex.lock();
// 				std::ofstream f;
// 				f.open( "output/whole_fitness.dat", ios::app );
// 				for( auto r: res )
// 					f << r << " ";
// 				f<< std::endl;
// 
// 				f.close();
// 				wMutex.unlock();

				std::sort( res.begin(), res.end() );
// 				return res[res.size()-1];
				return meanFromVector( res );
//  				return res[0];
//  				return res[7];

			}

			/**
			 * @todo document
			 * @param[in] x The vector x containing the
			 *
			 */
			double
			WholeTomatoMkII( const ChromosomeT< double > &x, const ChromosomeT< int > &n )
			{
				/* the result */
				std::vector<double> res;

				int I = 0;

				ChromosomeT< double > x_( 7 );

				x_[0] = x[0];
				x_[1] = x[1];
				x_[2] = x[2];

				for( auto v : n )
					if( v < 0 )
						return 10000;

				if( x_[1] < 0 )
					return 10000;
				
				for( int i = 0; i < A.size(); i++ ) {
					auto idx = idxs[i];
					/* get the indeces for the solution */
					int j,k;
					j = k = 0;
					/* recompile chromosome x */
					x_[ 3 ] = (double)n[ idx[ 0 ] ];
					x_[ 4 ] = (double)n[ idx[ 1 ] ];
					x_[ 5 ] = (double)n[ idx[ 2 ] ];
					x_[ 6 ] = (double)n[ idx[ 3 ] ];

// 					for( auto & c : idx ) {
// 						std::cout << c << " ";
// 
// 					}
// 					std::cout << "" << std::endl;
// 					std::cout << "" << std::endl;

					res.push_back( WholeTomatoMkII( A[i], x_, b[i] ) );
// 					std::cout << i << " " << res[i] << std::endl;

				}

				double ret = meanFromVector( res );
// 				std::cout << ret << std::endl;
				std::sort( res.begin(), res.end() );


				wMutex.lock();
				std::ofstream f;
				f.open( "output/whole_fitness.dat", ios::app );
				f << _i_++ << '\t';
				for( auto r: res )
					f << r << " ";
				f << '\t' << ret << '\t' << res[res.size()-1] << '\t' << res[0];
				
				f<< std::endl;

				f.close();
				wMutex.unlock();
				
				return res[0];
// 				return ret;
//  				return res[0];
//  				return res[7];

			}
			
			/**
			 * This approach will solve the scene defined by the 10x3 matrix
			 * The approach is described in the Master-Thesis of C.Gnip
			 * Basically solves the linear equation @f[r=\mathbf{Ax}-\mathbf{b}@f]
			 * @param[in] A The 10x3 Matrix that ist used in this solution
			 * @param[in] x The vector containing the variables
			 * @param[in] b Representing the vector b
			 * @return The residuum of the equation system representing the "Fitness" of the given Solution in @see x
			 *
			 */
			inline double WholeTomato( const NRmatrix<T> &A, const ChromosomeT< double > &x, const NRvector<T> &b )
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
				res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
				res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
				res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

				return res;

			}

			/**
			 * @todo documentation
			 * @param[in] A The 10x3 Matrix that ist used in this solution
			 * @param[in] x The vector containing the variables
			 * @param[in] b Representing the vector b
			 * @return The residuum of the equation system representing the "Fitness" of the given Solution in @see x
			 *
			 */
			inline double WholeTomatoMkI( const NRmatrix<T> &A, const ChromosomeT< double > &x, const NRvector<T> &b )
			{
				double res;
				double prod_Ax[3] = {0.,0.,0.};
				
				/* multiply the matrix with the vector */
				for( int i = 0; i < A.nrows(); i++ )
					for( int j = 0; j < A.ncols(); j++ )
						prod_Ax[i] += A[i][j]*x[j];

				/* sum up */
				res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
				res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
				res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

				return res;

			}
			
			/**
			 * @todo documentation
			 * This approach will solve calculate the 10x3 matrix described
			 * in the Master-Thesis of C.Gnip
			 * Basically solves the linear equation @f[r=\mathbf{Ax}-\mathbf{b}@f]
			 * @param[in] A The 10x3 Matrix that ist used in this solution
			 * @param[in] x The vector containing the variables
			 * @param[in] b Representing the vector b
			 * @return The residuum of the equation system representing the "Fitness" of the given Solution in @see x
			 *
			 */
			inline double WholeTomatoMkII( const NRmatrix<T> &A, const ChromosomeT< double > &x, const NRvector<T> &b )
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
				res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
				res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
				res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

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