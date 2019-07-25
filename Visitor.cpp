//访问者模式目的：把处理从数据结构分离出来。
//如果系统有比较稳定的数据结构，又有易于变化的算法的话，使用访问者模式比较合适

#include <string>
#include <list>
#include <vector>
#include <iostream>
using namespace std;

class Man;
class Woman;

class Action
{
protected:
	string action;
public:
	virtual ~Action() {};
	virtual void GetManConclusion(Man* concreteElementA) = 0;
	virtual void GetWomanConclusion(Woman* concreteElementB) = 0;
};


class Person
{
public:
	virtual ~Person() {};
	virtual void Accept(Action* visitor) = 0;
	//string Get(){ return action; }
	//void Set(string value) { action = value; }
	//virtual void GetConclusion()=0;
};

class Man :public Person
{
public:
	string name = "男人";
	void Accept(Action* visitor) override
	{
		visitor->GetManConclusion(this);
	}
};

class Woman :public Person
{
public:
	string name = "女人";
	void Accept(Action* visitor) override
	{
		visitor->GetWomanConclusion(this);
	}
};

class Success :public Action
{
protected:
	string action = "成功";
public:
	void GetManConclusion(Man* concreteElementA) override
	{
		cout<< concreteElementA->name << action << "时，背后多半有一个伟大的女人。" << endl;
	}
	void GetWomanConclusion(Woman* concreteElementB) override
	{
		cout << concreteElementB->name << action << "时，背后大多有一个不成功的男人。" << endl;
	}
};

class Failing :public Action
{
protected:
	string action = "失败";
public:
	void GetManConclusion(Man* concreteElementA) override
	{
		cout << concreteElementA->name << action << "时，闷头喝酒，谁也不用劝。" << endl;
	}
	void GetWomanConclusion(Woman* concreteElementB) override
	{
		cout << concreteElementB->name << action << "时，眼汪汪，谁也劝不了。" << endl;
	}
};

class Amativeness :public Action
{
protected:
	string action = "恋爱";
public:
	void GetManConclusion(Man* concreteElementA) override
	{
		cout << concreteElementA->name << action <<  "时,凡事不懂也要装懂。"  << endl;
	}
	void GetWomanConclusion(Woman* concreteElementB) override
	{
		cout << concreteElementB->name << action << "时,遇事懂也装作不懂。"  << endl;
	}
};


//对象结构
class ObjectStructure
{
private:
	list<Person*> elements;
	list<Person*>::iterator iter;
public:
	//增加
	void Add(Person* element)
	{
		elements.push_back(element);
	}
	//移除
	void Detach(Person* element)
	{
		elements.remove(element);
	}
	void Display(Action* visitor)
	{
		for (iter = elements.begin(); iter != elements.end(); ++iter)
		{
			(*iter)->Accept(visitor);
		}
	}
};

int main()
{
	ObjectStructure* o = new ObjectStructure();
	o->Add(new Man());
	o->Add(new Woman());

	//成功时的反应
	Success* v1 = new Success();
	o->Display(v1);

	//失败时的反应
	Failing* v2 = new Failing();
	o->Display(v2);

	//恋爱时的反应
	Amativeness* v3 = new Amativeness();
	o->Display(v3);

	return 0;
}





class Visitor;
//Element类，定义一个Accept操作，它以一个访问者为参数
class Element
{
public:
	virtual ~Element() {};
	virtual void Accept(Visitor* visitor) = 0;
};

//ConcreteElementA和ConcreteElementB类，具体元素，实现Accept操作
class ConcreteElementA :public Element
{
public:
	string name = "ConcreteElementA";
	void Accept(Visitor* visitor)override;//先申明
	void OperationA() { }
};

class ConcreteElementB :public Element
{
public:
	string name = "ConcreteElementB";
	void Accept(Visitor* visitor)override;//先申明
	void OperationB() { }
};

//Visitor类，为该对象结构中ConcreteElement的每一个类声明一个Visit操作
class Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA* concreteElementA)=0;
	virtual void VisitConcreteElementB(ConcreteElementB* concreteElementB)=0;
};

void ConcreteElementA:: Accept(Visitor* visitor)//定义位于Visitor类后，否则会报错“使用未定义的类型”
{
	visitor->VisitConcreteElementA(this);
};


void ConcreteElementB:: Accept(Visitor* visitor)//定义位于Visitor类后，否则会报错“使用未定义的类型”
{
	visitor->VisitConcreteElementB(this);
}

//具体访问者
class ConcreteVisitor1 :public Visitor
{
public:
	string name = "ConcreteVisitor1";
	void VisitConcreteElementA(ConcreteElementA* concreteElementA) override
	{
		cout << concreteElementA->name << "被" << this->name << "访问" << endl;
	}

	void VisitConcreteElementB(ConcreteElementB* concreteElementB) override
	{
		cout << concreteElementB->name << "被" << this->name << "访问" << endl;
	}
};

class ConcreteVisitor2 :public Visitor
{
public:
	string name = "ConcreteVisitor2";
	void VisitConcreteElementA(ConcreteElementA* concreteElementA) override
	{
		cout << concreteElementA->name << "被" << this->name << "访问" << endl;
	}

	void VisitConcreteElementB(ConcreteElementB* concreteElementB) override
	{
		cout << concreteElementB->name << "被" << this->name << "访问" << endl;
	}
};



//ObjectStructure类，能枚举它的元素，可以提供一个高层的接口以允许访问者访问它的元素
class ObjectStructure2
{
private:
	list<Element*> elements;
public:
	void Attach(Element* element)
	{
		elements.push_back(element);
	}

	void Detach(Element* element)
	{
		list<Element*>::iterator iter = elements.begin();
		list<Element*>::iterator pos;
		for (; iter != elements.end(); ++iter)
		{
			if (*iter == element)
			{
				pos = iter;
			}
		}
		if (*pos != element && iter == elements.end())
		{
			throw "element not found";
		}
		else
		{
			elements.erase(pos);
		}
	}

	void Accept(Visitor* visitor)
	{
		for (Element* i : elements)
		{
			i->Accept(visitor);
		}
	}
};

int main()
{
	ObjectStructure2* o = new ObjectStructure2();
	ConcreteElementA* A= new ConcreteElementA;
	ConcreteElementB* B= new ConcreteElementB();
	o->Attach(A);
	o->Attach(B);

	ConcreteVisitor1* v1 = new ConcreteVisitor1();
	ConcreteVisitor2* v2 = new ConcreteVisitor2();

	o->Accept(v1);
	o->Accept(v2);

	o->Detach(A);
	o->Detach(B);

	return 0;
}