/**
 * @file AntennaConfiguration.cpp
 * This File contains the main() of the AntennaApp-Project
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <array>
#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <future>
#include <thread>
#include <vector>

#define _USE_SHARK_3_0_
#define _Write_Result
#define _DROP_BAD_
// #define _PREPROCESS_OUTPUT
#define _REFINE_SELECTION
#define _PP_FORM_GROUPS

#ifdef _USE_SHARK_3_0_
	#include "../libSolve/processMkII.h"

#endif

#include "../include/PRPSEvolution.h"
#include "../include/PRPSError.h"
#include "../include/PRPSEvolutionGeneralExceptions.h"

#include "AntennaConfiguration.h"

#include "../libPermutate/permutate.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"
#include "../libCalibration/calib.h"

#include "../libSolve/solve.h"
#include "../libSolve/solveresult.h"

#ifndef _USE_SHARK_3_0_
	/* workaround, we need to include the stuff from Shark 3.0b first to avoid compiler crashes*/
	#include "../libSolve/process.h"
#endif

#include "../libSolve/preprocessing.h"
#include "../libSolve/postprocessing.h"

#define USAGE_AND_EXIT \
	{																		\
	std::cout << "USAGE: " << std::endl << "\t " << argv[0] 				\
	<< " [VARIANT_SW] [NO_OF_SOLUTIONS] [DROPBAD] [FILENAME] [MU] [Lambda] [UseNMats] [DEFAULT_MAX_EVALUATIONS]"<< std::endl; \
	exit(-1); 																\
	}
// #include <EALib/ChromosomeCMA.h>

const int EXPECTED = 9;

using namespace PRPSEvolution;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

const int SOLUTION_AMOUNT = 1;
const int DEFAULT_MAX_EVALUATIONS = 4500;

int			VARIANT_SW;
int			NO_OF_SOLUTIONS;
int			MU					= 0;
int			LAMBDA				= 0;
int			UseNMats			= 1;
int			EVALUATIONS			= DEFAULT_MAX_EVALUATIONS;

bool		DROPBAD				= false;

std::string	FILENAME			="";

/**
 */
int main ( int argc, char *argv[ ] ) {
	fprintf(stdout,"%s Version %d.%d.%x\n",
			argv[0],
			VERSION_MAJOR,
			VERSION_MINOR,
			VERSION_SUB_MINOR
			);

	if( argc < EXPECTED )
		USAGE_AND_EXIT;
	
	if( argc > 1 )
		VARIANT_SW = atoi( argv[1] );

	if( argc > 2 )
		NO_OF_SOLUTIONS = atoi( argv[2] );
	
	if( argc > 3 )
		if(atoi( argv[3] ) > 0)
			DROPBAD = true;

	if( argc > 4 )
		FILENAME = argv[4];

	if( argc > 5 )
		MU = atoi(argv[5]);

	if( argc > 6 )
		LAMBDA = atoi(argv[6]);

	if( argc > 7 )
		UseNMats = atoi(argv[7]);
	
	if( argc > 8 )
		if(atoi( argv[8] ) > 0)
			EVALUATIONS = atoi(argv[8]);

	/**********************************************************************/
	PRPSEvolution::System sys;

	/**********************************************************************/
	Calibration::performCalibration< ANTENNA_AMOUNT, CALIBRATION_POINTS_AVAILABLE, Doub >
					PC;
					
	/**********************************************************************/
	Permutate::permuteAntennas< ANTENNA_AMOUNT, Permutate::MAX_PERMUTATION_AMOUNT, Doub >
					PA( sys.constants );

	/* PA is an 8x35 array of type permutateAntennas of type Doub */

	/**********************************************************************/
	std::cout << std::endl;
	std::cout << "*PreProcessing.." << std::endl;

	Solve::PreProcessing<ANTENNA_AMOUNT, 5, Doub, Doub> preprocess( PA.configurations, PA.d_k0_mat, UseNMats , 0 );

	std::cout << std::endl;

	std::cout << "*PreProcessing.. done" << std::endl;

	/**********************************************************************/
	std::cout << std::endl;
	std::cout << "*Processing.. Create Solution(s).." << std::endl;

#ifdef _USE_SHARK_3_0_

	steady_clock::time_point t_000 = steady_clock::now();
	steady_clock::time_point t_00 = steady_clock::now();
	steady_clock::time_point t_0 = steady_clock::now();
	steady_clock::time_point t_1 = steady_clock::now();

	int meanTime = 0;

	/**********************************************************************/
	if( VARIANT_SW == 0 ) {
		t_00			= steady_clock::now();
		auto A 			= preprocess.matrices;
		auto v			= preprocess.vectors;
		auto name		= preprocess.names;

		Solve::Process_MkII		process( A, v, name, MU, LAMBDA );
		std::cout << "Mark II :: Solving for WholeTomato Mark II" << std::endl;

		std::ostringstream s;
		s << "output/mkII/" << FILENAME;
		for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {

			process.setOutputFilePathBase( s.str() );

			t_0 = steady_clock::now();
			process.WholeTomatoMkII( preprocess.antennas );

			process.incrementFileCounter();
			t_1 = steady_clock::now();

// 			std::cout << "Mark II :: "
// 					<< i
// 					<< " "
// 					<< duration_cast<milliseconds>(t_1-t_0).count()
// 					<< " ms"
// 					<< std::endl;

			meanTime += duration_cast<milliseconds>(t_1-t_0).count();

		}
		std::cout << "Mark II :: "
				<< duration_cast<milliseconds>(t_1-t_00).count()
				<< " ms for "
				<< NO_OF_SOLUTIONS
				<< " Solutions"
				<< std::endl;

		t_1 = steady_clock::now();

		std::cout << "Mark II :: total " << duration_cast<milliseconds>(t_1-t_000).count() << " ms" << std::endl;
		std::cout << "Mark II :: " << meanTime/NO_OF_SOLUTIONS << " ms / solution" << std::endl;

		return 0;

	}

	/**********************************************************************/
	if( VARIANT_SW == 1 ) {
		int l = 0;
		std::cout << "Mark II :: Solving Variant A" << std::endl;
		for( auto A: preprocess.matrices ) {
			t_00					= steady_clock::now();
			auto v					= preprocess.vectors [ l ];
			auto name				= preprocess.names[ l++ ];

			Solve::Process_MkII		process( A, v, name );
			std::cout << "Mark II :: Solving for WholeTomato Mark I" << std::endl;

			std::ostringstream s;
			s << "output/mkII/CMA-ES_wt_mkI-A-" << l;
			process.setOutputFilePathBase( s.str() );
			
			for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {

				t_0 = steady_clock::now();
				process.WholeTomatoMkI_A();

				process.incrementFileCounter();
				t_1 = steady_clock::now();
				std::cout << "Mark II :: " << i << " " << duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

				meanTime += duration_cast<milliseconds>(t_1 -t_0).count();
				
			}
			std::cout << "Mark II :: " << duration_cast<milliseconds>(t_1 -t_00).count() << " ms" << " for " << NO_OF_SOLUTIONS << " Solutions"<< std::endl;
			std::cout << "Mark II :: " << meanTime/NO_OF_SOLUTIONS << " ms / solution" << std::endl;
		}
		
		t_1 = steady_clock::now();

		std::cout << "Mark II :: total " << duration_cast<milliseconds>(t_1 -t_000).count() << " ms" << std::endl;

	}

	/**********************************************************************/
	if( VARIANT_SW == 1 ) {
		int l = 0;
		int meanTime = 0;

		std::cout << "Mark II :: Solving Variant B" << std::endl;
		for( auto A: preprocess.matrices ) {
			t_00					= steady_clock::now();
			auto v					= preprocess.vectors [ l ];
			auto name				= preprocess.names[ l++ ];

			Solve::Process_MkII		process( A, v, name );
			std::cout << "Mark II :: Solving for WholeTomato Mark I" << std::endl;

			std::ostringstream s;
			s << "output/mkII/CMA-ES_wt_mkI-B-" << l;
			process.setOutputFilePathBase( s.str() );
				
			for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {
				t_0 = steady_clock::now();
				process.WholeTomatoMkI_B();

				process.incrementFileCounter();
				t_1 = steady_clock::now();
				std::cout << "Mark II :: " << i << " " << duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

				meanTime += duration_cast<milliseconds>(t_1 -t_0).count();

			}
			std::cout << "Mark II :: " << duration_cast<milliseconds>(t_1 -t_00).count() << " ms" << " for " << NO_OF_SOLUTIONS << " Solutions"<< std::endl;
			std::cout << "Mark II :: " << meanTime/NO_OF_SOLUTIONS << " ms / solution" << std::endl;
			
		}

		t_1 = steady_clock::now();

		std::cout << "Mark II :: total " << duration_cast<milliseconds>(t_1 -t_000).count() << " ms" << std::endl;

	} 

	/**********************************************************************/
	if( VARIANT_SW == 2 ) {
		Solve::Process_MkII process;

		process.setOutputFilePathBase("output/mkII/CMA-ES_test");

		std::cout << "Mark II :: Solving for Test Sphere" << std::endl;
		for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {
			process.Process_MkII_test();

			process.incrementFileCounter();

		}
		steady_clock::time_point t_1 = steady_clock::now();

		std::cout << "Mark II :: " << duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;
		
		return 0;
		
	}

	/**********************************************************************/
	/* This will only solve for one matrix at a time 						 */
	if( VARIANT_SW == 3 ) {
		t_00			= steady_clock::now();
		
		auto As 		= preprocess.matrices;
		auto vs			= preprocess.vectors;
		auto names		= preprocess.names;

		std::cout << "Mark II :: Solving for WholeTomato Mark II Variant 3" << std::endl;
		for( int j = 0; j < As.size(); j++ ) {
			auto A		= As[j];
			auto v		= vs[j];
			auto name	= names[j];

			meanTime = 0; 

			Solve::Process_MkII		process( A, v, name, MU, LAMBDA );
			std::ostringstream s;
			s << "output/mkII/" << FILENAME << "." << j;
			for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {

				process.setOutputFilePathBase( s.str() );

				t_0 = steady_clock::now();
				
				/* get a solution */
				process.WholeTomatoMkII( 4 );

				process.incrementFileCounter();
				t_1 = steady_clock::now();
// 				std::cout << j <<"\tMark II :: "
// 						<< i
// 						<< " "
// 						<< duration_cast<milliseconds>(t_1-t_0).count()
// 						<< " ms"
// 						<< std::endl;

				meanTime += duration_cast<milliseconds>(t_1-t_0).count();

			}
			std::cout << j << "\tMark II :: "
					<< duration_cast<milliseconds>(t_1-t_00).count()
					<< " ms for "
					<< NO_OF_SOLUTIONS
					<< " Solutions"
					<< std::endl;

			t_1 = steady_clock::now();

			std::cout << j <<"\tMark II :: total " << duration_cast<milliseconds>(t_1-t_000).count() << " ms" << std::endl;
			std::cout << j <<"\tMark II :: " << meanTime/NO_OF_SOLUTIONS << " ms / solution" << std::endl;
			
		}
		
		return 0;

	}

	/**********************************************************************/
	/* This will solve for groups of matrices								 */
	if( VARIANT_SW == 4 ) {
		t_00			= steady_clock::now();
		
		auto As 		= preprocess.matGroups;
		auto vs			= preprocess.vectorGroups;
		auto names		= preprocess.nameGroups;

		std::cout << "Mark II :: Solving for WholeTomato Mark II Variant 4" << std::endl;
		for( int j = 0; j < As.size(); j++ ) {
			auto A		= As[ j ];
			auto v		= vs[ j ];
			auto name	= names[ j ];

			meanTime = 0; 

			Solve::Process_MkII		process( A, v, name, MU, LAMBDA );
			process.setMaxEvauations( EVALUATIONS );
			
			std::ostringstream s;
			s << "output/mkII/" << FILENAME << "." << j;

			int dimension = preprocess.antennasPerGroup;
			process.setAntennaCoords( PC.c_k0 );
			
			std::cout << " dimension " << dimension << std::endl;
			for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {

				process.setOutputFilePathBase( s.str() );

				t_0 = steady_clock::now();
				process.WholeTomatoMkII( dimension );

				process.incrementFileCounter();
				t_1 = steady_clock::now();

				meanTime += duration_cast<milliseconds>(t_1-t_0).count();

			}
			std::cout << j << "\tMark II :: "
					<< duration_cast<milliseconds>(t_1-t_00).count()
					<< " ms for "
					<< NO_OF_SOLUTIONS
					<< " Solutions"
					<< std::endl;

			t_1 = steady_clock::now();

			std::cout << j <<"\tMark II :: total " << duration_cast<milliseconds>(t_1-t_000).count() << " ms" << std::endl;
			std::cout << j <<"\tMark II :: " << meanTime/NO_OF_SOLUTIONS << " ms / solution" << std::endl;
			
		}
		
		return 0;

	}

	/**********************************************************************/
	/*
	 * This will solve for groups of matrices, while using the rounding
	 * Model
	 * 
	 */
	if( VARIANT_SW == 5 ) {
		t_00			= steady_clock::now();

		auto As 		= preprocess.matGroups;
		auto vs			= preprocess.vectorGroups;
		auto names		= preprocess.nameGroups;

		std::cout << "Mark II :: Solving for WholeTomato Mark II Variant 5" << std::endl;
		for( int j = 0; j < As.size(); j++ ) {
			auto A		= As[ j ];
			auto v		= vs[ j ];
			auto name	= names[ j ];

			meanTime = 0;

			Solve::Process_MkII		process( A, v, name, MU, LAMBDA );
			process.setMaxEvauations( EVALUATIONS );

			std::ostringstream s;
			s << "output/mkII/" << FILENAME << "." << j;

			int dimension = preprocess.antennasPerGroup;

			std::cout << " dimension " << dimension << std::endl;
			for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {

				process.setOutputFilePathBase( s.str() );

				t_0 = steady_clock::now();
				process.WholeTomatoMkII_B( dimension );

				process.incrementFileCounter();
				t_1 = steady_clock::now();

				meanTime += duration_cast<milliseconds>(t_1-t_0).count();

			}
			std::cout << j << "\tMark II :: "
					<< duration_cast<milliseconds>(t_1-t_00).count()
					<< " ms for "
					<< NO_OF_SOLUTIONS
					<< " Solutions"
					<< std::endl;

			t_1 = steady_clock::now();

			std::cout << j <<"\tMark II :: total " << duration_cast<milliseconds>(t_1-t_000).count() << " ms" << std::endl;
			std::cout << j <<"\tMark II :: " << meanTime/NO_OF_SOLUTIONS << " ms / solution" << std::endl;

		}

		return 0;

	}
	
	/**********************************************************************/
	/* the calibration variant */
	if( VARIANT_SW == 10 ) {
		t_00			= steady_clock::now();

		std::cout << "Mark II :: Solving for WholeTomato Mark II Variant 10" << std::endl;

		meanTime = 0;

		int j = 0;
		
		for( auto b : PC.c_k0 ) {
	
			std::ostringstream s;
			s << "output/mkII/" << FILENAME << "." << j++;

			Solve::Process_MkII		process(PC.A, b, "1");
			
			process.setMaxEvauations( EVALUATIONS );
			
			for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {

				process.setOutputFilePathBase( s.str() );

				t_0 = steady_clock::now();
				process.EvolutionaryCalibration( );

				process.incrementFileCounter();
				t_1 = steady_clock::now();
	// 				std::cout << j <<"\tMark II :: "
	// 						<< i
	// 						<< " "
	// 						<< duration_cast<milliseconds>(t_1-t_0).count()
	// 						<< " ms"
	// 						<< std::endl;

				meanTime += duration_cast<milliseconds>(t_1-t_0).count();

			}
			std::cout << j << "\tMark II :: "
					<< duration_cast<milliseconds>(t_1-t_00).count()
					<< " ms for "
					<< NO_OF_SOLUTIONS
					<< " Solutions"
					<< std::endl;
		}
		t_1 = steady_clock::now();

		std::cout << j <<"\tMark II :: total " << duration_cast<milliseconds>(t_1-t_000).count() << " ms" << std::endl;
		std::cout << j <<"\tMark II :: " << meanTime/NO_OF_SOLUTIONS << " ms / solution" << std::endl;

		return 0;

	}
#else
	Solve::Process process;

	int i = 0;

	const double fitness = 1e-20;
	process.setMinSolutionFitness( fitness );

	steady_clock::time_point t_00 = steady_clock::now();
	steady_clock::time_point t_0 = steady_clock::now();
	steady_clock::time_point t_1 = steady_clock::now();
	
	std::vector<std::future<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>> resultsA;
	std::vector<std::future<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<int>,Doub>>> resultsB;
	
// 	std::vector<std::future<Solve::solveresult_t<std::array<ChromosomeT<double>,2>,Doub>>> results1A;
// 	std::vector<std::future<Solve::solveresult_t<std::array<ChromosomeT<double>,2>,Doub>>> resultsB;

	/**********************************************************************/
	if( VARIANT_SW == 0 ) {
		std::cout << "Solving single matrices" << std::endl;

	for( auto A: preprocess.matrices ) {
		auto names		= preprocess.names;
		auto numOAnts	= preprocess.antennas;
		auto b = preprocess.vectors[i++];

		for( int Solution = 0; Solution < NO_OF_SOLUTIONS; Solution++ ) {

// 			process.setSeed(duration_cast<microseconds>(t_0-t_00).count());

			t_0 = steady_clock::now();

// 			resultsA.push_back( std::async( std::launch::async,
// 											&Solve::Process::findSolution<Solve::solveresult_t<ChromosomeT<double>,Doub>>,
// 											&process,
// 											A,
// 											b,
// 											Solve::ESStrategy::OnePlusOne,
// 											duration_cast<microseconds>(t_1-t_00).count() ));
			
			resultsA.push_back( std::async( std::launch::deferred, &Solve::Process::findSolution, &process, A, b ));

			t_1 = steady_clock::now();

// 			process.setSeed(duration_cast<microseconds>(t_1-t_00).count());
// 			process.setESStrategy( Solve::ESStrategy::MuPlusLambda );

// 			resultsA.push_back( std::async( std::launch::async,
// 											&Solve::Process::findSolutionSolveSingle<Solve::solveresult_t<std::vector<ChromosomeT<double>>,Doub>>,
// 											&process,
// 											A,
// 											b,
// 											names,
// 											numOAnts,
// 											Solve::ESStrategy::MuPlusLambda_MkII,
// 											duration_cast<microseconds>(t_1-t_00).count() ));
// 			resultsB.push_back( std::async( std::launch::deferred, &Solve::Process::findSolution, &process, A, b  ));

		}
	}
	}

	/**********************************************************************/
	if( VARIANT_SW == 1 ) {
		std::cout << "Solving all matrices" << std::endl;

	auto A			= preprocess.matrices;
	auto b			= preprocess.vectors;
	auto names		= preprocess.names;
	auto numOAnts	= preprocess.antennas;

	std::cout << "num o Ants " << numOAnts << std::endl;

	for( int Solution = 0; Solution < NO_OF_SOLUTIONS; Solution++ ) {

		process.setSeed(duration_cast<microseconds>(t_1-t_00).count());

		t_0 = steady_clock::now();

		resultsA.push_back( std::async( std::launch::async,
										&Solve::Process::findSolutionCMA_ES_MkII<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>,
										&process ));

		t_1 = steady_clock::now();

// 		resultsB.push_back( std::async( std::launch::async,
// 										&Solve::Process::findSolution<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<int>,Doub>>,
// 										&process,
// 										A,
// 										b,
// 										names,
// 										numOAnts,
// 										Solve::ESStrategy::MuCommaLambda_MkII,
// 										duration_cast<microseconds>(t_1-t_00).count() ));

	}
	}

	/**********************************************************************/
	/* This will test the performance of the different algorithms */
	if( VARIANT_SW == 2 ) {
		steady_clock::time_point t_0 = steady_clock::now();
		steady_clock::time_point t_00 = steady_clock::now();
		std::cout << "MKI :: Solving for Test Sphere" << std::endl;
		for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {
			process.findSolutionSphere<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>( Solve::ESStrategy::OnePlusOne );
			process.incrementFileCounter();
		}
		process.resetFileCounter();
		
		steady_clock::time_point t_1 = steady_clock::now();
		std::cout << "MKI :: 1 " << duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

		t_0 = steady_clock::now();
		
		for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {
			process.findSolutionSphere<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>( Solve::ESStrategy::MuCommaLambda );
			process.incrementFileCounter();
		}
		process.resetFileCounter();

		t_1 = steady_clock::now();
		std::cout << "MKI :: 2 " << duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

		t_0 = steady_clock::now();
		
		for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {
			process.findSolutionSphere<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>( Solve::ESStrategy::MuPlusLambda );
			process.incrementFileCounter();
		}
		process.resetFileCounter();

		t_1 = steady_clock::now();
		std::cout << "MKI :: 3 " << duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

		t_0 = steady_clock::now();
		
		for( int i = 0; i < NO_OF_SOLUTIONS; i++ ) {
			process.findSolutionSphere<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>( Solve::ESStrategy::CMA_ES_MkI );
			process.incrementFileCounter();
		}
		process.resetFileCounter();

		t_1 = steady_clock::now();
		std::cout << "MKI :: 4 " << duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

		t_1 = steady_clock::now();
		std::cout << "MKI :: total " << duration_cast<milliseconds>(t_1 -t_00).count() << " ms" << std::endl;
		
		return 0;
	}
// 	}

	std::cerr << "done "<<std::endl;

	std::ofstream f, f_fitness;
	f.open("output/solutionA.dat");
	f_fitness.open("output/solutionA_FitnessValues.dat");

	if ( !f.is_open() ) { exit(EXIT_FAILURE); }
	t_0 = steady_clock::now();

	std::cout << "*writing results to file.. " << std::endl;

	int droppedResults = 0;
	for( auto res = resultsA.begin(); res != resultsA.end(); ++res ) {
		while(res->wait_for(chrono::seconds(0)) != future_status::ready );

		auto r = res->get();
		f_fitness << r.iterations << " " << r.fitness <<" in: " << r.duration << " (µs)" << " " << r.converged <<std::endl;

// 		if( DROPBAD && !r.converged ) { droppedResults++; continue; }

		for( auto values : r.valCont )
			f << values << "\t";
		for( auto values : r.valDis )
			f << values << "\t";

		f << std::endl;

	}
	t_1 = steady_clock::now();

	std::cout << "file a written in: "
		<< duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

	std::cout << "Dropped: " << droppedResults << " results"<< std::endl;

	f.close();
	f_fitness.close();

	f.open("output/solutionB.dat");
	f_fitness.open("output/solutionB_FitnessValues.dat");

	if ( !f.is_open() ) { exit(EXIT_FAILURE); }

	t_0 = steady_clock::now();

	droppedResults = 0;
	for( auto res = resultsB.begin(); res != resultsB.end(); ++res ) {
		while(res->wait_for(chrono::seconds(0)) != future_status::ready );

		auto r = res->get();

		f_fitness << r.iterations << " " << r.fitness <<" in: " << r.duration << " (µs)" << " " << r.converged <<std::endl;

// 		if( DROPBAD && !r.converged ) { droppedResults++; continue; }

		for( auto values : r.valCont )
			f << values << "\t";
		for( auto values : r.valDis )
			f << values << "\t";

		f << std::endl;

	}
	t_1 = steady_clock::now();

	std::cout << "file b written in: "
		<< duration_cast<milliseconds>(t_1 -t_0).count() << " ms" << std::endl;

	std::cout << "Dropped: " << droppedResults << " results"<< std::endl;

	f.close();
	f_fitness.close();

	steady_clock::time_point t_nn = steady_clock::now();
	std::cout << "total computation time: "
		<< (duration_cast<milliseconds>(t_nn -t_00).count() / 1000)/ 60 << " m" << std::endl;

	std::cout << " done" << std::endl;

#endif /* _USE_SHARK_2_3_ */
	
	/**********************************************************************/

	return 0;

}
