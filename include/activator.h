// Copyright 2009 Micha�l Larouche <larouche@kde.org>
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
	typedef T* (*factory)(Zone& f) ;
	typedef void (*cleanup)(T*) ;

	activator()
	{
		factory_ = 0;
		cleanup_ = 0;
	}

	void operator=(const activator& other)
	{
		factory_ = other.factory_;
		cleanup_ = other.cleanup_;
	}

	activator(factory f, cleanup c)
	  : factory_(f), cleanup_(c)
	{
	}

	activator(const activator& a)
	  : factory_(a.factory_), cleanup_(a.cleanup_)
	{}

	factory factory_;
	cleanup cleanup_;
};
	
}

#endif
