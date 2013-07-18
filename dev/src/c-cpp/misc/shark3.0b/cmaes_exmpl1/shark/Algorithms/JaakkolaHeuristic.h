//===========================================================================
/*!
*  \brief Jaakkola's heuristic and related quantities for Gaussian kernel selection
*
*  \author  T. Glasmachers, O. Krause, C. Igel
*  \date    2010
*
*
*  \par Copyright (c) 1999-2010:
*      Institut f&uuml;r Neuroinformatik<BR>
*      Ruhr-Universit&auml;t Bochum<BR>
*      D-44780 Bochum, Germany<BR>
*      Phone: +49-234-32-25558<BR>
*      Fax:   +49-234-32-14209<BR>
*      eMail: Shark-admin@neuroinformatik.ruhr-uni-bochum.de<BR>
*      www:   http://www.neuroinformatik.ruhr-uni-bochum.de<BR>
*
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


#ifndef SHARK_ML_JAAKOLAHEURISTIC_H
#define SHARK_ML_JAAKOLAHEURISTIC_H


#include <shark/Data/Dataset.h>
#include <algorithm>
#include <shark/Core/Traits/ProxyReferenceTraits.h>
namespace shark{


/// \brief Jaakkola's heuristic and related quantities for Gaussian kernel selection
///
/// \par
/// Jaakkola's heuristic method for setting the width parameter of the
/// Gaussian radial basis function kernel is to pick a quantile (usually
/// the median) of the distribution of Euclidean distances between points
/// having different labels. The present implementation computes the kernel
/// width \f$ \sigma \f$ and the bandwidth
///    \f[ \gamma = \frac{1}{2 \sigma^2} \f]
/// based on the median or on any other quantile of the empirical
/// distribution.
///
/// In the original paper, only the distance to the closest point with
/// different label is considered. This behavior can be turned on by
/// an option of the constructor.
class JaakkolaHeuristic
{
public:
	/// Constructor
	/// \param dataset           vector-valued input data
	/// \param nearestFalseNeighbor  if true, only the nearest neighboring point with different label is considered (default false)
	template<class InputType>
	JaakkolaHeuristic(LabeledData<InputType,unsigned int> const& dataset, bool nearestFalseNeighbor = false)
	{
		typedef typename LabeledData<InputType,unsigned int>::const_element_range Elements;
		typedef typename ConstProxyReference<InputType const>::type Element;
		Elements elements = dataset.elements();
		if(!nearestFalseNeighbor) {
			for(typename Elements::iterator it = elements.begin(); it != elements.end(); ++it){
				Element x = it->input;
				typename Elements::iterator itIn = it;
				itIn++;
				for (; itIn != elements.end(); itIn++) {
					if (itIn->label == it->label) continue;
					Element y = itIn->input;
					double dist = distanceSqr(x,y);
					m_stat.push_back(dist);
				}
			}
		} else {
			for(typename Elements::iterator it = elements.begin(); it != elements.end(); ++it){
				double minDistSqr = 0;
				Element x = it->input;
				for (typename Elements::iterator itIn = elements.begin(); itIn != elements.end(); itIn++) {
					if (itIn->label == it->label) continue;
					Element y = itIn->input;
					double dist = distanceSqr(x,y);
					if( (minDistSqr == 0) || (dist < minDistSqr))  minDistSqr = dist;
				}
				m_stat.push_back(minDistSqr);
			}
		}
		std::sort(m_stat.begin(), m_stat.end());
	}
		
	/// Compute the given quantile (usually median)
	/// of the empirical distribution of Euclidean distances
	/// of data pairs with different labels.
	double sigma(double quantile = 0.5)
	{
		std::size_t ic = m_stat.size();
		SHARK_ASSERT(ic > 0);

		std::sort(m_stat.begin(), m_stat.end());

		if (quantile < 0.0)
		{
			// TODO: find minimum
			return std::sqrt(m_stat[0]);
		}
		if (quantile >= 1.0)
		{
			// TODO: find maximum
			return std::sqrt(m_stat[ic-1]);
		}
		else
		{
			// TODO: partial sort!
			double t = quantile * (ic - 1);
			std::size_t i = (std::size_t)floor(t);
			double rest = t - i;
			return ((1.0 - rest) * std::sqrt(m_stat[i]) + rest * std::sqrt(m_stat[i+1]));
		}
	}

	/// Compute the given quantile (usually the median)
	/// of the empirical distribution of Euclidean distances
	/// of data pairs with different labels converted into
	/// a value usable as the gamma parameter of the GaussianRbfKernel.
	double gamma(double quantile = 0.5)
	{
		double s = sigma(quantile);
		return 0.5 / (s * s);
	}


protected:
	/// all pairwise distances
	std::vector<double> m_stat;
};

}
#endif
