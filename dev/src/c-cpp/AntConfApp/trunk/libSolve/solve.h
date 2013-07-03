/**
 * @file solve.h
 * @date 2013|Jun|25
 *
 *
 */
#ifndef __LIB_SOLVE_H
	#define __LIB_SOLVE_H

#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <random>

#include "../include/coords.h"
#include "../include/PRPSEvolution.h"
#include "../include/PRPSEvolutionSolveExceptions.h"
#include "../include/PRPSEvolutionFIOExceptions.h"
#include "../include/PRPSEvolutionGeneralExceptions.h"

#include "../include/PRPSError.h"
#include "../libPermutate/permutate.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"
#include "../libNormalizer/normalizer.h"

#include "nr3/nr3.h"
#include "nr3/svd.h"

#include <EALib/ChromosomeCMA.h>
#include <SharkDefs.h>
#include <EALib/PopulationT.h>
#include <EALib/ObjectiveFunction.h>

namespace PRPSEvolution {
	namespace Solve {

		using namespace PRPSEvolution::Permutate;
		using namespace std;
		
		using std::chrono::duration_cast;
		using std::chrono::microseconds;
		using std::chrono::milliseconds;
		using std::chrono::steady_clock;

		/*******************************************************************/
		/* Enums ***********************************************************/
		/*******************************************************************/

		/**
		 * Represents the selection method for the Matrix A that will be used
		 * for the solution
		 * 
		 */
		enum SelectBy {
			ConditionNumber, Random, AllPossible

		};

		/**
		 * Represents the ES-strategy to find a solution
		 * 
		 */
		enum ESStrategy {
			OnePlusOne,		/**< @f[[1+1]-ES@f]*/
			MuPlusLambda,	/**< @f[[\mu+\lambda]-ES@f]*/
			MuCommaLambda	/**< @f[[\mu,\lambda]-ES@f]*/

		};

		
		/******************************************************************/
		/* Classes and so. ************************************************/
		/******************************************************************/

		/**
		 * Collect the fitness functions.
		 * Make sure they are static so we can function-pointer to them.
		 *
		 */
		template < typename T >
		struct Ueber9000
		{
			double (Ueber9000<double>::*evaluate)( const ChromosomeT< double >& );

			/**/
			NRmatrix< T > A;
			/**/
			NRvector< T > c_k0;

			/**
			 * Default constructor
			 */
			Ueber9000( ) : evaluate( &Ueber9000<double>::fitnessSphere ) { };

			/**
			 *
			 */
			Ueber9000(const Ueber9000 &me) : A(me.A), c_k0(me-c_k0) {
				if( A && c_k0 )
					evaluate = &WholeTomatoeApproach;

			}

			/**
			 * Construct Ueber9000 to use the WholeTomatoeApproach as fitness function
			 * @param[in] A_selected The matrix A for this Solution
			 * @param[in] c_k0_selected The vector c_k0 for this Solution
			 *
			 */
			Ueber9000( const NRmatrix< T > A_selected,
					   const NRvector< T > c_k0_selected ) : A( A_selected ), c_k0( c_k0_selected ) {

				/* the WholeTomatoeApproach is the model of choice if A_selected and c_k0_selected are given */
				evaluate = &Ueber9000<double>::WholeTomatoeApproach;

			}

			/**
			 * This method basically wraps around the real WholeTomatoeApproach-function.
			 * Maps the function so that it can be used with the evaluate-method
			 * @param[in] x The vector x
			 * 
			 */
			double
			WholeTomatoeApproach( const ChromosomeT< double > &x )
			{
				double res;

				/* call function */
				res = WholeTomatoeApproach( A, x, c_k0 );

				return res;

			}

			/**
			 * This approach will solve calculate the 10x3 matrix described
			 * in the Master-Thesis of C.Gnip
			 * Basically solves the linear equation @f[r=\mathbf{Ax}-\mathbf{b}@f]
			 * @param[in] A The 10x3 Matrix that ist used in this solution
			 * @param[in] x The vector containing the variables
			 * @param[in] c_k0 Representing the vector b
			 * @return The residuum of the equation system representing the "Fitness" of the given Solution in @see x
			 *
			 */
			inline double WholeTomatoeApproach( const NRmatrix<T> &A, const ChromosomeT< double > &x, const NRvector<T> &c_k0 )
			{
				double res;
				double prod_Ax[3];

				for( int i = 0; i < A.nrows(); i++ )
					for( int j = 0; j < A.ncols(); j++ )
						prod_Ax[i] += A[i][j]*x[j];

				/* multiply the matrix with the vector */
				/* sum up */
				res = (prod_Ax[0] - c_k0[0]) * (prod_Ax[0] - c_k0[0]);
				res += (prod_Ax[1] - c_k0[1]) * (prod_Ax[1] - c_k0[1]);
				res += (prod_Ax[2] - c_k0[2]) * (prod_Ax[2] - c_k0[2]);

				return res;

			}

			/***************************************************************/
			/***************************************************************/
			/***************************************************************/
			/**
			 * Approach 2 based on the thoughts of S. Winter.
			 * Here we want to optimize the wavenumbers
			 *
			 */
			double WavenumberVariation( const ChromosomeT< double > &n )
			{
				throw "Not implemented exeption";

			}

			/**
			 * Approach 3 based on the thoughts of by S. Winter
			 *
			 */
			double PositionVariation( const ChromosomeT< double > &pos )
			{
				throw "Not implemented exeption";

			}

			/**
			 * This ist the fitness function used in the EA algorithm
			 *
			 */
			double fitnessSphere( const ChromosomeT<double> &c )
			{
				double sum = Shark::sqr(c[0]);
				for(unsigned i=1; i<c.size(); i++) sum += Shark::sqr(c[i]);
				return sum;

			}

			/**
			 * The Rosenbrock implementation
			 *
			 */
			double fitnessRosenbrock( const ChromosomeT<double> &c )
			{
				double sum = 0.;

				for(unsigned i=0; i<c.size(); i++) {
					sum += ( 100 * Shark::sqr( c[i+1] - Shark::sqr(c[i]) )
								+ Shark::sqr(c[i]-1));

				}

				return sum;

			}

			/**
			 * The infamous Ackley-function
			 *
			 */
			double fitnessAckley( const std::vector< double >& x )
			{
				const double A = 20.;
				const double B = 0.2;
				const double C = M_2PI;

				unsigned i, n;
				double   a, b;

				for (a = b = 0., i = 0, n = x.size(); i < n; ++i) {
					a += x[ i ] * x[ i ];
					b += cos(C * x[ i ]);
				}

				return -A * exp(-B * sqrt(a / n)) - exp(b / n) + A + M_E;
			}

		};

		const int nConfigsForProcessing = 1;
			
		/*******************************************************************/
		/* PreProcessing Class *********************************************/
		/*******************************************************************/
		
		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
		class PreProcessing
		{
		/*******************************************************************/
		/*******************************************************************/
		/*******************************************************************/
		public:
			/** determines how many Configurations will solved for the Wavenumber */

			std::vector<NRmatrix<T>> matricesForSolution;

			std::vector<NRvector<T>> vectorsForSolution;
				
			PreProcessing
				( const std::array< AntennaPermutations< Permutate::MAX_PERMUTATION_AMOUNT, Doub >, N_ANTA> &, const NRmatrix<T> & );

		private:
			/** the container for the Phase data */
			std::array<T_Measure,N_ANTA> measuredPhase;
			
			/** the container for the Amp data */
			std::array<T_Measure,N_ANTA> measuredAmp;
			
			/** the container for the precalculated matrices */
			const std::array< AntennaPermutations< Permutate::MAX_PERMUTATION_AMOUNT, Doub >, N_ANTA>
					*precalculatedMats;

			/***************************************************************/
			/***************************************************************/
			/***************************************************************/
			/**
			 * Read in the measurements from a file
			 */
			int rMeasurementsFromFile( );

			/**
			 */
			std::array<T, N_ANTA> normalizeThetas( const std::array<T_Measure,N_ANTA> &, const std::array<T_Measure,N_ANTA> & );

			/**
			 */
			int selectReferenceAntennaForProcessing( PRPSEvolution::Solve::SelectBy );

			/**
			 */
			std::vector<NRmatrix< T >> selectAllPossible( const std::vector< std::string > & );
		
			/**
			 * This will select the matrices for the Processing and will return the array filed with them
			 * @param[in] method The selection Method
			 *
			 */
			std::vector<NRmatrix<T>>
				selectMatsForProcessing( PRPSEvolution::Solve::SelectBy, const std::vector< std::string > & );

			/**
			 * 
			 */
			std::vector<NRmatrix<T>>
				fillSelectMats( const std::array<T_Measure,N_ANTA> &, const std::vector<NRmatrix<T>> &, const std::vector<std::string> & );

			/**
			 * 
			 */
			std::vector<NRvector<T>>
// std::array<NRvector<T>, N_Configs>
				calcVectors( const std::vector<std::string> &, const std::array<T_Measure,N_ANTA> &, const NRmatrix<T> &, const T &);

			/**
			 * 
			 */
			std::vector<std::string> getPossibleNames( );
			
		};

		/******************************************************************/
		/* PreProcessing Function implementation **************************/
		/******************************************************************/
		/**
		 * Construct the object an perform neccessary PreProcessing steps.
		 * -# Read out the measurements from the given interface (e.g. a file)
		 * -# Normalize everything
		 * -# Select the matrices for further processing
		 * -# Fill the matrices with the information
		 * -# Precalculate the @f[c_{k0}@f]-Vector
		 * -# Store matrices to make them availiable in the next steps
		 *
		 */
		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::PreProcessing
		( const std::array< AntennaPermutations< Permutate::MAX_PERMUTATION_AMOUNT, Doub >, N_ANTA> &precalculatedMatrices, const NRmatrix<T> & d_k0s )
		{
			/***************************************************************/
			std::cout << "PreProcessing::Entering Construct()" << std::endl;

			/* latch in the matrices */
			precalculatedMats = &precalculatedMatrices;

			std::cout << "PreProcessing::Read from file.. .. ";
			rMeasurementsFromFile( );
			
			std::cout << " done" << std::endl;

			/***************************************************************/
			std::cout << "PreProcessing::normalization in process.. .. ";

			auto normThetas = normalizeThetas( measuredPhase, measuredAmp );
			
			std::cout << " done" << std::endl;

			/* identify the possible matrices by their names */
			/***************************************************************/
			std::cout << "PreProcessing::Identifying possible matrices.. .. ";

			auto Names = getPossibleNames( );
			std::cout << "done" << std::endl;

			/***************************************************************/
			std::cout << "PreProcessing::Selecting matrices.. .. ";
			auto selectedConfs = selectMatsForProcessing( SelectBy::AllPossible, Names );
			
			std::cout << " done" << std::endl;


			T a_1;
			{	/*
				 * workaround:
				 * a_1 can be found in the matrix so we do not have to pass
				 * it to the function seperately
				 */
				auto p = selectedConfs[0];
				a_1 = p[0][3];

// 				std::cout << "a_1" << a_1 << std::endl;
			}/* !workaround */

			
			/***************************************************************/
			std::cout << "PreProcessing:: Filling selected matrices with remaining information.. ..";
			selectedConfs = fillSelectMats( normThetas, selectedConfs, Names );

			std::cout << " done" << std::endl;

			/***************************************************************/
			std::cout << "PreProcessing::Calculate vectors.. ..";
			auto vectors = calcVectors( Names, normThetas, d_k0s, a_1 );

			std::cout << " done" << std::endl;

			
			/***************************************************************/
			vectorsForSolution = vectors;
			matricesForSolution = selectedConfs;
			
		}

		/**
		 * Read the measurements from file
		 *
		 */
		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
		int PreProcessing<N_ANTA,N_Configs,T,T_Measure>::rMeasurementsFromFile()
		{
			std::ifstream	file ( "data/Measurements.dat" );
			std::string		line;
			int				valuesRead;
			int				linesRead;

			valuesRead = linesRead = 0;

			/* simply fill with 0 */
			for( int i = 0; i < N_ANTA; i++ ) {
				measuredPhase[ i ] = (T_Measure) 0.0;
				measuredAmp[ i ] = (T_Measure) 0.0;
			}

			/* read out the file **************************************************/
			while( getline( file,line ) ) {
				std::stringstream   linestream( line );
				std::string         value;

				valuesRead = 0;
				while( getline( linestream, value, ',' ) ) {
						measuredPhase[ linesRead ] = ( valuesRead == 0 ) ? std::stod( value ):( measuredPhase[ linesRead ] ) ;
						measuredAmp[ linesRead ] = ( valuesRead == 1 ) ? std::stod( value ):( measuredAmp[ linesRead ] ) ;
					
						valuesRead++;
				}
				/* a line is read */
				if( valuesRead != (int) PRPSEvolution::EXPECTED_VALUES_MEASUREMENT_FILE )
					throw PRPSEvolution::Exceptions::FileIO::MalformedInputExeption;

				linesRead++;

			}
			/* check the input */
			if( linesRead != PRPSEvolution::EXPECTED_LINES_MEASUREMENT_FILE )
				throw PRPSEvolution::Exceptions::FileIO::MalformedInputExeption;

			/* dump everything to std::cout  */
// 			std::cout << "** PreProcessing:: I've read the following values: " << std::endl;
// 			std::cout << "Idx Phase" << " | "<< "Amp" << std::endl;
// 			for( int i = 0; i < measuredPhase.size(); i++ ) {
// 				std::cout << i
// 					<< " " << measuredPhase[ i ]
// 					<< " | " << measuredAmp[ i ]
// 					<< std::endl;
// 
// 			}

			return PRPSError::okay;
			
		}

		/**
		 * Perform the normalization of the input data.
		 * Scale it down to match the interval of @f[[0,2\pi]@f]
		 * @param[in] phase The measured phase data
		 * @param[in] amp The measured ampliture data
		 * @return The normailzed values for @f[ \Theta_k @f]
		 *
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::array<T, N_ANTA> PreProcessing<N_ANTA,N_Configs,T,T_Measure>::normalizeThetas
		( const std::array<T_Measure,N_ANTA> &phase, const std::array<T_Measure,N_ANTA> &amp )
		{
			Normalizer<N_ANTA, T> normalizer( PRPSEvolution::NormalizatioMethodes::CMPLX );

			auto ret = normalizer.normalize( phase, amp );

			return ret;

		}

		/**
		 * This method will select matrices for the real processing from the
		 * quantity of possible matrices. Possible matrices are the ones
		 * where the participation antennas delivered valid data.
		 * @param[in] method The selection method @see PRPSEvolution::Solve::SelectBy
		 * @return A std::vector containing the selected Matrices
		 *
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::vector<NRmatrix< T >>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::selectMatsForProcessing
		( PRPSEvolution::Solve::SelectBy method, const std::vector< std::string > &names)
		{
			std::vector<NRmatrix< T >> SelectedMat;

			switch( method ) {
				case (int) SelectBy::ConditionNumber:
					throw Exceptions::General::NotImplemented();
					break;
					
				case (int) SelectBy::Random:
					throw Exceptions::General::NotImplemented();
					break;

				case (int) SelectBy::AllPossible:
// 					std::cout << " Selecting All possible Matrices for a Solution" << std::endl;
					SelectedMat = selectAllPossible( names );
// 					std::cout << " Selecting All possible Matrices for a Solution" << std::endl;
					
					break;
				
			}

			/* send the selected ones to std::cout */
// 			int i = 0;
// 			for( auto mat : SelectedMat ) {
// 				std::cout << ++i << " " << names[i] << std::endl;
// 				Permutate::AntennaPermutations<0,Doub>::dump_matrix( mat );
// 
// 			}
			
			return SelectedMat;
			
		}

		/**
		 * Search through all availiable matrices and crawl out the needed ones
		 * @param[in] names The "names" of the correect matrices
		 * 
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::vector<NRmatrix< T >>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::selectAllPossible( const std::vector< std::string > &names )
		{
			std::vector<NRmatrix< T >> ret;

			int j = 0;
			for( auto p : *precalculatedMats ) {
				for( int i = 0; i < p.mat.size(); i++ ) {
					if( p.names[i] == names[j] )  {
						
						ret.push_back( p.mat[i] );
						if( j++ >= names.size() )
							break;
						
					}
					if( j >= names.size() )
							break;
					
				}
			}

			return ret;
		}
		
		/**
		 * Compute the names of the possible antennas
		 * @param[in] NoAvailiable
		 * @param[in] GroupSize
		 *
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::vector<std::string> PreProcessing<N_ANTA,N_Configs,T,T_Measure>::getPossibleNames( )
		{
			
			/* witch antennas delivered data ? */
			std::array<bool,N_ANTA> data;
			for( int i = 0; i < data.size(); i++ ) {
				data[i] = (measuredAmp[i]==(T)DATA_NV||measuredPhase[i]==(T)DATA_NV)?false:true;

			}

			int i = 0, j = 0;

			ostringstream os;
			/* possible permutations? */
			for( auto d : data ) {
				if( d ) { os << i++; j++; }
				else { i++; }
			}

			const std::size_t NoAvailiable = j;
			const std::size_t GroupSize = DEFAULT_MIN_GROUP_SIZE;
			
// 			std::cout << os.str() << " " << j << std::endl;
			
			int possiblePA = Permutate::Factorial( NoAvailiable - 1 );
			possiblePA /=
				(Permutate::Factorial( GroupSize-1 )
				* Permutate::Factorial( (NoAvailiable - 1) - (GroupSize -1) ) );

// 			std::cout << os.str() << " " << j << std::endl;
				
			int totalPossible = possiblePA * NoAvailiable;

// 			std::cerr << "possible " << possiblePA << std::endl;
// 			std::string s = os.str();
			
			std::vector< std::string > NamesPossible;

			std::size_t k = GroupSize - 1;
			i = 0;

			for( int l = 0; l < NoAvailiable; l++ ) {
				std::string s_ = os.str().erase( l, 1 );
				const char ref = os.str()[l];
// 				std::cout << s_ << std::endl;
				do {
					i++;
					/* create the name */
					ostringstream name;
					name << ref << std::string( s_.begin(),s_.begin() + k );

					NamesPossible.push_back(name.str());

				} while( Permutate::next_combination( s_.begin(),s_.begin() + k,s_.end() ) );
			}

			/* print the "names" of the possible matrices */
// 			std::cout << Names.size() << std::endl;
// 			for( int i = 0; i < Names.size(); i++ )
// 				std::cout << Names[i] << std::endl;

			return NamesPossible;
			
		}

		/**
		 * Fill in the remaining information before we can process any further
		 * @param[in] normThetas The normalized thetas from previous calculation
		 * @param[in] matrices The matrices we selected
		 *
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::vector<NRmatrix<T>>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::fillSelectMats
		( const std::array<T_Measure,N_ANTA> &normThetas, const std::vector<NRmatrix<T>> &matrices, const std::vector<std::string> &names )
		{
			std::vector<NRmatrix<T>> mats2return( matrices );

			std::array<T_Measure,4> thetas;
			int idx = 0;

// 			for( int j = 0; j < names[0].size(); j++ )
// 				std::cout << names[0][j];
// 			std::cout << std::endl;

			/* for each matrix */
			for( auto &mat: mats2return ) {
				
				auto name = names[idx];

				/* find ref antenna */
				std::array<int,4> antennas = { std::stoi( name.substr(0,1)),
												std::stoi( name.substr(1,1)),
												std::stoi( name.substr(2,1)),
												std::stoi( name.substr(3,1))
												};

				/* get the thetas */
				std::array<T_Measure,4> thetas = { normThetas[antennas[0]],
													normThetas[antennas[1]],
													normThetas[antennas[2]],
													normThetas[antennas[3]]
													};

				/* fill in the information */
				for( int i = 0; i < mat.nrows(); i++ ) {
					/* col 7 * ref antennas theta */
					mat[i][6] *= thetas[0];
						/* col 8-10 * the other antennas thetas */
					mat[i][7+i] *= thetas[i+1];

				}
				idx++;
			
			}

#ifdef SOLVE_DBG
			/* print to std::cout */
// 			for( auto &mat: mats2return ) {
// 				Permutate::AntennaPermutations<0,Doub>::dump_matrix( mat );
// 				
// 			}
#endif
			/*dump to file */
			std::ofstream f;
			f.open("output/finalmatdump.dat");

			if ( f.is_open() ) {
				int i = 0;
				for( auto& m : mats2return ) {
					f << names[i++] << std::endl;
					Permutate::AntennaPermutations<0,Doub>::dump_matrix_2_file( f, m );
				}
				f.close();

			} else {
				throw PRPSEvolution::Exceptions::FileIO::OutputExeption;

			}
			
			return mats2return;
		}

		/**
		 *
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::vector<NRvector<T>>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::calcVectors
		( const std::vector<std::string> &names, const std::array<T_Measure,N_ANTA> &normThetas, const NRmatrix<T> &d_k0s, const T &a_1 )
		{
			std::vector<NRvector<T>> ret;

			int idx = 0;

			const double pi = 3.14159;
			
			/* for each name find */
			for(auto name : names ) {
				/* find antennas */
				std::array<int,4> a = { std::stoi( name.substr(0,1) ),
												std::stoi( name.substr(1,1) ),
												std::stoi( name.substr(2,1) ),
												std::stoi( name.substr(3,1) )
												};

				NRvector<T> b;
				b.assign( 3, 0.0 );

				NRvector<T> a_0k;
				a_0k.assign( 3, 0.5 );

				NRvector<T> a_3k;
				a_3k.assign( 3, a_1 * (1/((2*pi)*(2*pi))) );

				/* the matrix is an upper triangle so we need the ? here */
				a_0k[0] *= (a[0] < a[1]) ? d_k0s[a[0]][a[1]]:d_k0s[a[1]][a[0]];
				a_0k[1] *= (a[0] < a[2]) ? d_k0s[a[0]][a[2]]:d_k0s[a[2]][a[0]];
				a_0k[2] *= (a[0] < a[3]) ? d_k0s[a[0]][a[3]]:d_k0s[a[3]][a[0]];

				a_3k[0] *= (normThetas[a[0]])*(normThetas[a[0]])
							- (normThetas[a[1]])*(normThetas[a[1]]);
							
				a_3k[1] *= (normThetas[a[0]])*(normThetas[a[0]])
							- (normThetas[a[2]])*(normThetas[a[2]]);
							
				a_3k[2] *= (normThetas[a[0]])*(normThetas[a[0]])
							- (normThetas[a[3]])*(normThetas[a[3]]);
				
				b[0]= a_0k[0];
				b[1]= a_0k[1];
				b[2]= a_0k[2];

				ret.push_back(b);
				
			}

			/***************************************************************/
			std::ofstream f;
			f.open("output/vector_b_dump.dat");
			if ( f.is_open() ) {
				for( auto b : ret )
						f << b[0] << "," << b[1] << "," << b[2] << std::endl;
				
				f.close();

			} else {
				throw PRPSEvolution::Exceptions::FileIO::OutputExeption;

			}


			return ret;
		}

		/******************************************************************/
		/* Process Class **************************************************/
		/******************************************************************/
		
		/**
		 * Find solutions for the possible matrices
		 *
		 */
		class Process
		{
		public:

			/** a Pointer to the object containing the fitness functions */
// 			Ueber9000<Doub> *ueber9000;
			/*	the strategy to find a solution */
			ESStrategy strategy;

			/* */
			
			/**
			 * Constructor

			 */
			Process(  ) {

			}

			Process(const Process &p) : strategy( p.strategy ), solutionFitness( p.solutionFitness ), minSolutionFitness( p.minSolutionFitness ) {
				
				
			}
			
			double getLastSolutionFitness() { return solutionFitness; }
			
			/**
			 * Set the ES-Strategy
			 * @param[in] Strategy The selected strategy
			 *
			 */
			void setESStrategy( ESStrategy Strategy ) {
				strategy = Strategy;
				
			}

			/**
			 * Find a Solution for a given pair of matrices
			 * @param[in] A_selected The matrix A to use in this solution
			 * @param[in] b_selected The c_k0' vector for this solution
			 * @return The solution
			 * 
			 */
			ChromosomeT<double> findSolution
			( const NRmatrix< Doub > &A_selected, const NRvector< Doub > &b_selected )
			{
				/* create a new instance of Ueber9000 */
				Ueber9000<Doub> ueber( A_selected, b_selected );
// 				Ueber9000<Doub> t;
// 				ueber9000 = &t;

				ChromosomeT<double> solution;
				
				switch( strategy ) {
					case (int) ESStrategy::OnePlusOne:
						solution = OnePlusOneES( &ueber );
						break;
						
                   case (int) ESStrategy::MuPlusLambda :
						solution = MuPlusLambdaES( &ueber );
						break;
						
					case (int) ESStrategy::MuCommaLambda:
						solution = MuCommaLambdaES( &ueber );
						break;
						
				}
				return solution;
				
			}

			int sq( int i ) {return i*i; }
			
			/**
			 * Sets the min. solution fitness we want to achieve.
			 * @param[in] value The new value for the solution fitness
			 * 
			 */
			void setMinSolutionFitness( double value ) { minSolutionFitness = value; }

			/**
			 * 
			 */
			void setSeed( unsigned int value ) { Rng::seed(value); }
			
		private:

			double solutionFitness;
			double minSolutionFitness;
			
			/* The strategies **********************************************/
			/** Enter description */
			ChromosomeT<double> OnePlusOneES( Ueber9000<double> *ueber9000 ) {
				// EA parameters
				const unsigned Dimension      = 10;
				const unsigned Iterations     = 3000;
				const double   MinInit        = -3.;
				const double   MaxInit        = 7.;
				const double   GlobalStepInit = 5.;

				ChromosomeCMA parent(Dimension),
								offspring(Dimension);

				double fitnessParent, fitnessOffspring;

				parent.init( Dimension, GlobalStepInit, MinInit, MaxInit );

				fitnessParent = (ueber9000->*ueber9000->evaluate)( parent );
				unsigned int t;
				// loop over generations
				for ( t = 0; t < Iterations; t++) {
					offspring = parent;
					offspring.mutate();

					fitnessOffspring =  (ueber9000->*ueber9000->evaluate)( offspring );

					bool success = ( fitnessOffspring < fitnessParent );

					if( success ) {
						offspring.updateCovariance();
						parent = offspring;
						fitnessParent = fitnessOffspring;
					}
					parent.updateGlobalStepsize( success );

					if( fitnessParent < minSolutionFitness )
						break;

				}
				solutionFitness = fitnessParent;
// 				std::cout << t << " Done \tFinal Fitness: " << fitnessParent << endl;
// 				for(unsigned i=0; i < Dimension; i++)
// 					std::cout << i << " " << parent[i] << " " ;

// 				std::cout << std::endl;

				return parent;
				
			}

			/** Enter description */
			ChromosomeT<double> MuCommaLambdaES( Ueber9000<double> *ueber9000 ) {

				const unsigned Mu           = 20;
				const unsigned Lambda       = 40;
				const unsigned Dimension    = 10;
				const unsigned Iterations   = 2000;
				const unsigned Interval     = 10;
				const unsigned NSigma       = 1;

				const double   GlobalStepInit = 5.;

				const double   MinInit        = -3.;
				const double   MaxInit        = 7.;
				const double   SigmaInit    = 3;

				/* activate elitist strategy */
				const bool     PlusStrategy = true;

				unsigned       i, t;

				// linear congruential generator
// 				std::mt19937 gen;

				// initialize the generator
// 				gen.seed((unsigned int)time(NULL));

				// define populations
				PopulationT<double> parents(Mu,     ChromosomeT< double >(Dimension),
								ChromosomeT< double >(NSigma));
				PopulationT<double> offsprings(Lambda, ChromosomeT< double >(Dimension),
									ChromosomeT< double >(NSigma));

				// minimization task
				parents.setMinimize();
				offsprings.setMinimize();

				// initialize parent population
				for (i = 0; i < parents.size(); ++i) {
					parents[ i ][ 0 ].initialize(MinInit,   MaxInit);
					parents[ i ][ 1 ].initialize(SigmaInit, SigmaInit);
				}

				// selection parameters (number of elitists)
				unsigned numElitists = PlusStrategy ? Mu : 0;

				// standard deviations for mutation of sigma
				double     tau0 = 1. / sqrt(2. * Dimension);
				double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));

				// evaluate parents (only needed for elitist strategy)
				if (PlusStrategy)
					for (i = 0; i < parents.size(); ++i)
						parents[ i ].setFitness((ueber9000->*ueber9000->evaluate)(parents[ i ][ 0 ]));

				std::vector<double> fitness;
				fitness.reserve(10);

				// iterate
				for (t = 0; t < Iterations; ++t) {
					// generate new offsprings
					for (i = 0; i < offsprings.size(); ++i) {
						// select two random parents
						Individual& mom = parents.random();
						Individual& dad = parents.random();

						// recombine object variables discrete, step sizes intermediate
						offsprings[ i ][ 0 ].recombineDiscrete(mom[ 0 ], dad[ 0 ]);
						offsprings[ i ][ 1 ].recombineGenIntermediate(mom[ 1 ], dad[ 1 ]);

						// mutate object variables normal distributed,
						// step sizes log normal distributed
						offsprings[ i ][ 1 ].mutateLogNormal(tau0,  tau1);
						offsprings[ i ][ 0 ].mutateNormal(offsprings[ i ][ 1 ], true);
					}

					// evaluate objective function (parameters in chromosome #0)
					for (i = 0; i < offsprings.size(); ++i)
						offsprings[ i ].setFitness((ueber9000->*ueber9000->evaluate)(offsprings[ i ][ 0 ]));

					// select (mu,lambda) or (mu+lambda)
					parents.selectMuLambda(offsprings, numElitists);

					// print out best value found so far
					if( parents.best().fitnessValue() < minSolutionFitness )
						break;

				}

				auto p = parents.best();

				solutionFitness = parents.best().fitnessValue();
// 				std::cout << t << " Done \tFinal Fitness: " << parents.best().fitnessValue() << endl;
/*
				for( int i = 0; i < 10; i++ )
					std::cout << i << " " << p[0][i] << " " ;
				std::cout << std::endl;*/

				return p[0];
				
			}

			/** Enter description */
			ChromosomeT<double> MuPlusLambdaES( Ueber9000<double> *ueber9000 ) {

				const unsigned Mu           = 5;
				const unsigned Lambda       = 10;
				const unsigned Dimension    = 10;
				const unsigned Iterations   = 2000;
				const unsigned Interval     = 10;
				const unsigned NSigma       = 1;

				const double   GlobalStepInit = 5.;


				const double   MinInit        = -3.;
				const double   MaxInit        = 7.;
				const double   SigmaInit    = 6;

				/* activate elitist strategy */
				const bool     PlusStrategy = true;

				unsigned       i, t;

				// initialize random number generator
// 				Rng::seed((unsigned int)time(NULL));

				// define populations
				PopulationT<double> parents(Mu,     ChromosomeT< double >(Dimension),
								ChromosomeT< double >(NSigma));
				PopulationT<double> offsprings(Lambda, ChromosomeT< double >(Dimension),
									ChromosomeT< double >(NSigma));

				// minimization task
				parents   .setMinimize();
				offsprings.setMinimize();

				// initialize parent population
				for (i = 0; i < parents.size(); ++i) {
					parents[ i ][ 0 ].initialize(MinInit,   MaxInit);
					parents[ i ][ 1 ].initialize(SigmaInit, SigmaInit);
				}

				// selection parameters (number of elitists)
				unsigned numElitists = PlusStrategy ? Mu : 0;

				// standard deviations for mutation of sigma
				double     tau0 = 1. / sqrt(2. * Dimension);
				double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));

				// evaluate parents (only needed for elitist strategy)
				if (PlusStrategy)
					for (i = 0; i < parents.size(); ++i)
						parents[ i ].setFitness((ueber9000->*ueber9000->evaluate)(parents[ i ][ 0 ]));

				std::vector<double> fitness;
				fitness.reserve(10);

				// iterate
				for (t = 0; t < Iterations; ++t) {
					// generate new offsprings
					for (i = 0; i < offsprings.size(); ++i) {
						// select two random parents
						Individual& mom = parents.random();
						Individual& dad = parents.random();

						// recombine object variables discrete, step sizes intermediate
						offsprings[ i ][ 0 ].recombineDiscrete(mom[ 0 ], dad[ 0 ]);
						offsprings[ i ][ 1 ].recombineGenIntermediate(mom[ 1 ], dad[ 1 ]);

						// mutate object variables normal distributed,
						// step sizes log normal distributed
						offsprings[ i ][ 1 ].mutateLogNormal(tau0,  tau1);
						offsprings[ i ][ 0 ].mutateNormal(offsprings[ i ][ 1 ], true);
					}

					// evaluate objective function (parameters in chromosome #0)
					for (i = 0; i < offsprings.size(); ++i)
						offsprings[ i ].setFitness((ueber9000->*ueber9000->evaluate)(offsprings[ i ][ 0 ]));

					// select (mu,lambda) or (mu+lambda)
					parents.selectMuLambda(offsprings, numElitists);

					// print out best value found so far
					if( parents.best().fitnessValue() < minSolutionFitness )
						break;
				}

				auto p = parents.best();
				solutionFitness = parents.best().fitnessValue();
				
// 				std::cout << t << " Done \tFinal Fitness: " << parents.best().fitnessValue() << endl;

// 				for( int i = 0; i < 10; i++ )
// 					std::cout << i << " " << p[0][i] << " " ;
// 				std::cout << std::endl;

				return p[0];
				
			}

			
// 			void Another( &ueber ) {
// 				const unsigned Mu           = 5;
// 				const unsigned Lambda       = 10;
// 				const unsigned Dimension    = 10;
// 				const unsigned Iterations   = 2000;
// 				const unsigned Interval     = 10;
// 				const unsigned NSigma       = 1;
// 
// 				const double   GlobalStepInit = 5.;
// 				
// 
// 				const double   MinInit        = -3.;
// 				const double   MaxInit        = 7.;
// 				const double   SigmaInit    = 6;
// 
// 				/* activate elitist strategy */
// 				const bool     PlusStrategy = true;
// 
// 				unsigned       i, t;
// 
// 				// initialize random number generator
// 				Rng::seed(1234);
// 
// 				// define populations
// 				PopulationT<double> parents(Mu,     ChromosomeT< double >(Dimension),
// 								ChromosomeT< double >(NSigma));
// 				PopulationT<double> offsprings(Lambda, ChromosomeT< double >(Dimension),
// 									ChromosomeT< double >(NSigma));
// 
// 				// minimization task
// 				parents   .setMinimize();
// 				offsprings.setMinimize();
// 
// 				// initialize parent population
// 				for (i = 0; i < parents.size(); ++i) {
// 					parents[ i ][ 0 ].initialize(MinInit,   MaxInit);
// 					parents[ i ][ 1 ].initialize(SigmaInit, SigmaInit);
// 				}
// 
// 				// selection parameters (number of elitists)
// 				unsigned numElitists = PlusStrategy ? Mu : 0;
// 
// 				// standard deviations for mutation of sigma
// 				double     tau0 = 1. / sqrt(2. * Dimension);
// 				double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));
// 
// 				// evaluate parents (only needed for elitist strategy)
// 				if (PlusStrategy)
// 					for (i = 0; i < parents.size(); ++i)
// 						parents[ i ].setFitness((ueber9000->*ueber9000->evaluate)(parents[ i ][ 0 ]));
// 
// 				std::vector<double> fitness;
// 				fitness.reserve(10);
// 				
// 				// iterate
// 				for (t = 0; t < Iterations; ++t) {
// 					// generate new offsprings
// 					for (i = 0; i < offsprings.size(); ++i) {
// 						// select two random parents
// 						Individual& mom = parents.random();
// 						Individual& dad = parents.random();
// 
// 						// recombine object variables discrete, step sizes intermediate
// 						offsprings[ i ][ 0 ].recombineDiscrete(mom[ 0 ], dad[ 0 ]);
// 						offsprings[ i ][ 1 ].recombineGenIntermediate(mom[ 1 ], dad[ 1 ]);
// 
// 						// mutate object variables normal distributed,
// 						// step sizes log normal distributed
// 						offsprings[ i ][ 1 ].mutateLogNormal(tau0,  tau1);
// 						offsprings[ i ][ 0 ].mutateNormal(offsprings[ i ][ 1 ], true);
// 					}
// 
// 					// evaluate objective function (parameters in chromosome #0)
// 					for (i = 0; i < offsprings.size(); ++i)
// 						offsprings[ i ].setFitness((ueber9000->*ueber9000->evaluate)(offsprings[ i ][ 0 ]));
// 
// 					// select (mu,lambda) or (mu+lambda)
// 					parents.selectMuLambda(offsprings, numElitists);
// 
// 					// print out best value found so far
// 					if( parents.best().fitnessValue() < 1e-18 )
// 						break;
// 
// // 					/* convergenzkriterium */
// // 					if( t > 10 ) {
// // 						double sum = 0.;
// // 						for( auto i : fitness ) {
// // 							sum += i;
// // // 						
// // 						}						
// // 						sum -= fitness.size()*fitness[0];
// // 						sum = abs( sum );
// // 
// // 						if( sum < .1) break;
// // 						fitness.erase( fitness.begin(), fitness.begin() + 1 );
// // 
// // 					}
// // // 					fitness.resize(9);
// // 					fitness.push_back( parents.best().fitnessValue() );
// 					
// 				}
// 				
// 				auto p = parents.best();
// 				std::cout << t << " Done \tFinal Fitness: " << parents.best().fitnessValue() << endl;
// 				
// 				for( int i = 0; i < 10; i++ )
// 					std::cout << i << " " << p[0][i] << " " ;
// 				std::cout << std::endl;
// 				
// 			}

		};

		/******************************************************************/
		/* Process Class Function implementation **************************/
		/******************************************************************/

		/******************************************************************/
		/* PostProcessing Class *******************************************/
		/******************************************************************/
		
		class PostProcessing
		{
		public:
			PostProcessing(){

			}
			/* check plausibility of result */
			/* compute Wavenumbers */
			/* report success/ failure */
			
		};

		/******************************************************************/
		/* PostProcessing Function implementation *************************/
		/******************************************************************/
		
	}
}
#endif