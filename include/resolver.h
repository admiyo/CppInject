#ifndef DEPENDENCY_RESOLVER_H
#define DEPENDENCY_RESOLVER_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#include <typeinfo>
#include <iostream>
#include <stdexcept>



namespace dependency{

  /*callback to free an object at a given scope.*/
  class destroyer{
  public:
    destroyer(){};
    virtual ~destroyer(){};
    virtual void operator()() = 0;
  };


  class ZoneType{
  protected:    
    ZoneType()
      {
      };
  };

  class GlobalZoneType: public ZoneType {
    GlobalZoneType(){
    };
  public:
    const static GlobalZoneType instance;
  };
  
  template <class T>
    class ConcreteZoneType: public ZoneType{
  public:
    ConcreteZoneType<T>(){
    };
    const static ConcreteZoneType<T> instance;
  };


  /*
    A Hierarchical zone of control.
  */
  class Zone{
    std::vector<destroyer*> destroyers;
  public:

    const ZoneType * zoneType ;
    Zone* parent_;
  Zone(const ZoneType* type):zoneType(type){parent_ = 0;};
  Zone(Zone * parent,const ZoneType* type):zoneType(type){parent_ = parent;};
    virtual ~Zone(){
      for (std::vector<destroyer*>::iterator itr = destroyers.begin();
 	   itr != destroyers.end();++itr){
	destroyer*  destroy = *itr;
	(*destroy)();
	delete destroy;
      }
    };

    virtual  bool operator == (Zone& other){
      return this->zoneType == other.zoneType;
    }

    operator const std::string (){
      return std::string("");
    }

    void push_destroyer(destroyer* d){
      destroyers.push_back(d);
    }
  };


  template <class T>
    T* default_factory(Zone& f){
    return new T;
  };

  template <class T>
    void default_cleaner(T* t){
    delete t;
  };
  

  template <class T>
    class activator {
    public:
      typedef T* (*factory)(Zone& f) ;
      typedef void (*cleanup)(T*) ;
      
      activator(){
	factory_ = 0;
	cleanup_ = 0;
      };
      void operator = (const activator& other){
	factory_ = other.factory_;
	cleanup_ = other.cleanup_;
      }
      
    activator(factory  f, cleanup  c):
      factory_(f), cleanup_(c){};
      
    activator(const activator& a):
      factory_(a.factory_), cleanup_(a.cleanup_){};
      
      factory  factory_;
      cleanup  cleanup_;
    };



  /**
   *
   */
  template <typename T, int Which=0> class supply{
    
    class TDestroyer: public destroyer{
      Zone* zone_;
    public:
      TDestroyer(Zone* zone){
	zone_ = zone;
      }
      void operator()(){
	supply<T>::release(zone_);
      }
    };
  public:
    typedef T* (*factory)(Zone& f) ;
    typedef void (*cleanup)(T*) ;

    supply * next;

    supply(){
      next= 0;
    };
    supply(supply * next){
      this->next = next;
    }

    virtual ~supply(){
    }
  private:
    static std::map < const ZoneType *, activator<T> > activator_map; 
    static std::map < Zone* , T* > object_map;

  public:
    static void 
    configure(const ZoneType& zoneType, activator<T> act){
      activator_map[&zoneType] = act;
    }

    static void 
    configure(const ZoneType& zoneType, factory factfunct,cleanup cleanfunct){
      activator_map[&zoneType] = activator<T>(factfunct, cleanfunct);
    }

    static void configure(factory factfunct,cleanup cleanfunct){
      configure(GlobalZoneType::instance, factfunct,cleanfunct);
    }

    static void configure(factory factfunct){
      configure(GlobalZoneType::instance, factfunct, default_cleaner<T>);
    }

    static void configure(cleanup cleanfunct){
      configure (GlobalZoneType::instance, default_factory<T>, cleanfunct);
    }

    static void configure(){
      configure (GlobalZoneType::instance, 
		 activator<T>(default_factory<T>, default_cleaner<T>));
    }

    static T* fetch(Zone& zone){
      Zone* zonep = &zone;
      T * val = object_map[zonep];
      if (!val){
	
	activator<T> act = activator_map[zone.zoneType];

	if (0 == act.factory_) {
	  if (zone.parent_){
	    return fetch(*zone.parent_);
	  }else{
	    std::string message
	      ("No factory function registered and no parent for ");
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
    static void release(Zone* zone){
      T * val = object_map[zone];
      if (!val){
	if (zone->parent_){
	  release(zone->parent_);
	}
	
	//We may want to put an assert failure here.
	return;
      }
      
      (activator_map[zone->zoneType].cleanup_)(object_map[zone]);
      object_map.erase(zone);
    }
  };



  template<class T> const ConcreteZoneType<T> 
    ConcreteZoneType<T>::instance;

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
