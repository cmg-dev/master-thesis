//===========================================================================
/*!
 *  \file LBFGS.h
 *
 *  \brief LBFGS
 *
 *  The Limited-Memory Broyden, Fletcher, Goldfarb, Shannon (BFGS) algorithm
 *  is a quasi-Newton method for unconstrained real-valued optimization.
 *  See: http://en.wikipedia.org/wiki/LBFGS for details.
 *
 *  \author S. Dahlgaard
 *  \date 2012
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


#ifndef SHARK_ML_OPTIMIZER_LBFGS_H
#define SHARK_ML_OPTIMIZER_LBFGS_H

#include <shark/Algorithms/AbstractSingleObjectiveOptimizer.h>
#include <shark/Core/SearchSpaces/VectorSpace.h>
#include <shark/Algorithms/GradientDescent/LineSearch.h>
#include <shark/LinAlg/Base.h>

#include <deque>

namespace shark {

//! \brief Limited-Memory Broyden, Fletcher, Goldfarb, Shannon algorithm for unconstrained optimization
class LBFGS : public AbstractSingleObjectiveOptimizer< VectorSpace<double> > {
public:
	LBFGS() {
		m_features |= REQUIRES_VALUE;
		m_features |= REQUIRES_FIRST_DERIVATIVE;
		m_numHist = 100;
	}

	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "LBFGS"; }

	void init(const ObjectiveFunctionType &objectiveFunction, const SearchPointType &startingPoint) {
		checkFeatures(objectiveFunction);

		m_linesearch.init(objectiveFunction);
		m_dimension = startingPoint.size();
		m_best.point = startingPoint;
		m_hdiag = 1.0;         // Start with the identity
		m_updThres = 1e-10;       // Reasonable threshold

		// Get space for the different vectors we store.
		m_gradient.resize(m_dimension, false);
		m_searchDirection.resize(m_dimension, false);
		m_oldPoint.resize(m_dimension, false);
		m_searchDirections.clear();
		m_steps.clear();
		
		//in th first step we don't have usefull hessian information so we use the gradient directly.
		m_best.value = objectiveFunction.evalDerivative(m_best.point,m_gradient);
		m_searchDirection = -m_gradient;
		m_initialStepLength = 0.0;//1.0 as step length might be very wrong.
		for (size_t i = 0; i < m_gradient.size(); ++i)
			m_initialStepLength += std::abs(m_gradient(i));
		m_initialStepLength = std::min(1.0, 1.0 / m_initialStepLength);
	}
	
	using AbstractSingleObjectiveOptimizer< VectorSpace<double> >::init;

	/**
	 * \brief Specify the amount of steps to be memorized and used to find the
	 * L-BFGS direction.
	 * \param [in] numhist The amount of steps to use.
	 */
	void setHistCount(unsigned int numhist) {
		SHARK_CHECK(numhist > 0, "[LBFGS::setHistCount] An empty history is not allowed");
		m_numHist = numhist;
	}

	void step(const ObjectiveFunctionType &objectiveFunction) {
		// Perform line search
		m_oldGrad = m_gradient;
		m_oldPoint = m_best.point;
		m_linesearch(m_best.point, m_best.value, m_searchDirection, m_gradient, m_initialStepLength);
		
		// Update the history if necessary
		RealVector y = m_gradient - m_oldGrad;
		RealVector s = m_best.point - m_oldPoint;
		updateHist(y, s);

		// Get the LBFGS direction
		getDirection(m_searchDirection);
		m_initialStepLength = 1.0;
	}

	//from IConfigure
	void configure(const PropertyTree &node) {
		PropertyTree::const_assoc_iterator it = node.find("linesearch");
		if (it!=node.not_found()) {
			m_linesearch.configure(it->second);
		}
	}

	//from ISerializable
	virtual void read(InArchive &archive) {
		archive>>m_linesearch;
		archive>>m_initialStepLength;
		archive>>m_dimension;
		archive>>m_numHist;
		archive>>m_hdiag;
		archive>>m_best.point;
		archive>>m_best.value;
		archive>>m_gradient;
		archive>>m_oldGrad;
		archive>>m_oldPoint;
		archive>>m_searchDirection;
		archive>>m_searchDirections;
		archive>>m_steps;
	}

	virtual void write(OutArchive &archive) const {
		archive<<m_linesearch;
		archive<<m_initialStepLength;
		archive<<m_dimension;
		archive<<m_numHist;
		archive<<m_hdiag;
		archive<<m_best.point;
		archive<<m_best.value;
		archive<<m_gradient;
		archive<<m_oldGrad;
		archive<<m_oldPoint;
		archive<<m_searchDirection;
		archive<<m_searchDirections;
		archive<<m_steps;
	}


	//linesearch handling
	const LineSearch &lineSearch()const {
		return m_linesearch;
	}
	LineSearch &lineSearch() {
		return m_linesearch;
	}

protected: // Methods

	void updateHist(RealVector& y, RealVector &step) {
		//Only update if <y,s> is above some reasonable threshold.
		double ys = inner_prod(y, step);
		if (ys > m_updThres) {
			// Only store m_numHist steps, so possibly pop the oldest.
			if (m_searchDirections.size() >= m_numHist) {
				m_searchDirections.pop_front();
				m_steps.pop_front();
			}
			m_searchDirections.push_back(step);
			m_steps.push_back(y);
			// Update the hessian approximation.
			m_hdiag = ys / inner_prod(y,y);
		}
	}
	/// \brief Get the LBFGS direction. 
	///
	/// This approximates the inverse hessian multiplied by the gradient.
	/// This uses the rho, alpha and beta vectors. Description of these
	/// can be seen in ie. the wiki page of LBFGS.
	void getDirection(RealVector& searchDirection) {
		
		RealVector rho(m_numHist);
		RealVector alpha(m_numHist);
		RealVector beta(m_numHist);

		for (size_t i = 0; i < m_searchDirections.size(); ++i)
			rho(i) = 1.0 / inner_prod(m_steps[i], m_searchDirections[i]);

		searchDirection = -m_gradient;
		for (int i = m_searchDirections.size() - 1; i >= 0; --i) {
			alpha(i) = rho(i) * inner_prod(m_searchDirections[i], searchDirection);
			searchDirection -= alpha(i) * m_steps[i];
		}
		searchDirection *= m_hdiag;
		for (size_t i = 0; i < m_searchDirections.size(); ++i) {
			beta(i) = rho(i) * inner_prod(m_steps[i], searchDirection);
			searchDirection += m_searchDirections[i] * (alpha(i) - beta(i));
		}
	}


protected: // Instance vars

	LineSearch      m_linesearch;

	size_t m_dimension;
	double m_updThres;         // Threshold for when to update history.
	unsigned int m_numHist;          // Number of steps to use for LBFGS.
	// Hessian approximation. We use a diagonal matrix, where each element is
	// the same, so we only need to store one double.
	double          m_hdiag;
	double m_initialStepLength;

	// Gradient, direction, etc.
	RealVector      m_gradient;
	RealVector      m_oldGrad;
	RealVector      m_searchDirection;
	RealVector      m_oldPoint;

	// Saved steps for creating the approximation.
	// Use deque as it gives fast pop.front, push.back and access. Supposedly.
	// dirs holds the values x_(k+1) - x_k
	// steps holds the values g_(k+1) - g_k
	std::deque<RealVector> m_searchDirections;
	std::deque<RealVector> m_steps;
};

}
#endif
