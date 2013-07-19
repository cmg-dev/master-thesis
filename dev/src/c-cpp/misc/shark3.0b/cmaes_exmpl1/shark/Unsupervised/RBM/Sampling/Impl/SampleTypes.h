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
#ifndef SHARK_UNSUPERVISED_RBM_SAMPLING_IMPL_SAMPLETYPES_H
#define SHARK_UNSUPERVISED_RBM_SAMPLING_IMPL_SAMPLETYPES_H

#include <shark/Data/BatchInterfaceAdaptStruct.h>

namespace shark{
namespace detail{
///\brief Represents a single sample of the GibbsOperator.
///
///This class is not actually used by the GibbsOperator since it works only on a Batch of samples.
///Still you need this type to get Batch<GibbsSample<...> >::type. Therefore it is only useful for direct use,
///when an explicit copy of a sample is needed.
template<class Statistics>
struct GibbsSample{
public:
	RealVector input;
	Statistics statistics;
	RealVector state;
	
	///\brief Constructs sample with size neurons
	GibbsSample(){}
	explicit GibbsSample(std::size_t numNeurons):
	input(numNeurons),statistics(numNeurons),state(numNeurons)
	{}
	GibbsSample(RealVector const& input, Statistics const& statistics, RealVector const& state)
	:input(input),statistics(statistics),state(state)
	{}
	
	friend void swap(GibbsSample& sample1, GibbsSample& sample2){
		using std::swap;
		swap(sample1.input,sample2.input);
		swap(sample1.statistics,sample2.statistics);
		swap(sample1.state,sample2.state);
	}
};

template<class HiddenSample, class VisibleSample>
struct MarkovChainSample{
	HiddenSample hidden;
	VisibleSample visible;
	double energy;
		
	explicit MarkovChainSample(std::size_t hiddenNeurons, std::size_t visibleNeurons)
	:hidden(hiddenNeurons),visible(visibleNeurons),energy(0){}

	explicit MarkovChainSample(HiddenSample const& hidden, VisibleSample const& visible, double energy)
	:hidden(hidden),visible(visible),energy(energy)
	{}
	
	friend void swap(MarkovChainSample& sample1, MarkovChainSample& sample2){
		using std::swap;
		swap(sample1.hidden,sample2.hidden);
		swap(sample1.visible,sample2.visible);
		swap(sample1.energy,sample2.energy);
	}
};
}
//now create the batch specialisation for our new sample types

#define GibbsSampleVars (RealVector, input)(Statistics, statistics)(RealVector, state)
template<class Statistics>
struct Batch< detail::GibbsSample<Statistics> >{
	SHARK_CREATE_BATCH_INTERFACE( detail::GibbsSample<Statistics>,GibbsSampleVars)
};
#undef GibbsSampleVars

template<class Hidden, class Visible>
struct Batch< detail::MarkovChainSample<Hidden,Visible> >{
private:
	SHARK_FUSION_DEFINE_STRUCT_INLINE(FusionType, 
		SHARK_TRANSFORM_BATCH_ATTRIBUTES_TPL(type,(Hidden, hidden)(Visible, visible)(double, energy))
	)
public:
	struct type:public detail::FusionFacade<FusionType>{
		typedef detail::MarkovChainSample<Hidden,Visible> value_type;
	
		SHARK_CREATE_BATCH_REFERENCES_TPL((Hidden, hidden)(Visible, visible)(double, energy))
		SHARK_CREATE_BATCH_ITERATORS()
		
		type(){}
		type(std::size_t batchSize, std::size_t numVisible, std::size_t numHidden){
			FusionType::visible.resize(batchSize,numVisible);
			FusionType::hidden.resize(batchSize,numHidden);
			FusionType::energy.resize(batchSize);
		}
		
		friend void swap(type& op1, type& op2){
			boost::fusion::swap(fusionize(op1),fusionize(op2));
		}
		std::size_t size()const{
			return shark::size(boost::fusion::at_c<0>(fusionize(*this)));
		}
		template<class Archive>
		void serialize(Archive & archive,unsigned int version)
		{
			boost::fusion::for_each(fusionize(*this), detail::ItemSerializer<Archive>(archive));
		}
	};
	typedef detail::MarkovChainSample<Hidden,Visible> value_type;
	typedef typename type::reference reference;
	typedef typename type::const_reference const_reference;
	typedef typename type::iterator iterator;
	typedef typename type::const_iterator const_iterator;

	static type createBatch(value_type const& input, std::size_t size = 1){
		return type(size,shark::size(FusionType::visible),shark::size(FusionType::hidden));
	}
};
}
#endif
