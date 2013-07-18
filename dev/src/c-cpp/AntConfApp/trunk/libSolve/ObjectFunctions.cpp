
// #include <stdlib.h>
#include <EALib/ObjectiveFunction.h>
// #include "ObjectFunctions.h"

// #include <LinAlg/LinAlg.h>

/**************************************************************************/
/**************************************************************************/

WholeTomatoMkI::WholeTomatoMkI(unsigned d) : ObjectiveFunctionVS<double>(d, NULL)
{
	m_name = "Whole Tomato Mark I";
}

WholeTomatoMkI::~WholeTomatoMkI()
{}


unsigned int WholeTomatoMkI::objectives() const
{
	return 1;
}

void WholeTomatoMkI::result(double* const& point, std::vector<double>& value)
{

	double result = 0.0;

	for (unsigned i = 0; i < m_dimension - 1; i++)
		result += 100.0 * (point[i+1] - point[i] * point[i]) *
				  (point[i+1] - point[i] * point[i]) +
				  (point[i] - 1.0) * (point[i] - 1.0);

	value.resize(1);
	value[0] = result;

	m_timesCalled++;
}

bool WholeTomatoMkI::ProposeStartingPoint(double*& point) const
{

	for (unsigned int i = 0; i < m_dimension; i++)
		point[i] = Rng::gauss();

	return true;
}

bool WholeTomato_MkI::utopianFitness(std::vector<double>& fitness) const
{
	fitness.resize(1, false);
	fitness[0] = 0.0;
	return true;
}

/**************************************************************************/
/**************************************************************************/

WholeTomato_MkII::WholeTomato_MkII(unsigned d) : ObjectiveFunctionVS<double>(d, NULL)
{
	m_name = "WholeTomato Mark II";
}

WholeTomato_MkII::~WholeTomato_MkII()
{}


unsigned int WholeTomato_MkII::objectives() const
{
	return 1;
}

void WholeTomato_MkII::result(double* const& point, std::vector<double>& value)
{

}

bool WholeTomato_MkII::ProposeStartingPoint(double*& point) const
{

	return true;
}

bool WholeTomato_MkII::utopianFitness(std::vector<double>& fitness) const
{
	fitness.resize(1, false);
	fitness[0] = 0.0;
	return true;
}

