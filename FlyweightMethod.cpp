//享元模式：运用共享技术有效地支持大量细粒度的对象
#include <iostream>
#include<unordered_map>
#include<string>

using namespace std;

//Flyweight：所有具体享元类的超类或接口，通过这个接口，Flyweight可以接受并作用于外部状态
class Flyweight
{
public:
	virtual void Operation(int extrinsicstate) = 0;
};

//继承Flyweight超类或实现Flyweight接口,并为内部状态增加存储空间
class ConcreteFlyweight : public Flyweight
{
public:
	void Operation(int extrinsicstate) override
	{
		cout << "Concrete Flyweight: " << extrinsicstate << endl;
	}
};

class UnsharedConcreteFlyweight : public Flyweight
{
public:
	void Operation(int extrinsicstate) override
	{
		cout << "UnsharedConcreteFlyweight: " << extrinsicstate << endl;
	}
};

//享元工厂，用来创建Flyweight对象
class FlyweightFactory
{
private:
	unordered_map<string, ConcreteFlyweight*> flyweights;//哈希表
public:
	//初始化工厂时，先生成三个实例
	FlyweightFactory()
	{
		flyweights.insert(std::make_pair("X", new ConcreteFlyweight()));
		flyweights.insert(std::make_pair("Y", new ConcreteFlyweight()));
		flyweights.insert(std::make_pair("Z", new ConcreteFlyweight()));
	}
	//根据客户端请求，获得已生成的实例
	Flyweight* GetFlyweight(string key)
	{
		return ((Flyweight*)flyweights[key]);
	}
};

//用户(外部对象考虑由客户端对象存储,当调用Flyweight对象的操作时，将该状态传递给它)
class User
{
private:
	string name;
public:
	User(string name) { this->name = name; }
	string GetName(){ return this->name; }
};

//网站抽象类
class WebSite
{
public:
	virtual void Use(User* user) = 0;//使用方法需要传递“用户”对象
};

//具体网站
class ConcreteWebSite : public WebSite
{
private:
	string webname;
public:
	ConcreteWebSite(string name) { this->webname = name; }
	void Use(User* user) override { cout << "Website classification: " << webname <<" User: "<<user->GetName()<< endl; }
};

//网站工厂
class WebSiteFactory
{
private:
	unordered_map<string, ConcreteWebSite*> flyweights;
public:
	WebSite* GetWebSiteCategory(string key)
	{
		unordered_map<string, ConcreteWebSite*>::iterator search = flyweights.find(key);
		if (search == flyweights.end())
		{
			flyweights.insert(std::make_pair(key, new ConcreteWebSite(key)));//内部状态存储于ConcreteWebSite对象之中
		}
		return ((WebSite*)flyweights[key]);
	}

	//获取网站分类总数
	int GetWebSiteCount()
	{
		return flyweights.size();
	}
};



int main()
{
	/*
	int extrinsicstate = 22;

	FlyweightFactory* f = new FlyweightFactory();

	Flyweight* fx = f->GetFlyweight("X");
	fx->Operation(--extrinsicstate);

	Flyweight* fy = f->GetFlyweight("Y");
	fy->Operation(--extrinsicstate);

	Flyweight* fz = f->GetFlyweight("Z");
	fz->Operation(--extrinsicstate);

	Flyweight* uf = new UnsharedConcreteFlyweight();

	uf->Operation(--extrinsicstate);
	*/

	WebSiteFactory* f = new WebSiteFactory();

	WebSite* fx = f->GetWebSiteCategory("产品展示");//实例化“产品展示”的“网站”对象
	fx->Use(new User("Ken"));//外部对象

	WebSite* fy = f->GetWebSiteCategory("产品展示");//共享上方生成的对象，不再实例化
	fy->Use(new User("Katy"));//外部对象

	WebSite* fz = f->GetWebSiteCategory("产品展示");
	fz->Use(new User("Cherry"));//外部对象

	WebSite* fl = f->GetWebSiteCategory("博客");
	fl->Use(new User("Kary"));//外部对象

	WebSite* fm = f->GetWebSiteCategory("博客");
	fm->Use(new User("John"));//外部对象

	WebSite* fn = f->GetWebSiteCategory("博客");
	fn->Use(new User("Ken"));//外部对象

	cout << f->GetWebSiteCount() << endl;//统计实例化的个数，尽管给了5个不同的用户，但实际上只有两个网站实例

	return 0;
}

//享元对象内部并且不会随环境改变而改变的共享部分，可以称为是享元对象的内部状态，而随环境改变而改变的，不可以共享的状态就是外部状态
//享元模式可以避免大量非常相似类的开销。在程序设计中，有时候需要生成大量细粒度的类实例来表示数据。
//如果能发现这些实例除了几个参数外基本上都是相同的，有时候能受大幅度减少需要实例化的类的数量
//但使用享元模式需要维护一个记录了系统已有的所有享元的列表，而这本身需要耗费资源，另外享元模式使得系统更加复杂。