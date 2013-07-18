//===========================================================================
/*!
 *  \file SteepestDescent.h
 *
 *  \brief SteepestDescent
 *
 *  \author O. Krause
 *  \date 2010
 *
 *  \par Copyright (c) 1998-2007:
 *      Institut f&uuml;r Neuroinformatik<BR>
 *      Ruhr-Universit&auml;t Bochum<BR>
 *      D-44780 Bochum, Germany<BR>
 *      Phone: +49-234-32-25558<BR>
 *      Fax:   +49-234-32-14209<BR>
 *      eMail: Shark-admin@neuroinformatik.ruhr-uni-bochum.de<BR>
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
#ifndef SHARK_ML_OPTIMIZER_STEEPESTDESCENT_H
#define SHARK_ML_OPTIMIZER_STEEPESTDESCENT_H

#include <shark/Algorithms/AbstractSingleObjectiveOptimizer.h>
#include <shark/Core/SearchSpaces/VectorSpace.h>

namespace shark{

///@brief Standard steepest descent.
class SteepestDescent : public AbstractSingleObjectiveOptimizer<VectorSpace<double> >
{
public:
	SteepestDescent() {
		m_features |= REQUIRES_FIRST_DERIVATIVE;

		m_learningRate = 0.1;
		m_momentum = 0.3;
	}

	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "SteepestDescent"; }

	void init(const ObjectiveFunctionType & objectiveFunction, const SearchPointType& startingPoint) {
		checkFeatures(objectiveFunction);

		m_path.resize(startingPoint.size());
		m_path.clear();
		m_best.point = startingPoint;
		m_best.value = objectiveFunction.evalDerivative(m_best.point,m_derivative);
	}
	using AbstractSingleObjectiveOptimizer<VectorSpace<double> >::init;

	void configure( const PropertyTree & node ) {
		m_learningRate=node.get("learningRate",0.1);
		m_momentum=node.get("momentum",0.3);
	}

	/*!
	 *  \brief get learning rate
	 */
	double learningRate() const {
		return m_learningRate;
	}

	/*!
	 *  \brief set learning rate
	 */
	void setLearningRate(double learningRate) {
		m_learningRate = learningRate;
	}

	/*!
	 *  \brief get momentum parameter
	 */
	double momentum() const {
		return m_momentum;
	}

	/*!
	 *  \brief set momentum parameter
	 */
	void setMomentum(double momentum) {
		m_momentum = momentum;
	}
	/*!
	 *  \brief updates searchdirection and then does simple gradient descent
	 */
	void step(const ObjectiveFunctionType& objectiveFunction) {
		m_path = -m_learningRate * m_derivative + m_momentum * m_path;
		m_best.point+=m_path;
		m_best.value = objectiveFunction.evalDerivative(m_best.point,m_derivative);
	}
	virtual void read( InArchive & archive )
	{
		archive>>m_path;
		archive>>m_learningRate;
		archive>>m_momentum;
	}

	virtual void write( OutArchive & archive ) const
	{
		archive<<m_path;
		archive<<m_learningRate;
		archive<<m_momentum;
	}

private:
	RealVector m_path;
	ObjectiveFunctionType::FirstOrderDerivative m_derivative;
	double m_learningRate;
	double m_momentum;
};

}
#endif

