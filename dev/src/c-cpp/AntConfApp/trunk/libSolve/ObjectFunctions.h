/**
 * 
 * 
 */

#ifdef _PRPSEVOLUTION_OBJECTFUNCTIONS_H_
	#define _PRPSEVOLUTION_OBJECTFUNCTIONS_H_

// #include <stdlib.h>
#include <EALib/ObjectiveFunction.h>

/**
 * 
 * 
 */
class WholeTomatoMkI : public ObjectiveFunctionVS<double> {
public:
	//! Constructor
	WholeTomatoMkI( unsigned d = 29 );

	//! Destructor
	~WholeTomatoMkI();

	unsigned int objectives() const;
	void result(double* const& point, std::vector<double>& value);
	bool ProposeStartingPoint(double*& point) const;
	bool utopianFitness(std::vector<double>& fitness) const;
};

/**
 *
 *
 */
class WholeTomato_MkII : public ObjectiveFunctionVS<double> {
public:
	//! Constructor
	WholeTomato_MkII( unsigned d = 29 );

	//! Destructor
	~WholeTomato_MkII();

	unsigned int objectives() const;
	void result(double* const& point, std::vector<double>& value);
	bool ProposeStartingPoint(double*& point) const;
	bool utopianFitness(std::vector<double>& fitness) const;
};

#endif /* !_PRPSEVOLUTION_OBJECTFUNCTIONS_H_ */