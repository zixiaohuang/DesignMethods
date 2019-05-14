//尽管将一个系统分割成许多对象通常可以增加其可复用性，但是对象间相互连接的激增又会降低其可复用性
//大量的连接使得一个对象不可能在没有其他对象的支持下工作，系统表现为一个不可分割的整体，所以，对系统的行为进行任何较大的改动就十分困难了
//'迪米特法则'，如果两个类不必彼此直接通信，那么这两个类就不应当发生直接的相互作用。
//如果其中一个类需要调用另一类的某一个方法的话，可以通过第三者转发这个调用。

//中介者模式：用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显示地相互引用，从而使得耦合松散，而且可以独立地改变它们之间的交互
#include <string>
#include <iostream>

using namespace std;

class Colleague;
class ConcreteColleague1;
class ConcreteColleague2;


//抽象中介者类
class Mediator
{
public:
	virtual void Send(string message, Colleague* colleague)=0;
};

//抽象同事类
class Colleague
{
protected:
	Mediator* mediator;

public:
	//构造方法，得到中介者对象
	Colleague(Mediator* mediator) { this->mediator = mediator; }
	virtual void Send(string message) {};
	virtual void Notify(string message) {};
};

//具体中介类
class ConcreteMediator :public Mediator
{
private:
	Colleague* colleague1;
	Colleague* colleague2;

public:
	void SetColleague1(Colleague* value) { this->colleague1 = value; }
	void SetColleague2(Colleague* value) { this->colleague2 = value; }
	void Send(string message, Colleague* colleague) override
	{
		if (colleague == colleague1)//根据对象做出选择判断，通知对象
		{
			colleague2->Notify(message);
		}
		else
		{
			colleague1->Notify(message);
		}
	}
};

class ConcreteColleague1 :public Colleague
{
public:
	ConcreteColleague1(Mediator* mediator) :Colleague(mediator) {};
	void Send(string message) override
	{
		mediator->Send(message,this);//发送信息时通常是中介者发送出去
	}
	void Notify(string message) override
	{
		cout << "Colleague1 get the message: " << message << endl;
	}
};


class ConcreteColleague2 :public Colleague
{
public:
	ConcreteColleague2(Mediator* mediator) :Colleague(mediator) {};
	void Send(string message) override
	{
		mediator->Send(message,this);
	}
	void Notify(string message) override
	{
		cout << "Colleague2 get the message: " << message << endl;
	}
};

int main()
{
	ConcreteMediator* m = new ConcreteMediator();

	//让两个具体同事类认识中介对象
	ConcreteColleague1* c1 = new ConcreteColleague1(m);
	ConcreteColleague2* c2 = new ConcreteColleague2(m);

	//让中介者认识各个具体同事类对象
	m->SetColleague1(c1);
	m->SetColleague2(c2);

	//具体同事类对象发送信息都是通过中介者转发
	c1->Send("吃饭了吗？");
	c2->Send("没有呢，打算请客吗？");

	return 0;
}

//中介者模式很容易在系统中应用，也很容易在系统中误用。当系统出现‘多对多’交互复杂对象群时，不要急于使用中介者模式，要先反思你的系统在设计是不是合理
//中介者模式优点：Mediator的出现减少了各个Colleague的耦合，使得可以独立地改变和复用各个Colleague类和Mediator
//缺点：由于ConcreteMediator控制集中化，于是就把交互复杂性变为了中介者的复杂性，这就使得中介者会变得比任何一个ConcreteMediator都复杂
//中介者模式一般应用于一组对象以定义良好但是复杂的方式进行通信的场合
