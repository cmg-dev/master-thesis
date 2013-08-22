#ifndef _WHOLETOMATO_MARKIII_
#define _WHOLETOMATO_MARKIII_

#include <shark/ObjectiveFunctions/AbstractObjectiveFunction.h>
#include <shark/Rng/GlobalRng.h>
#include <nr3/nr3.h>

namespace PRPSEvolution {
	namespace Models {
		using namespace shark;

		/**
		*
		*/
		struct WholeTomatoMkIII : public SingleObjectiveFunction {

			typedef AbstractOptimizer<shark::VectorSpace< double >,double,SingleObjectiveResultSet<typename shark::VectorSpace< double >::PointType> > base_type;

			typedef typename base_type::ObjectiveFunctionType ObjectiveFunctionType;

			WholeTomatoMkIII( unsigned int numberOfVariables = 5 ):m_numberOfVariables( numberOfVariables ) {
				m_features |= CAN_PROPOSE_STARTING_POINT;
				
				/* read in the coords */
				coords = rCoords( );
				
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
					x(i) = Rng::uni(-2, 2);
// 					x(i) = Rng::uni(-10, 10);
				}
				for (unsigned int i = 3; i < x.size(); i++) {
					x(i) = std::round( Rng::uni(2, 20) );

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
			inline double mkII( const NRmatrix<Doub> &A, const double* x, const NRvector<Doub> &b ) const;

			/**
			 * Collects the constrains for this model
			 * @param[in] x The vector containing the variables
			 * @return
			 *
			 */
			inline bool constrains(const double* x) const;

			/**
			 *
			 */
			void setParams( const std::vector<NRmatrix< Doub >> &M,
							const std::vector<NRvector< Doub >> &v,
							const std::vector<std::string> &n
						) {
				setMats(M);
				setVecs(v);
				setNames(n);

				setIdx( parseIdxFromNames( n ) );

			}

			/**
			 *
			 */
			void setParams( const std::vector<NRmatrix< Doub >> &M,
							const std::vector<NRvector< Doub >> &v,
							const std::vector<std::vector<int>> &i
						) {
				setMats(M);
				setVecs(v);
				setIdx(i);

			}

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

		private:
			/* the coordinates of the antennas */
			std::vector<std::array<double,3>> coords;
			
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
			 *
			 */
			std::vector<std::array<double,3>>
			rCoords( )
			{
				/* stores the ideal points */
				std::vector<std::array<double,3>> coords;

				std::ifstream	file ( "output/coorddump.dat" );
				std::string		line;
				int				valuesRead;
				int				linesRead;

				valuesRead = linesRead = 0;

				/* read out the file **************************************************/
				while( getline( file,line ) ) {
					std::stringstream   linestream( line );
					std::string         value;

					valuesRead = 0;
					std::array<double,3> coord;
					while( getline( linestream, value, ',' ) ) {
							coord[ valuesRead++ ] = std::stod( value );

					}
					coords.push_back(coord);

					linesRead++;

				}

				return points;
				
			}
		};

		ANNOUNCE_SINGLE_OBJECTIVE_FUNCTION(WholeTomatoMkIII, soo::RealValuedObjectiveFunctionFactory);

	}
}
#endif