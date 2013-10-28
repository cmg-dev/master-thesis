#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "../include/PRPSEvolution.h"
#include "../include/PRPSEvolutionGeneralExceptions.h"
#include "../include/PRPSEvolutionFIOExceptions.h"
#include <complex>
#include <array>
#include <random>
#include <algorithm>
#include "normalizer.h"

namespace PRPSEvolution {


	const double pi = 3.14159;
	/**
	 * 
	 */
	template<std::size_t N, typename T>
	std::array<T, N>
	Normalizer<N,T>::complexNorm
	( const std::array<T,N> &p, const std::array<T,N> &a )
	{
		std::array<std::complex<T>, N>  C;
		std::array<T, N> res;

		const T SCALING_FAKTOR = 2.7;
// 		const double pi = 3.14159;

		int i = 0;
		for(auto & c: C ) {
			if( p[i] != DATA_NV || a[i] != DATA_NV ) {
				c = std::complex<T> (p[i],a[i]*SCALING_FAKTOR);
				res[i] = arg( c );

				if(( p[i] < 0 && a[i] < 0 ) || ( p[i] > 0 && a[i] < 0 ))
					res[i] += 2*pi;

			} else {
				res[i]=(T) DATA_NV;

			}
			i++;
			/* ? scale to [0, 2\pi] ?*/

		}

		return res;
	}

	/**
	 * 
	 */
	template<std::size_t N, typename T>
	std::array<T, N>
	Normalizer<N,T>::randNorm( )
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

	/*
	 * 
	 */
	std::vector<std::array<double,3>>
	rPoints( )
	{
		/* stores the ideal points */
		std::vector<std::array<double,3>> points;

		std::ifstream	file ( "input/idealPoints.dat" );
		std::string		line;
		int				valuesRead;
		int				linesRead;

		valuesRead = linesRead = 0;

		/* read out the file **************************************************/
		while( getline( file,line ) ) {
			std::stringstream   linestream( line );
			std::string         value;

			valuesRead = 0;
			std::array<double,3> point;
			
			while( getline( linestream, value, '	' ) ) {
					point[ 0 ] = ( valuesRead == 0 ) ? std::stod( value ):( point[ 0 ] ) ;
					point[ 1 ] = ( valuesRead == 1 ) ? std::stod( value ):( point[ 1 ] ) ;
					point[ 2 ] = ( valuesRead == 2 ) ? std::stod( value ):( point[ 2 ] ) ;
					valuesRead++;

			}
			points.push_back(point);

			linesRead++;

		}

		std::cout << "**** ideal points" << std::endl;
		for( auto p : points ) {
			std::cout << "\t";
			for( auto c : p ) {
				std::cout << c << " ";
			}
			std::cout  << std::endl;
		}
		std::cout  << std::endl;
		
		return points;
		
	}

	/*
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
		/* check the input */

		std::cout << "**** ideal coords" << std::endl;
		for( auto p : coords ) {
			std::cout << "\t";
			for( auto c : p ) {
				std::cout << c << " ";
			}
			std::cout  << std::endl;
		}
		std::cout  << std::endl;
		
		return coords;
		
	}
	
	/**
	 * 
	 */
	template<std::size_t N, typename T>
	std::array<T, N>
	idealPhaseFromInput
	(
		std::vector<std::array<double,3>> p,
		std::vector<std::array<double,3>> c,
		int SELECT_IDEAL_POINT,
		double LAMBDA
	)
	{
		std::array<T, N>				ret;
		/* distance to tag */
		std::vector<std::array<T, N>>	thetas;

		int j = 0;
		/* calculate all ideal points */
		for( auto point : p ) {
			std::array<T, N> theta;
			int i = 0;
			for( auto coord : c ) {
				double d = std::sqrt (
						  ( coord[0]-point[0] ) * ( coord[0]-point[0] )
						+ ( coord[1]-point[1] ) * ( coord[1]-point[1] )
						+ ( coord[2]-point[2] ) * ( coord[2]-point[2] )
					);

				int n = std::floor( (d)/(LAMBDA/2) );
				
				double phase = (2*d)/(LAMBDA)-n;

				double d_test = (LAMBDA/2)*(phase+n);
// 				std::cout << "[" << j << "," << i << "] d_test-d= "
// 						<< ( d_test - d ) << std::endl;
				
				phase *= 2*pi;

				theta[i++] = phase;
				
			}
// 			j++;
			thetas.push_back( theta );
			
		}

// 		ret[1] = 65535;
// 		ret[6] = 65535;
		
		/* select the thetas from one point */
		if( SELECT_IDEAL_POINT > thetas.size() || SELECT_IDEAL_POINT < 0 )
			return ret;

		return thetas[SELECT_IDEAL_POINT];

	}

	/**
	 * 
	 */
	template<std::size_t N, typename T>
	std::array<T, N>
	Normalizer<N,T>::idealNorm( )
	{
		auto points = rPoints();
		auto coords = rCoords();

		std::cout << "using ideal norm" << std::endl;
		
		auto ret = idealPhaseFromInput<N,T>( points, coords, SELECT_IDEAL_POINT, LAMBDA );

		return ret;
	}
	
	/**
	 *
	 */
	template<std::size_t N, typename T>
	std::array<T, N> Normalizer<N,T>::normalize
	( std::array<T,N> phase,
		std::array<T,N> amp )
	{
		std::array<T, N> ret;


		switch( Method ) {
			case (int) NormalizationMethods::Native:
				ret = phase;

				break;

			case (int) NormalizationMethods::Ideal:
				ret = idealNorm( );
				break;

			case (int) NormalizationMethods::Complex:
			case (int) NormalizationMethods::CMPLX:
				ret = complexNorm( phase, amp );
				break;

			case (int) NormalizationMethods::RND:
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
			throw PRPSEvolution::Exceptions::FileIO::OutputFailure();

		}

		return ret;

	}

	template<std::size_t N, typename T>
	void
	Normalizer<N,T>::setSelectIdealPoint( int i )
	{
		SELECT_IDEAL_POINT = i;
	
	}

	template<std::size_t N, typename T>
	void
	Normalizer<N,T>::setLambda( double l )
	{
		LAMBDA = l;
	
	}
	
	/** An instance for 8 antennas represented by double values */
	template class Normalizer<8,double>;

	/* template function */
	template std::array<double, 8> idealPhaseFromInput(
		std::vector<std::array<double,3>> p,
		std::vector<std::array<double,3>> c,
		int SELECT_IDEAL_POINT,
		double LAMBDA );
	
}