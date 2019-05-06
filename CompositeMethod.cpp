//组合模式:将对象组合成树形结构以表示‘部分-整体’的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性
#include<string>
#include<list>
#include<iostream>

using namespace std;

//Component为组合中的对象声明接口，在适当情况下，实现所有类共有接口的默认行为。声明一个接口用于访问和管理Component的子部件
class Component
{
protected:
	string name;
public:
	Component(string name) { this->name = name; }
	virtual void Add(Component* c) {};
	virtual void Remove(Component* c) {};
	virtual void Display(int depth) {};
};

string PrintTree(const char s, int t)
{
	string s1;
	for (int i = 0; i < t; ++i)
	{
		s1=s1+s;
	}
	return s1;
}

//Leaf在组合中表示叶节点对象，叶节点没有子节点
class Leaf :public Component
{
public:
	Leaf(string name) :Component(name) {};
	//叶子没法再增加分枝和树枝，所以Add和Remove方法实现它没有意义，只是为了消除抽象
	void Add(Component* c) override
	{
		cout << "Cannot add to a leaf" << endl;
	}
	void Remove(Component* c) override
	{
		cout << "Cannot remove from a leaf" << endl;
	}
	void Display(int depth) override
	{
		cout << PrintTree('-', depth) << name << endl;
	}
};

//Composite定义有枝节点行为，用来存储子部件，在Component接口中实现与子部件有关的操作，比如增加Add和删除Remove
class Composite :public Component
{
private:
	list<Component*>children;//用于存储其下属的枝节点和叶节点
public:
	Composite(string name) :Component(name) {};
	void Add(Component* c) override
	{
		children.push_back(c);
	}
	void Remove(Component* c)override
	{
		//children.pop_back();
		for (list<Component*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			if (*i == c)
			{
				children.erase(i);
				break;
			}
		}
	}
	void Display(int depth) override//显示其枝节点名称，并对其下级进行遍历
	{
		cout << PrintTree('-', depth) << name << endl;
		for (auto& children:children)
		{
			children->Display(depth + 2);
		}
	}
};

int main()
{
	//生成树根root，根上长出两叶LeafA和LeafB
	Composite* root = new Composite("root");
	root->Add(new Leaf("Leaf A"));
	root->Add(new Leaf("Leaf B"));
	
	//根上长出分支Composite X，分枝上也有两叶LeafXA和LeafBX
	Composite* comp = new Composite("Composite X");
	comp->Add(new Leaf("Leaf XA"));
	comp->Add(new Leaf("Leaf XB"));

	root->Add(comp);

	//在CompositeX上再长出分支CompositeXY，分枝上也有两叶LeafXYA和LeafXYB
	Composite* comp2 = new Composite("Composite XY");
	comp2->Add(new Leaf("Leaf XYA"));
	comp2->Add(new Leaf("Leaf XYB"));
	comp->Add(comp2);

	root->Add(new Leaf("Leaf C"));

	Leaf* leaf = new Leaf("Leaf D");
	root->Add(leaf);
	root->Remove(leaf);

	root->Display(1);

	return 0;
}