/**
 * @file PRPSEvolution.h
 * @date 2013|Jun|18
 * This file collects definitions belonging to the PRPSEvolution-namespace. Especially const. defines.
 *
 */

#ifndef __PRPSEVOLUTION_H_
#define __PRPSEVOLUTION_H_

namespace PRPSEvolution {
	const int	ANTENNA_AMOUNT		=	8;

	/*
	 * This two constants represent the calibration method, we need 4 discrete positions
	 * and 8 values per postition (representing the antennas) to calculate the coordinates
	 */
	const int	EXPECTED_LINES_CALIBRATION_FILE	=	4;
	const int	EXPECTED_VALUES_CALIBRATION_FILE	=	ANTENNA_AMOUNT;

	const int	EXPECTED_LINES_COORD_FILE			=	ANTENNA_AMOUNT;
	/* meaning one value for either x, y and z coords */
	const int	EXPECTED_VALUES_COORD_FILE			=	3;

	const int	EXPECTED_LINES_SYSTEM_INI_FILE	=	2;

	const int	MAT_ROWS	=	3;
	const int	MAT_COLS	=	10;

}

#endif /* !__PRPSEVOLUTION_H_ */