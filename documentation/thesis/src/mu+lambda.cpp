MuPlusLambdaES( Ueber9000<double> *ueber9000, double seed ) {
	steady_clock::time_point t_0 = steady_clock::now();

	const unsigned Mu           = 5;
	const unsigned Lambda       = 25;
	const unsigned Dimension    = ueber9000->Dimension;
	const unsigned Iterations   = 3000;
	const unsigned Interval     = 10;
	const unsigned NSigma       = 1;

	const double   GlobalStepInit = 5.;

	const double   MinInit        = -7.;
	const double   MaxInit        = 7.;
	const double   SigmaInit    = 6;

	/* activate elitist strategy */
	const bool     PlusStrategy = true;
	bool			Convergence = false;

	unsigned       i, t;

	Rng::seed(seed);

	// define populations
	PopulationT<double> parents(Mu,     
			ChromosomeT< double >(Dimension),
			ChromosomeT< double >(NSigma));

	PopulationT<double> offsprings(Lambda, 
			ChromosomeT< double >(Dimension),
			ChromosomeT< double >(NSigma));

	// minimization task
	parents   .setMinimize();
	offsprings.setMinimize();

	// initialize parent population
	for (i = 0; i < parents.size(); ++i) {
		parents[ i ][ 0 ].initialize(MinInit,   MaxInit);
		parents[ i ][ 1 ].initialize(SigmaInit, SigmaInit);
	}

	// selection parameters
	unsigned numElitists = PlusStrategy ? Mu : 0;

	// standard deviations for mutation of sigma
	double     tau0 = 1. / sqrt(2. * Dimension);
	double     tau1 = 1. / sqrt(2. * sqrt((double)Dimension));

	// this is for plus-strategy only
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

		/* convergenzkriterium */
		if( t > 20 ) {
			double sum = 0.;
			for( auto i : fitness ) {
				sum += i;

			}
			sum /= fitness[fitness.size()-1];
			sum = abs( sum );
			if( sum == fitness.size() ) { Convergence = true; break; }
			fitness.erase( fitness.begin(), fitness.begin() + 1 );

		}
		fitness.push_back( parents.best().fitnessValue() );

	}

	steady_clock::time_point t_1 = steady_clock::now();

	auto p = parents.best();
	solutionFitness = parents.best().fitnessValue();

	res.fitness = p.fitnessValue();
	res.iterations = t;
	res.duration = duration_cast<microseconds>(t_1-t_0).count();
	res.converged = Convergence;

	return res;

}
