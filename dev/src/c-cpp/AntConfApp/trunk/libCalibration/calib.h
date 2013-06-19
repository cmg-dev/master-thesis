#ifndef _CALIB_H_
#define _CALIB_H_

/**
 * This will perform the calibration stuff
 *
 */
struct AntennaCalibration {
	/* the matrices of the popssible combinations */
	NRmatrix<Doub> A;

	/* the condition number of a matrix */
	std::array<Doub, ANTENNA_AMOUNT> conditionNumbers;

};

#endif /* !_CALIB_H_ */