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
 : mZoneType(type), mParent(0)
{
}

Zone::Zone(Zone * parent, const ZoneType* type)
 : mParent(parent), mZoneType(type)
{
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
	return mZoneType == other.mZoneType;
}

void Zone::push_destroyer(destroyer* d)
{
	destroyers.push_back(d);
}

Zone *Zone::parent() const
{
	return mParent;
}

const ZoneType *Zone::zoneType() const
{
	return mZoneType;
}

}