#ifndef _EVOLUTIONARY_CALIBRATION_H_
#define _EVOLUTIONARY_CALIBRATION_H_

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Algorithms/DirectSearch/CMA.h>
#include <shark/Algorithms/AbstractOptimizer.h>
#include <shark/Rng/GlobalRng.h>
#include <nr3/nr3.h>
#include "../solve.h"

namespace PRPSEvolution {
	namespace Models {
	using namespace shark;

		/**
		*
		*/
struct EvolutionaryCalibration : public SingleObjectiveFunction {

	typedef AbstractOptimizer<shark::VectorSpace< double >,double,SingleObjectiveResultSet<typename shark::VectorSpace< double >::PointType> > base_type;

	typedef typename base_type::ObjectiveFunctionType ObjectiveFunctionType;

	EvolutionaryCalibration( ) {
		m_numberOfVariables = Solve::ProblemDimensions::Calibration;
		m_features |= CAN_PROPOSE_STARTING_POINT;
	}

	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "Evolutionary Calibration"; }

	std::size_t numberOfVariables()const{
		return m_numberOfVariables;
	}

	bool hasScalableDimensionality()const{
		return true;
	}

	void setNumberOfVariables( std::size_t numberOfVariables ){
		m_numberOfVariables = numberOfVariables;
	}

	void configure(const PropertyTree &node) {
		m_numberOfVariables = node.get("numberOfVariables", 5l);
	}

	/**
	 * Generate a starting value
	 * @param[out] x The suggested search point
	 * 
	 */
	void proposeStartingPoint(SearchPointType &x) const {
		x.resize(numberOfVariables());

		for (unsigned int i = 0; i < 3; i++) {
			x( i ) = Rng::uni(-10, 10);
		}
	}

	/**
	 *
	 */
	double eval(const SearchPointType &p) const;

	/**
	 *
	 */
	void setParams( const NRmatrix< Doub > &M,
					const NRvector< Doub > &v
				) {
		setMat(M);
		setVec(v);
	}


	/**
	*
	*/
	void setMat( const NRmatrix< Doub > &M ) {
		A = M;
		A_isSet = true;

	}

	/**
	*
	*/
	void setVec( const NRvector< Doub > &v ) {
		b = v;
		b_isSet = true;
	}

	inline double mkII( const NRmatrix<Doub> &A, const double* x, const NRvector<Doub> &b ) const;

private:
	std::size_t m_numberOfVariables;

	/** The Matrices we need to solve the Problem */
	NRmatrix< Doub > A;
	bool A_isSet = false;

	/** The b-vector needed to find a Solution */
	NRvector< Doub > b;
	bool b_isSet = false;

};

		ANNOUNCE_SINGLE_OBJECTIVE_FUNCTION(EvolutionaryCalibration, soo::RealValuedObjectiveFunctionFactory);

	}
} /* end namespace */

#endif /* _EVOLUTIONARY_CALIBRATION_H_ */