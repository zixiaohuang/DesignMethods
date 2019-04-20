#include <string>
#include <iostream>

using namespace std;

class SchoolGirl
{
private:
	string name;
public:
	void SetName(string value)
	{
		name = value;
	}
	string GetName()
	{
		return name;
	}
};

//接口，实现送礼物的动作
class IGiveGift
{
	virtual void GiveDolls() = 0;
	virtual void GiveFlowers() = 0;
	virtual void GiveChocolate() = 0;
};

class Pursuit:public IGiveGift
{
private:
	SchoolGirl mm;
public:
	Pursuit() { this->mm.SetName("None"); }
	Pursuit(SchoolGirl mm)
	{
		this->mm = mm;
	}

	void GiveDolls() override
	{
		cout << mm.GetName() << ",Here is a doll for you" << endl;
	}

	void GiveFlowers() override
	{
		cout << mm.GetName() << ",Here is a flower for you" << endl;
	}

	void GiveChocolate() override
	{
		cout << mm.GetName() << ",Here is a chocolate for you" << endl;
	}
};

class Proxy : public IGiveGift
{
private:
	Pursuit gg;
public:
	Proxy(SchoolGirl mm)
	{
		gg = Pursuit(mm);
	}

	void GiveDolls() override
	{
		gg.GiveDolls();
	}

	void GiveFlowers() override
	{
		gg.GiveFlowers();
	}

	void GiveChocolate() override
	{
		gg.GiveChocolate();
	}
};

int main(int argc, char* argv[])
{
	SchoolGirl mm = SchoolGirl();
	mm.SetName("Taylor Swift");

	Proxy me = Proxy(mm);

	me.GiveDolls();
	me.GiveFlowers();
	me.GiveChocolate();

	return 0;
}