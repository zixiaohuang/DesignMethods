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
		this->name = "����";
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

		return "�ҵ����ֽ�" + name + " " + result;
	}
	virtual ~Animal() {};
};

//����ӿڣ��������麯���ĳ�����
class InChange
{
protected://ֻ��Ҫ�̳е�����ʹ�ã�������protected���η�
	virtual string ChangeThing(string thing) = 0;
};

class Cat :public Animal
{
public:
	Cat() { };//���������벻ͨ��
	Cat(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "��";
	}
};

class Dog :public Animal
{
public:
	Dog() {};
	Dog(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "��";
	}
};

class Cattle :public Animal
{
public:
	Cattle() {};
	Cattle(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "��";
	}
};

class Sheep :public Animal
{
public:
	Sheep() {};
	Sheep(string name) :Animal(name) { };
	string getShoutSound() override
	{
		return "��";
	}
};

class MachineCat : public Cat, InChange
{
public:
	MachineCat() {};
	MachineCat(string name) :Cat(name) {};
	string ChangeThing(string thing)override
	{
		return Cat::Shout() + "�������ܵĿڴ����ҿ��Ա���� " + thing;
	}

};

void main()
{
	vector<Animal*> arrayAnimal;
	Animal* cat1 = new MachineCat("����");
	Animal* cat2 = new Cat();
	Animal* dog1 = new Dog("��ë");
	Animal* cat3 = new Cat("����");
	arrayAnimal.push_back(cat1);
	arrayAnimal.push_back(dog1);
	arrayAnimal.push_back(cat2);
	arrayAnimal.push_back(cat3);

	for (int i = 0; i < (arrayAnimal.size()); ++i)
	{
		cout << (arrayAnimal[i]->Shout()) << endl;
	}


}