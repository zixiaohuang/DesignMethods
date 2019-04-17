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
	virtual ~Operation() {};//定义纯虚构函数，可以析构派生类
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
			throw "Division by zero condition!";
		result = _numberA / _numberB;
		return result;
	}
};

class OperationFactory
{
public:
	static Operation* createOperate(const char operate)
	{
		Operation* oper=NULL;//创建一个父类的指针
		switch (operate)
		{
		case '+':
			oper = new OperationAdd;//指向子类
			break;
		case '-':
			oper = new OperationSub;
			break;
		case '*':
			oper = new OperationMul;
			break;
		case '/':
			oper = new OperationDiv;
			break;
		default:
			throw "Unknow operation";
		}
		return oper;
	}
};

int main(int argc, char* argv[])
{
	Operation* oper;
	double NumberA = 1.0;
	double NumberB = 0.0;
	oper = OperationFactory::createOperate('+');
	oper->SetValue(NumberA, NumberB);
	//oper:Operation(NumberA, NumberB); 不能调用构造函数，都会自动析构清理，需要另外定义一个设置值的函数
	double result = oper->GetResult();
	cout << result << endl;
	return 0;
}