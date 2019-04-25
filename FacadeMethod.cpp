//
// Created by ken on 19-4-25.
//

//外观模式：为子系统中的一组接口提供一个一致的界面，此模式定义了一个高层接口，这个接口使得这一子系统更加容易使用
#include <iostream>

using namespace std;

class SubSystemOne
{
public:
    void MethodOne()
    {
        cout<<"Subsystem method one"<<endl;
    }
};

class SubSystemTwo
{
public:
    void MethodTwo()
    {
        cout<<"Subsystem method two"<<endl;
    }
};

class SubSystemThree
{
public:
    void MethodThree()
    {
        cout<<"Subsystem method three"<<endl;
    }
};

class SubSystemFour
{
public:
    void MethodFour()
    {
        cout<<"Subsystem method four"<<endl;
    }
};

class Facade
{
    SubSystemOne* one;
    SubSystemTwo* two;
    SubSystemThree* three;
    SubSystemFour* four;

public:
    Facade(){one = new SubSystemOne();two = new SubSystemTwo();three = new SubSystemThree(); four = new SubSystemFour();}
    void MethodA()
    {
        cout<<"------Method A-------"<<endl;
        one->MethodOne();
        two->MethodTwo();
        four->MethodFour();
    }

    void MethodB()
    {
        cout<<"------Method B-------"<<endl;
        two->MethodTwo();
        three->MethodThree();
    }
};


int main()
{
    Facade* facade = new Facade();

    facade->MethodA();
    facade->MethodB();

    return 0;
}