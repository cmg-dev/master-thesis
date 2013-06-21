/**
 * @file PRPSError.h
 * @date 2013|Jun|18
 * This file cantains definitions belonging to the PRPSError-namespace
 * 
 */
#ifndef __PRPSERROR_H_
#define __PRPSERROR_H_

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

namespace PRPSError{
	namespace FileIO {
		/** this ist no error */
		const int	okay				=	0;
		/** if no other error fits */
		const int	generalError		=	-1;
		/** file not found error */
		const int	fnf					=	-2;
		/** malformed input */
		const int	inputmalformed		=	-3;
		
	}
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

namespace PRPSError{
	/** this ist no error */
	const int	okay				=	0;
	/** if no other error fits */
	const int	general				=	-1;
	/** this is devastating */
	const int	critical			=	10;

}

#endif /* !__PRPSERROR_H_ */