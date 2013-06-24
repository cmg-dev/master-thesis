#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <array>
#include <iostream>
#include<fstream>
#include<sstream>
#include<string>

#include "AntennaConfiguration.h"
#include "../libPermutate/permutate.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"
#include "../libCalibration/calib.h"

const int MAX_PERMUATION_AMOUNT = 35;
const int ROWS = 3;
const int COLS = 3;

int main ( int argc, char *argv[ ] ) {
	PRPSEvolution::System sys;
	PRPSEvolution::Calibration::performCalibration<ANTENNA_AMOUNT, 4, Doub> PC;
	
	/* perform calibration */

	/**/
	permuteAntennas< ANTENNA_AMOUNT,MAX_PERMUTATION_AMOUNT, Doub > PA(0);
	
	/* read the coordinate file */
	PA.rCoordFile();
	
	/**/
	PA.computePermutations( sys.constants );

	std::cout << "Dumping Matrices... " ;
	PA.dumb_matrices_2_file();
	std::cout << "done" << std::endl;
	
// 	if (argc < 2) {
// 		fprintf(stdout,"%s Version %d.%d.%x\n",
// 			argv[0],
// 			VERSION_MAJOR,
// 			VERSION_MINOR,
// 			VERSION_SUB_MINOR
// 			);
// 		fprintf(stdout,"Usage: %s number\n",argv[0]);
// 		return 1;
// 
// 	}
// 
// 	std::array<NRmatrix<Doub>,MAX_PERMUATION_AMOUNT> mat;
// 
// 	double val = 0.0;
// 	NRmatrix<Doub> mat1(3,3,val);
// 
// 	for( auto& s: mat) {
//   		s = mat1;
// 		val = val + 1.0;
// 		mat1.assign( s.ncols(), s.nrows(), val);
// 		
// 	}
// 
// 	for( auto& s: mat) {
// 		for( int i = 0; i <s.nrows(); i++) {
// 			for( int j = 0; j <s.ncols(); j++) {
// 				std::cout << (double ) s[i][j] << "\t" ;
// 				
// 			}
// 			std::cout << std::endl;
// 		
// 		}
// 		std::cout << std::endl;
// 	}
// 	double inputValue = atof(argv[1]);
// 	double outputValue = sqrt(inputValue);
// 	fprintf(stdout,"The square root of %g is %g\n",
// 		inputValue, outputValue );

	return 0;

}
