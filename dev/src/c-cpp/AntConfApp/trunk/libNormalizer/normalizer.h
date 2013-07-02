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
#include "../include/PRPSEvolutionGeneralExceptions.h"
#include "../include/PRPSEvolutionFIOExceptions.h"
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
				if( p[i] != DATA_NV || a[i] != DATA_NV ) {
					c = complex<T> (p[i],a[i]*SCALING_FAKTOR);
					res[i] = arg( c );
					
				} else {
					res[i]=(T) DATA_NV;
					
				}
				i++;
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

			std::ofstream f;
			f.open("output/normalizedThetas.dat");
			if ( f.is_open() ) {
				for( int i = 0; i < ret.size(); ) {
					f << ret[i];
					if( ++i < ret.size() ) f << std::endl;

				}
				f << std::endl;
				f.close();

			} else {
				throw PRPSEvolution::Exceptions::FileIO::OutputExeption;

			}
			
			return ret;
		
		}
		

	};

}
#endif /* !___LIB_NORMALIZE_H */
