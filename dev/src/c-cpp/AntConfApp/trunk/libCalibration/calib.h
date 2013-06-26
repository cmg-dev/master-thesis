#ifndef _CALIB_H_
#define _CALIB_H_

#include "nr3/nr3.h"
#include "nr3/svd.h"

#include "../include/coords.h"
#include "../include/PRPSEvolution.h"
#include "../include/PRPSEvolutionCalibrationExeptions.h"
#include "../include/PRPSError.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"

namespace PRPSEvolution {
	namespace Calibration {
		/**
		* This will perform the calibration stuff
		*
		*/
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		struct performCalibration {
		private:

			/* Temp data container *****************************************/

			/**
			 * This is the array where the result is stored
			 */
			std::array< NRvector< T >, N_ANTA>				AntennaCoordinates;
			Positioning::CoordContainer< N_CALPOS, T >	CalibrationPointsCoordinates;

			/* store the distances for every calibration point belonging to every antenna */
			std::array< std::array< T , N_ANTA >, N_CALPOS >		distances;

			/* Used for the calculation ************************************/
			/*	A represents the matrix of the geometrical relation of the
			 *	calibration points
			 *
			 */
			NRmatrix< T > A;

			/*	there are N_ANTA-vectors that are calculated using:
			 *	c_k0 = 1/2[r_0^2-r_k^2+d_k0^2]
			 *	The Amount of entries depends on the number of Points used for calibration
			 *	in general the number of entries id equal to N_CALPOS -1
			 * 
			 */
			std::array< NRvector< T >, N_ANTA > c_k0;

			/* functions ***************************************************/
			int rMeasuredDistances();

			int rCalibrationPointRelations();

			NRmatrix< T > calcGeometricalMatrix();

			NRvector< T > calcDistanceVector( int i );

			std::array< NRvector< T >, N_ANTA > SolveCalibration();

			void dumpDistanceVector();

			void dumpGeometricalMatrix();
			
			void dumpDistances();

			
			void dumpCoordsToFile();

			
		public:
			performCalibration();

		};

		/******************************************************************/
		/* Caluculation ***************************************************/
		/******************************************************************/
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		NRmatrix< T > performCalibration<N_ANTA,N_CALPOS,T>::calcGeometricalMatrix()
		{
			NRmatrix< T > a;
			a.assign( MAT_ROWS, MAT_ROWS, ( T ) 0. );

			for( int i = 0; i < a.nrows(); i++ ) {
				a[i][0] = CalibrationPointsCoordinates.x_[ i + 1 ] -
							CalibrationPointsCoordinates.x_[ 0 ];

				a[i][1] = CalibrationPointsCoordinates.y_[ i + 1 ] -
							CalibrationPointsCoordinates.y_[ 0 ];

				a[i][2] = CalibrationPointsCoordinates.z_[ i + 1 ]-
							CalibrationPointsCoordinates.z_[ 0 ];
			}

			return a;
		}
		
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		NRvector< T > performCalibration<N_ANTA,N_CALPOS,T>::calcDistanceVector( int j )
		{
			NRvector< T > c;
			/* 3 x 1 matrix */
			c.assign( MAT_ROWS, ( T ) 0. );

			auto xyz = CalibrationPointsCoordinates;

			std::array< T, MAT_ROWS > d_k0;
			
			for( int i = 0; i < d_k0.size(); i++ ) {
				d_k0[ i ] = (xyz.x_[i+1]-xyz.x_[0])
							+ (xyz.y_[i+1]-xyz.y_[0])
							+ (xyz.z_[i+1]-xyz.z_[0]);

			}
			for( int i = 0; i < c.size(); i++ ) {
				c[ i ] = 0.5* ( ( distances[3][j]*distances[3][j] )
						- ( distances[i][j]*distances[i][j] )
						+ ( d_k0[i]*d_k0[i] ) );

			}

			return c;
		}
		
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		std::array< NRvector< T >, N_ANTA > performCalibration<N_ANTA,N_CALPOS,T>::SolveCalibration()
		{
			SVD svd( A );
			std:array< NRvector< T >, N_ANTA > x;

			for( auto& x_ : x ) x_.assign( A.nrows(), 0.0 );

			int i = 0;
			for( auto& b:c_k0 ) {
				svd.solve( b, x[i++] );
// 				AntennaCoordinates[ i++ ] = x;
			}

			return x;
// 			throw( "Not implemented" );
		}

		/******************************************************************/
		/* Constructors ***************************************************/
		/******************************************************************/
		
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		performCalibration<N_ANTA,N_CALPOS,T>::performCalibration ()
		{
			std::cout << "*** Performing calibration " << std::endl;

			/* read in the values */
			if( rMeasuredDistances() )
				std::cout << "*** Error while reading input file 1" << std::endl;
			
			if( rCalibrationPointRelations() )
				std::cout << "*** Error while reading input file 2" << std::endl;

			/* fill the matrix A */
			A = calcGeometricalMatrix();

			int i = 0;
			/* fill the vactor c_k0 */
			for( auto& c: c_k0 ) {
				c = calcDistanceVector( i++ );

			}
			dumpGeometricalMatrix();
			dumpDistances();
			dumpDistanceVector();
			
			/* perform calculation */
			AntennaCoordinates = SolveCalibration();

			/* dump */
			dumpCoordsToFile();

		}

		/******************************************************************/
		/******************************************************************/
		/******************************************************************/
		/**
		 *
		 *
		 */
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		int performCalibration<N_ANTA,N_CALPOS,T>::rCalibrationPointRelations()
		{
			std::ifstream	file ( "data/calibrationPointsRelation.dat" );
			std::string		line;
			int				valuesRead;
			int				linesRead;
			
			valuesRead = linesRead = 0;

			/* make the code shorter */
			auto& cpc = CalibrationPointsCoordinates;
			while( getline( file,line ) ) {
				std::stringstream	linestream( line );
				std::string			value;

				valuesRead = 0;
				
				while( getline( linestream, value, ',' ) ) {
					cpc.x_[ valuesRead ] = ( linesRead == 0 ) ? std::stod( value ):( cpc.x_[ valuesRead ] ) ;
					cpc.y_[ valuesRead ] = ( linesRead == 1 ) ? std::stod( value ):( cpc.y_[ valuesRead ] ) ;
					cpc.z_[ valuesRead ] = ( linesRead == 2 ) ? std::stod( value ):( cpc.z_[ valuesRead ] ) ;

					valuesRead++;

				}
				linesRead++;

			}
			file.close();

// 			std::cout << "** I've read the following values: " << std::endl;
// 			std::cout << "x" << '\t'<< "y" << '\t' << "z" << std::endl;
// 			for( int i = 0; i < N_CALPOS; i++ ) {
// 				std::cout << cpc.x_[ i ] << '\t'
// 							<< cpc.y_[ i ] << '\t'
// 							<< cpc.z_[ i ] << std::endl;
// 
// 			}
			return PRPSError::FileIO::okay;
// 			throw( "NOT implemented, yet" );

		}

		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		int performCalibration<N_ANTA,N_CALPOS,T>::rMeasuredDistances()
		{
			std::ifstream	file ( "data/MeasuredDistances.dat" );
			std::string		line;
			int				valuesRead;
			int				linesRead;


			for( auto& pos: distances )
				for( auto& dist: pos )
					dist = ( T ) 0.;

			valuesRead = linesRead = 0;

			auto& pos = distances;
			while( getline( file,line ) ) {
				auto&				dist				= pos[linesRead];
				std::stringstream	linestream( line );
				std::string			value;

				valuesRead = 0;

				while( getline( linestream, value, ',' ) ) {
					dist[ valuesRead ] = std::stod( value );
					valuesRead++;

				}
				linesRead++;

			}
			file.close();

			return PRPSError::FileIO::okay;

		}

		/******************************************************************/
		/* Dump some stuff to somewhere ***********************************/
		/******************************************************************/
		
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		void performCalibration<N_ANTA,N_CALPOS,T>::dumpCoordsToFile()
		{
			std::ofstream f;
			f.open("output/coorddump.dat");
			if ( f.is_open() ) {
				int i = 0;
				for( auto& coord : AntennaCoordinates ) {
					f << coord[0] << ',' << coord[1] << ',' << coord[2] << std::endl;
				}
				f.close();
			}
			return;

		}

		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		void performCalibration<N_ANTA,N_CALPOS,T>::dumpDistances()
		{
			for( auto& pos: distances ) {
				for( auto& dist: pos ) {
					std::cout << dist << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		void performCalibration<N_ANTA,N_CALPOS,T>::dumpGeometricalMatrix()
		{
			std::cout << "A = \t" << std::endl;
			for( int i = 0; i < A.nrows(); i++ ) {
				for( int j = 0; j < A.ncols(); j++ ) {
					std::cout << A[i][j] << " ";
				}
				std::cout << std::endl;
			}
				
		}
		
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		void performCalibration<N_ANTA,N_CALPOS,T>::dumpDistanceVector()
		{
			for( auto& pos: c_k0 ) {
				for( int i = 0; i < pos.size(); i++ ) {
					std::cout << pos[i] << " | ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		
	}
}
#endif /* !_CALIB_H_ */