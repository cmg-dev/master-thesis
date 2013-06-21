


#ifndef __LIB_PERMUTATE_H
	#define __LIB_PERMUTATE_H

#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

#include "../include/coords.h"
#include "../include/PRPSEvolution.h"
#include "../include/PRPSError.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"

#include "nr3/nr3.h"
#include "nr3/svd.h"

using namespace PRPSEvolution;
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/

/**
 * The maximum amount of Permutations for one reference antenna
 */
const int MAX_PERMUTATION_AMOUNT = 35;


/**************************************************************************/
/* Definitions ************************************************************/
/**************************************************************************/

/**
 *
 */
template < std::size_t N_MAT, typename T >
struct AntennaPermutations {
	/* use svd-algorithms from numerical recipes vol 3 */
// 	SVD svd;

	/* the matrices of the popssible combinations */
	std::array< NRmatrix< T >, N_MAT > mat;

	/* the condition number of a matrix */
	std::array< Doub, ANTENNA_AMOUNT > conditionNumbers;

	/**
	 *
	 */
	static void dumb_matrix( NRmatrix< T > mat, int n, int m ) {
		std::cout << "** Begin matrix dump: *****" << std::endl;
		for( int i = 0; i < n; i++ ){
			for( int j = 0; j < m; j++ ){
				std::cout << mat[i][j] << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
		std::cout << "** End matrix dump: *****" << std::endl;
	}

	/**
	 * 
	 */
	static void dumb_matrix_2_file( std::ofstream &f, NRmatrix< T > mat, int n, int m ) {
		if( !f ) return;
		for( int i = 0; i < n; i++ ){
			for( int j = 0; j < m; j++ ){
				f << mat[i][j];
				if( j+1 != m )	f << ',';
				
			}
			f << '\n';
			
		}
		f << '\n';
		
	}

	/**
	 *
	 */
	AntennaPermutations( void ) {
		/* init all of the matrices */
		for(auto& m: mat) {
			m.assign( 3, 10, (T)0.0);

		}
	}
};

/**
 * This will collect some stuff for calculating the permutation of the antennas
 * 
 */
template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
struct permuteAntennas {
	int ref;
	/* We will store the x-y-z-coords we received from the antenna in this array */
 	Positioning::CoordContainer< N_ANTA, T > AntennaCoordinates;
	/* this array will store all possible matrices of the system */
	std::array< AntennaPermutations< N_ANTPERM, Doub >, N_ANTA> configurations;
	
	/* store the reference antenna while constructing */
  	permuteAntennas( const int _refAnt = 0 );

	int rCoordFile();

	/**/
	int computePermutations( const PRPSEvolution::Constants &co );

	/**/
	const NRmatrix<T> computeMatrix( const int ref, const int a1, const int a2, const int a3, const PRPSEvolution::Constants &co );

	/**/
	void dumpConfigurationsToFile( );

	void dumb_matrices_2_file( );
	
};

/**************************************************************************/
/* Declarations ***********************************************************/
/**************************************************************************/

/**************************************************************************/
template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
permuteAntennas< N_ANTA, N_ANTPERM, T >::permuteAntennas( const int _refAnt)
{
	ref = _refAnt;

}


/**************************************************************************/
/**
 * Load the csv-file containing the coordinates and store it into the container
 *
 */
template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
int permuteAntennas< N_ANTA, N_ANTPERM, T >::rCoordFile()
{
	std::ifstream	file ( "data/MeasuredDistances.dat" );
	std::string		line;
	int				valuesRead;
	int				linesRead;

	valuesRead = linesRead = 0;

	/* simply fill with 0 */
	for( int i = 0; i < N_ANTA; i++ ) {
		AntennaCoordinates.x_[ i ] = 0.0;
		AntennaCoordinates.y_[ i ] = 0.0;
		AntennaCoordinates.z_[ i ] = 0.0;

	}

	/* read out the file **************************************************/
	while( getline( file,line ) ) {
		std::stringstream   linestream( line );
		std::string         value;

		valuesRead = 0;
		while( getline( linestream, value, ',' ) ) {
 				AntennaCoordinates.x_[ valuesRead ] = ( linesRead == 0 ) ? std::stod( value ):( AntennaCoordinates.x_[ valuesRead ] ) ;
 				AntennaCoordinates.y_[ valuesRead ] = ( linesRead == 1 ) ? std::stod( value ):( AntennaCoordinates.y_[ valuesRead ] ) ;
 				AntennaCoordinates.z_[ valuesRead ] = ( linesRead == 2 ) ? std::stod( value ):( AntennaCoordinates.z_[ valuesRead ] ) ;

				valuesRead++;
		}

		/* a line is read */
		if( valuesRead != (int) N_ANTA )
			return PRPSError::FileIO::inputmalformed;

		linesRead++;

	}

	/* check the input */
	if( linesRead != PRPSEvolution::EXPECTED_LINES_COORD_FILE )
		return PRPSError::FileIO::inputmalformed;

	std::cout << "** I've read the following values: " << std::endl;
 	std::cout << "x" << '\t'<< "y" << '\t' << "z" << std::endl;
	for( int i = 0; i < N_ANTA; i++ ) {
		std::cout << AntennaCoordinates.x_[ i ] << '\t'
					<< AntennaCoordinates.y_[ i ] << '\t'
					<< AntennaCoordinates.z_[ i ] << std::endl;

	}

	return PRPSError::okay;

}

/**************************************************************************/
/**
 *
 *
 */
template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
int permuteAntennas< N_ANTA, N_ANTPERM, T >::computePermutations( const PRPSEvolution::Constants &co )
{
	int Ant = 0;
	int x,y;

	auto i_goal = N_ANTA-1;
	auto j_goal = N_ANTA;
	auto k_goal = N_ANTA;

	auto i_start = 0;
	auto j_start = 0;
	auto k_start = 0;
	auto m_i = 0;
	
 	x = y = 0;

	auto& c = configurations;

	for( int r = 0; r < N_ANTA; r++ ) {
		i_start = 0;
		m_i=0;
		/* get the matrices for one configuration */
		auto& m = c[r].mat;
		/* run through all configurations **********************************/
		for( int i = i_start; i < i_goal; i++  ) {
			if( i == r ) {
				i_start++;
				continue;
			}
				

// 			std::cout << m.size() << " i "<< i<< std::endl;
			
			j_start = i_start + 1;

			/* for every Matrix in this configuration */
			for( int j = j_start; j < j_goal; j++ ) {
				/* skip the reference antenna */
				if( j == r ) { continue; }
				k_start = j + 1;

				for( int k = k_start; k < k_goal; k++ ) {
					if( k == r ) { continue; }
					
// 					std::cout << m_i << " " << std::endl;
					/* assign the new matrix */
					m[m_i++] = computeMatrix( r, i, j, k, co );
					
//  					if( r == 7 ) {
// 						std::cout << x << " " << std::endl;
// 						AntennaPermutations< N_ANTPERM, Doub >::dumb_matrix( m[k], 3, 10 );
// 					}
// 					if( r == 0 ){
// 						std::cout << x << " " << std::endl;
// 						AntennaPermutations< N_ANTPERM, Doub >::dumb_matrix( m[k], 3, 10 );
// 					}
					
					x++;
				}
				j_start++;
			}
			i_start++;
		}
	}
	std::cout << "processed " << x << '\n';

	int i, j;
	i = j = 0;
	
// 	/* run through all configurations *************************************/
// 	for( auto& c : configurations )
// 	{
// 		i=0;
// 		/* for every Matrix in this configuration */
// 		for( auto& m : c.mat ) {
// 			std::cout << "** Matrix " << i++ << std::endl;
// 			c.dumb_matrix( m, 3, 10 );
// 
// 		}
// 		std::cout << "******" << j << std::endl;
// 		j++;
// 
// 	}
}

/**
 * This method will compute all the possible permutations for the given reference antenna ref
 * @param[in] ref The reference antenna
 * @param[in] a1 First antenna
 * @param[in] a2 Second antenna
 * @param[in] a3 Third antenna
 *
 */
template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
const NRmatrix<T> permuteAntennas< N_ANTA, N_ANTPERM, T >::computeMatrix( const int ref, const int a1, const int a2, const int a3, const PRPSEvolution::Constants &co )
{
	NRmatrix<T> m;
	m.assign( 3, 10, ( T ) 0.0 );
	
// 	std::cout << ref << "|" << a1 << "|" << a2 << "|" << a3 << std::endl;

	/* latch in the coordinates, makes code more readable */
	T x[4] = {
			AntennaCoordinates.x_[ ref ],
			AntennaCoordinates.x_[ a1 ],
			AntennaCoordinates.x_[ a2 ],
			AntennaCoordinates.x_[ a3 ]
			};

	T y[4] = {
			AntennaCoordinates.y_[ ref ],
			AntennaCoordinates.y_[ a1 ],
			AntennaCoordinates.y_[ a2 ],
			AntennaCoordinates.y_[ a3 ]
			};

	T z[4] = {
			AntennaCoordinates.z_[ ref ],
			AntennaCoordinates.z_[ a1 ],
			AntennaCoordinates.z_[ a2 ],
			AntennaCoordinates.z_[ a3 ]
			};

	/* fill the geometrical matrix */
	for( int i = 0; i 	< 3; i++ ) {
		/* The matrix Z */
		m[i][0] = x[i+1]-x[0];
		m[i][1] = y[i+1]-y[0];
		m[i][2] = z[i+1]-z[0];

		/* The matrix P */
		m[i][i+3] = -co.a_1;

		/* prefill the matrix V */
		m[i][6] = -co.a_2;

		m[i][i+7] = co.a_2;
		
	}
	
	return m;
}

template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
void permuteAntennas< N_ANTA, N_ANTPERM, T >::dumb_matrices_2_file( )
{
// 	std::cout <<" dump " << std::endl;
	
	std::ofstream f;
	f.open("output/matdump.dat");

	if ( f.is_open() ) {
		for( auto& c : configurations )
			for( auto& m : c.mat ) {
				c.dumb_matrix( m, 3, 10 );
				c.dumb_matrix_2_file( f, m, 3, 10 );
			}

	}
	f.close();
}

/**
 * This method will compute all the possible permutations for the given reference antenna ref
 * @param[in] ref The reference antenna
 *
 */
// template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
// int permuteAntennas< N_ANTA, N_ANTPERM, T >::computePermutations( const int ref )
// {
// 
// 
// 	
// }

// void test2( void );
// 
// void test3() {
// 	std::cout << "Hello World" << std::endl;
// 
// }


#endif
