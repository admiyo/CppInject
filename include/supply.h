// Copyright 2009 Micha�l Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_SUPPLY_H_
#define _CPPINJECT_SUPPLY_H_

#include "activator.h"
#include "destroyer.h"
#include "Zone.h"
#include "ZoneType.h"

#include <string>

namespace dependency
{

/**
 *
 */
template <typename T, int Which=0> class supply
{
	class TDestroyer : public destroyer
	{
		Zone* zone_;
	public:
		TDestroyer(Zone* zone)
		{
			zone_ = zone;
		}
		
		void operator()()
		{
			supply<T>::release(zone_);
		}
	};
	
public:
	typedef T* (*factory)(Zone& f) ;
	typedef void (*cleanup)(T*) ;

	supply * next;

	supply()
	{
		next= 0;
	};
	
	supply(supply * next)
	{
		this->next = next;
	}

	virtual ~supply()
	{
	}
	
private:
	static std::map< const ZoneType *, activator<T> > activator_map; 
	static std::map< Zone* , T* > object_map;

public:
	static void configure(const ZoneType& zoneType, activator<T> act)
	{
		activator_map[&zoneType] = act;
	}

	static void configure(const ZoneType& zoneType, factory factfunct,cleanup cleanfunct)
	{
		activator_map[&zoneType] = activator<T>(factfunct, cleanfunct);
	}

	static void configure(factory factfunct,cleanup cleanfunct)
	{
		configure(GlobalZoneType::instance, factfunct,cleanfunct);
	}

	static void configure(factory factfunct)
	{
		configure(GlobalZoneType::instance, factfunct, default_cleaner<T>);
	}

	static void configure(cleanup cleanfunct)
	{
		configure (GlobalZoneType::instance, default_factory<T>, cleanfunct);
	}

	static void configure()
	{
		configure (GlobalZoneType::instance,activator<T>(default_factory<T>, default_cleaner<T>));
	}

	static T* fetch(Zone& zone)
	{
		Zone* zonep = &zone;
		T * val = object_map[zonep];
		
		if (!val)
		{
			activator<T> act = activator_map[zone.zoneType];

			if (0 == act.factory_)
			{
				if (zone.parent_)
				{
					return fetch(*zone.parent_);
				}
				else
				{
					std::string message("No factory function registered and no parent for ");
					message.push_back( Which );

					throw std::logic_error(message);
				}
			}
			
			//This needs a lock in order to be thread safe.
			{
			  val = (*act.factory_)(zone);
			  object_map[&zone] = val;

			  destroyer* d = new TDestroyer(&zone);
			  zone.push_destroyer(d);
			}
		}
		
		return val;
	}

	static void release(Zone* zone)
	{
		T * val = object_map[zone];
		if (!val)
		{
			if (zone->parent_)
			{
				release(zone->parent_);
			}
	
			//We may want to put an assert failure here.
			return;
		}
		
		(activator_map[zone->zoneType].cleanup_)(object_map[zone]);
		object_map.erase(zone);
	}
};
  
}

#endif
