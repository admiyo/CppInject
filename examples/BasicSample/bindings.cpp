#include <CppInject.h>
#include "sample_classes.h"

using namespace CppInject;

A* create(Zone& zone){
  return new A();
}

B * make(Zone& zone){
  return new B();
}

void destroy(A* a){
  delete a;
}

C* makeC(Zone& zone){
  return new C(supply<A>::fetch(zone));
}

void dropC(C* c){
  delete(c);
}


Base* makeBase(Zone& zone){
  return new Derived();
}

//REGISTER(A);
//REGISTER_FACTORY_WHICH(A,1,destroy);

void
register_all_bindings(){
  supply<A>::configure();
  supply<A,1>::configure(destroy);
  supply<B>::configure(make);
  supply<B,1>::configure();
  supply<C>::configure(makeC,dropC);
  //  supply<Base>::configure(makeBase);
}


