//迭代器模式：提供一种方法顺序访问一个聚合对象中各个元素，而又不暴露该对象的内部表示

#include<vector>
#include<string>
#include<iostream>

using namespace std;

//迭代器负责定义访问和遍历元素的接口
template<class Item>
class Iterator
{
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual Item* currentItem() = 0;
	virtual bool isDone() = 0;
	virtual ~Iterator(){}
};

//前置声明
template<class Item>
class ConcreteAggregate;

//具体迭代器（可以有不同种类的迭代器），继承Iterator，实现迭代器接口，并要记录遍历中的当前位置
//正向迭代器
template<class Item>
class ConcreteIterator :public Iterator<Item>
{
private:
	ConcreteAggregate<Item>* aggregate;
	int current;

public:
	ConcreteIterator(ConcreteAggregate<Item>* a):aggregate(a),current(0){}
	void first()override
	{
		current = 0;
	}

	void next()override
	{
		if (current < aggregate->getLen())
		{
			current++;
		}

	}

	Item* currentItem() override
	{
		if (current < aggregate->getLen())
			return &(*aggregate)[current];
		else
			return NULL;
	}

	bool isDone()
	{
		return (current >= aggregate->getLen());
	}
};

//反向迭代器
template<class Item>
class ConcreteIteratorDesc :public Iterator<Item>
{
private:
	ConcreteAggregate<Item>* aggregate;
	int current;

public:
	ConcreteIteratorDesc(ConcreteAggregate<Item>* a) :aggregate(a), current(aggregate->getLen()-1) {}
	void first()override
	{
		current = aggregate->getLen()-1;
	}

	void next()override
	{
		if (current >=0)
		{
			current--;
		}

	}

	Item* currentItem() override
	{
		if (current >= 0)
			return &(*aggregate)[current];
		else
			return NULL;
	}

	bool isDone()
	{
		return (current<0);
	}
};

//集体角色：集合角色负责提供创建具体迭代器角色的接口
template<class Item>
class Aggregate
{
public:
	virtual Iterator<Item>* createIterator() = 0;
	virtual Iterator<Item>* createIteratorDesc() = 0;
	virtual void addobject(Item s) {};
	virtual ~Aggregate(){}
};

//具体集合角色：具体集合角色实现创建具体迭代器角色的接口，这个具体迭代器角色与该集合的结构相关
template<class Item>
class ConcreteAggregate:public Aggregate<Item>
{
private:
	vector<Item> items;
public:
	Iterator<Item>* createIterator() override
	{
		return new ConcreteIterator<Item>(this);
	}

	Iterator<Item>* createIteratorDesc() override
	{
		return new ConcreteIteratorDesc<Item>(this);
	}

	Item& operator[](int index)
	{
		return items[index];
	}

	void addobject(Item s) override
	{
		items.push_back(s);
	}

	int getLen()
	{
		return items.size();
	}
};

int main()
{
	Aggregate<string>* a=new ConcreteAggregate<string>();
	a->addobject("Tom");
	a-> addobject("Sam");
	a->addobject("John");
	a->addobject("Chalie");

	Iterator<string>* it = a->createIterator();

	for (it->first(); !it->isDone(); it->next())
	{
		cout << *(it->currentItem()) <<", Please buy tickets"<< endl;
	}

	Iterator<string>* it2 = a->createIteratorDesc();

	for (it2->first(); !it2->isDone(); it2->next())
	{
		cout << *(it2->currentItem()) << ", Please buy tickets" << endl;
	}


	delete it;
	delete it2;
	delete a;
	return 0;

}

