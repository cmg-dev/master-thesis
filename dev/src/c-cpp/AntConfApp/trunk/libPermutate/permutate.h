


#ifndef __LIB_PERMUTATE_H
	#define __LIB_PERMUTATE_H

#include "coords.h"
#include "PRPSEvolution.h"
#include "PRPSError.h"
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

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

	void dumb_matrix( NRmatrix< T > mat, int n, int m ) {
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
	
	AntennaPermutations( void ) {
		/* init all of the matrices */
		for(auto& m: mat) {
			m.assign( 3, 10, (T)0.0);
		}

// 		for(auto& m: mat)
// 			dumb_matrix( m, 3, 10 );

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
 	Positioning::CoordContainer<N_ANTA, T> AntennaCoordinates;
	/* this array will store all possible matrices of the system */
	std::array< AntennaPermutations< N_ANTPERM, Doub>, N_ANTA> configurations;
	
	/* store the reference antenna while constructing */
  	permuteAntennas( const int _refAnt = 0 );

	int rCoordFile();

	/**/
	int computePermutations( );

	/**/
	int computeMatrix( const int ref, const int a1, const int a2, const int a3 );


	/**********************************************************************/
//  	private:

// 	int computePermutations( const int ref );

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
	ifstream		file ( "data/MeasuredDistances.dat" );
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
int permuteAntennas< N_ANTA, N_ANTPERM, T >::computePermutations( )
{
	int Ant = 0;

	std::cout << "** Matrix " <<  std::endl;

	int r,i,j,k;
	int x,y;

	x = y = k = j = i = r = 0;
	/* run through all configurations */
	
 	for( auto& c : configurations ) 
	{
		i=0;
 		for( auto& m : c.mat ) {
			std::cout << "** Matrix " << i++ << std::endl;
			c.dumb_matrix( m, 3, 10 );
// 			/* assign the new matrix */
// // 			m[x] = computeMatrix(r,i,j,k );
// 			m[x].assign(3,10, (T) 42.0 );
// 			x++;
//
		}
		std::cout << "******" << j << std::endl;
		j++;
	}
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
int permuteAntennas< N_ANTA, N_ANTPERM, T >::computeMatrix( const int ref, const int a1, const int a2, const int a3 )
{
		
	
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
