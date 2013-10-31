#ifndef _WHOLETOMATO_REDUCED_
#define _WHOLETOMATO_REDUCED_

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Rng/GlobalRng.h>
#include <nr3/nr3.h>

// #define TEST_translateIdxFromNamesToArrayIdxs_samlple_data

namespace PRPSEvolution {
	namespace Models {
		using namespace shark;

		/**
		*
		*/
		struct WholeTomatoReduced : public SingleObjectiveFunction {

			typedef AbstractOptimizer<shark::VectorSpace< double >,double,SingleObjectiveResultSet<typename shark::VectorSpace< double >::PointType> > base_type;
			typedef typename base_type::ObjectiveFunctionType ObjectiveFunctionType;

			WholeTomatoReduced( unsigned int numberOfVariables = Solve::ProblemDimensions::WholeTomatoReduced )
			:m_numberOfVariables(numberOfVariables) {
				m_features |= CAN_PROPOSE_STARTING_POINT;
			}

			/// \brief From INameable: return the class name.
			std::string name() const
			{ return "WholeTomato Mark II"; }

			std::size_t numberOfVariables() const{
				return m_numberOfVariables;
			}

			bool hasScalableDimensionality() const{
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

				for (unsigned int i = 0; i < 3; i++) {
					x(i) = Rng::uni(-1, 1);
				}

			}

			/**
			*
			*/
			double eval(const SearchPointType &p) const;

			/**
			* The model itself.
			* @param[in] A	The Matrix A. for this Solution
			* @param[in] x	The x vector, contains the free parameter
			* @param[in] b	The b vector for this solution
			* @return
			*
			*/
			inline double reduced( const NRmatrix<Doub> &A, const double* x, const NRvector<Doub> &b ) const;

			/**
			 * Collects the constrains for this model
			 * @param[in] x The vector containing the variables
			 * @return
			 *
			 */
			inline bool constrains(const double* x) const;

			/**
			 *
			 * 
			 */
			void setParams( const std::vector<NRmatrix< Doub >> &M,
							const std::vector<NRvector< Doub >> &v,
							const std::vector<std::string> &n,
							const std::vector<NRvector< Doub >> &c,
							const double l
						) {
				setMats( M );
				setVecs( v );
				setNames( n );

				setIdx( parseIdxFromNames( n ) );
				setTranslation( translateIdxFromNamesToArrayIdxs( idxs ) );
				
				setAntennaCoords( c );
				setLambda( l );

			}

			/**
			 *
			 * 
			 */
			void setParams( const std::vector<NRmatrix< Doub >> &M,
							const std::vector<NRvector< Doub >> &v,
							const std::vector<std::vector<int>> &i,
							const std::vector<NRvector< Doub >> &c
						) {
				setMats( M );
				setVecs( v );
				setIdx( i );
				setAntennaCoords( c );

			}

			/** */
			std::array<double, 8> calcWavenumbers2( double x, double y, double z);
// 			{
// 				double xyz [] {x,y,z};
// 				return WholeTomatoReduced::calcWavenumbers(xyz);
// 			}
			
		private:
			int WAVENUMBER_OFFSET = 3;

			std::size_t m_numberOfVariables;

			/** The Matrices we need to solve the Problem */
			std::vector<NRmatrix< Doub >> As;
			bool A_isSet = false;

			/** The b-vector needed to find a Solution */
			std::vector<NRvector< Doub >> bs;
			bool b_isSet = false;

			std::vector<std::string> Names;
			bool Names_isSet = false;

			std::vector<std::vector<int>> idxs;
			bool Idx_isSet = false;

			std::vector<int> translation;
			bool Translation_isSet = false;

			std::vector<NRvector< Doub >> antennaCoords;
			bool AntennaCoords_isSet = false;

			double lambda;
			bool Lambda_isSet = false;
			
			bool continuesWavenumbers = true;
// 			bool continuesWavenumbers = false;

			std::array<Doub,8> Wavenumbers;
			
			/**
			 *
			 */
			void setMats( const std::vector<NRmatrix< Doub >> &M ) {
				As = M;
				A_isSet = true;

			}

			/**
			 *
			 */
			void setVecs( const std::vector<NRvector< Doub >> &v ) {
				bs = v;
				b_isSet = true;
			}

			/**
			 *
			 */
			void setNames( const std::vector<std::string> &n ) {
				Names = n;
				Names_isSet = true;
			}

			/**
			 *
			 */
			void setIdx( const std::vector<std::vector<int>> &i ) {
				idxs = i;
				Idx_isSet = true;
			}

			/**
			 *
			 */
			void setTranslation( const std::vector<int> &t ) {
				translation = t;
				Translation_isSet = true;
			}

			
			void setAntennaCoords( const std::vector<NRvector< Doub >> &c ) {
				antennaCoords = c;
				AntennaCoords_isSet = true;
			}

			void setLambda( const double l) {
				lambda = l;
				Lambda_isSet = true;
			}
			
			/**
			* This function will parse the indeces used for a solution
			* @param[in] namess Contains the "Name" of each matrix we want to use in this solution
			* @return A two dimensional vector with the indeces of each antenna for each matrix
			*
			*/
			std::vector<std::vector<int>>
			parseIdxFromNames
			( const std::vector<std::string> &namess ) {
				std::vector<std::vector<int>> res;

				for( auto names: namess ) {
					std::vector<int> idxs;
					for( int i = 0; i < names.size(); i++ ) {
						idxs.push_back( std::stoi( names.substr(i,1)) );

					}
					res.push_back( idxs );
				}

#ifdef OUTPUT
				for( auto idx: res ) {
					for( auto i: idx ) {
						std::cout << i << " ";
					}
					std::cout << std::endl;
				}
#endif
				return res;
			}

			/**
			* This function translates the availiable antenna names to the
			* indeces used for the solution
			* @param[in] namess Contains the "Name" of each matrix we want to use in this solution
			* @return A two dimensional vector with the indeces of each antenna for each matrix
			*
			*/
			std::vector<int>
			translateIdxFromNamesToArrayIdxs
			( const std::vector<std::vector<int>> &idxsAntennas ) {

				int translation[8];
				int j = 0;
				std::vector<std::vector<int>> IN;


				for(auto& t :translation )
					t = -1;

				IN = idxsAntennas;

#ifdef TEST_translateIdxFromNamesToArrayIdxs_samlple_data
				std::vector<std::vector<int>> temps;
				std::vector<int> temp;

				temp.push_back(2);
				temp.push_back(4);
				temp.push_back(5);
				temp.push_back(7);

				temps.push_back( temp );
				IN = temps;

#endif

				/* create the translation */
				for( auto idxs: IN ) {
					for( auto idx: idxs ) {
						translation[idx] =
							( translation[idx] == -1 ) ?
								(WAVENUMBER_OFFSET + j++) : translation[idx];

					}
				}

#ifdef TEST_translateIdxFromNamesToArrayIdxs_samlple_data
 				std::cout << "** translation result **" << std::endl;
				int i = 0;
				for( auto idx: translation ) {
						std::cout << i++ << " " << idx << std::endl;
				}

				exit(0);
#endif
				/* project to vector */
				std::vector<int> res;
				for( auto idx: translation )
					res.push_back( idx );

				return res;
			}

			/** */
			inline std::array<double, 8> calcWavenumbers( const double *x ) const;

			inline double panalty(const double* x) const;
			
		};

		ANNOUNCE_SINGLE_OBJECTIVE_FUNCTION(WholeTomatoReduced, soo::RealValuedObjectiveFunctionFactory);

	}
}
#endif