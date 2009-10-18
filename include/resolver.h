#ifndef DEPENDENCY_RESOLVER_H
#define DEPENDENCY_RESOLVER_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#include <typeinfo>
#include <iostream>

#include "destroyer.h"
#include "ZoneType.h"
#include "GlobalZoneType.h"
#include "ConcreteZoneType.h"
#include "Zone.h"
#include "activator.h"
#include "supply.h"

namespace dependency
{
  template < typename T, int Which >
    std::map < const ZoneType *,  activator<T> > 
    supply<T,Which>::activator_map;
  
  template <typename T, int Which>
    std::map < Zone*, T* >
    supply<T,Which>::object_map;
  

#define REGISTER(CLASS)					\
  bool register##CLASS(){				\
    supply<CLASS>::configure();				\
    return true;					\
  }							\
  static bool __registered##CLASS = register##CLASS()

#define REGISTER_FACTORY(CLASS,FACTORY)			\
  bool register##CLASS(){				\
    supply<CLASS>::configure(FACTORY);			\
    return true;					\
  }							\
  static bool __registered##CLASS = register##CLASS()

#define REGISTER_FACTORY_CLEANER(CLASS,FACTORY,CLEANER)	\
  bool register##CLASS(){				\
    supply<CLASS>::configure(FACTORY,CLEANER);		\
    return true;					\
  }							\
  static bool __registered##CLASS = register##CLASS()

};

#endif
