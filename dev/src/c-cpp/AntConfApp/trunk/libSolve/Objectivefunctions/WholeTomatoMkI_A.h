#ifndef _WHOLETOMATO_MARKI_VAR_A_
#define _WHOLETOMATO_MARKI_VAR_A_

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Rng/GlobalRng.h>
#include <nr3/nr3.h>

namespace PRPSEvolution {
	using namespace shark;

	/*
	 * SingleObjectiveFunction :=
	 *		typedef AbstractObjectiveFunction< VectorSpace< double >, double > SingleObjectiveFunction;
	 */
	
	/**
	* \brief
	*/
	struct WholeTomatoMkI_A : public SingleObjectiveFunction {

		WholeTomatoMkI_A( unsigned int numberOfVariables = 7 )
				: m_numberOfVariables(numberOfVariables) {
			m_features |= CAN_PROPOSE_STARTING_POINT;
		}

		/// \brief From INameable: return the class name.
		std::string name() const
		{ return "WholeTomato Mark I Variant A"; }

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

		void proposeStartingPoint(SearchPointType &x) const {
			x.resize(numberOfVariables());

			for (unsigned int i = 0; i < x.size(); i++) {
				x(i) = Rng::uni(0, 1);
			}
		}

		/**
		 * 
		 */
		double eval( const SearchPointType &x ) const {
			if( !A_isSet || !b_isSet )
				return -1;
			
			m_evaluationCounter++;

			
			const double res = mkI( A, x, b );

			return res;

		}

		/**
		 * 
		 */
		void setParams( const NRmatrix< Doub > &M, const NRvector< Doub > &v ) {
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
		
		/**
		 * @todo documentation
		 * @param[in] A The 10x3 Matrix that ist used in this solution
		 * @param[in] x The vector containing the variables
		 * @param[in] b Representing the vector b
		 * @return The residuum of the equation system representing the "Fitness" of the given Solution in @see x
		 *
		 */
// 		inline double test( const NRmatrix< Doub > &A, const SearchPointType &x, const NRvector< Doub > &b );


		inline double mkI( const NRmatrix<Doub> &A, const SearchPointType &x, const NRvector<Doub> &b ) const
		{
			double res;
			double prod_Ax[3] = {0.,0.,0.};

#ifdef _DROP_BAD_
			for(int i = 3; i < A.nrows(); i++ )
				if( x[i] < 0 )
					return -1.;
				
#endif
			/* multiply the matrix with the vector */
			for( int i = 0; i < A.nrows(); i++ )
				for( int j = 0; j < A.ncols(); j++ )
					prod_Ax[i] += A[i][j]*x[j];

			/* sum up */
			res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
			res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
			res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

			return res;

		}

	private:
		std::size_t m_numberOfVariables;

		/** The Matrices we need to solve the Problem */
		NRmatrix< Doub > A;
		bool A_isSet = false;

		/** The b-vector needed to find a Solution */
		NRvector< Doub > b;
		bool b_isSet = false;
		
	};
	
	ANNOUNCE_SINGLE_OBJECTIVE_FUNCTION(
		WholeTomatoMkI_A,
		shark::soo::RealValuedObjectiveFunctionFactory
	);
	
}

#endif /* _WHOLETOMATO_MARKI_VAR_A_ */