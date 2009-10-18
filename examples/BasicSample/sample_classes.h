 #ifndef SAMPLE_CLASSES_H
 #define SAMPLE_CLASSES_H



 class A{
    static int i;
    int  count;
 public:

    A();
    ~A();
    void activity();
 };


 class B{
    static int i;
    int  count;
 public:
    B();
    ~B();
    void dothing();
 };

 class C{
    static int i;
    int  count;
    A* a_;
 public:

    C(A* a);
    ~C();
    void action();
 };



 class D{

 public:

    ~D();
    void action(){};
 };



class Base {
 public:
  virtual ~Base(){}
  virtual void do_action();
};

class Derived : public Base
{
 public:
  virtual ~Derived(){}
  virtual void do_action();
};


//These are for scopes.
class Session{};
class Request{};



 #endif
