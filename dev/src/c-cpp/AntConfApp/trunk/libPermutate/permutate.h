#ifndef __LIB_PERMUTATE_H_
#define __LIB_PERMUTATE_H_

#include "nr3/nr3.h"
#include "nr3/svd.h"
#include "prps.h"

#include <stdio.h>
#include <stdlib.h>
#include <array>


/**
 * The maximum amount of Permutations for one reference antenna
 */
const int MAX_PERMUTATION_AMOUNT = 35;

/**
 *	
 */
template <class T>
struct coords {
	T x, y, z;

	/* set x-y-z to the initial value */
// 	coords( T _initVal )  {
// 		x = y = z = _initVal;
// 
// 	};
	
};

/**
 * This will collect some stuff for calculating the permutation of the antennas
 * 
 */
struct permuteAntennas {
	int ref;
	/* We will store the x-y-z-coords we received from the Antenna in this array */
	std::array<coords<double>, ANTENNA_AMOUNT> antennaCoords;
	
	/* store the reference antenna while constructing */
  	permuteAntennas( int _refAnt ) { ref = _refAnt; };


	// read in and store in antennaCoords
// 	readCSVFile();

	//compute permutations

	//
// 	permut
};

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