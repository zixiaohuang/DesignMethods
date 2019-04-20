#include <string>
using namespace std;

//����Factoryģʽ
//���������
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

//�����շ�����
class CashNormal :public CashSuper
{
public:
	double acceptCash(double money) override
	{
		return money;
	}
};

//�����շ�����
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

//�����շ�����
class CashReturn :public CashSuper
{
private:
	double moneyCondition = 0.0;//��������
	double moneyReturn = 0.0;//����ֵ
public:
	CashReturn(double moneyCondition, double moneyReturn)
	{
		this->moneyCondition = moneyCondition;
		this->moneyReturn = moneyReturn;
	}
	double acceptCash(double money)
	{
		double result = money;
		if (money >= moneyCondition)//�����ڷ�������������Ҫ��ȥ����ֵ
		{
			result = money - (money / moneyCondition)*moneyReturn;
		}
		return result;
	}
};

//�ֽ��շѹ���
class CashFactory
{
public:
	static CashSuper* createCashAccept(const char* type)
	{
		CashSuper* cs;
		switch (hash_run_time(type))
		{
		case hash_compile_time("�����շ�"):
			cs = new CashNormal;
			break;
		case hash_compile_time("��300��100"):
			cs = new CashReturn(300.0, 100.0);
			break;
		case hash_compile_time("��8��"):
			cs = new CashRebate(0.8);
			break;
		}
		return cs;
	}
};

//����Strategyģʽ:����һϵ���㷨�ķ�������������Щ�㷨��ɵĶ�����ͬ�Ĺ�����ֻ��ʵ�ֲ�ͬ������ͬ�ķ����������е��㷨�������˸����㷨����ʹ���㷨��֮������
//CashSuper,CashNormal,CashRebate,CashReturn�����ø���,ֻҪ��һ��CashContext
class CashContext
{
private:
	CashSuper* cs;
public:
	CashContext(const char* type)
	{//����ģʽ�빤��ģʽ���
		switch (hash_run_time(type))
		{
		case hash_compile_time("�����շ�"):
			cs = new CashNormal;
			break;
		case hash_compile_time("��300��100"):
			cs = new CashReturn(300.0, 100.0);
			break;
		case hash_compile_time("��8��"):
			cs = new CashRebate(0.8);
			break;
		}
	}
	double GetResult(double money)
	{
		return cs->acceptCash(money);
	}
};