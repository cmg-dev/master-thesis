//===========================================================================
/*!
 *  \file rank.inl
 *
 *  \brief Used to determine the rank of the symmetric matrix \em amatA.
 *
 *  \author  M. Kreutz
 *  \date    1998
 *
 *  \par Copyright (c) 1998-2001:
 *      Institut f&uuml;r Neuroinformatik<BR>
 *      Ruhr-Universit&auml;t Bochum<BR>
 *      D-44780 Bochum, Germany<BR>
 *      Phone: +49-234-32-25558<BR>
 *      Fax:   +49-234-32-14209<BR>
 *      eMail: Shark-admin@neuroinformatik.ruhr-uni-bochum.de<BR>
 *      www:   http://www.neuroinformatik.ruhr-uni-bochum.de<BR>
 *
 *
 *  <BR><HR>
 *  This file is part of LinAlg. This library is free software;
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
#ifndef SHARK_LINALG_RANK_INL
#define SHARK_LINALG_RANK_INL

#include <cmath>

//===========================================================================
/*!
 *  \brief Determines the numerical rank of the symmetric matrix "amatA".
 *
 *  Given the \f$ n \times n \f$ matrix \em amatA, this function uses the
 *  eigenvectors \em vmatA and the eigenvalues \em dvecA to
 *  calculate the rank of \em amatA.
 *
 *      \param  amatA \f$ n \times n \f$ matrix, which is symmetric
 *                    and is not changed by the function.
 *      \param  vmatA \f$ n \times n \f$ matrix with the normalized
 *                    eigenvectors, each column contains one eigenvector.
 *                    The matrix is not changed by the function.
 *      \param  dvecA n-dimensional vector of the eigenvalues,
 *                    given in descending order.
 *                    The vector is not changed by the function.
 *      \return       The rank of matrix \em amatA.
 *      \throw SharkException the type of the exception will be
 *             "size mismatch" and indicates that \em dvecA
 *             is not one-dimensional or that \em amatA or
 *             \em vmatA has not the same number of rows or columns
 *             than \em dvecA contains values
 *
 *
 *  Please follow the link to view the source code of the example.
 *  The example can be executed in the example directory
 *  of package LinAlg.
 *
 *  \author  M. Kreutz
 *  \date    1995
 *
 *  \par Changes
 *      none
 *
 *  \par Status
 *      stable
 *
 */
template<class MatrixT,class MatrixU,class VectorT>
unsigned shark::rank
(
	const MatrixT& amatA,
	const MatrixU& vmatA,
	const VectorT& dvecA
)
{
	SIZE_CHECK
	(
		dvecA.size() == amatA.size1() &&
		dvecA.size() == amatA.size2() &&
		dvecA.size() == vmatA.size1() &&
		dvecA.size() == vmatA.size2()
	);

	unsigned n = dvecA.size();
	unsigned r;
	double   s;
	double   u;

	/*
	  determine numerical rank: if the last eigenvalues are < 0, the
       	  numerical error for the values > 0 is at least as large as the
	  abslolute value of the last eigenvalue, thus values below this
	  threshold are to be discarded. Additional thresholds are the relative
	  machine accuracy and the relative error in the eigenvalues
	 */
	for (r = 0; r < n && dvecA(r) > 0; r++);

	u = r < n ? fabs(dvecA(n - 1)) : 0.0;
	r = 0;
	s = 0.0;
	while (r < n     &&
			dvecA(r) > u &&
			dvecA(r) + s > s &&
			dvecA(r) > eigenerr(amatA, vmatA, dvecA, r)) {
		s += dvecA(r++);
	}

	return r;
}
#endif
