//===========================================================================
/*!
 *  \brief Trainer for the ATM Multi-class Support Vector Machine
 *
 *
 *  \author  T. Glasmachers
 *  \date    2007-2012
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


#ifndef SHARK_ALGORITHMS_MCSVMATMTRAINER_H
#define SHARK_ALGORITHMS_MCSVMATMTRAINER_H


#include <shark/Algorithms/Trainers/AbstractSvmTrainer.h>
#include <shark/Algorithms/QP/QpMcDecomp.h>
#include <shark/Algorithms/QP/QpMcLinear.h>


namespace shark {


///
/// \brief Training of ATM-SVMs for multi-category classification.
///
/// The ATM-SVM is a special support vector machine variant for
/// classification of more than two classes. Given are data
/// tuples \f$ (x_i, y_i) \f$ with x-component denoting input
/// and y-component denoting the label 1, ..., d (see the tutorial on
/// label conventions; the implementation uses values 0 to d-1),
/// a kernel function k(x, x') and a regularization
/// constant C > 0. Let H denote the kernel induced
/// reproducing kernel Hilbert space of k, and let \f$ \phi \f$
/// denote the corresponding feature map.
/// Then the SVM classifier is the function
/// \f[
///     h(x) = \arg \max (f_c(x))
/// \f]
/// \f[
///     f_c(x) = \langle w_c, \phi(x) \rangle + b_c
/// \f]
/// \f[
///     f = (f_1, \dots, f_d)
/// \f]
/// with class-wise coefficients w_c and b_c given by the
/// (primal) optimization problem
/// \f[
///     \min \frac{1}{2} \sum_c \|w_c\|^2 + C \sum_i L(y_i, f(x_i))
/// \f]
/// \f[
///     \text{s.t. } \sum_c f_c = 0
/// \f]
/// The special property of the so-called ATM machine is its
/// loss function, which arises from the application of the
/// total maximum operator to absolute margin violations.
/// Let \f$ h(m) = \max\{0, 1-m\} \f$ denote the hinge loss
/// as a function of the margin m, then the ATM loss is given
/// by
/// \f[
///     L(y, f(x)) = \max_c h((2 \cdot \delta_{c,y} - 1) \cdot f_c(x))
/// \f]
/// where the Kronecker delta is one if its arguments agree and
/// zero otherwise.
///
/// For more details refer to the technical report:<br/>
/// <p>Fast Training of Multi-Class Support Vector Machines. &Uuml; Dogan, T. Glasmachers, and C. Igel, Technical Report 2011/3, Department of Computer Science, University of Copenhagen, 2011.</p>
///
template <class InputType, class CacheType = float>
class McSvmATMTrainer : public AbstractSvmTrainer<InputType, unsigned int>
{
public:

	/// \brief Convenience typedefs:
	/// this and many of the below typedefs build on the class template type CacheType.
	/// Simply changing that one template parameter CacheType thus allows to flexibly
	/// switch between using float or double as type for caching the kernel values.
	/// The default is float, offering sufficient accuracy in the vast majority
	/// of cases, at a memory cost of only four bytes. However, the template
	/// parameter makes it easy to use double instead, (e.g., in case high
	/// accuracy training is needed).
	typedef CacheType QpFloatType;
	typedef blas::matrix<QpFloatType> QpMatrixType;
	typedef blas::matrix_row<QpMatrixType> QpMatrixRowType;
	typedef blas::matrix_column<QpMatrixType> QpMatrixColumnType;

	typedef KernelMatrix<InputType, QpFloatType> KernelMatrixType;
	typedef CachedMatrix< KernelMatrixType > CachedMatrixType;
	typedef PrecomputedMatrix< KernelMatrixType > PrecomputedMatrixType;

	typedef AbstractModel<InputType, RealVector> ModelType;
	typedef AbstractKernelFunction<InputType> KernelType;
	typedef AbstractSvmTrainer<InputType, unsigned int> base_type;

	//! Constructor
	//! \param  kernel         kernel function to use for training and prediction
	//! \param  C              regularization parameter - always the 'true' value of C, even when unconstrained is set
	//! \param  unconstrained  when a C-value is given via setParameter, should it be piped through the exp-function before using it in the solver?
	McSvmATMTrainer(KernelType* kernel, double C, bool unconstrained = false)
	: base_type(kernel, C, unconstrained)
	{ }

	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "McSvmATMTrainer"; }

	void train(KernelExpansion<InputType>& svm, const LabeledData<InputType, unsigned int>& dataset)
	{
		std::size_t i, ic = dataset.numberOfElements();
		unsigned int c, classes = numberOfClasses(dataset);
		// the following test is "<=" rather than "=" to account for the rare case that one fold doesn't contain all classes due to sample scarcity
		SHARK_CHECK(classes <= svm.outputSize(), "[McSvmATMTrainer::train] invalid number of outputs in the kernel expansion");
		svm.setKernel(base_type::m_kernel);
		svm.setBasis(dataset.inputs());
		classes = svm.outputSize();
		std::size_t e, a, p;
		RealVector param = svm.parameterVector();

		// prepare the problem description
		RealVector alpha = RealZeroVector(classes * ic);
		RealVector bias = RealZeroVector(classes);

		// TODO: initialize alpha (and bias) from the parameters
// 		if (svm.hasOffset()) bias = RealVectorRange(param, Range(classes * ic, classes * ic + classes));

		RealMatrix gamma(classes, classes);
		{
			unsigned int y, p;
			for (y=0; y<classes; y++) for (p=0; p<classes; p++) gamma(y, p) = 1.0;
		}
		UIntVector rho(classes);
		{
			unsigned int p;
			for (p=0; p<classes; p++) rho(p) = 0;
		}
		QpSparseArray<QpFloatType> nu(classes*classes, classes, classes*classes);
		{
			unsigned int y, p, r;
			for (r=0, y=0; y<classes; y++)
			{
				for (p=0; p<classes; p++, r++)
				{
					nu.add(r, p, (QpFloatType)((p == y) ? 1.0 : -1.0));
				}
			}
		}
		QpSparseArray<QpFloatType> M(classes * classes * classes, classes, 2 * classes * classes * classes);
		{
			QpFloatType c_ne = (QpFloatType)(-1.0 / (double)classes);
			QpFloatType c_eq = (QpFloatType)1.0 + c_ne;
			for (unsigned int r=0, yv=0; yv<classes; yv++)
			{
				for (unsigned int pv=0; pv<classes; pv++)
				{
					QpFloatType sign = QpFloatType((yv == pv) ? -1 : 1);//cast to keep MSVC happy...
					for (unsigned int yw=0; yw<classes; yw++, r++)
					{
						M.setDefaultValue(r, sign * c_ne);
						if (yw == pv)
						{
							M.add(r, pv, -sign * c_eq);
						}
						else
						{
							M.add(r, pv, sign * c_eq);
							M.add(r, yw, -sign * c_ne);
						}
					}
				}
			}
		}
		KernelMatrixType km(*base_type::m_kernel, dataset.inputs());

		// solve the problem
		if (base_type::precomputeKernel())
		{
			PrecomputedMatrixType matrix(&km);
			QpMcDecomp< PrecomputedMatrixType > solver(matrix, gamma, rho, nu, M, true);
			QpSolutionProperties& prop = base_type::m_solutionproperties;
			// solver.setShrinking(base_type::m_shrinking);
			solver.setShrinking(false);   // hack to avoid shrinking-related bug
			solver.solve(dataset.labels(), this->C(), alpha, base_type::m_stoppingcondition, &prop, (svm.hasOffset() ? &bias : NULL));
		}
		else
		{
			CachedMatrixType matrix(&km, base_type::m_cacheSize);
			QpMcDecomp< CachedMatrixType > solver(matrix, gamma, rho, nu, M, true);
			QpSolutionProperties& prop = base_type::m_solutionproperties;
			// solver.setShrinking(base_type::m_shrinking);
			solver.setShrinking(false);   // hack to avoid shrinking-related bug
			solver.solve(dataset.labels(), this->C(), alpha, base_type::m_stoppingcondition, &prop, (svm.hasOffset() ? &bias : NULL));
		}
		// write the solution into the model
		for (e=0, a=0, i=0; i<ic; i++)
		{
			unsigned int y = dataset.element(i).label;
			for (c=0; c<classes; c++, e++)
			{
				double sum = 0.0;
				unsigned int r = classes * y;
				for (p=0; p<classes; p++, r++) sum += nu(r, c) * alpha(a + p);
				param(e) = sum;
			}
			a += classes;
		}
		if (svm.hasOffset()) RealVectorRange(param, Range(e, e + classes)) = bias;
		svm.setParameterVector(param);

		base_type::m_accessCount = km.getAccessCount();
		if (base_type::sparsify()) svm.sparsify();
	}
};


class LinearMcSvmATMTrainer : public AbstractLinearSvmTrainer
{
public:
	LinearMcSvmATMTrainer(double C, double accuracy = 0.001) : AbstractLinearSvmTrainer(C, accuracy)
	{ }

	/// \brief From INameable: return the class name.
	std::string name() const
	{ return "LinearMcSvmATMTrainer"; }

	void train(LinearModel<CompressedRealVector, RealVector>& model, const LabeledData<CompressedRealVector, unsigned int>& dataset)
	{
		SHARK_CHECK(! model.hasOffset(), "[LinearMcSvmATMTrainer::train] models with offset are not supported (yet).");

		std::size_t dim = model.inputSize();
		std::size_t classes = model.outputSize();
/*
		CompressedRealMatrix w(classes, dim);
		std::vector<CompressedRealMatrixRow> w_s;
		for (std::size_t c=0; c<classes; c++) w_s.push_back(CompressedRealMatrixRow(w, c));
		typedef McPegasos<CompressedRealVector> PegasosType;
		PegasosType::solve(
				dataset,
				PegasosType::emAbsolute,
				PegasosType::elTotalMax,
				true,
				C(),
				w_s,
				std::min((std::size_t)1000, dataset.numberOfElements()),
				accuracy());
*/
		QpMcLinearATM solver(dataset, dim, classes);
		RealMatrix w = solver.solve(C(), m_stoppingcondition, &m_solutionproperties, m_verbosity > 0);
		model.setStructure(w);
	}
};


}
#endif
