//===========================================================================
/*!
*  \file CMA.h
*
*  \brief Implements the most recent version of the non-elitist CMA-ES.
*
*  The algorithm is described in
*
*  Hansen, N., S. Kern (2004). Evaluating the CMA Evolution Strategy
*  on Multimodal Test Functions. In Proceedings of the Eighth
*  International Conference on Parallel Problem Solving from Nature
*  (PPSN VIII), pp. 282-291, LNCS, Springer-Verlag
*
*  \par Copyright (c) 1998-2008:
*      Institut f&uuml;r Neuroinformatik<BR>
*      Ruhr-Universit&auml;t Bochum<BR>
*      D-44780 Bochum, Germany<BR>
*      Phone: +49-234-32-25558<BR>
*      Fax:   +49-234-32-14209<BR>
*      eMail: shark-admin@neuroinformatik.ruhr-uni-bochum.de<BR>
*      www:   http://www.neuroinformatik.ruhr-uni-bochum.de<BR>
*      <BR>
*
*
*  <BR><HR>
*  This file is part of Shark. This library is free software;
*  you can redistribute it and/or modify it under the terms of the
*  GNU General Public License as published by the Free Software
*  Foundation; either version 3, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this library; if not, see <http://www.gnu.org/licenses/>.
*  
*/
//===========================================================================


#ifndef SHARK_EA_CMA_H
#define SHARK_EA_CMA_H

#include <shark/Core/Probe.h>
#include <shark/Algorithms/AbstractSingleObjectiveOptimizer.h>
#include <shark/Core/SearchSpaces/VectorSpace.h>

#include <shark/Statistics/Distributions/MultiVariateNormalDistribution.h>
#include <shark/Algorithms/DirectSearch/TypedIndividual.h>

namespace shark {
	namespace cma {
		/**
		* \brief Models the recombination type.
		*/
		enum RecombinationType {
			EQUAL = 0,
			LINEAR = 1,
			SUPERLINEAR = 2
		};

		/**
		* \brief Models the update type.
		*/
		enum UpdateType {
		    RANK_ONE = 0, ///< Rank-one covariance matrix update.
		    RANK_MU = 1, ///< Rank-mu covariance matrix update.
		    RANK_ONE_AND_MU = 2 ///< Combination of both update variants.
		};

		/**
		* \brief Chromosome of the CMA-ES.
		*/
		struct Chromosome {

			/**
			* \brief Default c'tor.
			*/
			Chromosome( unsigned int dimension = 0 );

			/**
			* \brief Adjusts the dimension of the chromosome.
			*/
			void setDimension( unsigned int dimension );

			/**
			* \brief Serializes the chromosome to the supplied archive.
			* \tparam Archive Type of the archive.
			* \param [in, out] archive Object of type archive.
			* \param [in] version Currently unused.
			*/
			template<typename Archive>
			void serialize( Archive & archive, const unsigned int version ) {
				archive & m_recombinationType;
				archive & m_updateType;

				archive & m_sigma;

				archive & m_cC;
				archive & m_cCU;
				archive & m_cCov;
				archive & m_cSigma;
				archive & m_cSigmaU;
				archive & m_dSigma;

				archive & m_muEff;
				archive & m_muCov;

				archive & m_mean;
				archive & m_weights;

				archive & m_evolutionPathC;
				archive & m_evolutionPathSigma;

				archive & m_mutationDistribution;
			}

			/**
			* \brief Prints the chromosome for debugging purposes.
			*/
			template<typename Stream>
			void print( Stream & s ) const {
				s << "Sigma: " << m_sigma << std::endl;
				s << "cc: " << m_cC << std::endl;
				s << "ccu: " << m_cCU << std::endl;
				s << "ccov: " << m_cCov << std::endl;
				s << "csigma: " << m_cSigma << std::endl;
				s << "csigmaU: " << m_cSigmaU << std::endl;
				s << "dsigma: " << m_dSigma << std::endl;
				s << "mueff: " << m_muEff << std::endl;
				s << "mucov: " << m_muCov << std::endl;
				s << "mean: " << m_mean << std::endl;
				s << "weights: " << m_weights << std::endl;
				s << "pc: " << m_evolutionPathC << std::endl;
				s << "ps: " << m_evolutionPathSigma << std::endl;
				m_mutationDistribution.print( s );
			}

			RecombinationType m_recombinationType; ///< Stores the recombination type.
			UpdateType m_updateType; ///< Stores the update strategy.

			double m_sigma;
			double m_cC; 
			double m_cCU; 
			double m_cCov;
			double m_cSigma;
			double m_cSigmaU;
			double m_dSigma;

			double m_muEff;
			double m_muCov;

			RealVector m_mean;
			RealVector m_weights;

			RealVector m_evolutionPathC;
			RealVector m_evolutionPathSigma;

			shark::MultiVariateNormalDistribution m_mutationDistribution;
		};

	}

	/**
	* \brief Implements the CMA-ES.
	*
	*  The algorithm is described in
	*
	*  Hansen, N., S. Kern (2004). Evaluating the CMA Evolution Strategy
	*  on Multimodal Test Functions. In Proceedings of the Eighth
	*  International Conference on Parallel Problem Solving from Nature
	*  (PPSN VIII), pp. 282-291, LNCS, Springer-Verlag
	*/
	class CMA 
	: public shark::ProbeProvider< CMA >
	, public AbstractSingleObjectiveOptimizer<VectorSpace<double> >
	{
	public:

		/**
		* \brief Default c'tor.
		*/
		CMA();

		/// \brief From INameable: return the class name.
		std::string name() const
		{ return "CMA-ES"; }

		/**
		* \brief Calculates the center of gravity of the given population \f$ \in \mathbb{R}^d\f$.
		*
		* 
		*/
		template<typename Container, typename Extractor>
		RealVector cog( const Container & container, const RealVector & weights, const Extractor & e ) {

			RealVector result( m_numberOfVariables, 0. );

			for( unsigned int j = 0; j < container.size(); j++ )
				result += weights( j ) * e( container[j] );

			return( result );
		}

		/**
		* \brief Calculates lambda for the supplied dimensionality n.
		*/
		static unsigned suggestLambda( unsigned int dimension ) ;

		/**
		* \brief Calculates mu for the supplied lambda and the recombination strategy.
		*/
		static unsigned suggestMu( unsigned int lambda, shark::cma::RecombinationType recomb = shark::cma::SUPERLINEAR ) ;

		/**
		* \brief Configures the algorithm based on the supplied configuration.
		*/
		void configure( const PropertyTree & node ) ;

		void read( InArchive & archive );
		void write( OutArchive & archive ) const;

		using AbstractSingleObjectiveOptimizer<VectorSpace<double> >::init;
		/**
		* \brief Initializes the algorithm for the supplied objective function.
		*/
		void init( ObjectiveFunctionType const& function, SearchPointType const& p);

		/**
		* \brief Initializes the algorithm for the supplied objective function.
		*/
		void init( 
			unsigned int numberOfVariables, 
			unsigned int lambda, 
			unsigned int mu,
			const RealVector & initialSearchPoint,
			double initialSigma,				       
			const boost::optional< RealMatrix > & initialCovarianceMatrix = boost::optional< RealMatrix >() 
		) ;

		/**
		* \brief Executes one iteration of the algorithm.
		*/
		void step(ObjectiveFunctionType const& function);

		/** \brief Accesses the current step size. */
		double sigma() const {
			return m_chromosome.m_sigma;
		}

		/** \brief Accesses the current population mean. */
		RealVector const& mean() const {
			return m_chromosome.m_mean;
		}

		/** \brief Accesses the current weighting vector. */
		RealVector const& weights() const {
			return m_chromosome.m_weights;
		}

		/** \brief Accesses the evolution path for the covariance matrix update. */
		RealVector const& evolutionPath() const {
			return m_chromosome.m_evolutionPathC;
		}

		/** \brief Accesses the evolution path for the step size update. */
		RealVector const& evolutionPathSigma() const {
			return m_chromosome.m_evolutionPathSigma;
		}

		/** \brief Accesses the covariance matrix of the normal distribution used for generating offspring individuals. */
		RealMatrix const& covarianceMatrix() const {
			return m_chromosome.m_mutationDistribution.covarianceMatrix();
		}

		/** 
		 * \brief Accesses the recombination type.
		 */
		cma::RecombinationType recombinationType() const {
			return m_chromosome.m_recombinationType;
		}

		/** 
		 * \brief Returns a mutable reference to the recombination type.
		 */
		cma::RecombinationType & recombinationType() {
			return m_chromosome.m_recombinationType;
		}

		/**
		 * \brief Returns a const reference to the update type.
		 */
		const cma::UpdateType & updateType() const {
			return m_chromosome.m_updateType;
		}

		/**
		 * \brief Returns a mutable reference to the update type.
		 */
		cma::UpdateType& updateType() {
			return m_chromosome.m_updateType;
		}

		/**
		 * \brief Returns a const reference to the chromosome.
		 */
		shark::cma::Chromosome const& chromosome() const {
			return m_chromosome;
		}

		/**
		 * \brief Returns the size of the parent population \f$\mu\f$.
		 */
		unsigned int mu() const {
			return m_mu;
		}

		/**
		 * \brief Returns a mutable reference to the size of the offspring population \f$\mu\f$.
		 */
		unsigned int & lambda(){
			return m_mu;
		}
	protected:
		/**
		* \brief Updates the strategy parameters based on the supplied offspring population.
		*/
		void updateStrategyParameters( const std::vector<TypedIndividual<RealVector, RealVector> > & offspring ) ;
	
		unsigned int m_numberOfVariables; ///< Stores the dimensionality of the search space.
		unsigned int m_mu; ///< The size of the parent population.
		unsigned int m_lambda; ///< The size of the offspring population, needs to be larger than mu.

		shark::cma::Chromosome m_chromosome; ///< Stores the strategy parameters of the algorithm.

		/**** Probes ****/
		boost::shared_ptr< shark::Probe > mp_sigmaProbe;
		boost::shared_ptr< shark::Probe > mp_meanProbe;
		boost::shared_ptr< shark::Probe > mp_weightsProbe;

		boost::shared_ptr< shark::Probe > mp_evolutionPathCProbe;
		boost::shared_ptr< shark::Probe > mp_evolutionPathSigmaProbe;

		boost::shared_ptr< shark::Probe > mp_mutationDistributionProbe;

	};

	/** \brief Registers the CMA with the factory. */
	ANNOUNCE_SINGLE_OBJECTIVE_OPTIMIZER( CMA, soo::RealValuedSingleObjectiveOptimizerFactory );

}

#endif
