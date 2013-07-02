/**
 * @file permutate.h
 * @date 2013|Jun|25
 * 
 * 
 *
 */
#ifndef __LIB_PERMUTATE_H
	#define __LIB_PERMUTATE_H

#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>

#include "../include/coords.h"
#include "../include/PRPSEvolution.h"
#include "../include/PRPSEvolutionPermutationExceptions.h"
#include "../include/PRPSEvolutionFIOExceptions.h"
#include "../include/PRPSError.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"

#include "nr3/nr3.h"
#include "nr3/svd.h"

// using namespace PRPSEvolution;
/**************************************************************************/
/**************************************************************************/
/**************************************************************************/
namespace PRPSEvolution {
	namespace Permutate {
		/**
		* The maximum amount of Permutations for one reference antenna,
		* we need this const-expression for the template
		*
		*/
		const int MAX_PERMUTATION_AMOUNT = 35;

		/******************************************************************/
		inline int Factorial(int x) {
			return (x == 1 ? x : x * Factorial(x - 1));
		}
		

		/******************************************************************/
		template <typename Iterator>
		inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
		{
		/* Credits: Thomas Draper */
		if ((first == last) || (first == k) || (last == k))
			return false;
		Iterator itr1 = first;
		Iterator itr2 = last;
		++itr1;
		if (last == itr1)
			return false;
		itr1 = last;
		--itr1;
		itr1 = k;
		--itr2;
		while (first != itr1)
		{
			if (*--itr1 < *itr2)
			{
				Iterator j = k;
				while (!(*itr1 < *j)) ++j;
				std::iter_swap(itr1,j);
				++itr1;
				++j;
				itr2 = k;
				std::rotate(itr1,j,last);
				while (last != j)
				{
					++j;
					++itr2;
				}
				std::rotate(k,itr2,last);
				return true;
			}
		}
		std::rotate(first,k,last);
		return false;
		}

		/******************************************************************/
		/* Definitions ****************************************************/
		/******************************************************************/

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
// 			std::array< Doub, N_MAT > conditionNumbers;

			/* names resembles the contributing antennas for this Matrix */
			std::array< std::string, N_MAT > names;

			/**
			* 
			*/
			static void dump_matrix( NRmatrix< T > mat ) {
				std::cout << "** Begin matrix dump: *****" << std::endl;
				for(int i=0;i<mat.nrows();i++){
					for(int j=0;j<mat.ncols();j++){
						std::cout << mat[i][j] << " | ";
					}
					std::cout << '\n';
				}
				std::cout << '\n';
				std::cout << "** End matrix dump: *****" << std::endl;
			}

			/**
			* 
			*/
			static void dump_matrix_2_file( std::ofstream &f, NRmatrix< T > mat) {
				if( !f ) return;
				
				for(int i=0;i<mat.nrows();i++) {
					for(int j=0;j<mat.ncols();j++) {
						f << mat[i][j];
						if(j+1!=mat.ncols())	f << ',';

					}
					f << '\n';
				}
				f << '\n';
			}

			/**
			*
			*/
			AntennaPermutations( void ) { }
			
		};

		/**
		* This will collect some stuff for calculating the permutation of the antennas
		*
		*/
		template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
		struct permuteAntennas {
			int ref;
			PRPSEvolution::Constants systemConstants;
			/* We will store the x-y-z-coords we received from the antenna in this array */
			Positioning::CoordContainer< N_ANTA, T > AntennaCoordinates;
			
			/* this array will store all possible matrices of the system */
			std::array< AntennaPermutations< N_ANTPERM, Doub >, N_ANTA>
					configurations;

			/* 8 x 8 Matrix containing the distance^2 for each */
			NRmatrix<T> d_k0_mat;

					
			/* store the reference antenna while constructing */
			permuteAntennas( const PRPSEvolution::Constants c );

			int rCoordFile();

			/**/
			int computePermutations( const PRPSEvolution::Constants &co );

			/**/
			template < std::size_t NN, std::size_t MM >
			const NRmatrix<T> computeMatrix( const int ref,
												const int a1,
												const int a2,
												const int a3,
												const PRPSEvolution::Constants &co );

			/**/
			NRmatrix<T> compute_d_k0_Mat();
			
			/**/
			void dumpConfigurationsToFile( );

			/**/
			void dump_matrices_2_file( );

		};

		/**************************************************************************/
		/* Declarations ***********************************************************/
		/**************************************************************************/

		/**************************************************************************/
		template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
		permuteAntennas< N_ANTA, N_ANTPERM, T >::permuteAntennas( const PRPSEvolution::Constants c )
		: systemConstants( c )
		{
			/**************************************************************/
			std::cout << "permuteAntennas:: Reading coords from file.. " ;

			rCoordFile();

			std::cout << "okay" << std::endl;

			/**************************************************************/
			std::cout << "permuteAntennas:: Filling distance matrix.. " ;

			d_k0_mat = compute_d_k0_Mat();

			std::cout << "done" << std::endl;

			/**************************************************************/
			std::cout << "permuteAntennas:: Doing computations.. " ;

			computePermutations( systemConstants );

			std::cout << "done" << std::endl;

			/**************************************************************/
			std::cout << "permuteAntennas:: Dumping Matrices.. " ;

			dump_matrices_2_file();

			std::cout << "done" << std::endl;

		}

		/**************************************************************************/
		/**
		*	Load the csv-file containing the coordinates and store it into the container.
		*
		*/
		template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
		int permuteAntennas< N_ANTA, N_ANTPERM, T >::rCoordFile()
		{
		// 	std::ifstream	file ( "data/coordinatesPrecalculated.dat" );
			std::ifstream	file ( "data/coorddump.dat" );
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
						AntennaCoordinates.x_[ linesRead ] = ( valuesRead == 0 ) ? std::stod( value ):( AntennaCoordinates.x_[ linesRead ] ) ;
						AntennaCoordinates.y_[ linesRead ] = ( valuesRead == 1 ) ? std::stod( value ):( AntennaCoordinates.y_[ linesRead ] ) ;
						AntennaCoordinates.z_[ linesRead ] = ( valuesRead == 2 ) ? std::stod( value ):( AntennaCoordinates.z_[ linesRead ] ) ;

						valuesRead++;
				}
				/* a line is read */
				if( valuesRead != (int) PRPSEvolution::EXPECTED_VALUES_COORD_FILE )
					throw PRPSEvolution::Exceptions::FileIO::MalformedInputExeption;

				linesRead++;

			}
			/* check the input */
			if( linesRead != PRPSEvolution::EXPECTED_LINES_COORD_FILE )
				throw PRPSEvolution::Exceptions::FileIO::MalformedInputExeption;
		/*
			std::cout << "** I've read the following values: " << std::endl;
			std::cout << "x" << " | "<< "y" << " | " << "z" << std::endl;
			for( int i = 0; i < N_ANTA; i++ ) {
				std::cout << AntennaCoordinates.x_[ i ] << " | "
							<< AntennaCoordinates.y_[ i ] << " | "
							<< AntennaCoordinates.z_[ i ] << std::endl;

			}*/

			return PRPSError::okay;

		}

		/**************************************************************************/
		/**
		* This method handles the computation of the antenna permutations
		* @param[in] co Constant structure with the system constants we need @see PRPSEvolution::Constants
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
				/* used as matrix index */
				m_i = 0;
				/* get the matrices for one configuration */
				auto& m = c[r].mat;
				auto& names = c[r].names;

				/* run through all configurations **********************************/
				for( int i = i_start; i < i_goal; i++  ) {
					if( i == r ) {
						i_start++;
						continue;
					}
					j_start = i_start + 1;

					/* for every Matrix in this configuration */
					for( int j = j_start; j < j_goal; j++ ) {
						/* skip the reference antenna */
						if( j == r ) { continue; }
						k_start = j + 1;

						for( int k = k_start; k < k_goal; k++ ) {
							if( k == r ) { continue; }

							/* assign the new matrix */
							ostringstream convert;
							convert << r << i << j << k;
							
							names[ m_i ] = convert.str();
							m[ m_i++ ] = computeMatrix< MAT_ROWS, MAT_COLS >( r, i, j, k, co );

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

		}

		/**
		* This method will compute all the possible permutations based on the given reference antenna @see ref
		* @param[in] ref The reference antenna
		* @param[in] a1 First antenna
		* @param[in] a2 Second antenna
		* @param[in] a3 Third antenna
		*
		*/
		template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
		template < std::size_t NN, std::size_t MM >
		const NRmatrix<T> permuteAntennas< N_ANTA, N_ANTPERM, T >::computeMatrix( const int ref, const int a1, const int a2, const int a3, const PRPSEvolution::Constants &co )
		{
			NRmatrix<T> m;
			m.assign( NN, MM, ( T ) 0. );

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

		/**
		* This method will dump all the Antennas to an output file
		*
		*/
		template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
		void permuteAntennas< N_ANTA, N_ANTPERM, T >::dump_matrices_2_file( )
		{
			std::ofstream f;
			f.open("output/matdump.dat");

			if ( f.is_open() ) {
				for( auto& c : configurations ) {
					int i = 0;
					
					for( auto& m : c.mat ) {
						f << c.names[i++] << std::endl;
						c.dump_matrix_2_file( f, m );
					}
				}
				f.close();

			} else {
				throw PRPSEvolution::Exceptions::FileIO::OutputExeption;

			}



		}

		template < std::size_t N_ANTA, std::size_t N_ANTPERM, typename T >
		NRmatrix<T> permuteAntennas< N_ANTA, N_ANTPERM, T >::compute_d_k0_Mat()
		{
			NRmatrix<T> mat;
			mat.assign( N_ANTA, N_ANTA, 0.0 );
			T x, y, z;
			
			for(int i=0;i<mat.nrows();i++) {
				/* the upper half would be enough but its simpler to access the other one */
				for(int j=i;j<mat.nrows();j++) {
// 				for(int j=0;j<mat.nrows();j++) {
					x = AntennaCoordinates.x_[i] -
						 AntennaCoordinates.x_[j];
						
					y = AntennaCoordinates.y_[i] -
						 AntennaCoordinates.y_[j];
						 
					z = AntennaCoordinates.z_[i] -
						 AntennaCoordinates.z_[j];
					
					mat[i][j] = (x*x + y*y + z*z);
					
				}
			}

// #ifdef PERMUTATE_DBG
// 			std::cout << std::endl;
// 			for(int i=0;i<mat.nrows();i++) {
// 				for(int j=0;j<mat.nrows();j++) {
// 					std::cout << mat[i][j] << " ";
// 				}
// 				std::cout << std::endl;
// 			}
// #endif
			return mat;
			
		}
		
	}
}
// void test2( void );
// 
// void test3() {
// 	std::cout << "Hello World" << std::endl;
// 
// }


#endif
