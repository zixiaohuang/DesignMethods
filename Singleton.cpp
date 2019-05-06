//单例模式：保证一个类仅有一个实例，并提供一个访问它的全局访问点
//通常我们可以让一个全局变量使得一个对象被访问，但它不能防止你实例化多个对象，一个最好的办法是，让类自身赋值保存它的唯一实例。
//这个类可以保证没有其他实例可以被创建，并且它可以提供一个访问实例的方法。

#include <iostream>
#include <mutex>

using namespace std;
std::mutex mtx;

class CSingleton1
{
private:
	CSingleton1(){}//构造函数是私有的，这就堵死了外界new创建此类实例的可能
	static CSingleton1 *m_pInstance;
public:
	static CSingleton1 *GetInstance()//此方法是获得本类实例的唯一全局访问点
	{
		if (m_pInstance == nullptr)//若实例不存在，则new一个新实例，否则返回已有的实例
			m_pInstance = new CSingleton1();
		return m_pInstance;
	}
};

//m_pInstance指向的空间什么时候释放？实例的析构函数什么时候执行？
//一个妥善的方法是让这个类自己知道在适合的时候把自己删除，或者把删除自己的操作挂在操作系统中的某个合适的点上


class CSingleton2
{
private:
	CSingleton2() {}
	static CSingleton2 *m_pInstance;
	class CGarbo//被定义为CSingleton私有内嵌类，以防该类被其他地方滥用
	{
	public:
		~CGarbo()//它的唯一工作就是在析构函数中删除CSingleton的实例
		{
			if (CSingleton2::m_pInstance)
				delete CSingleton2::m_pInstance;
		}
	};
	static CGarbo Garbo;//定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数

public:
	static CSingleton2 *GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CSingleton2();
		return m_pInstance;
	}
};

class CSingleton3
{
private:
	CSingleton3(){}
	//声明拷贝构造和类赋值为私有，禁止类拷贝和类赋值
	CSingleton3(const CSingleton3 &);
	CSingleton3& operator = (const CSingleton3 &) {};
public:
	static CSingleton3& GetInstance()
	{
		static CSingleton3 instance; //局部静态变量
		return instance;
	}
};

//多线程的程序中，多个线程同时访问Singleton类，调用GetInstance()方法，会有可能造成创建多个实例
class CSingleton4
{
private:
	CSingleton4() {}
	//声明拷贝构造和类赋值为私有，禁止类拷贝和类赋值
	CSingleton4(const CSingleton4 &);
	CSingleton4& operator = (const CSingleton4 &) {};
public:
	static CSingleton4* pInstance;
	static CSingleton4* GetInstance()
	{
		if (pInstance == NULL)
		{
			mtx.lock();
			if (pInstance == NULL)
			{
				pInstance = new CSingleton4();
			}
			mtx.unlock();
		}
	}
};

CSingleton4* pInstance = 0;

int main()
{
	CSingleton2* s1 = CSingleton2::GetInstance();
	CSingleton2* s2 = CSingleton2::GetInstance();

	if (s1 = s2)
	{
		cout << "Same object" << endl;
	}

	return 0;
}