// Copyright 2009 Michaël Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#include "Zone.h"

#include "destroyer.h"
#include "ZoneType.h"

namespace dependency
{

Zone::Zone(const ZoneType* type)
 : zoneType(type)
{
	_parent = 0;
}

Zone::Zone(Zone * parent, const ZoneType* type)
 : zoneType(type)
{
	_parent = parent;
}

Zone::~Zone()
{
	for( std::vector<destroyer*>::iterator itr = destroyers.begin(); itr != destroyers.end(); ++itr )
	{
		destroyer* destroy = *itr;
		(*destroy)();
		delete destroy;
	}
}

bool Zone::operator==(const Zone &other)
{
	return this->zoneType == other.zoneType;
}

void Zone::push_destroyer(destroyer* d)
{
	destroyers.push_back(d);
}

}