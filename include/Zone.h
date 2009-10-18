// Copyright 2009 Michaël Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_ZONE_H_
#define _CPPINJECT_ZONE_H_

#include <vector>

namespace dependency
{

class ZoneType;
class destroyer;

/**
 * @brief A Hierarchical zone of control.
 */
class Zone
{
 public:
	const ZoneType * zoneType ;
	Zone* _parent;
	
	Zone(const ZoneType* type);
	Zone(Zone * parent, const ZoneType* type);
	
	virtual ~Zone();

	bool operator==(const Zone &other);

	void push_destroyer(destroyer* d);

private:
	std::vector<destroyer*> destroyers;
};

}
#endif