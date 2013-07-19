/*
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
*/
#ifndef SHARK_UNSUPERVISED_RBM_ANALYTICS_H
#define SHARK_UNSUPERVISED_RBM_ANALYTICS_H


#include "Impl/analytics.h"

#include <shark/Unsupervised/RBM/RBM.h>
#include <shark/Data/Dataset.h>
#include <shark/LinAlg/Base.h>
#include <boost/foreach.hpp>

namespace shark {
///\brief Calculates the value of the partition function $Z$.
///
///Only useful for small input and theoritical analysis
///
///@param rbm the rbm for which to calculate the function
///@param beta the inverse temperature of the rbm. default is 1
///@return the value of the partition function $Z*e^(-constant)$
template<class RBMType>
double logPartitionFunction(RBMType const& rbm, double beta = 1.0) {
	//choose correct version based on the enumeration tags
	typedef typename RBMType::HiddenType::StateSpace::EnumerationTag HiddenTag;
	typedef typename RBMType::VisibleType::StateSpace::EnumerationTag VisibleTag;
	
	return detail::logPartitionFunction(rbm,VisibleTag(),HiddenTag(),beta);
}


///\brief Estimates the negative log-likelihood of a set of input vectors under the models distribution using the partition function
///
///Only useful for small input and theoritical analysis
///
///@param rbm the Restricted Boltzman machine for which the negative log likelyhood of the data is to be calculated
///@param inputs the input vectors
///@param partition the value of the partition function of the RBM.
///@param beta the inverse temperature of the rbm. default is 1
///@return the log-likelihood
template<class RBMType>
double negativeLogLikelihoodFromLogPartition(
	RBMType const&rbm, 
	UnlabeledData<RealVector> const& inputs, 
	double logPartition, 
	double beta = 1.0
) {
	double logP=0;
	BOOST_FOREACH(RealMatrix const& batch,inputs.batches()) {
		RealScalarVector betaBatch(batch.size1(),beta);
		logP += sum(rbm.energy().logUnnormalizedPropabilityVisible(batch, betaBatch));
		logP -= batch.size1()*logPartition;
	}
	return -logP;
}

///\brief Estimates the negative log-likelihood of a set of input vectors under the models distribution.
///
///Only useful for small input and theoritical analysis
///
///@param rbm the Restricted Boltzman machine for which the negative log likelyhood of the data is to be calculated
///@param inputs the input vectors
///@param beta the inverse temperature of the rbm. default is 1
///@return the log-likelihood
template<class RBMType>
double negativeLogLikelihood(
	RBMType const& rbm, 
	UnlabeledData<RealVector> const& inputs, 
	double beta = 1.0
) {
	double const logPartition = logPartitionFunction(rbm,beta);
	return negativeLogLikelihoodFromLogPartition(rbm,inputs,logPartition,beta);
}
}
#endif
