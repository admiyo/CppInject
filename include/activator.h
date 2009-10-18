// Copyright 2009 Michaël Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_ACTIVATOR_H_
#define _CPPINJECT_ACTIVATOR_H_

// TODO: Remove
#include "Zone.h"

namespace dependency
{

template <class T>
T* default_factory(Zone& f)
{
	return new T;
};

template <class T>
void default_cleaner(T* t)
{
	delete t;
};

template <class T>
class activator
{
public:
	typedef T* (*factoryFunction)(Zone& f) ;
	typedef void (*cleanupFunction)(T*) ;

	activator()
	  : mFactory(0), mCleanup(0)
	{
	}

	void operator=(const activator& other)
	{
		mFactory = other.mFactory;
		mCleanup = other.mCleanup;
	}

	activator(factoryFunction f, cleanupFunction c)
	  : mFactory(f), mCleanup(c)
	{
	}

	activator(const activator& a)
	  : mFactory(a.mFactory), mCleanup(a.mCleanup)
	{}

	factoryFunction factory() const
	{
		return mFactory;
	}

	cleanupFunction cleanup() const
	{
		return mCleanup;
	}

private:
	factoryFunction mFactory;
	cleanupFunction mCleanup;
};
	
}

#endif
