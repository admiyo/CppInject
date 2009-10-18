 #include "resolver.h"
 #include "sample_classes.h"

 #include <iostream>

 using namespace std;
 using namespace dependency;


 extern void register_all_bindings();

 int main(){
   Zone globalZone(&GlobalZoneType::instance);
   Zone session1(&globalZone, &ConcreteZoneType<Session>::instance);
   Zone request1(&session1, &ConcreteZoneType<Request>::instance);
   Zone request2(&session1, &ConcreteZoneType<Request>::instance);

    std::cout << __FUNCTION__ << std::endl;

    register_all_bindings();

    A* a = supply<A>::fetch(request1);
    B* b = supply<B>::fetch(request2);
    a->activity();
    b->dothing();

    a = supply<A>::fetch(request2);
    b = supply<B>::fetch(request1);
    a->activity();
    b->dothing();

    a = supply<A>::fetch(request2);
    b = supply<B>::fetch(request1);
    a->activity();
    b->dothing();

    a = supply<A,1>::fetch(request1);
    b = supply<B,1>::fetch(request2);
    a->activity();
    b->dothing();

    a = supply<A,1>::fetch(request2);
    b = supply<B,1>::fetch(request1);
    a->activity();
    b->dothing();

    C* c = supply<C>::fetch(request1);
    c->action();
    try{
       c = supply<C,3>::fetch(request1);
    }catch(logic_error le){
      cout << "this error is intentional:" 
	   << le.what() 
	   << endl;
    }

	system("pause");
 }
