/*
	Copyright (C) 2006, Mike Gashler

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	see http://www.gnu.org/copyleft/lesser.html
*/

#include "GHeap.h"
#include "GError.h"
#ifndef MIN_PREDICT
#include "GHashTable.h"
#endif // MIN_PREDICT

using namespace GClasses;

// virtual
GHeap::~GHeap()
{
	clear();
}

void GHeap::clear()
{
	while(m_pCurrentBlock)
	{
		char* pNext = *(char**)m_pCurrentBlock;
		delete[] m_pCurrentBlock;
		m_pCurrentBlock = pNext;
	}
	m_nCurrentPos = m_nMinBlockSize;
}