//抽象工厂模式：提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类

#include<iostream>

using namespace std;

class Department
{
private:
	int _id;
	string _deptName;
public:
	void SetID(int value) { _id = value; }
	int GetID() { return _id; }
	void SetName(string name) { _deptName = name; }
	string GetName() { return _deptName; }
};

class User
{
private:
	int _id;
	string _name;
public:
	void SetID(int value) { _id = value; }
	int GetID() { return _id; }
	void SetName(string name) { _name = name; }
	string GetName() { return _name; }
};

//IDepartment接口,用于客户端访问，解除与具体数据库访问的耦合
class IDepartment
{
public:
	virtual void Insert(Department department) = 0;

	virtual Department GetDepartment(int id)=0;
};

//SqlserverDepartment类，用于访问SQL server的Department
class SqlserverDepartment : public IDepartment
{
public:
	void Insert(Department department) override
	{
		cout << "Add a record to the Department table in SQL server" << endl;
	}
	Department GetDepartment(int id) override
	{
		cout << "Get a record from the Department table in SQL server according to the ID" << endl;
		return NULL;
	}
};

//AccessDepartment类，用于访问Access的Department
class AccessDepartment :public IDepartment
{
public:
	void Insert(Department department) override
	{
		cout << "Add a record to the Department table in SQL server" << endl;
	}
	Department GetDepartment(int id) override
	{
		cout << "Get a record from the Department table in SQL server according to the ID" << endl;
		return NULL;
	}
};

class IUser
{
public:
	virtual void Insert(User user) = 0;
	virtual User GetUser(int id)=0;
};

//SqlserverDepartment类，用于访问SQL server的Department
class SqlserverUser : public IUser
{
public:
	void Insert(User user) override
	{
		cout << "Add a record to the User table in SQL server" << endl;
	}
	User GetUser(int id) override
	{
		cout << "Get a record from the User table in SQL server according to the ID" << endl;
		return NULL;
	}
};

//AccessDepartment类，用于访问Access的Department
class AccessUser :public IUser
{
public:
	void Insert(User user) override
	{
		cout << "Add a record to the User table in Access server" << endl;
	}
	User GetUser(int id) override
	{
		cout << "Get a record from the User table in Access server according to the ID" << endl;
		return NULL;
	}
};

//IFactory接口，定义一个创建访问Department表对象的抽象工厂接口
class IFactory
{
public:
	virtual IUser* CreateUser() = 0;
	virtual IDepartment* CreateDepartment() = 0;

};

//SqlServerFactory类，实现IFactory接口，实例化SqlserverUser和SqlserverDepartment
class SqlServerFactory :public IFactory
{
public:
	IUser* CreateUser()override
	{
		return new SqlserverUser();
	}

	IDepartment* CreateDepartment()
	{
		return new SqlserverDepartment();
	}
};

class AccessFactory : public IFactory
{
public:
	IUser* CreateUser() override
	{
		return new AccessUser();
	}

	IDepartment* CreateDepartment() override
	{
		return new AccessDepartment();
	}
};

int main()
{
	User user;
	Department dept;
	IFactory* factory = new AccessFactory();
	IUser* iu = factory->CreateUser();

	iu->Insert(user);
	iu->GetUser(1);

	IDepartment* id = factory->CreateDepartment();
	id->Insert(dept);
	id->GetDepartment(1);

}


//抽象工厂模式优点：1.易于交换产品系列 2.让具体的创建实例过程与客户端分离，客户端是通过它们的抽象接口操纵实例，产品的具体类名也被具体工厂的实现分离
//缺点：增加一个新的项目，需要增加三个类，还需要更改工厂接口
//可利用反射来完善，但c++没有反射的机制，需要另行写