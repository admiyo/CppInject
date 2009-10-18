// Copyright 2009 Michaël Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_CONCRETEZONETYPE_H_
#define _CPPINJECT_CONCRETEZONETYPE_H_

#include "ZoneType.h"

namespace dependency
{

template <class T>
class ConcreteZoneType : public ZoneType
{
public:
	ConcreteZoneType<T>() {}
	
public:
	const static ConcreteZoneType<T> instance;
};

template<class T> const ConcreteZoneType<T> ConcreteZoneType<T>::instance;

}
#endif
