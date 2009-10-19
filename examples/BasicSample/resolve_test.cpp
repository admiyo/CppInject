 #include <CppInject.h>
 #include "sample_classes.h"

 #include <iostream>

 using namespace std;
 using namespace CppInject;


 extern void register_all_bindings();

 int main(){
   Zone globalZone(&GlobalZoneType::instance);
   Zone session1( &ConcreteZoneType<Session>::instance, &globalZone );
   Zone request1( &ConcreteZoneType<Request>::instance, &session1 );
   Zone request2( &ConcreteZoneType<Request>::instance, &session1 );

    std::cout << __FUNCTION__ << std::endl;

    register_all_bindings();

    A* a = supply<A>::fetch(request1);
    B* b = supply<B>::fetch(request2);
    a->activity();
    b->dothing();

	cout << "----------------" << endl;

    a = supply<A>::fetch(request2);
    b = supply<B>::fetch(request1);
    a->activity();
    b->dothing();

	cout << "----------------" << endl;

    a = supply<A>::fetch(request2);
    b = supply<B>::fetch(request1);
    a->activity();
    b->dothing();

	cout << "----------------" << endl;

    a = supply<A,1>::fetch(request1);
    b = supply<B,1>::fetch(request2);
    a->activity();
    b->dothing();

	cout << "----------------" << endl;

    a = supply<A,1>::fetch(request2);
    b = supply<B,1>::fetch(request1);
    a->activity();
    b->dothing();

	cout << "----------------" << endl;

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
