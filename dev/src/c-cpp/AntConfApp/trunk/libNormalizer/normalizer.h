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
#include <random>
// #include <algorithm>

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
									const std::array<T,N> &a )
		{
			std::array<complex<T>, N>  C;
			std::array<T, N> res;

			const T SCALING_FAKTOR = 2.7;
			const double pi = 3.14159;
			
			int i = 0;
			for(auto & c: C ) {
				if( p[i] != DATA_NV || a[i] != DATA_NV ) {
					c = complex<T> (p[i],a[i]*SCALING_FAKTOR);
					res[i] = arg( c );

					if(( p[i] < 0 && a[i] < 0 ) || ( p[i] > 0 && a[i] < 0 ))
						res[i] += 2*pi;
						
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
		 */
		std::array<T, N> randNorm( )
		{
			std::array<T, N> ret;
			
			std::default_random_engine dre;
			std::uniform_real_distribution<double> dr(-10.0,10);

			for( auto &r: ret )
				r = dr(dre);

			ret[1] = 65535;
			ret[6] = 65535;
			return ret;
			
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
				case (int) NormalizatioMethodes::Native:
					ret = phase;
					
					break;

				case (int) NormalizatioMethodes::B:
					break;

				case (int) NormalizatioMethodes::CMPLX:
					ret = complexNorm( phase, amp );
					break;

				case (int) NormalizatioMethodes::RND:
					ret = randNorm( );
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
// 				return -1;
// 				throw PRPSEvolution::Exceptions::FileIO::OutputExeption;

			}
			
			return ret;
		
		}
		

	};

}
#endif /* !___LIB_NORMALIZE_H */
