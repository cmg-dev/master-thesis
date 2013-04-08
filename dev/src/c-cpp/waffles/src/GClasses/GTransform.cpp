/*
	Copyright (C) 2006, Mike Gashler

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	see http://www.gnu.org/copyleft/lesser.html
*/

#include "GTransform.h"
#include "GDom.h"
#include "GVec.h"
#ifndef MIN_PREDICT
#include "GDistribution.h"
#endif // MIN_PREDICT
#include "GRand.h"
#ifndef MIN_PREDICT
#include "GManifold.h"
#include "GCluster.h"
#include "GString.h"
#endif // MIN_PREDICT
#include "GNeuralNet.h"
#ifndef MIN_PREDICT
#include "GRecommender.h"
#endif // MIN_PREDICT
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <cmath>

namespace GClasses {

using std::string;
using std::vector;
using std::ostringstream;

GTransform::GTransform()
{
}

GTransform::GTransform(GDomNode* pNode, GLearnerLoader& ll)
{
}

// virtual
GTransform::~GTransform()
{
}

// virtual
GDomNode* GTransform::baseDomNode(GDom* pDoc, const char* szClassName) const
{
	GDomNode* pNode = pDoc->newObj();
	pNode->addField(pDoc, "class", pDoc->newString(szClassName));
	return pNode;
}

// ---------------------------------------------------------------

GIncrementalTransform::GIncrementalTransform(GDomNode* pNode, GLearnerLoader& ll)
: GTransform(pNode, ll), m_pInnerBuf(NULL)
{
	m_pRelationBefore = GRelation::deserialize(pNode->field("before"));
	m_pRelationAfter = GRelation::deserialize(pNode->field("after"));
}

// virtual
GDomNode* GIncrementalTransform::baseDomNode(GDom* pDoc, const char* szClassName) const
{
	if(!m_pRelationAfter.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = GTransform::baseDomNode(pDoc, szClassName);
	pNode->addField(pDoc, "before", m_pRelationBefore->serialize(pDoc));
	pNode->addField(pDoc, "after", m_pRelationAfter->serialize(pDoc));
	return pNode;
}

void GIncrementalTransform::train(GMatrix& data)
{
	m_pRelationBefore = data.relation();
	m_pRelationAfter = trainInner(data);
}

void GIncrementalTransform::train(sp_relation& relation)
{
	m_pRelationBefore = relation;
	m_pRelationAfter = trainInner(relation);
}

#ifndef MIN_PREDICT
//static
void GIncrementalTransform::test()
{
	// Make an input matrix
	vector<size_t> valCounts;
	valCounts.push_back(0);
	valCounts.push_back(1);
	valCounts.push_back(2);
	valCounts.push_back(3);
	valCounts.push_back(0);
	GMatrix m(valCounts);
	m.newRows(2);
	m[0][0] = 2.4; m[0][1] = 0; m[0][2] = 0; m[0][3] = 2; m[0][4] = 8.2;
	m[1][0] = 0.0; m[1][1] = 0; m[1][2] = 1; m[1][3] = 0; m[1][4] = 2.2;

	// Make an expected output matrix
	GMatrix e(2, 7);
	e[0][0] = 1; e[0][1] = 0; e[0][2] = 0; e[0][3] = 0; e[0][4] = 0; e[0][5] = 1; e[0][6] = 1;
	e[1][0] = 0; e[1][1] = 0; e[1][2] = 1; e[1][3] = 1; e[1][4] = 0; e[1][5] = 0; e[1][6] = 0;

	// Transform the input matrix and check it
	GIncrementalTransformChainer trans(new GNormalize(), new GNominalToCat());
	trans.train(m);
	GMatrix* pA = trans.transformBatch(m);
	Holder<GMatrix> hA(pA);
	if(pA->sumSquaredDifference(e) > 1e-12)
		throw Ex("Expected:\n", to_str(e), "\nGot:\n", to_str(*pA));
	if(!pA->relation()->areContinuous())
		throw Ex("failed");
	GMatrix* pB = trans.untransformBatch(*pA);
	Holder<GMatrix> hB(pB);
	if(pB->sumSquaredDifference(m) > 1e-12)
		throw Ex("Expected:\n", to_str(m), "\nGot:\n", to_str(*pB));
	if(!pB->relation()->isCompatible(*m.relation().get()) || !m.relation()->isCompatible(*pB->relation().get()))
		throw Ex("failed");

	// Round-trip it through serialization
	GDom doc;
	GDomNode* pNode = trans.serialize(&doc);
	GRand rand(0);
	GLearnerLoader ll(rand);
	GIncrementalTransform* pTrans = ll.loadIncrementalTransform(pNode);

	// Transform the input matrix again, and check it
	GMatrix* pC = pTrans->transformBatch(m);
	Holder<GMatrix> hC(pC);
	if(pC->sumSquaredDifference(e) > 1e-12)
		throw Ex("Expected:\n", to_str(e), "\nGot:\n", to_str(*pC));
	if(!pC->relation()->areContinuous())
		throw Ex("failed");
	GMatrix* pD = trans.untransformBatch(*pC);
	Holder<GMatrix> hD(pD);
	if(pD->sumSquaredDifference(m) > 1e-12)
		throw Ex("Expected:\n", to_str(m), "\nGot:\n", to_str(*pD));
	if(!pD->relation()->isCompatible(*m.relation().get()) || !m.relation()->isCompatible(*pD->relation().get()))
		throw Ex("failed");
}
#endif // MIN_PREDICT

// ---------------------------------------------------------------

GIncrementalTransformChainer::GIncrementalTransformChainer(GIncrementalTransform* pFirst, GIncrementalTransform* pSecond)
: GIncrementalTransform(), m_pFirst(pFirst), m_pSecond(pSecond)
{
}

GIncrementalTransformChainer::GIncrementalTransformChainer(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll)
{
	m_pFirst = ll.loadIncrementalTransform(pNode->field("first"));
	m_pSecond = ll.loadIncrementalTransform(pNode->field("second"));
}

// virtual
GIncrementalTransformChainer::~GIncrementalTransformChainer()
{
	delete(m_pFirst);
	delete(m_pSecond);
}

#ifndef MIN_PREDICT
// virtual
GDomNode* GIncrementalTransformChainer::serialize(GDom* pDoc) const
{
	if(!m_pRelationBefore.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = baseDomNode(pDoc, "GIncrementalTransformChainer");
	pNode->addField(pDoc, "first", m_pFirst->serialize(pDoc));
	pNode->addField(pDoc, "second", m_pSecond->serialize(pDoc));
	return pNode;
}
#endif // MIN_PREDICT

// virtual
sp_relation GIncrementalTransformChainer::trainInner(GMatrix& data)
{
	m_pFirst->train(data);
	GMatrix* pData2 = m_pFirst->transformBatch(data); // todo: often this step is computation overkill since m_pSecond may not even use it during training. Is there a way to avoid doing it?
	Holder<GMatrix> hData2(pData2);
	m_pSecond->train(*pData2);
	return m_pSecond->after();
}

// virtual
sp_relation GIncrementalTransformChainer::trainInner(sp_relation& relation)
{
	m_pFirst->train(relation);
	m_pSecond->train(m_pFirst->after());
	return m_pSecond->after();
}

// virtual
void GIncrementalTransformChainer::transform(const double* pIn, double* pOut)
{
	double* pBuf = m_pFirst->innerBuf();
	m_pFirst->transform(pIn, pBuf);
	m_pSecond->transform(pBuf, pOut);
}

// virtual
void GIncrementalTransformChainer::untransform(const double* pIn, double* pOut)
{
	double* pBuf = m_pFirst->innerBuf();
	m_pSecond->untransform(pIn, pBuf);
	m_pFirst->untransform(pBuf, pOut);
}

#ifndef MIN_PREDICT
// virtual
void GIncrementalTransformChainer::untransformToDistribution(const double* pIn, GPrediction* pOut)
{
	double* pBuf = m_pFirst->innerBuf();
	m_pSecond->untransform(pIn, pBuf);
	m_pFirst->untransformToDistribution(pBuf, pOut);
}
#endif // MIN_PREDICT

// ---------------------------------------------------------------

// virtual
GIncrementalTransform::~GIncrementalTransform()
{
	delete[] m_pInnerBuf;
}

// virtual
GMatrix* GIncrementalTransform::doit(GMatrix& in)
{
	train(in);
	return transformBatch(in);
}

// virtual
GMatrix* GIncrementalTransform::transformBatch(GMatrix& in)
{
	if(!m_pRelationAfter.get())
		throw Ex("train has not been called");
	size_t nRows = in.rows();
	GMatrix* pOut = new GMatrix(m_pRelationAfter);
	Holder<GMatrix> hOut(pOut);
	pOut->newRows(nRows);
	for(size_t i = 0; i < nRows; i++)
		transform(in.row(i), pOut->row(i));
	return hOut.release();
}

double* GIncrementalTransform::innerBuf()
{
	if(!m_pInnerBuf)
		m_pInnerBuf = new double[m_pRelationAfter->size()];
	return m_pInnerBuf;
}

// virtual
GMatrix* GIncrementalTransform::untransformBatch(GMatrix& in)
{
	if(!m_pRelationBefore.get())
		throw Ex("train has not been called");
	size_t nRows = in.rows();
	GMatrix* pOut = new GMatrix(before());
	pOut->newRows(nRows);
	Holder<GMatrix> hOut(pOut);
	for(size_t i = 0; i < nRows; i++)
		untransform(in.row(i), pOut->row(i));
	return hOut.release();
}

// ---------------------------------------------------------------

GPCA::GPCA(size_t targetDims, GRand* pRand)
: GIncrementalTransform(), m_targetDims(targetDims), m_pBasisVectors(NULL), m_pEigVals(NULL), m_aboutOrigin(false), m_pRand(pRand)
{
}

GPCA::GPCA(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll), m_pEigVals(NULL), m_pRand(&ll.rand())
{
	m_targetDims = m_pRelationBefore->size();
	m_pBasisVectors = new GMatrix(pNode->field("basis"));
	m_aboutOrigin = pNode->field("aboutOrigin")->asBool();
}

// virtual
GPCA::~GPCA()
{
	delete(m_pBasisVectors);
	delete[] m_pEigVals;
}

#ifndef MIN_PREDICT
// virtual
GDomNode* GPCA::serialize(GDom* pDoc) const
{
	if(!m_pRelationBefore.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = baseDomNode(pDoc, "GPCA");
	pNode->addField(pDoc, "basis", m_pBasisVectors->serialize(pDoc));
	pNode->addField(pDoc, "aboutOrigin", pDoc->newBool(m_aboutOrigin));
	return pNode;
}
#endif // MIN_PREDICT

void GPCA::computeEigVals()
{
	delete[] m_pEigVals;
	m_pEigVals = new double[m_targetDims];
}

// virtual
sp_relation GPCA::trainInner(GMatrix& data)
{
	if(!m_pRelationBefore->areContinuous(0, m_pRelationBefore->size()))
		throw Ex("GPCA doesn't support nominal values. (You could filter with nominaltocat to make them real.)");
	delete(m_pBasisVectors);
	m_pBasisVectors = new GMatrix(m_pRelationBefore);
	m_pBasisVectors->newRows(m_targetDims + 1);

	// Compute the mean
	size_t nInputDims = m_pRelationBefore->size();
	double* pMean = m_pBasisVectors->row(0);
	if(m_aboutOrigin)
		GVec::setAll(pMean, 0.0, nInputDims);
	else
		data.centroid(pMean);

	// Make a copy of the data
	GMatrix tmpData(data.relation(), data.heap());
	tmpData.copy(&data);

	// Compute the principle components
	double sse = 0;
	if(m_pEigVals)
		sse = tmpData.sumSquaredDistance(pMean);
	for(size_t i = 0; i < m_targetDims; i++)
	{
		double* pVector = m_pBasisVectors->row(i + 1);
		tmpData.principalComponentIgnoreUnknowns(pVector, pMean, m_pRand);
		tmpData.removeComponent(pMean, pVector);
		if(m_pEigVals)
		{
			double t = tmpData.sumSquaredDistance(pMean);
			m_pEigVals[i] = (sse - t) / nInputDims;
			sse = t;
		}
	}

	return new GUniformRelation(m_targetDims, 0);
}

// virtual
sp_relation GPCA::trainInner(sp_relation& relation)
{
	throw Ex("This transform cannot be trained without data");
	return m_pRelationBefore;
}

// virtual
void GPCA::transform(const double* pIn, double* pOut)
{
	double* pMean = m_pBasisVectors->row(0);
	size_t nInputDims = m_pRelationBefore->size();
	for(size_t i = 0; i < m_targetDims; i++)
	{
		double* pBasisVector = m_pBasisVectors->row(i + 1);
		pOut[i] = GVec::dotProductIgnoringUnknowns(pMean, pIn, pBasisVector, nInputDims);
	}
}

// virtual
void GPCA::untransform(const double* pIn, double* pOut)
{
	size_t nInputDims = m_pRelationBefore->size();
	GVec::copy(pOut, m_pBasisVectors->row(0), nInputDims);
	for(size_t i = 0; i < m_targetDims; i++)
		GVec::addScaled(pOut, pIn[i], m_pBasisVectors->row(i + 1), nInputDims);
}

// virtual
void GPCA::untransformToDistribution(const double* pIn, GPrediction* pOut)
{
	throw Ex("Sorry, PCA cannot untransform to a distribution");
}

/*
GPCARotateOnly::GPCARotateOnly(GArffRelation* pRelation, GMatrix* pData)
{
	m_pRelation = pRelation;
	m_pInputData = pData;
	m_pOutputData = NULL;
}

GPCARotateOnly::~GPCARotateOnly()
{
	delete(m_pOutputData);
}

// static
GMatrix* GPCARotateOnly::DoPCA(GArffRelation* pRelation, GMatrix* pData)
{
	GPCA pca(pRelation, pData);
	pca.DoPCA();
	return pca.ReleaseOutputData();
}

void GPCARotateOnly::DoPCA()
{
	// Compute the eigenvectors
	GMatrix m;
	m_pInputData->ComputeCovarianceMatrix(&m, m_pRelation);
	GMatrix eigenVectors;
	eigenVectors.ComputeEigenVectors(m.GetColumnCount(), &m);
	m_pOutputData = new GMatrix(m_pInputData->rows());
	int nRowCount = m_pInputData->rows();
	int nInputCount = m_pRelation->GetInputCount();
	int nOutputCount = m_pRelation->GetOutputCount();
	int nAttributeCount = m_pRelation->size();
	double* pInputRow;
	double* pOutputRow;
	int n, i, j, nIndex;

	// Allocate space for the output
	for(n = 0; n < nRowCount; n++)
	{
		pOutputRow = new double[nAttributeCount];
		m_pOutputData->AddRow(pOutputRow);
	}

	// Compute the output
	double* pEigenVector;
	Holder<double> hInputVector(new double[nInputCount]);
	double* pInputVector = hInputVector.Get();
	for(i = 0; i < nInputCount; i++)
	{
		nIndex = m_pRelation->GetInputIndex(i);
		pEigenVector = eigenVectors.row(i);
		for(n = 0; n < nRowCount; n++)
		{
			pInputRow = m_pInputData->row(n);
			for(j = 0; j < nInputCount; j++)
				pInputVector[j] = pInputRow[m_pRelation->GetInputIndex(j)];
			pOutputRow = m_pOutputData->row(n);
			pOutputRow[nIndex] = GVec::dotProduct(pInputVector, pEigenVector, nInputCount);
		}
	}
	for(i = 0; i < nOutputCount; i++)
	{
		for(n = 0; n < nRowCount; n++)
		{
			nIndex = m_pRelation->GetOutputIndex(i);
			pInputRow = m_pInputData->row(n);
			pOutputRow = m_pOutputData->row(n);
			pOutputRow[nIndex] = pInputRow[nIndex];
		}
	}
}

GMatrix* GPCARotateOnly::ReleaseOutputData()
{
	GMatrix* pData = m_pOutputData;
	m_pOutputData = NULL;
	return pData;
}
*/
GMatrix* GPCARotateOnly::transform(size_t nDims, size_t nOutputs, GMatrix* pData, size_t nComponents, GRand* pRand)
{
	// Init the basis vectors
	size_t nElements = nDims * nDims;
	double* pBasisVectors = new double[nElements + nDims * 4];
	ArrayHolder<double> hBasisVectors(pBasisVectors);
	double* pComponent = &pBasisVectors[nElements];
	double* pA = &pBasisVectors[nElements + nDims];
	double* pB = &pBasisVectors[nElements + 2 * nDims];
	double* pMean = &pBasisVectors[nElements + 3 * nDims];
	size_t j;
	for(size_t i = 0; i < nElements; i++)
		pBasisVectors[i] = 0;
	for(size_t i = 0; i < nDims; i++)
		pBasisVectors[nDims * i + i] = 1;

	// Compute the mean
	for(j = 0; j < nDims; j++)
		pMean[j] = pData->mean(j);

	// Make a copy of the data
	GMatrix* pOutData = new GMatrix(pData->relation());
	pOutData->copy(pData);
	Holder<GMatrix> hOutData(pOutData);

	// Rotate the basis vectors
	double dDotProd;
	for(size_t i = 0; i < nComponents; i++)
	{
		// Compute the next principle component
		pOutData->principalComponent(pComponent, pMean, pRand);
		pOutData->removeComponent(pMean, pComponent);

		// Use the current axis as the first plane vector
		GVec::copy(pA, &pBasisVectors[nDims * i], nDims);

		// Use the modified Gram-Schmidt process to compute the other plane vector
		GVec::copy(pB, pComponent, nDims);
		dDotProd = GVec::dotProduct(pB, pA, nDims);
		GVec::addScaled(pB, -dDotProd, pA, nDims);
		double dMag = sqrt(GVec::squaredMagnitude(pB, nDims));
		if(dMag < 1e-6)
			break; // It's already close enough. If we normalized something that small, it would just mess up our data
		GVec::multiply(pB, 1.0 / dMag, nDims);

		// Rotate the remaining basis vectors
		double dAngle = atan2(GVec::dotProduct(pComponent, pB, nDims), dDotProd);
		for(j = i; j < nDims; j++)
		{
			GVec::rotate(&pBasisVectors[nDims * j], nDims, dAngle, pA, pB);
			GAssert(std::abs(GVec::squaredMagnitude(&pBasisVectors[nDims * j], nDims) - 1.0) < 1e-4);
		}
	}

	// Align data with new basis vectors
	double* pInVector;
	double* pOutVector;
	size_t nCount = pData->rows();
	for(size_t i = 0; i < nCount; i++)
	{
		pInVector = pData->row(i);
		pOutVector = pOutData->row(i);
		for(j = 0; j < nDims; j++)
			pOutVector[j] = GVec::dotProduct(pMean, pInVector, &pBasisVectors[nDims * j], nDims);
	}

	return hOutData.release();
}

#ifndef MIN_PREDICT
//static
void GPCARotateOnly::test()
{
	GRand prng(0);
	GHeap heap(1000);
	GMatrix data(0, 2, &heap);
	double* pVec;
	pVec = data.newRow();	pVec[0] = 0;	pVec[1] = 0;
	pVec = data.newRow();	pVec[0] = 10;	pVec[1] = 10;
	pVec = data.newRow();	pVec[0] = 4;	pVec[1] = 6;
	pVec = data.newRow();	pVec[0] = 6;	pVec[1] = 4;
	GMatrix* pOut2 = GPCARotateOnly::transform(2, 0, &data, 2, &prng);
	for(size_t i = 0; i < pOut2->rows(); i++)
	{
		pVec = pOut2->row(i);
		if(std::abs(std::abs(pVec[0]) - 7.071067) < .001)
		{
			if(std::abs(pVec[1]) > .001)
				throw Ex("wrong answer");
		}
		else if(std::abs(pVec[0]) < .001)
		{
			if(std::abs(std::abs(pVec[1]) - 1.414214) > .001)
				throw Ex("wrong answer");
		}
		else
			throw Ex("wrong answer");
	}
	delete(pOut2);
}
#endif // !MIN_PREDICT

// --------------------------------------------------------------------------

GNoiseGenerator::GNoiseGenerator(GRand* pRand)
: GIncrementalTransform(), m_pRand(pRand), m_mean(0), m_deviation(1)
{
}

GNoiseGenerator::GNoiseGenerator(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll), m_pRand(&ll.rand())
{
	m_mean = pNode->field("mean")->asDouble();
	m_deviation = pNode->field("dev")->asDouble();
}

GNoiseGenerator::~GNoiseGenerator()
{
}

// virtual
GDomNode* GNoiseGenerator::serialize(GDom* pDoc) const
{
	if(!m_pRelationBefore.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = baseDomNode(pDoc, "GNoiseGenerator");
	pNode->addField(pDoc, "mean", pDoc->newDouble(m_mean));
	pNode->addField(pDoc, "dev", pDoc->newDouble(m_deviation));
	return pNode;
}

// virtual
sp_relation GNoiseGenerator::trainInner(GMatrix& data)
{
	return data.relation();
}

// virtual
sp_relation GNoiseGenerator::trainInner(sp_relation& relation)
{
	return relation;
}

// virtual
void GNoiseGenerator::transform(const double* pIn, double* pOut)
{
	size_t nDims = m_pRelationBefore->size();
	for(size_t i = 0; i < nDims; i++)
	{
		size_t vals = m_pRelationBefore->valueCount(i);
		if(vals == 0)
			pOut[i] = m_pRand->normal() * m_deviation + m_mean;
		else
			pOut[i] = (double)m_pRand->next(vals);
	}
}

// --------------------------------------------------------------------------

GPairProduct::GPairProduct(size_t nMaxDims)
: GIncrementalTransform(), m_maxDims(nMaxDims)
{
}

GPairProduct::GPairProduct(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll)
{
	m_maxDims = (size_t)pNode->field("maxDims")->asInt();
}

GPairProduct::~GPairProduct()
{
}

// virtual
GDomNode* GPairProduct::serialize(GDom* pDoc) const
{
	if(!m_pRelationBefore.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = baseDomNode(pDoc, "GPairProduct");
	pNode->addField(pDoc, "maxDims", pDoc->newInt(m_maxDims));
	return pNode;
}

// virtual
sp_relation GPairProduct::trainInner(GMatrix& data)
{
	size_t nAttrsIn = m_pRelationBefore->size();
	size_t nAttrsOut = std::min(m_maxDims, nAttrsIn * (nAttrsIn + 1) / 2);
	return new GUniformRelation(nAttrsOut, 0);
}

// virtual
sp_relation GPairProduct::trainInner(sp_relation& relation)
{
	size_t nAttrsIn = m_pRelationBefore->size();
	size_t nAttrsOut = std::min(m_maxDims, nAttrsIn * (nAttrsIn + 1) / 2);
	return new GUniformRelation(nAttrsOut, 0);
}

// virtual
void GPairProduct::transform(const double* pIn, double* pOut)
{
	size_t i, j, nAttr;
	size_t nAttrsIn = m_pRelationBefore->size();
	size_t nAttrsOut = m_pRelationAfter->size();
	nAttr = 0;
	for(j = 0; j < nAttrsIn && nAttr < nAttrsOut; j++)
	{
		for(i = j; i < nAttrsIn && nAttr < nAttrsOut; i++)
			pOut[nAttr++] = pIn[i] * pIn[j];
	}
	GAssert(nAttr == nAttrsOut);
}

// --------------------------------------------------------------------------

GReservoir::GReservoir(GRand& rand, double weightDeviation, size_t outputs, size_t hiddenLayers)
: GIncrementalTransform(), m_outputs(outputs), m_deviation(weightDeviation)
{
	m_pNN = new GNeuralNet(rand);
	for(size_t i = 0; i < hiddenLayers; i++)
		m_pNN->addLayer(outputs);
}

GReservoir::GReservoir(GDomNode* pNode, GLearnerLoader& ll)
{
	m_pNN = new GNeuralNet(pNode->field("nn"), ll);
	m_outputs = m_pNN->relLabels()->size();
	m_deviation = pNode->field("dev")->asDouble();
}

// virtual
GReservoir::~GReservoir()
{
	delete(m_pNN);
}

#ifndef MIN_PREDICT
// virtual
GDomNode* GReservoir::serialize(GDom* pDoc) const
{
	GDomNode* pNode = baseDomNode(pDoc, "GReservoir");
	pNode->addField(pDoc, "nn", m_pNN->serialize(pDoc));
	pNode->addField(pDoc, "dev", pDoc->newDouble(m_deviation));
	return pNode;
}
#endif // MIN_PREDICT


// virtual
sp_relation GReservoir::trainInner(GMatrix& data)
{
	return trainInner(data.relation());
}

// virtual
sp_relation GReservoir::trainInner(sp_relation& relation)
{
	sp_relation pRel = new GUniformRelation(m_outputs);
	if(!relation->areContinuous())
	{
		m_pNN->clearFeatureFilter();
		m_pNN->wrapFeatures(new GNominalToCat());
	}
	m_pNN->beginIncrementalLearning(relation, pRel);
	m_pNN->perturbAllWeights(m_deviation);
	return pRel;
}

// virtual
void GReservoir::transform(const double* pIn, double* pOut)
{
	m_pNN->predict(pIn, pOut);
}


// --------------------------------------------------------------------------

GDataAugmenter::GDataAugmenter(GIncrementalTransform* pTransform)
: GIncrementalTransform(), m_pTransform(pTransform)
{
}

GDataAugmenter::GDataAugmenter(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll)
{
	m_pTransform = ll.loadIncrementalTransform(pNode->field("trans"));
}

// virtual
GDataAugmenter::~GDataAugmenter()
{
	delete(m_pTransform);
}

#ifndef MIN_PREDICT
// virtual
GDomNode* GDataAugmenter::serialize(GDom* pDoc) const
{
	GDomNode* pNode = baseDomNode(pDoc, "GDataAugmenter");
	pNode->addField(pDoc, "trans", m_pTransform->serialize(pDoc));
	return pNode;
}
#endif // MIN_PREDICT

// virtual
sp_relation GDataAugmenter::trainInner(GMatrix& data)
{
	m_pTransform->train(data);
	GMixedRelation* pNewRel = new GMixedRelation();
	pNewRel->addAttrs(data.relation().get());
	pNewRel->addAttrs(m_pTransform->after().get());
	return pNewRel;
}

// virtual
sp_relation GDataAugmenter::trainInner(sp_relation& relation)
{
	m_pTransform->train(relation);
	GMixedRelation* pNewRel = new GMixedRelation();
	pNewRel->addAttrs(m_pRelationBefore.get());
	pNewRel->addAttrs(m_pTransform->after().get());
	return pNewRel;
}

// virtual
void GDataAugmenter::transform(const double* pIn, double* pOut)
{
	GVec::copy(pOut, pIn, m_pRelationBefore->size());
	m_pTransform->transform(pIn, pOut + m_pRelationBefore->size());
}

// virtual
void GDataAugmenter::untransform(const double* pIn, double* pOut)
{
	GVec::copy(pOut, pIn, m_pRelationBefore->size());
}

// virtual
void GDataAugmenter::untransformToDistribution(const double* pIn, GPrediction* pOut)
{
	throw Ex("Sorry, this method is not implemented yet");
}

// --------------------------------------------------------------------------
#ifndef MIN_PREDICT

GAttributeSelector::GAttributeSelector(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll), m_pRand(&ll.rand())
{
	m_labelDims = (size_t)pNode->field("labels")->asInt();
	m_targetFeatures = (size_t)pNode->field("target")->asInt();
	GDomNode* pRanksNode = pNode->field("ranks");
	GDomListIterator it(pRanksNode);
	m_ranks.reserve(it.remaining());
	for( ; it.current(); it.advance())
		m_ranks.push_back((size_t)it.current()->asInt());
	if(m_ranks.size() + (size_t)m_labelDims != (size_t)m_pRelationBefore->size())
		throw Ex("invalid attribute selector");
	if(m_targetFeatures > m_ranks.size())
		throw Ex("invalid attribute selector");
}

// virtual
GDomNode* GAttributeSelector::serialize(GDom* pDoc) const
{
	GDomNode* pNode = baseDomNode(pDoc, "GAttributeSelector");
	pNode->addField(pDoc, "labels", pDoc->newInt(m_labelDims));
	pNode->addField(pDoc, "target", pDoc->newInt(m_targetFeatures));
	GDomNode* pRanksNode = pNode->addField(pDoc, "ranks", pDoc->newList());
	for(size_t i = 0; i < m_ranks.size(); i++)
		pRanksNode->addItem(pDoc, pDoc->newInt(m_ranks[i]));
	return pNode;
}

sp_relation GAttributeSelector::setTargetFeatures(size_t n)
{
	if(n > m_pRelationBefore->size())
		throw Ex("out of range");
	GMixedRelation* pRelAfter;
	if(m_pRelationBefore->type() == GRelation::ARFF)
		pRelAfter = new GArffRelation();
	else
		pRelAfter = new GMixedRelation();
	for(size_t i = 0; i < m_targetFeatures; i++)
		pRelAfter->copyAttr(m_pRelationBefore.get(), m_ranks[i]);
	if(m_labelDims > m_pRelationBefore->size())
		throw Ex("label dims out of range");
	size_t featureDims = m_pRelationBefore->size() - m_labelDims;
	for(size_t i = 0; i < m_labelDims; i++)
		pRelAfter->copyAttr(m_pRelationBefore.get(), featureDims + i);
	return pRelAfter;
}

// virtual
sp_relation GAttributeSelector::trainInner(GMatrix& data)
{
	if(m_labelDims > data.cols())
		throw Ex("label dims is greater than the number of columns in the data");
	size_t curDims = data.cols() - m_labelDims;
	m_ranks.resize(curDims);
	GMatrix* pFeatures = data.cloneSub(0, 0, data.rows(), data.cols() - m_labelDims);
	Holder<GMatrix> hFeatures(pFeatures);
	GMatrix* pLabels = data.cloneSub(0, data.cols() - m_labelDims, data.rows(), m_labelDims);
	Holder<GMatrix> hLabels(pLabels);
	vector<size_t> indexMap;
	for(size_t i = 0; i < curDims; i++)
		indexMap.push_back(i);

	// Produce a ranked attributed ordering by deselecting the weakest attribute each time
	while(curDims > 1)
	{
		// Convert nominal attributes to a categorical distribution
		GNominalToCat ntc;
		ntc.train(*pFeatures);
		GMatrix* pFeatures2 = ntc.transformBatch(*pFeatures);
		Holder<GMatrix> hFeatures2(pFeatures2);

		// Train a single-layer neural network with the normalized remaining data
		GNeuralNet nn(*m_pRand);
		nn.setWindowSize(30);
		nn.setImprovementThresh(0.002);
		nn.train(*pFeatures2, *pLabels);
		vector<size_t> rmap;
		ntc.reverseAttrMap(rmap);

		// Identify the weakest attribute
		GNeuralNetLayer& layer = nn.layer(nn.layerCount() - 1);
		size_t pos = 0;
		double weakest = 1e308;
		size_t weakestIndex = 0;
		for(size_t i = 0; i < curDims; i++)
		{
			double w = 0;
			while(pos < nn.relFeatures()->size() && rmap[pos] == i)
			{
				for(vector<GNeuron>::iterator it = layer.m_neurons.begin(); it != layer.m_neurons.end(); it++)
					w = std::max(w, std::abs(it->m_weights[pos + 1]));
				pos++;
			}
			if(w < weakest)
			{
				weakest = w;
				weakestIndex = i;
			}
		}

		// Deselect the weakest attribute
		m_ranks[curDims - 1] = indexMap[weakestIndex];
		indexMap.erase(indexMap.begin() + weakestIndex);
		pFeatures->deleteColumn(weakestIndex);
		curDims--;
		GAssert(pFeatures->cols() == curDims);
	}
	m_ranks[0] = indexMap[0];
	return setTargetFeatures(m_targetFeatures);
}

// virtual
sp_relation GAttributeSelector::trainInner(sp_relation& relation)
{
	throw Ex("This transform cannot be trained without data");
	return m_pRelationBefore;
}

// virtual
void GAttributeSelector::transform(const double* pIn, double* pOut)
{
	size_t i;
	for(i = 0; i < m_targetFeatures; i++)
		pOut[i] = pIn[m_ranks[i]];
	size_t featureDims = m_pRelationBefore->size() - m_labelDims;
	for(size_t j = 0; j < m_labelDims; j++)
		pOut[i++] = pIn[featureDims + j];
}

//static
void GAttributeSelector::test()
{
	GRand prng(0);
	GMatrix data(0, 21);
	for(size_t i = 0; i < 256; i++)
	{
		double* pVec = data.newRow();
		prng.cubical(pVec, 20);
		pVec[20] = 0.2 * pVec[3] * pVec[3] * - 7.0 * pVec[3] * pVec[13] + pVec[17];
	}
	GAttributeSelector as(1, 3, &prng);
	as.train(data);
	std::vector<size_t>& r = as.ranks();
	if(r[1] == r[0] || r[2] == r[0] || r[2] == r[1])
		throw Ex("bogus rankings");
	if(r[0] != 3 && r[0] != 13 && r[0] != 17)
		throw Ex("failed");
	if(r[1] != 3 && r[1] != 13 && r[1] != 17)
		throw Ex("failed");
	if(r[2] != 3 && r[2] != 13 && r[2] != 17)
		throw Ex("failed");
}
#endif // MIN_PREDICT

// --------------------------------------------------------------------------

GNominalToCat::GNominalToCat(size_t nValueCap)
: GIncrementalTransform(), m_valueCap(nValueCap), m_preserveUnknowns(false)
{
}

GNominalToCat::GNominalToCat(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll)
{
	m_valueCap = (size_t)pNode->field("valueCap")->asInt();
	m_preserveUnknowns = pNode->field("pu")->asBool();
	init();
}

sp_relation GNominalToCat::init()
{
	sp_relation spRel;
	if(m_pRelationBefore->type() == GRelation::ARFF)
		spRel = new GArffRelation();
	else
		spRel = new GMixedRelation();
	size_t nDims = 0;
	size_t nAttrCount = m_pRelationBefore->size();
	const char* szName;
	for(size_t i = 0; i < nAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues == 0)
		{
			nDims++;
			if(m_pRelationBefore->type() == GRelation::ARFF)
			{
				szName = ((GArffRelation*)m_pRelationBefore.get())->attrName(i);
				((GArffRelation*)spRel.get())->addAttribute(szName, 0, NULL);
			}
			else
				((GMixedRelation*)spRel.get())->addAttr(0);
		}
		else if(nValues < 3 || nValues >= m_valueCap)
		{
			nDims++;
			if(m_pRelationBefore->type() == GRelation::ARFF)
			{
				szName = ((GArffRelation*)m_pRelationBefore.get())->attrName(i);
				((GArffRelation*)spRel.get())->addAttribute(szName, 0, NULL);
			}
			else
				((GMixedRelation*)spRel.get())->addAttr(0);
		}
		else if(nValues < m_valueCap)
		{
			nDims += nValues;
			if(m_pRelationBefore->type() == GRelation::ARFF)
			{
				szName = ((GArffRelation*)m_pRelationBefore.get())->attrName(i);
				string sName = szName;
				sName += "_";
				for(size_t j = 0; j < nValues; j++)
				{
					ostringstream oss;
					m_pRelationBefore->printAttrValue(oss, i, (double)j);
					sName += oss.str();
					((GArffRelation*)spRel.get())->addAttribute(sName.c_str(), 0, NULL);
				}
			}
			else
			{
				for(size_t j = 0; j < nValues; j++)
					((GMixedRelation*)spRel.get())->addAttr(0);
			}
		}
		else
		{
			nDims++;
			if(m_pRelationBefore->type() == GRelation::ARFF)
			{
				szName = ((GArffRelation*)m_pRelationBefore.get())->attrName(i);
				((GArffRelation*)spRel.get())->addAttribute(szName, 0, NULL);
			}
			else
				((GMixedRelation*)spRel.get())->addAttr(0);
		}
	}
	return spRel;
}

// virtual
GNominalToCat::~GNominalToCat()
{
}

// virtual
sp_relation GNominalToCat::trainInner(GMatrix& data)
{
	return init();
}

// virtual
sp_relation GNominalToCat::trainInner(sp_relation& relation)
{
	return init();
}

// virtual
GDomNode* GNominalToCat::serialize(GDom* pDoc) const
{
	if(!m_pRelationBefore.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = baseDomNode(pDoc, "GNominalToCat");
	pNode->addField(pDoc, "valueCap", pDoc->newInt(m_valueCap));
	pNode->addField(pDoc, "pu", pDoc->newBool(m_preserveUnknowns));
	return pNode;
}

// virtual
void GNominalToCat::transform(const double* pIn, double* pOut)
{
	size_t nInAttrCount = m_pRelationBefore->size();
	for(size_t i = 0; i < nInAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues < 3)
		{
			if(nValues == 0)
				*(pOut++) = *(pIn++);
			else if(nValues == 1)
			{
				if(*pIn == UNKNOWN_DISCRETE_VALUE)
					*(pOut++) = UNKNOWN_REAL_VALUE;
				else
					*(pOut++) = 0;
				pIn++;
			}
			else
			{
				if(*pIn == UNKNOWN_DISCRETE_VALUE)
				{
					if(m_preserveUnknowns)
						*(pOut++) = UNKNOWN_REAL_VALUE;
					else
						*(pOut++) = 0.5;
				}
				else
					*(pOut++) = *pIn;
				pIn++;
			}
		}
		else if(nValues < m_valueCap)
		{
			if(*pIn >= 0)
			{
				GAssert(*pIn < nValues);
				GVec::setAll(pOut, 0.0, nValues);
				pOut[(int)*pIn] = 1.0;
			}
			else
			{
				if(m_preserveUnknowns)
					GVec::setAll(pOut, UNKNOWN_REAL_VALUE, nValues);
				else
					GVec::setAll(pOut, 1.0 / nValues, nValues);
			}
			pOut += nValues;
			pIn++;
		}
		else
		{
			if(*pIn == UNKNOWN_DISCRETE_VALUE)
				*(pOut++) = UNKNOWN_REAL_VALUE;
			else
				*(pOut++) = *pIn;
			pIn++;
		}
	}
}

// virtual
void GNominalToCat::untransform(const double* pIn, double* pOut)
{
	size_t nOutAttrCount = m_pRelationBefore->size();
	for(size_t i = 0; i < nOutAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues < 3)
		{
			if(nValues == 0)
				*(pOut++) = *(pIn++);
			else if(nValues == 1)
			{
				if(*pIn == UNKNOWN_REAL_VALUE)
					*(pOut++) = UNKNOWN_DISCRETE_VALUE;
				else
					*(pOut++) = 0;
				pIn++;
			}
			else
			{
				if(*pIn == UNKNOWN_REAL_VALUE)
				{
					*(pOut++) = UNKNOWN_DISCRETE_VALUE;
					pIn++;
				}
				else
					*(pOut++) = (*(pIn++) < 0.5 ? 0 : 1);
			}
		}
		else if(nValues < m_valueCap)
		{
			double max = *(pIn++);
			*pOut = 0.0;
			for(size_t i = 1; i < nValues; i++)
			{
				if(*pIn > max)
				{
					max = *pIn;
					*pOut = (double)i;
				}
				pIn++;
			}
			pOut++;
		}
		else
		{
			if(*pIn == UNKNOWN_REAL_VALUE)
				*(pOut++) = UNKNOWN_DISCRETE_VALUE;
			else
				*(pOut++) = std::max(0.0, std::min(double(nValues - 1), floor(*pIn + 0.5)));
			pIn++;
		}
	}
}

#ifndef MIN_PREDICT
// virtual
void GNominalToCat::untransformToDistribution(const double* pIn, GPrediction* pOut)
{
	size_t nOutAttrCount = m_pRelationBefore->size();
	for(size_t i = 0; i < nOutAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues < 3)
		{
			if(nValues == 0)
			{
				GNormalDistribution* pNorm = pOut->makeNormal();
				pNorm->setMeanAndVariance(*pIn, 1.0); // todo: should we throw an exception here since we have no way to estimate the variance?
			}
			else if(nValues == 1)
			{
				GCategoricalDistribution* pCat = pOut->makeCategorical();
				pCat->setToUniform(1);
			}
			else
			{
				GCategoricalDistribution* pCat = pOut->makeCategorical();
				if(*pIn == UNKNOWN_REAL_VALUE)
					pCat->setToUniform(2);
				else
				{
					double* pVals = pCat->values(2);
					pVals[0] = 1.0 - *pIn;
					pVals[1] = *pIn;
					pCat->normalize(); // We have to normalize to ensure the values are properly clipped.
				}
			}
			pIn++;
			pOut++;
		}
		else if(nValues < m_valueCap)
		{
			GCategoricalDistribution* pCat = pOut->makeCategorical();
			pCat->setValues(nValues, pIn);
			pIn += nValues;
			pOut++;
		}
		else
		{
			GCategoricalDistribution* pCat = pOut->makeCategorical();
			pCat->setSpike(nValues, std::max(size_t(0), std::min(nValues - 1, size_t(floor(*pIn + 0.5)))), 3);
			pIn++;
			pOut++;
		}
	}
}
#endif // MIN_PREDICT

void GNominalToCat::reverseAttrMap(vector<size_t>& rmap)
{
	rmap.clear();
	size_t nInAttrCount = m_pRelationBefore->size();
	for(size_t i = 0; i < nInAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues < 3 || nValues >= m_valueCap)
			rmap.push_back(i);
		else
		{
			for(size_t j = 0; j < nValues; j++)
				rmap.push_back(i);
		}
	}
}

// --------------------------------------------------------------------------

GNormalize::GNormalize(double min, double max)
: GIncrementalTransform(), m_min(min), m_max(max), m_pMins(NULL), m_pRanges(NULL)
{
}

GNormalize::GNormalize(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll)
{
	m_min = pNode->field("min")->asDouble();
	m_max = pNode->field("max")->asDouble();
	size_t nAttrCount = m_pRelationBefore->size();
	m_pMins = new double[2 * nAttrCount];
	m_pRanges = &m_pMins[nAttrCount];
	GDomListIterator it1(pNode->field("mins"));
	if(it1.remaining() != nAttrCount)
		throw Ex("unexpected number of elements");
	GVec::deserialize(m_pMins, it1);
	GDomListIterator it2(pNode->field("ranges"));
	if(it2.remaining() != nAttrCount)
		throw Ex("unexpected number of elements");
	GVec::deserialize(m_pRanges, it2);
}

// virtual
GNormalize::~GNormalize()
{
	delete[] m_pMins;
}

// virtual
GDomNode* GNormalize::serialize(GDom* pDoc) const
{
	if(!m_pRelationBefore.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = baseDomNode(pDoc, "GNormalize");
	pNode->addField(pDoc, "min", pDoc->newDouble(m_min));
	pNode->addField(pDoc, "max", pDoc->newDouble(m_max));
	size_t nAttrCount = m_pRelationBefore->size();
	pNode->addField(pDoc, "mins", GVec::serialize(pDoc, m_pMins, nAttrCount));
	pNode->addField(pDoc, "ranges", GVec::serialize(pDoc, m_pRanges, nAttrCount));
	return pNode;
}

void GNormalize::setMinsAndRanges(sp_relation& pRel, const double* pMins, const double* pRanges)
{
	m_pRelationBefore = pRel;
	m_pRelationAfter = m_pRelationBefore;
	size_t nAttrCount = m_pRelationBefore->size();
	delete[] m_pMins;
	m_pMins = new double[2 * nAttrCount];
	m_pRanges = &m_pMins[nAttrCount];
	GVec::copy(m_pMins, pMins, nAttrCount);
	GVec::copy(m_pRanges, pRanges, nAttrCount);
}

// virtual
sp_relation GNormalize::trainInner(GMatrix& data)
{
	size_t nAttrCount = m_pRelationBefore->size();
	delete[] m_pMins;
	m_pMins = new double[2 * nAttrCount];
	m_pRanges = &m_pMins[nAttrCount];
	for(size_t i = 0; i < nAttrCount; i++)
	{
		if(m_pRelationBefore->valueCount(i) == 0)
		{
			data.minAndRange(i, &m_pMins[i], &m_pRanges[i]);
			if(m_pRanges[i] < 1e-12)
				m_pRanges[i] = 1.0;
		}
		else
		{
			m_pMins[i] = 0;
			m_pRanges[i] = 0;
		}
	}
	return data.relation();
}

// virtual
sp_relation GNormalize::trainInner(sp_relation& relation)
{
	throw Ex("This transform cannot be trained without data");
	return m_pRelationBefore;
}

// virtual
void GNormalize::transform(const double* pIn, double* pOut)
{
	size_t nAttrCount = m_pRelationBefore->size();
	double* pMins = m_pMins;
	double* pRanges = m_pRanges;
	for(size_t i = 0; i < nAttrCount; i++)
	{
		if(m_pRelationBefore->valueCount(i) == 0)
		{
			if(*pIn == UNKNOWN_REAL_VALUE)
				*pOut = UNKNOWN_REAL_VALUE;
			else
				*pOut = GMatrix::normalize(*pIn, *pMins, *pRanges, m_min, m_max - m_min);
		}
		else
			*pOut = *pIn;
		pOut++;
		pIn++;
		pMins++;
		pRanges++;
	}
}

// virtual
void GNormalize::untransform(const double* pIn, double* pOut)
{
	size_t nAttrCount = m_pRelationBefore->size();
	double* pMins = m_pMins;
	double* pRanges = m_pRanges;
	for(size_t i = 0; i < nAttrCount; i++)
	{
		if(m_pRelationBefore->valueCount(i) == 0)
		{
			if(*pIn == UNKNOWN_REAL_VALUE)
				*pOut = UNKNOWN_REAL_VALUE;
			else
				*pOut = GMatrix::normalize(*pIn, m_min, m_max - m_min, *pMins, *pRanges);
		}
		else
			*pOut = *pIn;
		pOut++;
		pIn++;
		pMins++;
		pRanges++;
	}
}

// virtual
void GNormalize::untransformToDistribution(const double* pIn, GPrediction* pOut)
{
	throw Ex("Sorry, cannot denormalize to a distribution");
}

// --------------------------------------------------------------------------

GDiscretize::GDiscretize(size_t buckets)
: GIncrementalTransform()
{
	m_bucketsIn = buckets;
	m_bucketsOut = -1;
	m_pMins = NULL;
	m_pRanges = NULL;
}

GDiscretize::GDiscretize(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll)
{
	m_bucketsIn = (size_t)pNode->field("bucketsIn")->asInt();
	m_bucketsOut = (size_t)pNode->field("bucketsOut")->asInt();
	size_t nAttrCount = m_pRelationBefore->size();
	m_pMins = new double[2 * nAttrCount];
	m_pRanges = &m_pMins[nAttrCount];
	GDomListIterator it1(pNode->field("mins"));
	if(it1.remaining() != nAttrCount)
		throw Ex("unexpected number of elements");
	GVec::deserialize(m_pMins, it1);
	GDomListIterator it2(pNode->field("ranges"));
	if(it2.remaining() != nAttrCount)
		throw Ex("unexpected number of elements");
	GVec::deserialize(m_pRanges, it2);
}

// virtual
GDiscretize::~GDiscretize()
{
	delete[] m_pMins;
}

// virtual
GDomNode* GDiscretize::serialize(GDom* pDoc) const
{
	GDomNode* pNode = baseDomNode(pDoc, "GDiscretize");
	pNode->addField(pDoc, "bucketsIn", pDoc->newInt(m_bucketsIn));
	pNode->addField(pDoc, "bucketsOut", pDoc->newInt(m_bucketsOut));
	size_t nAttrCount = m_pRelationBefore->size();
	pNode->addField(pDoc, "mins", GVec::serialize(pDoc, m_pMins, nAttrCount));
	pNode->addField(pDoc, "ranges", GVec::serialize(pDoc, m_pRanges, nAttrCount));
	return pNode;
}

// virtual
sp_relation GDiscretize::trainInner(GMatrix& data)
{
	// Make the relations
	m_bucketsOut = m_bucketsIn;
	if(m_bucketsOut > data.rows())
		m_bucketsOut = std::max((size_t)2, (size_t)sqrt((double)data.rows()));
	size_t nAttrCount = data.cols();
	GMixedRelation* pRelationAfter = new GMixedRelation();
	for(size_t i = 0; i < nAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues > 0)
			pRelationAfter->addAttr(nValues);
		else
			pRelationAfter->addAttr(m_bucketsOut);
	}

	// Determine the boundaries
	delete[] m_pMins;
	m_pMins = new double[2 * nAttrCount];
	m_pRanges = &m_pMins[nAttrCount];
	for(size_t i = 0; i < nAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues > 0)
		{
			m_pMins[i] = 0;
			m_pRanges[i] = 0;
		}
		else
			data.minAndRangeUnbiased(i, &m_pMins[i], &m_pRanges[i]);
	}
	return pRelationAfter;
}

// virtual
sp_relation GDiscretize::trainInner(sp_relation& relation)
{
	throw Ex("This transform cannot be trained without data");
	return m_pRelationBefore;
}

// virtual
void GDiscretize::transform(const double* pIn, double* pOut)
{
	if(!m_pMins)
		throw Ex("Train was not called");
	size_t nAttrCount = m_pRelationBefore->size();
	for(size_t i = 0; i < nAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues > 0)
			pOut[i] = pIn[i];
		else
			pOut[i] = std::max(0, std::min((int)(m_bucketsOut - 1), (int)(((pIn[i] - m_pMins[i]) * m_bucketsOut) / m_pRanges[i])));
	}
}

// virtual
void GDiscretize::untransform(const double* pIn, double* pOut)
{
	if(!m_pMins)
		throw Ex("Train was not called");
	size_t nAttrCount = m_pRelationBefore->size();
	for(size_t i = 0; i < nAttrCount; i++)
	{
		size_t nValues = m_pRelationBefore->valueCount(i);
		if(nValues > 0)
			pOut[i] = pIn[i];
		else
			pOut[i] = (((double)pIn[i] + .5) * m_pRanges[i]) / m_bucketsOut + m_pMins[i];
	}
}

// virtual
void GDiscretize::untransformToDistribution(const double* pIn, GPrediction* pOut)
{
	throw Ex("Sorry, cannot undiscretize to a distribution");
}




#ifndef MIN_PREDICT

GImputeMissingVals::GImputeMissingVals(GRand& rand)
: m_pCF(NULL), m_pNTC(NULL), m_rand(rand), m_pLabels(NULL), m_pBatch(NULL)
{
}

GImputeMissingVals::GImputeMissingVals(GDomNode* pNode, GLearnerLoader& ll)
: GIncrementalTransform(pNode, ll), m_rand(ll.rand()), m_pLabels(NULL), m_pBatch(NULL)
{
	m_pCF = ll.loadCollaborativeFilter(pNode->field("cf"));
	GDomNode* pNTC = pNode->fieldIfExists("ntc");
	if(pNTC)
		m_pNTC = new GNominalToCat(pNTC, ll);
	else
		m_pNTC = NULL;
}

// virtual
GImputeMissingVals::~GImputeMissingVals()
{
	delete(m_pCF);
	delete(m_pNTC);
	delete(m_pBatch);
}

// virtual
GDomNode* GImputeMissingVals::serialize(GDom* pDoc) const
{
	if(!m_pRelationBefore.get())
		throw Ex("train must be called before serialize");
	GDomNode* pNode = baseDomNode(pDoc, "GImputeMissingVals");
	pNode->addField(pDoc, "cf", m_pCF->serialize(pDoc));
	if(m_pNTC)
		pNode->addField(pDoc, "ntc", m_pNTC->serialize(pDoc));
	return pNode;
}

void GImputeMissingVals::setCollaborativeFilter(GCollaborativeFilter* pCF)
{
	delete(m_pCF);
	m_pCF = pCF;
}

// virtual
sp_relation GImputeMissingVals::trainInner(GMatrix& data)
{
	// Train the nominalToCat filter if needed
	if(data.relation()->areContinuous(0, data.cols()))
	{
		delete(m_pNTC);
		m_pNTC = NULL;
	}
	else if(!m_pNTC)
	{
		m_pNTC = new GNominalToCat();
		m_pNTC->preserveUnknowns();
	}
	GMatrix* pData;
	Holder<GMatrix> hData;
	if(m_pNTC)
	{
		m_pNTC->train(data);
		pData = m_pNTC->transformBatch(data);
		hData.reset(pData);
	}
	else
		pData = &data;

	// Train the collaborative filter
	if(!m_pCF)
		m_pCF = new GMatrixFactorization(std::max(size_t(2), std::min(size_t(8), data.cols() / 3)), m_rand);
	m_pCF->trainDenseMatrix(*pData, m_pLabels);
	return m_pRelationBefore;
}

// virtual
sp_relation GImputeMissingVals::trainInner(sp_relation& relation)
{
	throw Ex("This transform cannot be trained without data");
	return m_pRelationBefore;
}

// virtual
void GImputeMissingVals::transform(const double* pIn, double* pOut)
{
	// If there are no missing values, just copy it across
	const double* p = pIn;
	GRelation& rel = *m_pRelationBefore.get();
	size_t dims = rel.size();
	size_t i;
	for(i = 0; i < dims; i++)
	{
		if(rel.valueCount(i) == 0)
		{
			if(*p == UNKNOWN_REAL_VALUE)
				break;
		}
		else
		{
			if(*p == UNKNOWN_DISCRETE_VALUE)
				break;
		}
		p++;
	}
	if(i >= dims)
	{
		GVec::copy(pOut, pIn, dims);
		return;
	}

	// Convert to all real values if necessary
	double* pVec;
	if(m_pNTC)
	{
		pVec = m_pNTC->innerBuf();
		m_pNTC->transform(pIn, pVec);
		dims = m_pNTC->after()->size();
	}
	else
	{
		pVec = pOut;
		GVec::copy(pVec, pIn, dims);
	}

	// Impute the missing values
	m_pCF->impute(pVec, dims);

	// Convert back to nominal if necessary
	if(m_pNTC)
		m_pNTC->untransform(pVec, pOut);
}

// virtual
void GImputeMissingVals::untransform(const double* pIn, double* pOut)
{
	GVec::copy(pOut, pIn, m_pRelationAfter->size());
}

// virtual
void GImputeMissingVals::untransformToDistribution(const double* pIn, GPrediction* pOut)
{
	throw Ex("Sorry, cannot unimpute to a distribution");
}

// virtual
GMatrix* GImputeMissingVals::transformBatch(GMatrix& in)
{
	GMatrix* pOut = in.clone();
	size_t dims = in.cols();
	for(size_t i = 0; i < in.rows(); i++)
	{
		double* pVec = in[i];
		for(size_t j = 0; j < dims; j++)
		{
			if(*pVec == UNKNOWN_REAL_VALUE)
				*pVec = m_pCF->predict(i, j);
			pVec++;
		}
	}
	return pOut;
}

void GImputeMissingVals::setLabels(GMatrix* pLabels)
{
	m_pLabels = pLabels;
}

#endif // MIN_PREDICT


} // namespace GClasses

