//===========================================================================
/*!
 *  \brief Flexible error measure for classication tasks
 *
 *  \author T. Glasmachers
 *  \date 2011
 *
 *  \par Copyright (c) 2011:
 *      Institut f&uuml;r Neuroinformatik<BR>
 *      Ruhr-Universit&auml;t Bochum<BR>
 *      D-44780 Bochum, Germany<BR>
 *      Phone: +49-234-32-25558<BR>
 *      Fax:   +49-234-32-14209<BR>
 *      eMail: Shark-admin@neuroinformatik.ruhr-uni-bochum.de<BR>
 *      www:   http://www.neuroinformatik.ruhr-uni-bochum.de<BR>
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

#ifndef SHARK_OBJECTIVEFUNCTIONS_LOSS_DISCRETELOSS_H
#define SHARK_OBJECTIVEFUNCTIONS_LOSS_DISCRETELOSS_H


#include <shark/ObjectiveFunctions/Loss/AbstractLoss.h>


namespace shark {


///
/// \brief flexible loss for classification
///
/// \par
/// The DiscreteLoss class allows for the definition of
/// a cost matrix applied to a finite number of classes.
/// The cost of correct classification must be zero, all
/// other costs must be non-negative.
///
/// \par
/// Note: As a special case, this loss can be used to provide
/// a balanced error signal for unbalanced data sets.
///
class DiscreteLoss : public AbstractLoss<unsigned int, unsigned int>
{
public:

	/// Constructor
	/// \param  cost     cost matrix in the format (target, prediction).
	DiscreteLoss(RealMatrix const& cost);


	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "DiscreteLoss"; }

	/// inherited from AbstractLoss, evaluation of the loss function
	double eval(BatchLabelType const& target, BatchOutputType const& prediction) const;

	/// Define a new cost structure given by an explicit cost matrix.
	/// \param  cost   cost matrix in the format (target, prediction).
	void defineCostMatrix(RealMatrix const& cost);

	/// Define a new cost structure so that the cost of misclassifying
	/// a pattern is anti-proportional to the frequency of its class.
	/// This amounts to balancing the class-wise cost in unbalanced
	/// data sets (i.e., where one class is far more frequent than
	/// another).
	///
	/// \param  labels   label set to which the balanced loss should be adapted
	void defineBalancedCost(UnlabeledData<unsigned int> const& labels);

protected:
	/// cost matrix
	RealMatrix m_cost;
};


}
#endif
