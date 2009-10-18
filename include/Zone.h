#ifndef _CPPINJECT_ZONE_H_
#define _CPPINJECT_ZONE_H_

// TODO: move to .cpp and use forward declaration
#include "destroyer.h"
#inclide "ZoneType.h"

#include <vector>

namespace dependency
{

// TODO: Rename to my conventions

/**
 * @brief A Hierarchical zone of control.
 */
class Zone
{
 public:
	const ZoneType * zoneType ;
	Zone* _parent;
	
	Zone(const ZoneType* type)
	  : zoneType(type)
	{
		_parent = 0;
	}
	
	Zone(Zone * parent, const ZoneType* type)
	  : zoneType(type)
	{
		_parent = parent;
	}
	
	virtual ~Zone()
	{
		for( std::vector<destroyer*>::iterator itr = destroyers.begin(); itr != destroyers.end(); ++itr )
		{
			destroyer* destroy = *itr;
			(*destroy)();
			delete destroy;
		}
	}

	virtual bool operator==(Zone& other)
	{
		return this->zoneType == other.zoneType;
	}

	operator const std::string ()
	{
		return std::string("");
	}

	void push_destroyer(destroyer* d)
	{
		destroyers.push_back(d);
	}

private:
	std::vector<destroyer*> destroyers;
};

}
#endif