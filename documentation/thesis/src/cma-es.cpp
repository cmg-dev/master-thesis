CMA_ES_MkI( Ueber9000<double> *ueber9000, double seed, const bool PlusStrategy = false ) {
	// EA parameters
	CMA cma;
	steady_clock::time_point t_0 = steady_clock::now();
	
	const unsigned Iterations = 1000;
	const double MinInit = 1.;
	const double MaxInit = 1.;
	const double GlobalStepInit = 1.;
	const int Dimension = ueber9000->Dimension;
	unsigned Lambda = cma.suggestLambda(Dimension);
	unsigned Mu = cma.suggestMu(Lambda);

	T res;
	
	// define populations for minimization task
	Population parents (Mu,
			ChromosomeT< double >( Dimension ),
			ChromosomeT< double >( Dimension ));
	Population offsprings (Lambda,
			ChromosomeT< double >( Dimension ),
			ChromosomeT< double >( Dimension ));
	
	offsprings		.setMinimize( );
	parents			.setMinimize( );
	
	// initialize parent populations center of gravity
	for( int i = 0; i < parents.size( ); ++i )
		static_cast< ChromosomeT< double >& >( parents[i][0] ).
			initialize(MinInit, MaxInit);

	for( int j = 1; j < parents.size( ); ++j )
		static_cast< ChromosomeT< double >& >( parents[j][0] ) =
			static_cast< ChromosomeT< double >& >( parents[0][0] );

	// strategy parameters
	vector< double > variance( Dimension );

	for(int i = 0; i < Dimension; i++) variance[i] = 1.;
	
	cma.init(Dimension, variance, GlobalStepInit, parents,
				CMA::superlinear, CMA::rankmu);

	//
	// iterate
	//
	unsigned t ;
	for( t = 0; t < Iterations; ++t ) {
		for(unsigned k = 0; k < offsprings.size( ); k++ ) {
			cma.create(offsprings[k]);
			offsprings[k].setFitness(
					(ueber9000->*ueber9000->evaluate)(
						static_cast<ChromosomeT<double> &>(offsprings[k][0])
					)
			);

		}
		// select (mu,lambda) or (mu+lambda)
		parents.selectMuLambda(offsprings, 0u);
		// update strategy parameters
		cma.updateStrategyParameters(parents);

		if( parents.best().fitnessValue() < minSolutionFitness ) break;
		
	}
	steady_clock::time_point t_1 = steady_clock::now();

	Individual& best = parents.best();
	
	res.fitness = best.fitnessValue();
	res.iterations = t;
	res.valCont		= static_cast< ChromosomeT< double >& >( best[0] );
	res.duration = duration_cast<microseconds>(t_1-t_0).count();
	return res;
}
