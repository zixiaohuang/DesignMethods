#include <string>
#include <iostream>
using namespace std;

/*
class Person
{
private:
	string name;
public:
	Person(string name)
	{
		this->name = name;
	}
	void Show()
	{
		//cout<<"garbed"<<name<<endl;//不能用printf,printf是c用来输出单一字符的，用来输出string会产生乱码
		printf("garbed %s",name.c_str());
	}
};

//抽象类
class Finery
{
public:
	virtual void Show() = 0;
};

class TShirts : public Finery
{
public:
	void Show()override
	{
		printf("T-Shirt ");
	}
};

class BigTrouser : public Finery
{
public:
	void Show()override
	{
		printf("Trouser ");
	}
};

class WearSneakers : public Finery
{
public:
	void Show()override
	{
		printf("Sneakers ");
	}
};

class WearSuit : public Finery
{
public:
	void Show()override
	{
		printf("Suit ");
	}
};

class WearTie : public Finery
{
public:
	void Show()override
	{
		printf("Tie ");
	}
};

class WearLeatherShoes : public Finery
{
public:
	void Show()override
	{
		printf("Shoes ");
	}
};


void main(int argc, char* argv[])
{
	Person xc = Person("Tom");
	printf("\n First Look: ");
	Finery* dtx;
	dtx = new TShirts;
	dtx->Show();
	dtx = new BigTrouser;
	dtx->Show();
	dtx = new WearSneakers;
	dtx->Show();
	xc.Show();

	printf("\n Second Look: ");
	Finery* xz;
	xz = new WearSuit;
	xz->Show();
	xz = new WearTie;
	xz->Show();
	xz = new WearLeatherShoes;
	xz->Show();
	xc.Show();
}
*/

class Person
{
private:
	string name;
public:
	Person(){ }
	virtual ~Person() {};
	Person(string name) { this->name = name; }
	virtual string Show()
	{
		return "garbed " + name;
	}
};

//Decorator
class Finery : public Person
{
protected:
	Person* component;

public:
	void Decorate(Person* component)
	{
		this->component = component;
	}

	string Show() override
	{
		if (component != nullptr)
		{
			return component->Show();
		}
		return "";
	}
};

//Concrete Decorator
class TShirts : public Finery
{
public:
	TShirts(Person* p)
	{
		component = p;
	}
	string Show() override
	{
		return "T-Shirt " + component->Show();

	}
};

//Concrete Decorator
class BigTrouser : public Finery
{
public:
	BigTrouser(Person* p)
	{
		component = p;
	}
	string Show() override
	{
		return "Trouser " + component->Show();

	}
};

void main()
{
	Person* xc = new Person("Tom");

	printf("First Look: ");

	xc = new BigTrouser(xc);
	xc = new TShirts(xc);
	cout << xc->Show() << endl;


}