
#ifndef _PREPROCESSING_H_
	#define _PREPROCESSING_H_

// #include <chrono>
#include <iostream>
#include <sstream>
#include <string>
// #include <random>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <array>

#include "../libNormalizer/normalizer.h"
#include "../include/coords.h"
#include "../include/PRPSEvolution.h"
#include "../include/PRPSEvolutionSolveExceptions.h"
#include "../include/PRPSEvolutionFIOExceptions.h"
#include "../include/PRPSEvolutionGeneralExceptions.h"

#include "nr3/nr3.h"
#include "solve.h"

namespace PRPSEvolution {
	namespace Solve {

		using namespace PRPSEvolution::Permutate;
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
			/** The precalcultated matrices for a solution */
			std::vector<NRmatrix<T>>					matrices;

			/** The b-vectors for the solution */
			std::vector<NRvector<T>>					vectors;

			/** The "Names" of the matrices for a solution */
			std::vector<std::string>					names;

			/** Amount of antennas for the solution */
			int 										antennas;

			/** Will contain the groups of a matrix */
			std::vector<std::vector<NRmatrix<T>>>		matGroups;

			/** Contains a group of the b-vectors */
			std::vector<std::vector<NRvector<T>>>		vectorGroups;

			/** Contains the names of a group */
			std::vector<std::vector<std::string>>		nameGroups;
			
			/** Amount of antennas for the solution */
			int 										antennasPerGroup;

			PreProcessing (
				const std::array< AntennaPermutations< Permutate::MAX_PERMUTATION_AMOUNT, Doub >, N_ANTA> &,
				const NRmatrix<T> &,
				const PRPSEvolution::NormalizationMethods method,
				const int,
				const int,
				const double,
				const int
				);
				
			/**
			 * Returns the possible group size for one antenna
			 * The group size depends on the amount of antennas that provided
			 * a decent measurement and can be calculated by:
			 * @f[\frac{n!}{k!(n-k)!}@f]
			 * Where n is the amount of availiable-1 and k is the size of the group
			 * 
			 */
			int possibleGroupSize() { return gGroupSize; };
			
		private:
			/* stores the group size */
			int gGroupSize = DEFAULT_MIN_GROUP_SIZE;

			/** stores a bitmask which indicates the antennas contains valid data */
			std::array<bool,N_ANTA> dataValid;

			/** the container for the Phase data */
			std::array<T_Measure,N_ANTA> measuredPhase;

			/** the container for the Amp data */
			std::array<T_Measure,N_ANTA> measuredAmp;

			/** the container for the precalculated matrices */
			const std::array< AntennaPermutations< Permutate::MAX_PERMUTATION_AMOUNT, Doub >, N_ANTA>
					*precalculatedMats;

			/** The precalcultated matrices for a solution */
			std::vector<NRmatrix<T>>	Preprocessedmatrices;

			/** The b-vectors for the solution */
			std::vector<NRvector<T>>	PreprocessedPossiblevectors;

			/** The "Names" of the matrices for a solution */
			std::vector<std::string>	PreprocessedNames;

			int SELECT_IDEAL_POINT;
			
			double LAMBDA;
		
			/***************************************************************/
			/***************************************************************/
			/***************************************************************/
			/**
			 * Read in the measurements from a file
			 */
			int rMeasurementsFromFile( );

			/**
			 * 
			 */
			std::array<T, N_ANTA>
			normalizeThetas
			( const std::array<T_Measure,N_ANTA> &, const std::array<T_Measure,N_ANTA> &, PRPSEvolution::NormalizationMethods );

			/**
			 * 
			 */
			int selectReferenceAntennaForProcessing( PRPSEvolution::Solve::SelectBy );

			/**
			 */
			std::vector<NRmatrix< T >>
				selectAllPossible( const std::vector< std::string > & );

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

			/**
			 * 
			 */
			std::vector< std::string >
			selectNamesForProcessing
			(
			  const std::vector< std::string > &,
			  const std::vector< int > &,
			  const int &,
			  const int &,
			  const int &
			);

			/*
			 */
			std::vector<std::vector<NRvector<T>>>
				generateVectorGroups( std::vector<NRvector<T>> );

			/*
			 */
			std::vector<std::vector<NRmatrix<T>>>
				generateMatrixGroups( std::vector<NRmatrix<T>> );

			/*
			 */
			std::vector<std::vector<std::string>>
				generateNamesGroups( std::vector<std::string> );

			/*
			 */
			void
			dump_selected_mat_groups()
			{
				/*dump to file */
				std::ofstream f;
				f.open("output/selected_mats.dat");

				if ( f.is_open() ) {
					int i = 0;
					for( auto& g : matGroups ) {
						f << "++ Group " << i++ << " +++++++++" << std::endl;
						for( auto &m : g) {
							Permutate::AntennaPermutations<0,Doub>::dump_matrix_2_file( f, m );
							
						}
					}
					f.close();

				} else {
					throw PRPSEvolution::Exceptions::FileIO::OutputFailure();

				}
			}

			/*
			 */
			void
			dump_selected_vectors()
			{
				/*dump to file */
				std::ofstream f;
				f.open("output/selected_vecs.dat");

				if ( f.is_open() ) {
					int i = 0;
					for( auto& g : vectorGroups ) {
						for( auto &m : g) {
// 							Permutate::AntennaPermutations<0,Doub>::dump_matrix_2_file( f, m );

						}
					}
					f.close();

				} else {
					throw PRPSEvolution::Exceptions::FileIO::OutputFailure();

				}
			}

			/*
			 */
			void
			dump_selected_names()
			{
				/*dump to file */
				std::ofstream f;
				f.open("output/selected_names.dat");

				if ( f.is_open() ) {
					int i = 0;
					for( auto& g : nameGroups ) {
						f << "++ Group " << i++ << " +++++++++" << std::endl;

						for( auto &n : g) {
							f << n << std::endl;
// 							f << names[i++] << std::endl;
// 							Permutate::AntennaPermutations<0,Doub>::dump_matrix_2_file( f, m );

						}
					}
					f.close();

				} else {
					throw PRPSEvolution::Exceptions::FileIO::OutputFailure();

				}
			}
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
		 * @param[in] precalculatedMatrices Array containing the precalculated matricex from prior processing steps,
		 * 				This Array contains the static array for all possible permutations of the Antennas
		 * @param[in] d_k0s This Array contains the @f[d_{k0}@f], wich denotes
		 * 				the euklidean distances between the Antennas
		 * @param[in] finalAntAmount This field determines the Amount of Matrices
		 * 				we want to use for a calculation
		 * 
		 */
		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::PreProcessing
		(
		const std::array< AntennaPermutations< Permutate::MAX_PERMUTATION_AMOUNT, Doub >, N_ANTA> &precalculatedMatrices,
		const NRmatrix<T> & d_k0s,
		const PRPSEvolution::NormalizationMethods method,
		const int finalAntAmount,
		const int offset,
		const double lambda,
		const int point
		)
		{
			LAMBDA					= lambda;
			SELECT_IDEAL_POINT		= point;
			/***************************************************************/
			/* latch in the matrices */
			precalculatedMats = &precalculatedMatrices;
#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: Read from file.. .. ";
#endif
			rMeasurementsFromFile( );

#ifdef _PREPROCESS_OUTPUT
			std::cout << " done" << std::endl;
#endif

			/***************************************************************/
#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: normalization in process.. .. ";
#endif

			auto normThetas = normalizeThetas( measuredPhase, measuredAmp, method );

#ifdef _PREPROCESS_OUTPUT
			std::cout << " done" << std::endl;
#endif

			/* identify the possible matrices by their names */
			/***************************************************************/
#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: Identifying all possible matrices.. .. ";
#endif
			
			auto allPossibleNames = getPossibleNames( );

#ifdef _PREPROCESS_OUTPUT
			std::cout << "done" << std::endl;
#endif

			/***************************************************************/
#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: Selecting names.. .. ";
#endif

#ifdef _REFINE_SELECTION
			std::vector<int> idxs = {0,2,3,4};
			int quantity = 4;
			auto selectedNames = selectNamesForProcessing(
															allPossibleNames,
															idxs,
															quantity,
															finalAntAmount,
															offset
															);

#else
			auto selectedNames = allPossibleNames;

#endif /* _REFINE_SELECTION */
			
#ifdef _PREPROCESS_OUTPUT
			std::cout << "done" << std::endl;
#endif

			/***************************************************************/
#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: Selecting matrices.. .. ";
#endif

			auto selectedConfs = selectMatsForProcessing( SelectBy::AllPossible, selectedNames );

#ifdef _PREPROCESS_OUTPUT
			std::cout << " done" << std::endl;
#endif


			T a_1;
			{	/*
				 * workaround:
				 * a_1 can be found in the matrix so we do not have to pass
				 * it to the function seperately
				 */
				auto p = selectedConfs[ 0 ];
				a_1 = p[ 0 ][ 3 ];
#ifdef _PREPROCESS_OUTPUT
				std::cout << "a_1 = " << a_1 << std::endl;
#endif
			} /* !workaround */


			/***************************************************************/
#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: Filling selected matrices with remaining information.. ..";
#endif

			selectedConfs = fillSelectMats( normThetas, selectedConfs, selectedNames );

#ifdef _PREPROCESS_OUTPUT
			std::cout << " done" << std::endl;
#endif

			/***************************************************************/
#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: Calculate vectors.. ..";
#endif

			auto finalVectors = calcVectors( selectedNames, normThetas, d_k0s, a_1 );

#ifdef _PREPROCESS_OUTPUT
			std::cout << " done" << std::endl;
#endif

#ifdef _PREPROCESS_OUTPUT
			std::cout << "PreProcessing:: Creating Antanna Groups.. .. ";
#endif
			vectorGroups	= generateVectorGroups( finalVectors );
			matGroups		= generateMatrixGroups( selectedConfs );
			nameGroups		= generateNamesGroups( selectedNames );

			dump_selected_mat_groups();
			dump_selected_vectors();
			dump_selected_names();
			
#ifdef _PREPROCESS_OUTPUT
			std::cout << "done" << std::endl;
#endif
			/***************************************************************/
			vectors		= finalVectors;
			matrices	= selectedConfs;
			names		= selectedNames;

		}

		/**
		 *
		 */
// 		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
// 		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::PreProcessing
// 		(
// 		const std::array< AntennaPermutations< Permutate::MAX_PERMUTATION_AMOUNT, Doub >, N_ANTA> &precalculatedMatrices,
// 		const NRmatrix<T> & d_k0s,
// 		const PRPSEvolution::NormalizationMethods method,
// 		const int finalAntAmount,
// 		const int offset,
// 		const double lambda,
// 		const int point
// 		) : PreProcessing( precalculatedMatrices, d_k0s, method, finalAntAmount, offset )
// 		{
// // 			LAMBDA = lambda;
// // 			SELECT_IDEAL_POINT = point;
// // 			PreProcessing( precalculatedMatrices, d_k0s, method, finalAntAmount, offset );
// 
// 		}

		
		/**
		 * Create all possible groups according to @see possibleGroupSize
		 * @param[in] finalVectors the precalculated final vectors
		 * 
		 */
		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
		std::vector<std::vector<NRvector<T>>>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::generateVectorGroups( std::vector<NRvector<T>> finalVectors)
		{
			std::vector<std::vector<NRvector<T>>> ret;

			int i = 0, j = 0;
			for( int i = 0; i < finalVectors.size(); i+=gGroupSize ) {
				std::vector<NRvector<T>> vec;
				
				for( int j = 0; j < gGroupSize; j++ ) {
// 					std::cout << j << " " << i << std::endl;
					auto v = finalVectors[ j + i ];
					vec.push_back( v );

				}
				ret.push_back( vec );
			}
			return ret;
		}

		/**
		 * Create all possible groups of matrices according to @see possibleGroupSize
		 * @param[in] selectedConfs Vector containing the precalculated matrices
		 * 
		 */
		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
		std::vector<std::vector<NRmatrix<T>>>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::generateMatrixGroups( std::vector<NRmatrix<T>> selectedConfs)
		{
			std::vector<std::vector<NRmatrix<T>>> ret;

			for( int i = 0; i < selectedConfs.size(); i+=gGroupSize ) {
				std::vector<NRmatrix<T>> vec;

				for( int j = 0; j < gGroupSize; j++ ) {
// 					std::cout << j << " " << i << std::endl;
					auto v = selectedConfs[ j + i ];
					vec.push_back( v );

				}
				ret.push_back( vec );
			}
			return ret;
			
		}
		
		/**
		 * Create all possible groups of selected names according to @see possibleGroupSize
		 * @param[in] selectedNames Vector containing the names
		 *
		 */
		template < std::size_t N_ANTA, std::size_t N_Configs, typename T, typename T_Measure >
		std::vector<std::vector<std::string>>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::generateNamesGroups( std::vector<std::string> selectedNames )
		{
			std::vector<std::vector<std::string>> ret;

			for( int i = 0; i < selectedNames.size(); i+=gGroupSize ) {
				std::vector<std::string> vec;

				for( int j = 0; j < gGroupSize; j++ ) {
// 					std::cout << j << " " << i << std::endl;
					auto v = selectedNames[ j + i ];
					vec.push_back( v );

				}
				ret.push_back( vec );
			}
			return ret;
			
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

			/* if we want to use ideal input we set everything to 1.0 */
#ifdef _USE_IDEAL_INPUT
			for( int i = 0; i < N_ANTA; i++ ) {
				measuredPhase[ i ] = (T_Measure) 1.0;
				measuredAmp[ i ] = (T_Measure) 1.0;
			}
			
#else
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
					throw PRPSEvolution::Exceptions::FileIO::MalformedInput();

				linesRead++;

			}
			/* check the input */
			if( linesRead != PRPSEvolution::EXPECTED_LINES_MEASUREMENT_FILE )
				throw PRPSEvolution::Exceptions::FileIO::MalformedInput();

#endif
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
		( const std::array<T_Measure,N_ANTA> &phase, const std::array<T_Measure,N_ANTA> &amp, PRPSEvolution::NormalizationMethods method )
		{
			Normalizer<N_ANTA, T> normalizer( method );
// 			std::cout << "LAMBDA " << LAMBDA
// 				<< " SELECT_IDEAL_POINT " << SELECT_IDEAL_POINT
// 				<< std::endl;
				
			normalizer.setLambda( LAMBDA );
			normalizer.setSelectIdealPoint( SELECT_IDEAL_POINT );
			
			auto ret = normalizer.normalize( phase, amp );

			return ret;

		}

		/**
		 * This functions purpose is to select the 'names' (the permutations)
		 * for further processing. It's behaviour is controlled by the
		 * '_PP_FORM_GROUPS' macro. The default behaviour is to find the
		 * possible, unique names and return @see finalAntAmount of them.
		 * If the macro is set 
		 * 
		 * Refine the selected matrices so that only unique ones are left over
		 * @param[in] names Contains the possible matrix names
		 * @param[in] indices Indices of the antennas we want to choose
		 * @param[in] quantity Group size or the k-parameter
		 * 
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::vector< std::string >
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::selectNamesForProcessing
		( const std::vector< std::string > &names, const std::vector< int > &indices, const int &quantity, const int &finalAntAmount, const int &offset )
		{
			std::vector< std::string > ret;
			int found;

#ifdef _PREPROCESS_OUTPUT
			std::cout << std::endl;
#endif
			int possibleGroups = 0;
			
 			ostringstream os;
			/* possible permutations? */
			int i = 0;
			for( auto d: dataValid ) {
				if( d ) {
					os << std::to_string(i);
					possibleGroups++;
				}
				i++;
				
			}
// #ifdef _PREPROCESS_OUTPUT
// 			std::cout << "Selecting "<< quantity << " from " << indices.size() << std::endl;
// 			std::cout << "string "<< os.str() << std::endl;
// #endif

			/**/
			std::vector< std::string > select;

			/* k is the n over k, k */
			std::size_t k = quantity;
			std::string s_ = os.str();

			/* determine the unique permutations */
			do {
				/* create the name */
				ostringstream name;
				name << std::string( s_.begin(),s_.begin() + k );

// 				std::cout << " name " << name.str() << std::endl;
				select.push_back(name.str());

			} while( Permutate::next_combination( s_.begin(), s_.begin() + k, s_.end() ) );

			/* finalAntAmount == 0 means Select all antenna */
			int select_size = ( finalAntAmount == 0 ) ? select.size() : finalAntAmount;

			std::cout << "select_size " << select_size << " " << select.size() << std::endl;
			
// 			int select_size = select.size();
// 			ret.push_back( names[0] );
// 			ret.push_back( names[1] );

// 			ret.push_back( names[7] );
// 			ret.push_back( names[select.size()-1] );

			/* decide whether we want to group or not */
#ifdef _PP_FORM_GROUPS
			int AvailiablePerGroup = names.size()/ antennasPerGroup;

			for( int j = 0; j < possibleGroups; j++ ) {
				for( int i = 0; i < select_size; i++ ) {
						ret.push_back( names[ (AvailiablePerGroup*j) + i] );
// 					}
// 					if( (i-offset) >= select_size )
// 						break;

				}
			}
// 			for( auto a : ret )
// 				std::cout << " *" << a << std::endl;
#else
			/* recheck if the permutation exists in possible names, it should exist thou! */
			i = offset;
			for( auto name: names ) {
				if( name == select[i] ) {
					ret.push_back( name );
					i++;
				}
				if( (i-offset) >= select_size )
					break;

			}
#endif /* _PP_FORM_GROUPS */

			/* we need to determine the amount of antennas finally used */
			ostringstream os1;
			os1 << "01234567";
			
			int c = 0;
// 			string s = "01234567";
			for( int i = 0; i < 8; i++ ) {
				for( auto name: ret ) {
					if( string::npos != name.find(os1.str()[i] ) ) {
						c++;
						break;
					}
				}
			}

// 			std::cout << c << std::endl;
			if( c < 4 || c > 8 ) {
				exit(0);
				/** @todo throw exception */

			}
#ifdef _PP_FORM_GROUPS
			gGroupSize			= select_size;
			antennasPerGroup	= 3;
			antennasPerGroup	+= select_size;
			/* limit */
			antennasPerGroup	= (antennasPerGroup > 8) ? 8 : antennasPerGroup;
// 			std::cout << " ++ " << antennasPerGroup << std::endl;

#else
			gGroupSize			= select_size;
			antennasPerGroup	= c;
			antennas 			= c;
#endif			

			
			
#ifdef _PREPROCESS_OUTPUT
			std::cout << c << std::endl;
			for( auto name: ret )
				std::cout << name << std::endl;
#endif
			
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
		( PRPSEvolution::Solve::SelectBy method, const std::vector< std::string > &names )
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
					SelectedMat = selectAllPossible( names );
					break;

				case (int) SelectBy::AllFrom4Ant:
// 					SelectedMat = selectAllFrom4Ant( names );
					break;

			}

			/* send the selected ones to std::cout */
#ifdef _PREPROCESS_OUTPUT
			int i = 0;
			for( auto mat : SelectedMat ) {
				std::cout << ++i << " " << names[i] << std::endl;
				Permutate::AntennaPermutations<0,Doub>::dump_matrix( mat );

			}
#endif
			return SelectedMat;

		}

		/**
		 * Search through all availiable matrices and crawl out the needed ones
		 * @param[in] names The "names" of the correct matrices
		 *
		 */
		template<std::size_t N_ANTA,std::size_t N_Configs,typename T,typename T_Measure>
		std::vector<NRmatrix< T >>
		PreProcessing<N_ANTA,N_Configs,T,T_Measure>::selectAllPossible( const std::vector< std::string > &names )
		{
			std::vector<NRmatrix< T >> ret;
	
			int j = 0;
			for( auto name : names ) {
				for( auto p : *precalculatedMats ) {
					int i = 0;
					for( auto mat : p.mat ) {
						if( p.names[i++] == name )
							ret.push_back( mat );
					}
				}
			}
/*
			for( int i = 0; i < p.mat.size(); i++ ) {
				for( auto p : *precalculatedMats ) {
					if( p.names[i] == names[j] )  {

						ret.push_back( p.mat[i] );
						if( j++ >= names.size() )
							break;

					}
					if( j >= names.size() )
						break;

				}
				if( j >= names.size() )
						break;
			}*/

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
			std::array<bool,N_ANTA> data_;
			int c=0;
			for( int i = 0; i < data_.size(); i++ ) {
				data_[i] = (measuredAmp[i]==(T)DATA_NV||measuredPhase[i]==(T)DATA_NV)?false:true;
				c = (data_[i]) ? (c+1) : (c);
			}

			/* propagate to global var */
			dataValid = data_;

			int i = 0, j = 0;

			/* create string with all names of the antennas */
			ostringstream os;
			/* possible permutations? */
			for( auto d : data_ ) {
				if( d ) { os << i++; j++; }
				else { i++; }
			}

// 			std::cout << "***" <<  os.str() << std::endl;
			
			const std::size_t NoAvailiable = j;
			const std::size_t GroupSize = DEFAULT_MIN_GROUP_SIZE;

			/* n!/k!(n-k)! per antanna */
			int
			possiblePA	=
						Permutate::Factorial( NoAvailiable - 1 );
			possiblePA	/=
						(Permutate::Factorial( GroupSize-1 )
						* Permutate::Factorial( (NoAvailiable - 1) - (GroupSize -1) ) );

			/* propagate to global var for later use */
			gGroupSize			= possiblePA;
			antennasPerGroup	= NoAvailiable;
			
			/* total possible combinations */
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
// 			std::cout << NamesPossible.size() << std::endl;
// 			for( int i = 0; i < NamesPossible.size(); i++ )
// 				std::cout << NamesPossible[i] << std::endl;

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

			/* for each matrix */
			for( auto &mat: mats2return ) {

				auto name = names[idx];

				/* find ref antenna */
				std::array<int,4> antennas = { std::stoi( name.substr(0,1)),
												std::stoi( name.substr(1,1)),
												std::stoi( name.substr(2,1)),
												std::stoi( name.substr(3,1))
												};

				/* get the corresponding thetas */
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
// 				return mats2return;

// 				throw PRPSEvolution::Exceptions::FileIO::OutputExeption;

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
				/* find antennas in name */
				std::array<int,4> a = {
										std::stoi( name.substr(0,1) ),
										std::stoi( name.substr(1,1) ),
										std::stoi( name.substr(2,1) ),
										std::stoi( name.substr(3,1) )
									};

				/* init the vectors */
				NRvector<T> b;
				b.assign( 3, 0.0 );

				NRvector<T> a_0k;
				a_0k.assign( 3, 0.5 );

				NRvector<T> a_3k;
				a_3k.assign( 3, a_1 * (1/((2*pi)*(2*pi))) );

				/* the matrix is an upper triangle so we need the ? here */
// 				a_0k[0] *= (a[0] < a[1]) ? d_k0s[a[0]][a[1]]:d_k0s[a[1]][a[0]];
// 				a_0k[1] *= (a[0] < a[2]) ? d_k0s[a[0]][a[2]]:d_k0s[a[2]][a[0]];
// 				a_0k[2] *= (a[0] < a[3]) ? d_k0s[a[0]][a[3]]:d_k0s[a[3]][a[0]];

				for( int i = 0; i < 3; i++ ) {
					/* the matrix is an upper triangle so we need the ? here */
					a_0k[i] *= (a[0] < a[i+1]) ? d_k0s[a[0]][a[i+1]]:d_k0s[a[i+1]][a[0]];

					a_3k[i] *= (normThetas[a[0]])*(normThetas[a[0]])
							- (normThetas[a[i+1]])*(normThetas[a[i+1]]);

					/*** PROBLEM ***/
// 					b[i]= a_3k[i] - a_0k[i];
					b[i]= a_0k[i] - a_3k[i];
							
				}
							
// 				a_3k[0] *= (normThetas[a[0]])*(normThetas[a[0]])
// 							- (normThetas[a[1]])*(normThetas[a[1]]);

// 				a_3k[1] *= (normThetas[a[0]])*(normThetas[a[0]])
// 							- (normThetas[a[2]])*(normThetas[a[2]]);

// 				a_3k[2] *= (normThetas[a[0]])*(normThetas[a[0]])
// 							- (normThetas[a[3]])*(normThetas[a[3]]);

// 				b[0]= a_0k[0];
// 				b[1]= a_0k[1];
// 				b[2]= a_0k[2];

				ret.push_back(b);

			}

			/***************************************************************/
			std::ofstream f;
			f.open("output/vector_b_dump.dat");
			if ( f.is_open() ) {
				int i = 0;
				for( auto b : ret )	
						f << names[i++] << " " << b[0] << " " << b[1] << " " << b[2] << std::endl;

				f.close();

			} else {
// 				return -1;
// 				throw PRPSEvolution::Exceptions::FileIO::OutputExeption;

			}


			return ret;
		}
	}
}

#endif /* _PREPROCESSING_H_ */