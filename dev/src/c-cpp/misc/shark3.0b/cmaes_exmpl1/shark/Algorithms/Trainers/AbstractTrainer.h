//===========================================================================
/*!
 *  \brief Abstract Trainer Interface.
 *
 *  \author O. Krause, T.Glasmachers
 *  \date 2010-2011
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
//===========================================================================
#ifndef SHARK_ALGORITHMS_TRAINERS_ABSTRACTTRAINER_H
#define SHARK_ALGORITHMS_TRAINERS_ABSTRACTTRAINER_H


#include <shark/Core/IConfigurable.h>
#include <shark/Core/INameable.h>
#include <shark/Core/ISerializable.h>
#include <shark/Data/Dataset.h>
#include <shark/Models/AbstractModel.h>

namespace shark {


///
/// \brief Superclass of supervised learning algorithms
///
/// \par
/// AbstractTrainer is the super class of all trainers,
/// i.e., procedures for training or learning model
/// parameters. It provides a single virtual function to
/// train the model.
///
/// \par
/// Note: Most learning algorithms of this type operate on
/// a special model type, such as a linear model, a kernel
/// expansion, etc. Thus, these algorithms should provide
/// a specialized train method accepting only this model
/// type. The virtual train method should be overriden
/// with a method that checks the type of the model and
/// calls the specialized train method.
///
template <class Model, class LabelTypeT = typename Model::OutputType>
class AbstractTrainer : public IConfigurable, public INameable, public ISerializable
{
public:
	typedef Model ModelType;
	typedef typename ModelType::InputType InputType;
	typedef LabelTypeT LabelType;
	/// Core of the Trainer interface
	virtual void train(ModelType& model, const LabeledData<InputType, LabelType>& dataset) = 0;
};


///
/// \brief Superclass of unsupervised learning algorithms
///
/// \par
/// AbstractUnsupervisedTrainer is the superclass of all
/// unsupervised learning algorithms. It consists of a
/// single virtual function to train the model.
///
/// \par
/// Note: Most learning algorithms of this type operate on
/// a special model type, such as a linear model, a kernel
/// expansion, or a nearest neighbor model. Thus, these
/// algorithms should provide a specialized train method
/// that accepts only this model type. The virtual train
/// method should be overriden with a method that checks
/// the type of the model and calls the specialized train
/// method.
///
template <class Model>
class AbstractUnsupervisedTrainer : public IConfigurable, public INameable, public ISerializable
{
public:
	typedef Model ModelType;
	typedef typename Model::InputType InputType;
	/// Core of the Trainer interface
	virtual void train(ModelType& model, const UnlabeledData<InputType>& inputset) = 0;
};


}
#endif
