#include<cstdio>

class Operation
{
protected:
	double _numberA;
	double _numberB;
	double result;

public:
	Operation(double a, double b) :_numberA(a), _numberB(b) {};
	virtual ~Operation() {};//���崿�鹹��������������������
	virtual double GetResult()
	{
		return result;
	}
};

class OperationAdd :public Operation
{

};