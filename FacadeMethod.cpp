//
// Created by ken on 19-4-25.
//

//���ģʽ��Ϊ��ϵͳ�е�һ��ӿ��ṩһ��һ�µĽ��棬��ģʽ������һ���߲�ӿڣ�����ӿ�ʹ����һ��ϵͳ��������ʹ��
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