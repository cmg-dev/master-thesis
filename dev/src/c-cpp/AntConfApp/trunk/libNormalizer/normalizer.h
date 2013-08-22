/**
 * @file normalizer.h
 * Contains tne 'Normalizer' class that is able to perform the normalization of input data.
 * Also implements different methods of normalization, such as:
 * -Random
 * -Complex
 * -Ideal
 * -Native
 *
 */
#ifndef __LIB_NORMALIZE_H
	#define __LIB_NORMALIZE_H

namespace PRPSEvolution {
	
	/**
	 * Defines the methodes availiable for normalization
	 * 
	 */
	enum NormalizationMethods {
		Native, Ideal, CMPLX, RND, Complex
		
	};

	/**
	 * This class can perform the normalization of the input data
	 * 
	 */
	template<std::size_t N, typename T>
	struct Normalizer {

		/**
		 * Constructor
		 * @param[in] method Selects the Normalization function
		 * 
		 */
		Normalizer( NormalizationMethods method ): Method( method ) { };

		/**
		 * Calculates the normalizations
		 * @param[in] phase The measured phase data
		 * @param[in] amp The measured amplitude data
		 * @return Array containing the normalized values.
		 *
		 */
		std::array<T, N> normalize( std::array<T,N> phase,
									std::array<T,N> amp );

		/**
		 *
		 */
		void setSelectIdealPoint( int i );

		/**
		 *
		 */
		void setLambda( double l );
		
	private:
		/** Stores the selected normalization method */
		NormalizationMethods	Method;
		int						SELECT_IDEAL_POINT;
		double					LAMBDA;

		/**
		 * Computes the complex norm for the given combination of phase an amplitude data.
		 * @param[in] p Array containing the measured phase
		 * @param[in] a Array containing the measured amplitude
		 * @return Array containing the normalized values.
		 * 
		 */
		std::array<T, N> complexNorm( const std::array<T,N> &p,
									const std::array<T,N> &a );

		/**
		 * Creates a random norm for the input
		 * @return Array containing the normalized values.
		 * 
		 */
		std::array<T, N> randNorm( );

		/**
		 * Reads in the input/idealPoints.dat and computes the ideal phase values.
		 * The result is stored into: output/ideal.dat
		 * @return Array containing the normalized values.
		 *
		 */
		std::array<T, N> idealNorm( );
		
	};

}
#endif /* !___LIB_NORMALIZE_H */
