/*!
 *  \brief Specific error function for Feed-Forward-Networks which enforces it to have sparse hidden neuron activation
 *
 *  \author O.Krause
 *  \date 2012
 *
 *  \par Copyright (c) 1998-2011:
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
#ifndef SHARK_OBJECTIVEFUNCTIONS_SPARSEFFNETERROR_H
#define SHARK_OBJECTIVEFUNCTIONS_SPARSEFFNETERROR_H


#include <shark/Models/FFNet.h>
#include <shark/ObjectiveFunctions/Loss/AbstractLoss.h>
#include <shark/ObjectiveFunctions/DataObjectiveFunction.h>
#include "Impl/FunctionWrapperBase.h"

#include <boost/scoped_ptr.hpp>
namespace shark{

///
/// \brief Error Function for FFNets which should be trained with sparse activation of the hidden neurons
///
/// This error function optimizes a Network with respect to some loss function similar to the standard
/// ErrorFunction. Additionally another penalty term is added which enforces a sparse activation pattern of
/// the hidden neurons.
/// Given a target mean activation \f$ \rho \f$ the mean activation of hidden neuron j over the whole dataset
/// \f$ \rho_j\f$ is interpreted as the activation propability and penalized using the KL-divergence:
/// \f$ KL(\rho||\rho_j) = \rho log(\frac{\rho}{\rho_j})+(1-\rho) log(\frac{1-\rho}{1-\rho_j}) \f$
///
/// This Error Function has two meta-parameters: rho governs the desired mean activation and
/// beta the strength of regularization.
class SparseFFNetError : public SupervisedObjectiveFunction<RealVector, RealVector>
{
public:

	template<class HiddenNeuron,class VisibleNeuron>
	SparseFFNetError(FFNet<HiddenNeuron,VisibleNeuron>* model, AbstractLoss<RealVector, RealVector>* loss, double rho = 0.5, double beta = 0.1);
	SparseFFNetError(SparseFFNetError const& op):mp_wrapper(op.mp_wrapper->clone()){
		m_features |= HAS_FIRST_DERIVATIVE;
		m_features |= CAN_PROPOSE_STARTING_POINT;
	}
	SparseFFNetError& operator=(SparseFFNetError const& op){
		mp_wrapper.reset(op.mp_wrapper->clone());
		return *this;
	}

	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "SparseFFNetError"; }

	std::size_t numberOfVariables()const{
		return mp_wrapper->numberOfVariables();
	}

	void configure(PropertyTree const& node){
		mp_wrapper->configure(node);
	}
	void setDataset(LabeledData<RealVector, RealVector> const& dataset){
		mp_wrapper->setDataset(dataset);
	}

	void proposeStartingPoint(SearchPointType& startingPoint) const{
		mp_wrapper->proposeStartingPoint(startingPoint);
	}

	double eval(RealVector const& input) const{
        m_evaluationCounter++;
		return mp_wrapper->eval(input);
	}
	ResultType evalDerivative( SearchPointType const& input, FirstOrderDerivative & derivative ) const{
        m_evaluationCounter++;
		return mp_wrapper->evalDerivative(input,derivative);
	}

	friend void swap(SparseFFNetError& op1, SparseFFNetError& op2){
		swap(op1.mp_wrapper,op2.mp_wrapper);
	}

private:
	boost::scoped_ptr<detail::FunctionWrapperBase<RealVector,RealVector> > mp_wrapper;
};

}
#include "Impl/SparseFFNetError.inl"
#endif
