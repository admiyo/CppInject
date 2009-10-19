// Copyright 2009 Michaël Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_GLOBALZONETYPE_H_
#define _CPPINJECT_GLOBALZONETYPE_H_

#include "ZoneType.h"

namespace CppInject
{

class GlobalZoneType : public ZoneType
{
public:
	const static GlobalZoneType instance;
	
private:
	GlobalZoneType() {}
};

}
#endif
