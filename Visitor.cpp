//������ģʽĿ�ģ��Ѵ�������ݽṹ���������
//���ϵͳ�бȽ��ȶ������ݽṹ���������ڱ仯���㷨�Ļ���ʹ�÷�����ģʽ�ȽϺ���

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
	string name = "����";
	void Accept(Action* visitor) override
	{
		visitor->GetManConclusion(this);
	}
};

class Woman :public Person
{
public:
	string name = "Ů��";
	void Accept(Action* visitor) override
	{
		visitor->GetWomanConclusion(this);
	}
};

class Success :public Action
{
protected:
	string action = "�ɹ�";
public:
	void GetManConclusion(Man* concreteElementA) override
	{
		cout<< concreteElementA->name << action << "ʱ����������һ��ΰ���Ů�ˡ�" << endl;
	}
	void GetWomanConclusion(Woman* concreteElementB) override
	{
		cout << concreteElementB->name << action << "ʱ����������һ�����ɹ������ˡ�" << endl;
	}
};

class Failing :public Action
{
protected:
	string action = "ʧ��";
public:
	void GetManConclusion(Man* concreteElementA) override
	{
		cout << concreteElementA->name << action << "ʱ����ͷ�Ⱦƣ�˭Ҳ����Ȱ��" << endl;
	}
	void GetWomanConclusion(Woman* concreteElementB) override
	{
		cout << concreteElementB->name << action << "ʱ����������˭ҲȰ���ˡ�" << endl;
	}
};

class Amativeness :public Action
{
protected:
	string action = "����";
public:
	void GetManConclusion(Man* concreteElementA) override
	{
		cout << concreteElementA->name << action <<  "ʱ,���²���ҲҪװ����"  << endl;
	}
	void GetWomanConclusion(Woman* concreteElementB) override
	{
		cout << concreteElementB->name << action << "ʱ,���¶�Ҳװ��������"  << endl;
	}
};


//����ṹ
class ObjectStructure
{
private:
	list<Person*> elements;
	list<Person*>::iterator iter;
public:
	//����
	void Add(Person* element)
	{
		elements.push_back(element);
	}
	//�Ƴ�
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

	//�ɹ�ʱ�ķ�Ӧ
	Success* v1 = new Success();
	o->Display(v1);

	//ʧ��ʱ�ķ�Ӧ
	Failing* v2 = new Failing();
	o->Display(v2);

	//����ʱ�ķ�Ӧ
	Amativeness* v3 = new Amativeness();
	o->Display(v3);

	return 0;
}





class Visitor;
//Element�࣬����һ��Accept����������һ��������Ϊ����
class Element
{
public:
	virtual ~Element() {};
	virtual void Accept(Visitor* visitor) = 0;
};

//ConcreteElementA��ConcreteElementB�࣬����Ԫ�أ�ʵ��Accept����
class ConcreteElementA :public Element
{
public:
	string name = "ConcreteElementA";
	void Accept(Visitor* visitor)override;//������
	void OperationA() { }
};

class ConcreteElementB :public Element
{
public:
	string name = "ConcreteElementB";
	void Accept(Visitor* visitor)override;//������
	void OperationB() { }
};

//Visitor�࣬Ϊ�ö���ṹ��ConcreteElement��ÿһ��������һ��Visit����
class Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA* concreteElementA)=0;
	virtual void VisitConcreteElementB(ConcreteElementB* concreteElementB)=0;
};

void ConcreteElementA:: Accept(Visitor* visitor)//����λ��Visitor��󣬷���ᱨ��ʹ��δ��������͡�
{
	visitor->VisitConcreteElementA(this);
};


void ConcreteElementB:: Accept(Visitor* visitor)//����λ��Visitor��󣬷���ᱨ��ʹ��δ��������͡�
{
	visitor->VisitConcreteElementB(this);
}

//���������
class ConcreteVisitor1 :public Visitor
{
public:
	string name = "ConcreteVisitor1";
	void VisitConcreteElementA(ConcreteElementA* concreteElementA) override
	{
		cout << concreteElementA->name << "��" << this->name << "����" << endl;
	}

	void VisitConcreteElementB(ConcreteElementB* concreteElementB) override
	{
		cout << concreteElementB->name << "��" << this->name << "����" << endl;
	}
};

class ConcreteVisitor2 :public Visitor
{
public:
	string name = "ConcreteVisitor2";
	void VisitConcreteElementA(ConcreteElementA* concreteElementA) override
	{
		cout << concreteElementA->name << "��" << this->name << "����" << endl;
	}

	void VisitConcreteElementB(ConcreteElementB* concreteElementB) override
	{
		cout << concreteElementB->name << "��" << this->name << "����" << endl;
	}
};



//ObjectStructure�࣬��ö������Ԫ�أ������ṩһ���߲�Ľӿ�����������߷�������Ԫ��
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