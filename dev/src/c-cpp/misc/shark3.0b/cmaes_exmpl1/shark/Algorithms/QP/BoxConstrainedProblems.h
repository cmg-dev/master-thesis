/*!
 *  \brief Quadratic program definitions.
 *
 *  \author  T. Glasmachers, O.Krause
 *  \date    2013
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
#ifndef SHARK_ALGORITHMS_QP_BOXCONSTRAINEDPROBLEMS_H
#define SHARK_ALGORITHMS_QP_BOXCONSTRAINEDPROBLEMS_H
 
#include <shark/Algorithms/QP/QpSolver.h>
 

namespace shark {

/// \brief Working set selection by maximization of the projected gradient.
///
/// This selection operator picks a single variable index.
struct MaximumGradientCriterion{
	template<class Problem>
	double operator()(Problem& problem, std::size_t& i, std::size_t& j){
		double largestGradient = 0;

		for (std::size_t a = 0; a < problem.active(); a++){
			double v = problem.alpha(a);
			double g = problem.gradient(a);
			if (v < problem.boxMax(a)){
				if (g > largestGradient){
					largestGradient = g;
					i = a;
				}
			}
			if (v > problem.boxMin(a)){
				if (-g > largestGradient){
					largestGradient = -g;
					i = a;
				}
			}
		}
		j = i;  // working set consists of a single variable

		return largestGradient;
	}

	void reset(){}
};

/// \brief Working set selection by maximization of the dual objective gain.
struct MaximumGainCriterion{
	template<class Problem>
	double operator()(Problem& problem, std::size_t& i, std::size_t& j){
		//choose first variable by first order criterion
		MaximumGradientCriterion firstOrder;
		double maxGrad = firstOrder(problem,i,j);
		if (maxGrad == 0.0) return maxGrad;

		double gi = problem.gradient(i);
		typename Problem::QpFloatType* q = problem.quadratic().row(i, 0, problem.active());
		double Qii = problem.diagonal(i);

		// select second variable j with second order method
		double maxGain = 0.0;
		for (std::size_t a=0; a<problem.active(); a++)
		{
			if (a == i) continue;
			double aa = problem.alpha(a);
			double ga = problem.gradient(a);
			if ((aa > problem.boxMin(a) && ga < 0.0) 
			|| (aa < problem.boxMax(a) && ga > 0.0)){
				double Qia = q[a];
				double Qaa = problem.diagonal(a);

				double QD = Qii * Qaa;
				double detQ = QD - Qia * Qia;
				if (detQ < 1e-10 * QD)
				{
					if (Qii == 0.0 && Qaa == 0.0)
					{
						// Q has rank zero
						if (gi != 0.0 || ga != 0.0)
						{
							j = a;
							return maxGrad;		// infinite gain, return immediately
						}
					}
					else
					{
						// Q has rank one
						if (Qii * ga - Qia * gi != 0.0)
						{
							j = a;
							return maxGrad;		// infinite gain, return immediately
						}
						else
						{
							double g2 = ga*ga + gi*gi;
							double gain = (g2*g2) / (ga*ga*Qaa + 2.0*ga*gi*Qia + gi*gi*Qii);
							if (gain > maxGain)
							{
								maxGain = gain;
								j = a;
							}
						}
					}
				}
				else
				{
					// Q has rank two
					double gain = (ga*ga*Qii - 2.0*ga*gi*Qia + gi*gi*Qaa) / detQ;
					if (gain > maxGain)
					{
						maxGain = gain;
						j = a;
					}
				}
			}
		}

		return maxGrad;		// solution is not optimal
	}

	void reset(){}
};

/// \brief Quadratic program with box constraints.
///
/// \par
/// An instance of this class represents a quadratic program of the type
/// TODO: write documentation!
///
template<class SVMProblem>
class BoxConstrainedProblem{
public:
	typedef typename SVMProblem::QpFloatType QpFloatType;
	typedef typename SVMProblem::MatrixType MatrixType;
	typedef MaximumGainCriterion PreferedSelectionStrategy;

	BoxConstrainedProblem(SVMProblem& problem)
	: m_problem(problem)
	, m_gradient(problem.linear)
	, m_active (problem.dimensions())
	, m_alphaStatus(problem.dimensions(),AlphaFree){
		//compute the gradient if alpha != 0
		for (std::size_t i=0; i != dimensions(); i++){
			double v = alpha(i);
			if (v != 0.0){
				QpFloatType* q = quadratic().row(i, 0, dimensions());
				for (std::size_t a=0; a < dimensions(); a++) 
					m_gradient(a) -= q[a] * v;
			}
			updateAlphaStatus(i);
		}
	}
	std::size_t dimensions()const{
		return m_problem.dimensions();
	}

	std::size_t active()const{
		return m_active;
	}

	double boxMin(std::size_t i)const{
		return m_alphaStatus[i]==AlphaDeactivated? alpha(i): m_problem.boxMin(i);
	}
	double boxMax(std::size_t i)const{
		return m_alphaStatus[i]==AlphaDeactivated? alpha(i): m_problem.boxMax(i);
	}
	bool isLowerBound(std::size_t i)const{
		return m_alphaStatus[i] & AlphaLowerBound;
	}
	bool isUpperBound(std::size_t i)const{
		return m_alphaStatus[i] & AlphaUpperBound;
	}

	/// representation of the quadratic part of the objective function
	MatrixType& quadratic(){
		return m_problem.quadratic;
	}

	double linear(std::size_t i)const{
		return m_problem.linear(i);
	}

	double alpha(std::size_t i)const{
		return m_problem.alpha(i);
	}

	double diagonal(std::size_t i)const{
		return m_problem.diagonal(i);
	}

	double gradient(std::size_t i)const{
		return m_gradient(i);
	}
	
	std::size_t permutation(std::size_t i)const{
		return m_problem.permutation[i];
	}

	RealVector getUnpermutedAlpha()const{
		RealVector alpha(dimensions());
		for (std::size_t i=0; i<dimensions(); i++) 
			alpha(m_problem.permutation[i]) = m_problem.alpha(i);
		return alpha;
	}

	///\brief Does an update of SMO given a working set with indices i and j.
	virtual void updateSMO(std::size_t i, std::size_t j){
		SIZE_CHECK(i < active());
		SIZE_CHECK(j < active());
		if(i == j){//both variables are identical, thus solve the 1-d problem.
			// get the matrix row corresponding to the working set
			QpFloatType* q = quadratic().row(i, 0, active());

			// update alpha, that is, solve the sub-problem defined by i
			double numerator = gradient(i);
			double denominator = diagonal(i);
			double mu = numerator / denominator;

			mu = boundedAlphaUpdate(i,mu);
			// update the gradient
			for (std::size_t a = 0; a < active(); a++) 
				m_gradient(a) -= mu * q[a];
			
			updateAlphaStatus(i);
			return;
		}
		
		double Li = boxMin(i);
		double Ui = boxMax(i);
		double Lj = boxMin(j);
		double Uj = boxMax(j);

		// get the matrix rows corresponding to the working set
		QpFloatType* qi = quadratic().row(i, 0, active());
		QpFloatType* qj = quadratic().row(j, 0, active());

		// solve the 2D sub-problem imposed by the two chosen variables
		double mu_i = 0.0;
		double mu_j = 0.0;
		solve2DBox(alpha(i), alpha(j),
			m_gradient(i), m_gradient(j),
			diagonal(i), qi[j], diagonal(j),
			Li, Ui, Lj, Uj,
			mu_i, mu_j
		);
		
		mu_i= boundedAlphaUpdate(i,mu_i);
		mu_j= boundedAlphaUpdate(j,mu_j);

		// update the internal state
		for (std::size_t a = 0; a < active(); a++) 
			m_gradient(a) -= mu_i * qi[a] + mu_j * qj[a];
			
		updateAlphaStatus(i);
		updateAlphaStatus(j);
	}

	///\brief Returns the current function value of the problem.
	double functionValue()const{
		return 0.5*inner_prod(m_gradient+m_problem.linear,m_problem.alpha);
	}

	bool shrink(double){return false;}
	void reshrink(){}
	void unshrink(){}

	///\brief Remove the i-th example from the problem.
	virtual void deactivateVariable(std::size_t i){
		SIZE_CHECK(i < dimensions());
		double alphai = alpha(i);
		m_problem.alpha(i) = 0;
		//update the internal state
		QpFloatType* qi = quadratic().row(i, 0, active());
		for (std::size_t a = 0; a < active(); a++) 
			m_gradient(a) += alphai * qi[a];
		m_alphaStatus[i] = AlphaDeactivated;
	}
	///\brief Reactivate an previously deactivated variable.
	void activateVariable(std::size_t i){
		SIZE_CHECK(i < dimensions());
		m_alphaStatus[i] = AlphaFree;
		updateAlphaStatus(i);
	}
	
	/// exchange two variables via the permutation
	void flipCoordinates(std::size_t i, std::size_t j)
	{
		SIZE_CHECK(i < dimensions());
		SIZE_CHECK(j < dimensions());
		if (i == j) return;

		m_problem.flipCoordinates(i, j);
		std::swap( m_gradient[i], m_gradient[j]);
		std::swap( m_alphaStatus[i], m_alphaStatus[j]);
	}
	
	/// \brief adapts the linear part of the problem and updates the internal data structures accordingly.
	virtual void setLinear(std::size_t i, double newValue){
		m_gradient(i) -= linear(i);
		m_gradient(i) += newValue;
		m_problem.linear(i) = newValue;
	}

protected:
	SVMProblem& m_problem;

	/// gradient of the objective function at the current alpha
	RealVector m_gradient;	

	std::size_t m_active;

	std::vector<char> m_alphaStatus;

	/// \brief Bounds the given alpha value between lower and upper bound in a numerically stable way.
	double boundedAlphaUpdate(std::size_t i, double step){
		SIZE_CHECK(i < active());
		double& ai = m_problem.alpha(i);
		if (ai+step < boxMin(i)){
			step = -ai+boxMin(i);
			ai = boxMin(i);
		}
		else if (ai+step > boxMax(i)){
			step = -ai+boxMax(i);
			ai = boxMax(i);
		}
		else ai +=step;
		return step;
	}

	void updateAlphaStatus(std::size_t i){
		SIZE_CHECK(i < dimensions());
		m_alphaStatus[i] = AlphaFree;
		if(m_problem.alpha(i) == boxMax(i))
			m_alphaStatus[i] |= AlphaUpperBound;
		if(m_problem.alpha(i) == boxMin(i))
			m_alphaStatus[i] |= AlphaLowerBound;
	}

	/// Internally used by Solve2D;
	/// computes the solution of a
	/// one-dimensional sub-problem.
	double stepEdge(double alpha, double g, double Q, double L, double U, double& mu)
	{
		// compute the optimal unconstrained step
		double muHat = g / Q;

		// check for numerical problems
		if( !boost::math::isnormal( muHat ) )
		{
			if (g > 0.0) mu = 1e100;
			else mu = -1e100;
			return 1e100;
		}

		// compute the optimal constrained step
		double mu_g;
		if (muHat <= L - alpha)
		{
			mu_g = L - alpha;
			mu = -1e100;
		}
		else if (muHat >= U - alpha)
		{
			mu_g = U - alpha;
			mu = 1e100;
		}
		else
		{
			mu_g = muHat;
			mu = muHat;
		}

		// compute (twice) the gain
		double deltaMu = muHat - mu_g;
		return (muHat * muHat - deltaMu * deltaMu) * Q;
	}

	/// Exact solver for a two-dimensional sub-problem.
	/// If the optimal solution is on the edge, then the
	/// corresponding mu-value is set to either +1e100
	/// or -1e100 as an indication.
	void solve2DBox(
		double alphai, double alphaj,
		double gi, double gj,
		double Qii, double Qij, double Qjj,
		double Li, double Ui, double Lj, double Uj,
		double& mui, double& muj
	){
		double QD = Qii * Qjj;
		double detQ = QD - Qij * Qij;
		if (detQ < 1e-10 * QD)
		{
			if (Qii == 0.0 && Qjj == 0.0)
			{
				// Q has rank zero (is the zero matrix)
				// just follow the gradient
				if (gi > 0.0) mui = 1e100;
				else if (gi < 0.0) mui = -1e100;
				else mui = 0.0;
				if (gj > 0.0) muj = 1e100;
				else if (gj < 0.0) muj = -1e100;
				else muj = 0.0;
			}
			else
			{
				// Q has rank one
				double gamma = Qii * gj - Qij * gi;
				double edgei_mui = 0.0, edgei_muj = 0.0, edgei_gain = 0.0;
				double edgej_mui = 0.0, edgej_muj = 0.0, edgej_gain = 0.0;

				// edge with fixed mu_i
				if (Qij * gamma > 0.0)
				{
					edgei_mui = -1e100;
					edgei_gain = stepEdge(alphaj, gj - Qij * (Li - alphai), Qjj, Lj, Uj, edgei_muj);
				}
				else if (Qij * gamma < 0.0)
				{
					edgei_mui = 1e100;
					edgei_gain = stepEdge(alphaj, gj - Qij * (Ui - alphai), Qjj, Lj, Uj, edgei_muj);
				}

				// edge with fixed mu_j
				if (Qii * gamma < 0.0)
				{
					edgej_muj = -1e100;
					edgej_gain = stepEdge(alphai, gi - Qij * (Lj - alphaj), Qii, Li, Ui, edgej_mui);
				}
				else if (Qii * gamma > 0.0)
				{
					edgej_muj = 1e100;
					edgej_gain = stepEdge(alphai, gi - Qij * (Uj - alphaj), Qii, Li, Ui, edgej_mui);
				}

				// keep the better edge point
				if (edgei_gain > edgej_gain)
				{
					mui = edgei_mui;
					muj = edgei_muj;
				}
				else
				{
					mui = edgej_mui;
					muj = edgej_muj;
				}
			}
		}
		else
		{
			// Q has full rank of two, thus it is invertible
			double muiHat = (Qjj * gi - Qij * gj) / detQ;
			double mujHat = (Qii * gj - Qij * gi) / detQ;
			double edgei_mui = 0.0, edgei_muj = 0.0, edgei_gain = 0.0;
			double edgej_mui = 0.0, edgej_muj = 0.0, edgej_gain = 0.0;

			// edge with fixed mu_i
			if (muiHat < Li - alphai)
			{
				edgei_mui = -1e100;
				edgei_gain = stepEdge(alphaj, gj - Qij * (Li - alphai), Qjj, Lj, Uj, edgei_muj);
			}
			else if (muiHat > Ui - alphai)
			{
				edgei_mui = 1e100;
				edgei_gain = stepEdge(alphaj, gj - Qij * (Ui - alphai), Qjj, Lj, Uj, edgei_muj);
			}

			// edge with fixed mu_j
			if (mujHat < Lj - alphaj)
			{
				edgej_muj = -1e100;
				edgej_gain = stepEdge(alphai, gi - Qij * (Lj - alphaj), Qii, Li, Ui, edgej_mui);
			}
			else if (mujHat > Uj - alphaj)
			{
				edgej_muj = 1e100;
				edgej_gain = stepEdge(alphai, gi - Qij * (Uj - alphaj), Qii, Li, Ui, edgej_mui);
			}

			// keep the unconstrained optimum or the better edge point
			if (edgei_gain == 0.0 && edgej_gain == 0.0)
			{
				mui = muiHat;
				muj = mujHat;
			}
			else if (edgei_gain > edgej_gain)
			{
				mui = edgei_mui;
				muj = edgei_muj;
			}
			else
			{
				mui = edgej_mui;
				muj = edgej_muj;
			}
		}
	}
};



template<class Problem>
struct BoxConstrainedShrinkingProblem : public BoxConstrainedProblem<Problem>{
private:
	typedef BoxConstrainedProblem<Problem> base_type;
public:
	typedef typename base_type::QpFloatType QpFloatType;
	typedef typename base_type::MatrixType MatrixType;
	typedef typename base_type::PreferedSelectionStrategy PreferedSelectionStrategy;

	BoxConstrainedShrinkingProblem(Problem& problem, bool shrink=true)
	: base_type(problem)
	, m_isUnshrinked(false)
	, m_shrink(shrink)
	, m_shrinkCounter(std::min<std::size_t>(problem.dimensions(),1000))
	, m_gradientEdge(problem.linear){}
		
	using base_type::alpha;
	using base_type::gradient;
	using base_type::linear;
	using base_type::active;
	using base_type::dimensions;
	using base_type::quadratic;
	using base_type::isLowerBound;
	using base_type::isUpperBound;
	using base_type::boxMin;
	using base_type::boxMax;
		
	virtual void updateSMO(std::size_t i, std::size_t j){
		double aiOld = alpha(i);
		double ajOld = alpha(j);
		//call base class to do the step
		base_type::updateSMO(i,j);
		double ai = alpha(i);
		double aj = alpha(j);
		
		// update the gradient edge data structure to keep up with changes
		updateGradientEdge(i,aiOld,ai);
		updateGradientEdge(j,ajOld,aj);
	}

	bool shrink(double epsilon){
		if(!m_shrink) return false;
		
		//check if shrinking is necessary
		--m_shrinkCounter;
		if(m_shrinkCounter != 0) return false;
		m_shrinkCounter = std::min<std::size_t>(dimensions(),1000);
		
		return doShrink(epsilon);
	}

	///\brief Unshrink the problem
	void unshrink(){
		if (active() == dimensions()) return;
		m_isUnshrinked = true;
		
		// recompute the gradient of the whole problem.
		// we assume here that all shrinked variables are on the border of the problem.
		// the gradient of the active components is already correct and
		// we store the gradient of the subset of variables which are on the
		// borders of the box for the whole set.
		// Thus we only have to recompute the part of the gradient which is
		// based on variables in the active set which are not on the border.
		for (std::size_t a = active(); a < dimensions(); a++) 
			this->m_gradient(a) = m_gradientEdge(a);

		for (std::size_t i = 0; i < active(); i++)
		{
			//check whether alpha value is already stored in gradientEdge
			if (isUpperBound(i) || isLowerBound(i)) continue;
			
			QpFloatType* q = quadratic().row(i, 0, dimensions());
			for (std::size_t a = active(); a < dimensions(); a++) 
				this->m_gradient(a) -= alpha(i) * q[a] ;
		}

		this->m_active = dimensions();
	}

	void setShrinking(bool shrinking){
		m_shrink = shrinking;
		if(!shrinking)
			unshrink();
	}
	
	/// \brief Scales all box constraints by a constant factor and adapts the solution by scaling it by the same factor.
	void scaleBoxConstraints(double factor, double variableScalingFactor){
		base_type::scaleBoxConstraints(factor,variableScalingFactor);
		if(factor != variableScalingFactor){
			for(std::size_t i = 0; i != dimensions(); ++i){
				m_gradientEdge(i) = linear(i);
			}	
		}
		else{
			for(std::size_t i = 0; i != dimensions(); ++i){
				m_gradientEdge(i) -= linear(i);
				m_gradientEdge(i) *= factor;
				m_gradientEdge(i) += linear(i);
			}
		}
	}
	
	virtual void deactivateVariable(std::size_t i){
		SIZE_CHECK(i < dimensions());
		double alphai = alpha(i);
		base_type::deactivateVariable(i);
		updateGradientEdge(i,alphai,0.0);
	}
	
	/// \brief adapts the linear part of the problem and updates the internal data structures accordingly.
	virtual void setLinear(std::size_t i, double newValue){
		m_gradientEdge(i) -= linear(i);
		m_gradientEdge(i) += newValue;
		base_type::setLinear(i,newValue);
	}
protected:
	///\brief Updates the edge-part of the gradient when an alpha valu was changed
	///
	/// This function overwite the base class method and is called, whenever the
	/// base class changes an alpha value.
	void updateGradientEdge(std::size_t i, double oldAlpha, double newAlpha){
		SIZE_CHECK(i < active());
		if(!m_shrink || oldAlpha==newAlpha) return;
		bool isInsideOld = oldAlpha > boxMin(i) && oldAlpha < boxMax(i);
		bool isInsideNew = newAlpha > boxMin(i) && newAlpha < boxMax(i);
		//check if variable is relevant at all, that means that old and new alpha value are inside
		//or old alpha is 0 and new alpha inside
		if( (oldAlpha == 0 || isInsideOld) && isInsideNew  )
			return;

		//compute change to the gradient
		double diff = 0;
		if(!isInsideOld)//the value was on a border, so remove it's old influeence to the gradient
			diff -=oldAlpha;
		if(!isInsideNew){//variable entered boundary or changed from one boundary to another
			diff  += newAlpha;
		}

		QpFloatType* q = quadratic().row(i, 0, dimensions());
		for(std::size_t a = 0; a != dimensions(); ++a){
			m_gradientEdge(a) -= diff*q[a];
		}
	}
private:
	///\brief Shrink the variable from the Problem.
	void shrinkVariable(std::size_t i){
		SIZE_CHECK(i < active());
		base_type::flipCoordinates(i,active()-1);
		std::swap( m_gradientEdge[i], m_gradientEdge[active()-1]);
		--this->m_active;
	}
	
	bool doShrink(double epsilon){
		double largestUp;
		double smallestDown;
		getMaxKKTViolations(largestUp,smallestDown,active());

		// check whether unshrinking is necessary at this accuracy level
		if (!m_isUnshrinked  && (largestUp - smallestDown < 10.0 * epsilon))
		{
			unshrink();
			//recalculate maximum KKT violation for immediate re-shrinking
			getMaxKKTViolations(largestUp,smallestDown,dimensions());
		}
		//shrink
		smallestDown = std::min(smallestDown,0.0);
		largestUp = std::max(largestUp,0.0);
		for (std::size_t a = this->active(); a > 0; --a){
			if(testShrinkVariable(a-1,largestUp,smallestDown))
				this->shrinkVariable(a-1);
		}
		return true;
	}


	bool testShrinkVariable(std::size_t a, double largestUp, double smallestDown)const{
		if (
			( isLowerBound(a) && gradient(a) < smallestDown)
			|| ( isUpperBound(a) && gradient(a) >largestUp)
		){
			// In this moment no feasible step including this variable
			// can improve the objective. Thus deactivate the variable.
			return true;
		}
		return false;
	}

	void getMaxKKTViolations(double& largestUp, double& smallestDown, std::size_t maxIndex){
		largestUp = -1e100;
		smallestDown = 1e100;
		for (std::size_t a = 0; a < maxIndex; a++){
			if (!isLowerBound(a))
				smallestDown = std::min(smallestDown,gradient(a));
			if (!isUpperBound(a))
				largestUp = std::max(largestUp,gradient(a));
		}
	}
	
	bool m_isUnshrinked;
	
	///\brief true if shrinking is to be used.
	bool m_shrink;
	
	///\brief Number of iterations until next shrinking.
	std::size_t m_shrinkCounter;

	///\brief Stores the gradient of the alpha dimeensions which are either 0 or C
	RealVector m_gradientEdge;
};

}
#endif
