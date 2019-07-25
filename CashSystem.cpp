#include <string>
using namespace std;

//利用Factory模式
//定义抽象类
using hash_t = size_t;
constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_run_time(const char* str) 
{
	hash_t ret = basis;

	while (*str)
	{
		ret ^= *str;
		ret *= prime;
		str++;
	}
	return ret;
}

constexpr hash_t hash_compile_time(const char* str, hash_t last_value = basis)
{
	return *str ? hash_compile_time(str + 1, (*str^last_value)*prime) : last_value;
}

class CashSuper
{
public:
	virtual double acceptCash(double money) = 0;
};

//正常收费子类
class CashNormal :public CashSuper
{
public:
	double acceptCash(double money) override
	{
		return money;
	}
};

//打折收费子类
class CashRebate :public CashSuper
{
private:
	double moneyRebate = 1.0;
public:
	CashRebate(double moneyRebate)
	{
		this->moneyRebate = moneyRebate;
	}
	double acceptCash(double money) override
	{
		return money * moneyRebate;
	}
};

//返回收费子类
class CashReturn :public CashSuper
{
private:
	double moneyCondition = 0.0;//返利条件
	double moneyReturn = 0.0;//返利值
public:
	CashReturn(double moneyCondition, double moneyReturn)
	{
		this->moneyCondition = moneyCondition;
		this->moneyReturn = moneyReturn;
	}
	double acceptCash(double money)
	{
		double result = money;
		if (money >= moneyCondition)//若大于返利条件，则需要减去返利值
		{
			result = money - (money / moneyCondition)*moneyReturn;
		}
		return result;
	}
};

//现金收费工场
class CashFactory
{
public:
	static CashSuper* createCashAccept(const char* type)
	{
		CashSuper* cs;
		switch (hash_run_time(type))
		{
		case hash_compile_time("正常收费"):
			cs = new CashNormal;
			break;
		case hash_compile_time("满300返100"):
			cs = new CashReturn(300.0, 100.0);
			break;
		case hash_compile_time("打8折"):
			cs = new CashRebate(0.8);
			break;
		}
		return cs;
	}
};

//利用Strategy模式:定义一系列算法的方法，概念上这些算法完成的都是相同的工作，只是实现不同，以相同的方法调用所有的算法，减少了各种算法类与使用算法类之间的耦合
//CashSuper,CashNormal,CashRebate,CashReturn都不用更改,只要加一个CashContext
class CashContext
{
private:
	CashSuper* cs;
public:
	CashContext(const char* type)
	{//策略模式与工厂模式结合
		switch (hash_run_time(type))
		{
		case hash_compile_time("正常收费"):
			cs = new CashNormal;
			break;
		case hash_compile_time("满300返100"):
			cs = new CashReturn(300.0, 100.0);
			break;
		case hash_compile_time("打8折"):
			cs = new CashRebate(0.8);
			break;
		}
	}
	double GetResult(double money)
	{
		return cs->acceptCash(money);
	}
};