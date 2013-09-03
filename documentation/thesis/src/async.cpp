std::vector<std::future<Solve::solveresult_t<ChromosomeT<double>,ChromosomeT<double>,Doub>>> results;

/* create tasks */
for( int Solution = 0; Solution < NO_OF_SOLUTIONS; Solution++ ) {

	t_0 = steady_clock::now();

	resultsA.push_back( std::async( std::launch::async,
					&Solve::Process::findSolution<Solve::solveresult_t<ChromosomeT<double>,Doub>>,
					&process,
					A,
					b,
					Solve::ESStrategy::OnePlusOne,
					duration_cast<microseconds>(t_1-t_00).count() ));
	
	results.push_back( std::async( std::launch::deferred, &Solve::Process::findSolution, &process, A, b ));

	t_1 = steady_clock::now();
}

//++++++++++++++++++++++++

for( auto res = results.begin(); res != results.end(); ++res ) {
	while(res->wait_for(chrono::seconds(0)) != future_status::ready );

	auto r = res->get();
	f_fitness << r.iterations << " " << r.fitness <<" in: " << r.duration << " (µs)" << " " << r.converged <<std::endl;

	for( auto values : r.valCont )
		f << values << "\t";
	for( auto values : r.valDis )
		f << values << "\t";

	f << std::endl;

}
