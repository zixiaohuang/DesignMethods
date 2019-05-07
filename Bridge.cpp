
#include <iostream>

using namespace std;

//原始代码
//手机品牌
class HandsetBrand1
{
public:
	virtual void Run()
	{

	}
};

//手机品牌M
class HandsetBrandM1 :public HandsetBrand1
{

};

//手机品牌N
class HandsetBrandN1:public HandsetBrand1
{

};

//手机品牌M的游戏
class HandsetBrandMGame1 :public HandsetBrandM1
{
public:
	void Run() override
	{
		cout << "Run the ceilphone game of Brand M" << endl;
	}
};

//手机品牌N的游戏
class HandsetBrandNGame1 :public HandsetBrandM1
{
public:
	void Run() override
	{
		cout << "Run the ceilphone game of Brand N" << endl;
	}
};

//手机品牌M的通讯录
class HandsetBrandMAddressList1 :public HandsetBrandM1
{
public:
	void Run() override
	{
		cout << "Run the ceilphone address of Brand M" << endl;
	}
};

//手机品牌N的通讯录
class HandsetBrandNAddressList1 :public HandsetBrandM1
{
public:
	void Run() override
	{
		cout << "Run the ceilphone address of Brand N" << endl;
	}
};

int main2()
{
	HandsetBrand1* ab;
	ab = new HandsetBrandMAddressList1();
	ab->Run();

	ab = new HandsetBrandMGame1();
	ab->Run();

	ab = new HandsetBrandNAddressList1();
	ab->Run();

	ab = new HandsetBrandNGame1();
	ab->Run();

	return 0;
}

//面向对象的继承，既新颖功能又强大。但对象的继承关系是在编译时就定义好了，所以无法在运行时改变从父类继承的实现。
//子类的实现与它的父类有非常紧密的依赖关系，以至于父类实现的任何变化必然导致子类发生变化。
//当你需要复用子类时，如果继承下来的实现不适合解决新的问题，则父类必须重写或被其他更适合的类替换。这种依赖关系限制了灵活性并最终限制了复用性。


//合成/聚合复用原则：尽量使用合成/聚合，尽量不要使用类继承
//聚合表示一种弱的‘拥有’关系，体现的是A对象可以包含B对象，但B对象不是A对象的一部分
//合成则是一种强的‘拥有’关系，体现了严格的部分和整体的关系，部分和整体的生命周期一样
//优先使用对象的合成/聚合将有助于你保持每个类被封装，并被集中在单个任务上，这样类和类继承层次会保持较小规模，并且不太可能增长为不可控制的庞然大物。

//桥模式:将抽象部分与它的实现部分分离，使它们都可以独立地变换

//手机软件
class HandsetSoft
{
public:
	virtual void Run() = 0;
};

//游戏、通讯录等具体类
//手机游戏
class HandsetGame :public HandsetSoft
{
public:
	void Run() override
	{
		cout << "Run the ceilphone game " << endl;
	}
};

//手机通讯录
class HandsetAddressList : public HandsetSoft
{
public:
	void Run() override
	{
		cout << "Run the ceilphone address" << endl;
	}
};

//增加一个功能，只要直接增加这个类就可以
//如增加MP3音乐播放功能
class HandsetMP3 :public HandsetSoft
{
public:
	void Run()
	{
		cout << "Run the ceilphone MP3" << endl;
	}
};



//手机品牌类
//手机品牌
class HandsetBrand
{
protected:
	HandsetSoft* soft;//手机品牌包含有手机软件，但软件并不是品牌一部分，聚合关系

	//设置手机软件
public:
	void SetHandsetSoft(HandsetSoft* soft)//品牌需要关注软件，所有可在机器中安装软件（设置手机软件），以备运行
	{
		this->soft = soft;
	}

	//运行
	virtual void Run() = 0;
};

//手机品牌N
class HandsetBrandN :public HandsetBrand
{
public:
	void Run() override
	{
		soft->Run();
	}
};

class HandsetBrandM : public HandsetBrand
{
public:
	void Run() override
	{
		soft->Run();
	}
};

//增加S品牌,直接加
class HandsetBrandS : public HandsetBrand
{
public:
	void Run() override
	{
		soft->Run();
	}
};

int main()
{
	HandsetBrand* ab;
	ab = new HandsetBrandN();

	ab->SetHandsetSoft(new HandsetGame());
	ab->Run();

	ab->SetHandsetSoft(new HandsetAddressList());
	ab->Run();

	ab = new HandsetBrandM();

	ab->SetHandsetSoft(new HandsetGame());
	ab->Run();

	ab->SetHandsetSoft(new HandsetAddressList());
	ab->Run();

	return 0;
}

//继承是一种强耦合，父类变，子类就必须要变。只用继承会造成大量的类增加，不能满足开放-封闭原则时，就应该考虑用桥接模式
