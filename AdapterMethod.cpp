//适配器模式：将一个类的接口转换成客户希望的另外一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作
//分类：类适配器模式和对象适配器模式
//在软件开发后期或维护期考虑使用,双方都不太容易修改的时候再使用适配器模式

#include <iostream>

using namespace std;

//Target:客户所期待的接口
class Target
{
public:
	virtual void Request()
	{
		cout << "Normal Request！" << endl;
	}
};

//Adaptee:需要适配的类
class Adaptee
{
public:
	void SpecificRequest()
	{
		cout << "Specific Request！" << endl;
	}
};

//Adapter:通过在内部包装一个Adaptee对象，把源接口转换为目标接口
class Adapter :public Target
{
private:
	Adaptee adaptee; //建立一个私有的Adaptee对象
public:
	void Request() override //把表面上调用Request()方法变成实际调用SpecifiRequest()
	{
		adaptee.SpecificRequest();
	}
};

int main()
{
	Target* target = new Adapter();
	target->Request();
}