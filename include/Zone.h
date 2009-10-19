// Copyright 2009 Micha�l Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_ZONE_H_
#define _CPPINJECT_ZONE_H_

#include <vector>

namespace CppInject
{

class ZoneType;
class destroyer;

/**
 * @brief A Hierarchical zone of control.
 */
class Zone
{
 public:
	Zone(const ZoneType* type);
	Zone(const ZoneType* type, Zone * parent);
	
	virtual ~Zone();

	bool operator==(const Zone &other);

	void push_destroyer(destroyer* d);

	Zone *parent() const;

	const ZoneType *zoneType() const;

private:
	std::vector<destroyer*> destroyers;
	Zone* mParent;
	const ZoneType *mZoneType;
};

}
#endif