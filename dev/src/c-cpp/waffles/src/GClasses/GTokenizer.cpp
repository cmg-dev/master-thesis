/*
	Copyright (C) 2006, Mike Gashler

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	see http://www.gnu.org/copyleft/lesser.html
*/

#include "GTokenizer.h"
#include "GError.h"
#include "GHolders.h"
#ifndef MIN_PREDICT
#include "GFile.h"
#include "GString.h"
#endif // MIN_PREDICT
#include "GBitTable.h"
#include "GHeap.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#ifdef WINDOWS
	#include <io.h>
#else
	#include <unistd.h>
#endif

using std::string;
using std::map;
using std::string;

namespace GClasses {


GCharSet::GCharSet(const char* szChars)
	: m_bt(256)
{
	char c = '\0';
	while(*szChars != '\0')
	{
		if(*szChars == '-')
		{
			if(c == '\0')
				m_bt.set((unsigned char)*szChars);
			else
			{
				char d = szChars[1];
				if(d <= c)
					throw Ex("invalid character range");
				for(c++; c <= d && c != 0; c++)
					m_bt.set((unsigned char)c);
				szChars++;
			}
		}
		else
			m_bt.set((unsigned char)*szChars);
		c = *szChars;
		szChars++;
	}
}

bool GCharSet::find(char c)
{
	return m_bt.bit((unsigned char)c);
}


GTokenizer::GTokenizer(const char* szFilename)
{
	std::ifstream* pStream = new std::ifstream();
	m_pStream = pStream;
	pStream->exceptions(std::ios::failbit|std::ios::badbit);
	try
	{
		pStream->open(szFilename, std::ios::binary);
		pStream->seekg(0, std::ios::end);
		m_len = (size_t)pStream->tellg();
		pStream->seekg(0, std::ios::beg);
	}
	catch(const std::exception&)
	{
#ifdef WINDOWS
		if (_access(szFilename, 0) == 0)
#else
		if (access(szFilename, 0) == 0)
#endif
			throw Ex("Error while trying to open the existing file: ", szFilename);
		else
			throw Ex("File not found: ", szFilename);
	}
	m_pBufStart = new char[256];
	m_pBufPos = m_pBufStart;
	m_pBufEnd = m_pBufStart + 256;
	m_lineStart = m_len;
	m_line = 1;
}

GTokenizer::GTokenizer(const char* pFile, size_t len)
{
	if(len > 0)
	{
		m_pStream = new std::istringstream(string(pFile, len));
		m_len = len;
	}
	else
	{
		string s(pFile);
		m_len = s.length();
		m_pStream = new std::istringstream(s);
	}
	m_pBufStart = new char[256];
	m_pBufPos = m_pBufStart;
	m_pBufEnd = m_pBufStart + 256;
	m_lineStart = m_len;
	m_line = 1;
}

GTokenizer::~GTokenizer()
{
	delete[] m_pBufStart;
	delete(m_pStream);
}

void GTokenizer::growBuf()
{
	size_t len = m_pBufEnd - m_pBufStart;
	char* pNewBuf = new char[len * 2];
	m_pBufEnd = pNewBuf + (len * 2);
	memcpy(pNewBuf, m_pBufStart, len);
	m_pBufPos = pNewBuf + len;
	delete[] m_pBufStart;
	m_pBufStart = pNewBuf;
}

char GTokenizer::get()
{
	char c = m_pStream->get();
	m_len--;
	if(c == '\n')
	{
		m_line++;
		m_lineStart = m_len;
	}
	return c;
}

void GTokenizer::bufferChar(char c)
{
	if(m_pBufPos == m_pBufEnd)
		growBuf();
	*m_pBufPos = c;
	m_pBufPos++;
}

char* GTokenizer::nextUntil(GCharSet& delimeters, size_t minLen)
{
	m_pBufPos = m_pBufStart;
	while(m_len > 0)
	{
		char c = m_pStream->peek();
		if(delimeters.find(c))
			break;
		c = get();
		bufferChar(c);
	}
	if((size_t)(m_pBufPos - m_pBufStart) < minLen)
		throw Ex("Unexpected token on line ", to_str(m_line), ", col ", to_str(col()));
	if(m_pBufPos == m_pBufEnd)
		growBuf();
	*m_pBufPos = '\0';
	return m_pBufStart;
}

char* GTokenizer::nextUntilNotEscaped(char escapeChar, GCharSet& delimeters)
{
	m_pBufPos = m_pBufStart;
	char cCur = '\0';
	while(m_len > 0)
	{
		char c = m_pStream->peek();
		if(delimeters.find(c) && cCur != escapeChar)
			break;
		c = get();
		bufferChar(c);
		cCur = c;
	}
	if(m_pBufPos == m_pBufEnd)
		growBuf();
	*m_pBufPos = '\0';
	return m_pBufStart;
}

char* GTokenizer::nextWhile(GCharSet& set, size_t minLen)
{
	m_pBufPos = m_pBufStart;
	while(m_len > 0)
	{
		char c = m_pStream->peek();
		if(!set.find(c))
			break;
		c = get();
		bufferChar(c);
	}
	if((size_t)(m_pBufPos - m_pBufStart) < minLen)
		throw Ex("Unexpected token on line ", to_str(m_line), ", col ", to_str(col()));
	if(m_pBufPos == m_pBufEnd)
		growBuf();
	*m_pBufPos = '\0';
	return m_pBufStart;
}

void GTokenizer::skip(GCharSet& delimeters)
{
	while(m_len > 0)
	{
		char c = m_pStream->peek();
		if(!delimeters.find(c))
			break;
		c = get();
	}
}

void GTokenizer::skipTo(GCharSet& delimeters)
{
	while(m_len > 0)
	{
		char c = m_pStream->peek();
		if(delimeters.find(c))
			break;
		c = get();
	}
}

char* GTokenizer::nextArg(GCharSet& delimiters, char escapeChar)
{
	char c = m_pStream->peek();
	if(c == '"')
	{
		GCharSet cs("\"\n");
		advance(1);
		nextUntil(cs);
		if(peek() != '"')
			throw Ex("Expected matching double-quotes on line ", 
								 to_str(m_line), ", col ", to_str(col()));
		advance(1);
		while(!delimiters.find(m_pStream->peek()))
			advance(1);
		return m_pBufStart;
	}
	else if(c == '\'')
	{
		advance(1);
		GCharSet cs("'\n");
		nextUntil(cs);
		if(peek() != '\'')
			throw Ex("Expected a matching single-quote on line ", to_str(m_line), 
								 ", col ", to_str(col()));
		advance(1);
		while(!delimiters.find(m_pStream->peek()))
			advance(1);
		return m_pBufStart;
	}

	m_pBufPos = m_pBufStart;
	bool inEscapeMode = false;
	while(m_len > 0)
	{
		char c = m_pStream->peek();
		if(inEscapeMode)
		{
			if(c == '\n')
			{
				throw Ex("Error: '", to_str(escapeChar), "' character used as "
									 "last character on a line to attempt to extend string over "
									 "two lines on line" , to_str(m_line), ", col ", 
									 to_str(col()) );
			}
			c = get();
			bufferChar(c);
			inEscapeMode = false;			
		}
		else
		{
			if(c == '\n' || delimiters.find(c)){ break; }
			c = get();
			if(c == escapeChar)	{	inEscapeMode = true;	}
			else { bufferChar(c);	}
		}
	}

	if(m_pBufPos == m_pBufEnd)
	{
		growBuf();
	}
	*m_pBufPos = '\0';

	//	std::cerr << "nextArg: '" << m_pBufStart << "'\n"; //DEBUG
	return m_pBufStart;
}

void GTokenizer::advance(size_t n)
{
	while(n > 0 && m_len > 0)
	{
		get();
		n--;
	}
}

char GTokenizer::peek()
{
	if(m_len > 0)
		return m_pStream->peek();
	else
		return '\0';
}

size_t GTokenizer::line()
{
	return m_line;
}

size_t GTokenizer::remaining()
{
	return m_len;
}

void GTokenizer::expect(const char* szString)
{
	while(*szString != '\0' && m_len > 0)
	{
		char c = get();
		if(c != *szString)
			throw Ex("Expected \"", szString, "\" on line ", to_str(m_line), ", col ", to_str(col()));
		szString++;
	}
	if(*szString != '\0')
		throw Ex("Expected \", szString, \". Reached end-of-file instead.");
}

size_t GTokenizer::tokenLength()
{
	return m_pBufPos - m_pBufStart;
}

char* GTokenizer::trim(GCharSet& set)
{
	char* pStart = m_pBufStart;
	while(pStart < m_pBufPos && set.find(*pStart))
		pStart++;
	for(char* pEnd = m_pBufPos - 1; pEnd >= pStart && set.find(*pEnd); pEnd--)
		*pEnd = '\0';
	return pStart;
}

size_t GTokenizer::col()
{
	return m_lineStart - m_len + 1;
}

} // namespace GClasses
