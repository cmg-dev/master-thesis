/**
*
* \brief Fitness comparator for the single-objective case. 
* \author T.Voss
* \date 2010-2011
*
* \par Copyright (c):
*      Institut f&uuml;r Neuroinformatik<BR>
*      Ruhr-Universit&auml;t Bochum<BR>
*      D-44780 Bochum, Germany<BR>
*      Phone: +49-234-32-25558<BR>
*      Fax:   +49-234-32-14209<BR>
*      eMail: Shark-admin@neuroinformatik.ruhr-uni-bochum.de<BR>
*      www:   http://www.neuroinformatik.ruhr-uni-bochum.de<BR>
*      <BR>

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
#ifndef SHARK_ALGORITHMS_DIRECTSEARCH_FITNESS_COMPARATOR
#define SHARK_ALGORITHMS_DIRECTSEARCH_FITNESS_COMPARATOR

#include <shark/Algorithms/DirectSearch/EA.h>

namespace shark {

    /**
     * \brief Fitness comparator for the single-objective case.
     *
     * Please note that minimization is assumed here.
     */
    template<typename FitnessType>
    struct FitnessComparator {

	/**
	 * \brief Returns true if fitness of a smaller than fitness of b.
	 */
        template<typename Individual>
        bool operator()( const Individual & a, const Individual & b ) {
            return( a.fitness( FitnessType() )( 0 ) < b.fitness( FitnessType() )( 0 ) );
        }

    };
    
    /**
     * \brief Indirect (pointer,iterator) fitness comparator for the single-objective case.
     *
     * Please note that minimization is assumed here.
     */
    template<typename FitnessType>
    struct IndirectFitnessComparator {
        
        /**
         * \brief Returns true if fitness of a smaller than fitness of b.
         */
        template<typename Individual>
        bool operator()( const Individual & a, const Individual & b ) {
            return( a->fitness( FitnessType() )( 0 ) < b->fitness( FitnessType() )( 0 ) );
        }
        
    };

    /** \brief Convenience typedef for comparing penalized fitness values. */
    typedef FitnessComparator< tag::PenalizedFitness > PenalizedFitnessComparator;
    /** \brief Convenience typedef for comparing unpenalized fitness values. */
    typedef FitnessComparator< tag::UnpenalizedFitness > UnpenalizedFitnessComparator;
    /** \brief Convenience typedef for comparing scaled fitness values. */
    typedef FitnessComparator< tag::ScaledFitness > ScaledFitnessComparator;
    
    /** \brief Convenience typedef for comparing penalized fitness values. */
    typedef IndirectFitnessComparator< tag::PenalizedFitness > PenalizedIndirectFitnessComparator;
    /** \brief Convenience typedef for comparing unpenalized fitness values. */
    typedef IndirectFitnessComparator< tag::UnpenalizedFitness > UnpenalizedIndirectFitnessComparator;
    /** \brief Convenience typedef for comparing scaled fitness values. */
    typedef IndirectFitnessComparator< tag::ScaledFitness > ScaledIndirectFitnessComparator;
}

#endif
