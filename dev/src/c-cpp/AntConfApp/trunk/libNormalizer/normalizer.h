/**
 * @file normalizer.h
 * Collects normalizations for the input data
 *
 */
#ifndef __LIB_NORMALIZE_H
	#define __LIB_NORMALIZE_H

namespace PRPSEvolution {
	/**
	 * 
	 */
	enum NormalizatioMethodes {
		Native, B, CMPLX, RND
		
	};

	/**
	 * 
	 */
	template<std::size_t N, typename T>
	struct Normalizer {

		NormalizatioMethodes Method;

		/** Constructor
		 * @param[in] method Selects the Normalization function
		 * 
		 */
		Normalizer( NormalizatioMethodes method ): Method( method ) { };

		std::array<T, N> complexNorm( const std::array<T,N> &p,
									const std::array<T,N> &a );

		/**
		 */
		std::array<T, N> randNorm( );

		
		/**
		 * Calculates the normalizations
		 * @param[in] phase The measured phase data
		 * @param[in] amp The measured amplitude data
		 * 
		 */
		std::array<T, N> normalize( std::array<T,N> phase,
									std::array<T,N> amp );

	};

}
#endif /* !___LIB_NORMALIZE_H */
