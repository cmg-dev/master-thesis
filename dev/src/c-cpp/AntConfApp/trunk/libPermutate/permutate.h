#ifndef __LIB_PERMUTATE_H_
#define __LIB_PERMUTATE_H_

#include "nr3/nr3.h"
#include "nr3/svd.h"
#include "coords.h"
#include "PRPSEvolution.h"
#include "PRPSError.h"
#include <stdio.h>
#include <stdlib.h>
#include <array>

using namespace PRPSEvolution;
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

/**
 * The maximum amount of Permutations for one reference antenna
 */
const int MAX_PERMUTATION_AMOUNT = 35;


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

/**
 * This will collect some stuff for calculating the permutation of the antennas
 * 
 */
struct permuteAntennas {
	int ref;
	/* We will store the x-y-z-coords we received from the Antenna in this array */
 	Positioning::CoordContainer<ANTENNA_AMOUNT, double> AntennaCoordinates;
	
	/* store the reference antenna while constructing */
  	permuteAntennas( int _refAnt ) { ref = _refAnt; };

	
	// read in and store in antennaCoords
	int readCSVFile();

	/* this method will compute all the possible permutations */
	int computePermutations();
	
};

/**
 * Load the csv-file containing the coordinates and store it into the container
 *
 */
int permuteAntennas::readCSVFile() {
	ifstream		file ( "data/MeasuredDistances.dat" );
	std::string		line;
	int				valuesRead;
	int				linesRead;

	valuesRead = linesRead = 0;

	/* simply fill with 0 */
	for( int i = 0; i < ANTENNA_AMOUNT; i++ ) {
		AntennaCoordinates.x_[ i ] = 0.0;
		AntennaCoordinates.y_[ i ] = 0.0;
		AntennaCoordinates.z_[ i ] = 0.0;

	}

	while( getline( file,line ) ) {
		std::stringstream   linestream( line );
		std::string         value;

		valuesRead = 0;
		while( getline( linestream, value, ',' ) ) {
			std::cout <<  value << " ";

			try {
// 				AntennaCoordinates.x_[ valuesRead ] = std::stod(value);
// 				AntennaCoordinates.x_[ valuesRead ] = ( linesRead == 0 ) ? std::stod(value):(AntennaCoordinates.x_[ valuesRead ]) ;
// 				AntennaCoordinates.y_[ valuesRead ] = ( linesRead == 1 ) ? std::stod(value):(AntennaCoordinates.y_[ valuesRead ]) ;
// 				AntennaCoordinates.z_[ valuesRead ] = ( linesRead == 2 ) ? std::stod(value):(AntennaCoordinates.z_[ valuesRead ]) ;
			} catch ( char * str ) {
				cout << "Exception raised: " << str << '\n';

			}
			valuesRead++;

		}
		/* a line is read */
		if( valuesRead != PRPSEvolution::EXPECTED_VALUES_COORD_FILE )
			return PRPSError::FileIO::inputmalformed;

		linesRead++;
		std::cout << std::endl;
	}

	/* check the input */
	if( linesRead != PRPSEvolution::EXPECTED_LINES_COORD_FILE )
		return PRPSError::FileIO::inputmalformed;


	
	return PRPSError::okay;
}

/**
 * 
 */
struct AntennaPermutations {
	/* we use svd-algorithms from numerical recipes vol 3 */
	SVD svd;

	/* the matrices of the popssible combinations */
	std::array<NRmatrix<Doub>,MAX_PERMUTATION_AMOUNT> mat;
	
	/* the condition number of a matrix */
	std::array<double, ANTENNA_AMOUNT> conditionNumbers;
	
};

#endif