 #include "sample_classes.h"
 #include <iostream>


 using namespace std;

 A::A(){
    count = i++;
 }
 A::~A(){
    std::cout << "A:" << __FUNCTION__
 	     << " called from instance " << count <<"." <<std::endl;
 }

 void A::activity(){
    std::cout << "A:" << __FUNCTION__
 	     << " called from instance " << count <<"." <<std::endl;
 }



 B::B(){
    count = i++;
 }
 B::~B(){
    std::cout << "B:"  << __FUNCTION__
 	     << " called from instance " << count <<"." <<std::endl;
 }
 void B::dothing(){
    std::cout << "B:"  << __FUNCTION__
 	     << " called from instance " << count <<"." <<std::endl;
 }



 C::C(A* a){
    count = i++;
    a_ = a;
 }
 C::~C(){
    std::cout << "C:" << __FUNCTION__
 	     << " called from instance " << count <<"." <<std::endl;
 }


 void C::action(){
    std::cout << "C:" << __FUNCTION__
 	     << " called from instance " << count <<"." <<std::endl;

    a_->activity();
 }


void Base::do_action(){
   std::cout << "C:" << __FUNCTION__
 	     << " called from Base Class." <<std::endl;

}

void Derived::do_action(){
   std::cout << "C:" << __FUNCTION__
 	     << " called from Derived Class." <<std::endl;

}


 int A::i = 0;
 int B::i = 0;
 int C::i = 0;
