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

#include "AntennaConfiguration.h"
#include "../libPermutate/permutate.h"
#include "../libPRPSSystem/prpsevolutionsystem.h"
#include "../libCalibration/calib.h"
#include "../libSolve/solve.h"
#include "../libSolve/solveresult.h"
#include "../libSolve/process.h"
#include "../libSolve/preprocessing.h"
#include "../libSolve/postprocessing.h"

#include "../include/PRPSEvolutionGeneralExceptions.h"

#include <EALib/ChromosomeCMA.h>

using namespace PRPSEvolution;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

const int SOLUTION_AMOUNT = 1;

int		VARIANT_SW;
int		NO_OF_SOLUTIONS;
bool	DROPBAD = false;

/**
 */
int main ( int argc, char *argv[ ] ) {
	fprintf(stdout,"%s Version %d.%d.%x\n",
			argv[0],
			VERSION_MAJOR,
			VERSION_MINOR,
			VERSION_SUB_MINOR
			);

	if( argc > 1 )
		VARIANT_SW = atoi( argv[1] );
	if( argc > 2 )
		NO_OF_SOLUTIONS = atoi( argv[2] );
	if( argc > 3 )
		if(atoi( argv[3] ) > 0)
			DROPBAD = true;
	
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

	Solve::PreProcessing<ANTENNA_AMOUNT, 5, Doub, Doub> preprocess( PA.configurations, PA.d_k0_mat );

	std::cout << std::endl;

	std::cout << "*PreProcessing.. done" << std::endl;
	
	/**********************************************************************/
	std::cout << std::endl;
	std::cout << "*Processing.. Create Solution(s).." << std::endl;

	Solve::Process process;


	int i = 0;

	const double fitness = 1e-18;
	process.setMinSolutionFitness( fitness );

	steady_clock::time_point t_00 = steady_clock::now();
	steady_clock::time_point t_0 = steady_clock::now();
	steady_clock::time_point t_1 = steady_clock::now();

	std::vector<std::future<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>> resultsA;
	std::vector<std::future<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<int>,Doub>>> resultsB;
// 	std::vector<std::future<Solve::solveresult_t<std::array<ChromosomeT<double>,2>,Doub>>> resultsA;
// 	std::vector<std::future<Solve::solveresult_t<std::array<ChromosomeT<double>,2>,Doub>>> resultsB;

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
// 			resultsA.push_back( std::async( std::launch::deferred, &Solve::Process::findSolution, &process, A, b ));

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

	/**********************************************************************/

	return 0;

}
