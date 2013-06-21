#ifndef _CALIB_H_
#define _CALIB_H_

namespace PRPSEvolution {
	namespace Calibration {
		/**
		* This will perform the calibration stuff
		*
		*/
		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		struct performCalibration {
			/* We store the x-y-z-coords the calibration gave us in this container, the numbering matches the real antenna numbering */
			Positioning::CoordContainer< N_ANTA, T > coordinates;
	
			/* the matrices of the popssible combinations */
			NRmatrix<Doub> A;

			/* store the distances for every calibration point belonging to every antenna */
			std::array< std::array< T , N_CALPOS >, N_ANTA > distances;

			int rMeasuredDistances();

			performCalibration();

			void dumpCoordsToFile();

		};

		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		performCalibration<N_ANTA,N_CALPOS,T>::performCalibration ()
		{

			
		}

		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		int performCalibration<N_ANTA,N_CALPOS,T>::rMeasuredDistances()
		{

			
		}

		template < std::size_t N_ANTA, std::size_t N_CALPOS, typename T >
		void performCalibration<N_ANTA,N_CALPOS,T>::dumpCoordsToFile()
		{

			
		}
	}
}
#endif /* !_CALIB_H_ */