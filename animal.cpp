# include <cstdio>
# include <string>
# include <vector>
# include <iostream>

using namespace std;

class Animal
{
protected:
	string name = "";
	int shoutNum = 3;
	virtual string getShoutSound()
	{
		return "";
	}

public:
	Animal(string name)
	{
		this->name = name;
	}
	Animal()
	{
		this->name = "无名";
	}
	int GetShoutNum()
	{
		return shoutNum;
	}
	int SetShoutNum(int value)
	{
		shoutNum = value;
	}
	string Shout()
	{
		string result = "";
		for (int i = 0; i < shoutNum; i++)
			result += getShoutSound() + ", ";

		return "我的名字叫" + name + " " + result;
	}
	virtual ~Animal() {};
};

//定义接口，包含纯虚函数的抽象类
class InChange
{
protected://只需要继承的子类使用，所以用protected修饰符
	virtual string ChangeThing(string thing) = 0;
};

class Cat :public Animal
{
public:
	Cat() { };//不申明编译不通过
	Cat(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "喵";
	}
};

class Dog :public Animal
{
public:
	Dog() {};
	Dog(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "汪";
	}
};

class Cattle :public Animal
{
public:
	Cattle() {};
	Cattle(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "哞";
	}
};

class Sheep :public Animal
{
public:
	Sheep() {};
	Sheep(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "咩";
	}
};

class MachineCat : public Cat, InChange
{
public:
	MachineCat() {};
	MachineCat(string name) :Cat(name) {};
	string ChangeThing(string thing)override
	{
		return Cat::Shout() + "我有万能的口袋，我可以变出： " + thing;
	}

};

void main()
{
	vector<Animal*> arrayAnimal;
	Animal* cat1 = new MachineCat("叮当");
	Animal* cat2 = new Cat();
	Animal* dog1 = new Dog("阿毛");
	Animal* cat3 = new Cat("咪咪");
	arrayAnimal.push_back(cat1);
	arrayAnimal.push_back(dog1);
	arrayAnimal.push_back(cat2);
	arrayAnimal.push_back(cat3);

	for (int i = 0; i < (arrayAnimal.size()); ++i)
	{
		cout << (arrayAnimal[i]->Shout()) << endl;
	}


}