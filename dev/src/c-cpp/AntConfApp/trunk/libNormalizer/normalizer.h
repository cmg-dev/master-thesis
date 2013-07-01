/**
 * @file normalizer.h
 * Collects normalizations for the input data
 * 
 */
#ifndef __LIB_NORMALIZE_H
	#define __LIB_NORMALIZE_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// #include "../include/PRPSEvolutionGeneralExeptions.h"
#include "../include/PRPSEvolutionFIOExeptions.h"
#include <complex>
#include <array>

namespace PRPSEvolution {
	/**
	 * 
	 */
	enum NormalizatioMethodes {
		A, B, CMPLX
		
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
									const std::array<T,N> &a )
		{
			std::array<complex<T>, N>  C;
			std::array<T, N> res;

			T SCALING_FAKTOR = 2.7;

			int i = 0;
			for(auto & c: C ) {
				c = complex<T> (p[i],a[i]*SCALING_FAKTOR);
				res[i++] = arg( c );
				/* ? scale to [0, 2\pi] ?*/
				
			}

// 			for( auto & r: res )
// 				std::cout << r << " ";
// 			std:cout << std::endl;


			return res;
		}
		
		/**
		 * Calculates the normalizations
		 * @param[in] phase The measured phase data
		 * @param[in] amp The measured amplitude data
		 * 
		 */
		std::array<T, N> normalize( std::array<T,N> phase,
									std::array<T,N> amp ) {

			std::array<T, N> ret;

			switch( Method ) {
				case (int) NormalizatioMethodes::A:
					break;

				case (int) NormalizatioMethodes::B:
					break;

				case (int) NormalizatioMethodes::CMPLX:
					ret = complexNorm( phase, amp );
					break;
				
			}
			
			return ret;
		
		}
		

	};

}
#endif /* !___LIB_NORMALIZE_H */
