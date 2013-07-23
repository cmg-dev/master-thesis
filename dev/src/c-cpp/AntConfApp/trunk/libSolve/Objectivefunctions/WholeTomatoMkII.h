
#ifndef _WHOLETOMATO_MARKII_
#define _WHOLETOMATO_MARKII_

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Rng/GlobalRng.h>
#include <nr3/nr3.h>

namespace PRPSEvolution {
	using namespace shark;

	/**
	 *
	 */
	struct WholeTomatoMkII : public SingleObjectiveFunction {
		
		typedef AbstractOptimizer<shark::VectorSpace< double >,double,SingleObjectiveResultSet<typename shark::VectorSpace< double >::PointType> > base_type;

		typedef typename base_type::ObjectiveFunctionType ObjectiveFunctionType;
		
		WholeTomatoMkII(unsigned int numberOfVariables = 5):m_numberOfVariables(numberOfVariables) {
			m_features |= CAN_PROPOSE_STARTING_POINT;
		}

		/// \brief From INameable: return the class name.
		std::string name() const
		{ return "WholeTomato Mark II"; }

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

		double eval(const SearchPointType &p) const {
			m_evaluationCounter++;
			std::vector<double> res;
			
// 			for( )
				
			return mkII( As[0], p, bs[0] );
		}

		/**
		 *
		 */
		void setParams( const std::vector<NRmatrix< Doub >> &M, const std::vector<NRvector< Doub >> &v ) {
			setMats(M);
			setVecs(v);

		}

		/**
		 */
		void setMats( const std::vector<NRmatrix< Doub >> &M ) {
			As = M;
			A_isSet = true;

		}

		/**
		 */
		void setVecs( const std::vector<NRvector< Doub >> &v ) {
			bs = v;
			b_isSet = true;
		}
		
		inline double mkII( const NRmatrix<Doub> &A, const SearchPointType &x, const NRvector<Doub> &b ) const
		{
			double res;
				double prod_Ax[3] = {0.,0.,0.};
				double x_[10];

#ifdef _DROP_BAD_
				
#endif
				x_[0]=x[0];
				x_[1]=x[1];
				x_[2]=x[2];
				x_[3]=(x[3]*x[3])-(x[4]*x[4]);
				x_[4]=(x[3]*x[3])-(x[5]*x[5]);
				x_[5]=(x[3]*x[3])-(x[6]*x[6]);
				x_[6]=x[3];
				x_[7]=x[4];
				x_[8]=x[5];
				x_[9]=x[6];

				/* multiply the matrix with the vector */
				for( int i = 0; i < A.nrows(); i++ )
					for( int j = 0; j < A.ncols(); j++ )
						prod_Ax[i] += A[i][j]*x_[j];

				/* sum up */
				res =	(prod_Ax[0] - b[0]) * (prod_Ax[0] - b[0]);
				res +=	(prod_Ax[1] - b[1]) * (prod_Ax[1] - b[1]);
				res +=	(prod_Ax[2] - b[2]) * (prod_Ax[2] - b[2]);

				return res;

		}
		
	private:
		std::size_t m_numberOfVariables;

		/** The Matrices we need to solve the Problem */
		std::vector<NRmatrix< Doub >> As;
		bool A_isSet = false;

		/** The b-vector needed to find a Solution */
		std::vector<NRvector< Doub >> bs;
		bool b_isSet = false;
		
	};

	ANNOUNCE_SINGLE_OBJECTIVE_FUNCTION(WholeTomatoMkII, soo::RealValuedObjectiveFunctionFactory);

}

#endif