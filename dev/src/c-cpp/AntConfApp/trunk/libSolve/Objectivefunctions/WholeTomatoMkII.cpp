
// #include "WholeTomatoMkII.h"

// namespace PRPSEvolution {
// 	using namespace shark;
	
// double WholeTomatoMkII::eval(const SearchPointType &p) const
// {
// 	m_evaluationCounter++;
// 
// 	std::vector<double> res;
// 
// 	int I = 0;
// 
// 	double x[ 7 ];
// 
// 	x[ 0 ] = p[ 0 ];
// 	x[ 1 ] = p[ 1 ];
// 	x[ 2 ] = p[ 2 ];
// 	x[ 3 ] = p[ 3 ];
// 	x[ 4 ] = p[ 4 ];
// 	x[ 5 ] = p[ 5 ];
// 	x[ 6 ] = p[ 6 ];
// 
// 	for( int i = 3; i < m_numberOfVariables; i++)
// 		if( p[i] < 0 )
// 			return 10000;
// 
// 	bool doRecombination = true;
// 	if( As.size() == 1 )
// 		doRecombination = false;
// 
// 	for( int i = 0; i < As.size(); i++ ) {
// 		auto idx = idxs[i];
// 
// // 		for( auto c : idx )
// // 			std::cout << c;
// // 		std::cout << std::endl;
// 
// 		/* get the indeces for the solution */
// 		int j,k;
// 		j = k = 0;
// 
// 		if( doRecombination ) {
// // 			std::cout << "Do Recombine "
// // 			<< idx[ 0 ]
// // 			<< idx[ 1 ]
// // 			<< idx[ 2 ]
// // 			<< idx[ 3 ]
// // 			<< std::endl;
// 
// 			/* recompile chromosome x */
// 			x[ 3 ] = (double) p[ idx[ 0 ] ];
// 			x[ 4 ] = (double) p[ idx[ 1 ] ];
// 			x[ 5 ] = (double) p[ idx[ 2 ] ];
// 			x[ 6 ] = (double) p[ idx[ 3 ] ];
// 
// 		}
// 
// 		/* get a solution for all matrices in this group */
// 		res.push_back( mkII( As[i], x, bs[i] ) );
// 
// 	}
// 	/***************************************************************/
// 	/* different return methodes are implemented here */
// 	/* calc mean */
// 	double ret = Solve::meanFromVector( res );
// 
// 	/* sort */
// // 			std::sort( res.begin(), res.end() );
// 
// 	/* return highest value */
// // 			auto ret = res[0];
// 
// 	/* return lowest value */
// //  			auto ret = res[ res.size() - 1 ];
// 
// 	/* return median value */
// //  			auto ret = res[ (int)res.size()/2 ];
// 
// 	return ret;
// 
// }
// 
// inline double WholeTomatoMkII::mkII( const NRmatrix<Doub> &A, const double* x, const NRvector<Doub> &b ) const
// {
// 	double res;
// 	double prod_Ax[3] = {0.,0.,0.};
// 	double x_[10];
// 
// #ifdef _DROP_BAD_
// 
// #endif
// 	x_[0]=x[0];
// 	x_[1]=x[1];
// 	x_[2]=x[2];
// 	x_[3]=(x[3]*x[3])-(x[4]*x[4]);
// 	x_[4]=(x[3]*x[3])-(x[5]*x[5]);
// 	x_[5]=(x[3]*x[3])-(x[6]*x[6]);
// 	x_[6]=x[3];
// 	x_[7]=x[4];
// 	x_[8]=x[5];
// 	x_[9]=x[6];
// 
// 	/* multiply the matrix with the vector */
// 	for( int i = 0; i < A.nrows(); i++ )
// 		for( int j = 0; j < A.ncols(); j++ )
// 			prod_Ax[i] += A[i][j]*x_[j];
// 
// 	/* sum up */
// 	res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
// 	res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
// 	res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);
// 
// // 	return res;
// 
// }
// }