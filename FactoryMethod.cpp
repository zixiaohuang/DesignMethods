//
// Created by ken on 19-4-22.
//
/*简单工厂模式虽然简单,但系统需要引入新产品时,由于静态工厂方法通过所传入参数的
 *不同来创建不同的产品,必定要修改工厂类的源代码,违背了“开闭原则”
 *
 * */

#include<cstdio>
#include<iostream>
using namespace std;

class Operation
{
protected:
    double _numberA;
    double _numberB;
    double result=0;

public:
    Operation() { _numberA = 0.0; _numberB = 0.0; };
    Operation(double a, double b) :_numberA(a), _numberB(b) {};
    virtual ~Operation() {};
    virtual double GetResult()
    {
        return result;
    }
    void SetValue(double a, double b)
    {
        _numberA = a;
        _numberB = b;
    }
};

class OperationAdd :public Operation
{
public:
    OperationAdd() :Operation() {};
    OperationAdd(double a,double b) : Operation(a,b) {};

    double GetResult() override
    {
        //double result = 0;
        result = _numberA + _numberB;
        return result;
    }
};

class OperationSub : public Operation
{
public:
    OperationSub() :Operation() {};
    OperationSub(double a, double b) : Operation(a, b) {};

    double GetResult() override
    {
        //double result = 0;
        result = _numberA - _numberB;
        return result;
    }
};

class OperationMul : public Operation
{
public:
    OperationMul() :Operation() {};
    OperationMul(double a, double b) : Operation(a, b) {};
    double GetResult() override
    {
        //double result = 0;
        result = _numberA * _numberB;
        return result;
    }
};

class OperationDiv : public Operation
{
public:
    OperationDiv() :Operation() {};
    OperationDiv(double a, double b) : Operation(a, b) {};
    double GetResult() override
    {
        //double result = 0;
        if (_numberB == 0)
            throw runtime_error("Division by zero condition!");
        result = _numberA / _numberB;
        return result;
    }
};

//建立一个工厂接口,每添加一类只需要继承这个接口在后面添加，不需要修改原来的工厂函数
//让子类决定实例化哪一个类,工厂方法使一个类的实例化延迟到其子类
class IFactory
{
public:
    virtual Operation* CreateOperation(){};
};

class AddFactory : public IFactory
{
public:
    Operation* CreateOperation() override
    {
        return new OperationAdd;
    }
};

class SubFactory : public IFactory
{
public:
    Operation* CreateOperation() override
    {
        return new OperationSub;
    }
};

class MulFactory : public IFactory
{
public:
    Operation* CreateOperation() override
    {
        return new OperationMul;
    }
};

class DivFactory : public IFactory
{
public:
    Operation* CreateOperation() override
    {
        return new OperationDiv;
    }
};

int main(int argc, char* argv[])
{
    IFactory* operFactory = new AddFactory();
    Operation* oper = operFactory->CreateOperation();
    oper->SetValue(1.0,2.0);
    double result = oper->GetResult();
    return 0;
}