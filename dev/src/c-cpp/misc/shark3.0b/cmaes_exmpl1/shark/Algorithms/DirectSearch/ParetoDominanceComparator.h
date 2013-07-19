/**
 *
 * \brief Implementation of the Pareto-Dominance relation.
 *
 *  The function is described in
 *
 *  Christian Igel, Nikolaus Hansen, and Stefan Roth. 
 *  Covariance Matrix Adaptation for Multi-objective Optimization. 
 *  Evolutionary Computation 15(1), pp. 1-28, 2007
 *
 * <BR><HR>
 * This file is part of Shark. This library is free software;
 * you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation; either version 3, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PARETODOMINANCECOMPARATOR_H
#define PARETODOMINANCECOMPARATOR_H

#include <shark/Algorithms/DirectSearch/Traits/FitnessTraits.h>

namespace shark {
  /**
   * \brief Implementation of the Pareto-Dominance relation under the assumption of all objectives to be minimized.
   * \tparam FitnessType Models the fitness type, either Penalized or Unpenalized.
   */
   template<typename FitnessType>
	struct ParetoDominanceComparator {

	  BOOST_STATIC_CONSTANT( int, A_STRICTLY_DOMINATES_B = 3 ); ///< A strictly dominates B.
	  BOOST_STATIC_CONSTANT( int, A_WEAKLY_DOMINATES_B = 2 ); ///< A weakly dominates B.
	  BOOST_STATIC_CONSTANT( int, A_EQUALS_B = 1 ); ///< A equals B for every coordinate.
	  BOOST_STATIC_CONSTANT( int, ABNORMAL = 0 ); ///< Exceptional value, marks an error.
	  BOOST_STATIC_CONSTANT( int, B_STRICTLY_DOMINATES_A = -3 ); ///< B strictly dominates A.
	  BOOST_STATIC_CONSTANT( int, B_WEAKLY_DOMINATES_A = -2 ); ///< B weakly dominates B.
	  BOOST_STATIC_CONSTANT( int, TRADE_OFF = -1 ); ///< Both A and B are a valid trade-off.

	  /**
	   * \brief Compares two individuals with respect to the Pareto-Dominance relation.
	   * \tparam IndividualType The type of the individuals, needs to be a model of TypedIndividual.
	   * \param [in] i1 Individual A.
	   * \param [in] i2 Individual B.
	   * \returns An integer with values according to the constanst defined within this class.
	   */ 
		template<typename IndividualType>
		int operator()( const IndividualType & i1, const IndividualType & i2 ) {
			FitnessTraits<IndividualType> ft;

			unsigned flag1 = 0;
			unsigned flag2 = 0;
			unsigned flag3 = 0;

			unsigned int NoOfObj = ft( i1, FitnessType() ).size();//noObjectives();
			// std::cout << "(II) noObj: " << NoOfObj << std::endl;
			for (unsigned i = NoOfObj; i--;) {
				// if( i1.fitness( FitnessType() )[ i ] > i2.fitness( FitnessType() )[ i ] )
				if( ft( i1, FitnessType() )[ i ] > ft( i2, FitnessType() )[ i ] )
					flag1++;
				// else if( i1.fitness( FitnessType() )[ i ] < i2.fitness( FitnessType() )[ i ] )
				else if( ft( i1, FitnessType() )[ i ] < ft( i2, FitnessType() )[ i ] )
					flag3++;
				else
					flag2++;
			}

			if (flag1 + flag2 + flag3 != NoOfObj)
				return ABNORMAL; // abnormal
			else if (flag3 == NoOfObj)
				return( A_STRICTLY_DOMINATES_B ); // i1 dominates i2 completely
			else if (flag3 != 0 && flag1 == 0)
				return( A_WEAKLY_DOMINATES_B ); // i1 dominates i2 imcompletely
			else if (flag2 == NoOfObj)
				return( A_EQUALS_B ); // i1 equals i2
			else if (flag1 == NoOfObj)
				return( B_WEAKLY_DOMINATES_A ); // i2 dominates i1 completely
			else if (flag1 != 0 && flag3 == 0)
				return( B_STRICTLY_DOMINATES_A ); // i2 dominates i1 imcompletely

			return( TRADE_OFF ); // trade off
		}

	  /**
	   * \brief Compares two individuals with respect to the Pareto-Dominance relation.
	   * \tparam IndividualType The type of the individuals, needs to be a model of TypedIndividual.
	   * \tparam Extractor Functional type that allows for projecting the IndividualType in \f$\mathbb{R}^m\f$.
	   * \param [in] i1 Individual A.
	   * \param [in] i2 Individual B.
	   * \param [in] e Function object projecting the IndividualType in \f$\mathbb{R}^m\f$.
	   * \returns An integer with values according to the constanst defined within this class.
	   */
		template<typename IndividualType, typename Extractor>
		int operator()( const IndividualType & i1, const IndividualType & i2, Extractor & e ) {
			unsigned flag1 = 0;
			unsigned flag2 = 0;
			unsigned flag3 = 0;

			// unsigned int NoOfObj = i1.noObjectives();
			unsigned int NoOfObj = std::min( e( i1 ).size(), e( i2 ).size() );

			// std::cout << "No objectives: " << NoOfObj << std::endl;

			for (unsigned i = NoOfObj; i--;) {
				if( e( i1 )[i] > e( i2 )[i] )
					flag1++;
				else if( e( i1 )[i] < e( i2 )[i] )
					flag3++;
				else
					flag2++;
			}

			if (flag1 + flag2 + flag3 != NoOfObj)
				return ABNORMAL; // abnormal
			else if (flag3 == NoOfObj)
				return( A_STRICTLY_DOMINATES_B ); // i1 dominates i2 completely
			else if (flag3 != 0 && flag1 == 0)
				return( A_WEAKLY_DOMINATES_B ); // i1 dominates i2 imcompletely
			else if (flag2 == NoOfObj)
				return( A_EQUALS_B ); // i1 equals i2
			else if (flag1 == NoOfObj)
				return( B_WEAKLY_DOMINATES_A ); // i2 dominates i1 completely
			else if (flag1 != 0 && flag3 == 0)
				return( B_STRICTLY_DOMINATES_A ); // i2 dominates i1 imcompletely

			return( TRADE_OFF ); // trade off
		}



	};
}
#endif // PARETODOMINANCECOMPARATOR_H
