
#include <cstddef>

#ifndef _COORDS_H_
#define _COORDS_H_

namespace PRPSEvolution {
	namespace Positioning {
		/**
		*
		*/
		template < std::size_t N, typename T >
		struct CoordContainer {
			/* store the x,y,z values */
			T x_[N], y_[N], z_[N];

			/* set x-y-z to the initial value */
		// 	template< typename T1>
			CoordContainer( );

			typedef T value_type;
			
			template < typename T1 >
			CoordContainer( T1 init );

			T& operator[](std::size_t i);
// 			void setCoordinates(T _X, T _Y, T _Z );
			
		};

		/**
		 *
		 */
		template < std::size_t N, typename T >
		template < typename T1 >
		CoordContainer< N,T >::CoordContainer( T1 init ) {
			for( int i = 0; i < N; i++ ) {
				x_[i] = y_[i] = z_[i] = init;

			}
		}
		/**
		 *
		 */
		template < std::size_t N, typename T >
		CoordContainer< N,T >::CoordContainer( ) {
			for( int i = 0; i < N; i++ ) {
				x_[i] = y_[i] = z_[i] = (T) 0.0;

			}
		}
		/**
		 *
		 */
		template < std::size_t N, typename T >
		T& CoordContainer< N, T >::operator[](std::size_t i){
			return x_[i % N];

		}
	}
}

#endif /* !_COORDS_H_ */