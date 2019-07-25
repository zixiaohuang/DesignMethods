#include <iostream>
#include <string>
#include <list>
#include <time.h>

using namespace std;

//全局变量需要定义在类外
static int MuttonNumber;
static int ChickenNumber;

string  Get_Current_Date()
{
	struct tm t;
	time_t nowtime;
	nowtime = time(NULL); //获取日历时间   
	char tmp[64];
	localtime_s(&t, &nowtime);//t指向要填充的时间结构的指针,nowtime指针，指向存储的时间.如果成功，返回值则为零。 如果失败，返回值将是错误代码。
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", &t);
	return tmp;
}

//烤肉串者
class Barbecuer
{
public:
	void BakeMutton()
	{
		cout << "Bake the mutton" << endl;
	}

	void BakeChickenWing()
	{
		cout << "Bake the ChickenWing" << endl;
	}

	void SetMuttonValue(int value)
	{
		MuttonNumber = value;
	}

	void SetChickenValue(int value)
	{
		ChickenNumber = value;
	}

};

//抽象命令类
class Command
{
protected:
	Barbecuer* receiver;

public:
	Command(Barbecuer* receiver) { this->receiver = receiver; }
	virtual void ExcuteCommand() = 0;
	virtual string ReturnName() = 0;
	virtual int GetValue() = 0;
	virtual void Order() = 0;
};

//具体命令类
//烤羊肉串命令
class BakeMuttonCommand :public Command
{
public:
	BakeMuttonCommand(Barbecuer* receiver):Command(receiver){}
	void ExcuteCommand() override { receiver->BakeMutton(); };
	string ReturnName() override { return "The BakeMutton "; }
	int GetValue()override { return MuttonNumber; }
	void Order() override{ --MuttonNumber; }
};

//烤羊肉串命令
class BakeChickenWingCommand :public Command
{
public:
	BakeChickenWingCommand(Barbecuer* receiver) :Command(receiver) {}
	void ExcuteCommand() override{ receiver->BakeChickenWing(); };
	string ReturnName() override { return "The BakeChickenWing "; }
	int GetValue()override { return ChickenNumber; }
	void Order() override { --ChickenNumber; }
};

//服务员
class Waiter
{
private:
	list<Command*> orders;
public:
	//设置订单
	void SetOrder(Command* command)
	{
		if (command->GetValue() != 0)
		{
			orders.push_back(command);
			command->Order();
			cout << "Order " << command->ReturnName() << "Time: " << Get_Current_Date().c_str() << endl;
		}
		else
		{
			cout << command->ReturnName() << "has already sold out" << endl;
		}
	}
	//取消订单
	void CancelOrder(Command* command)
	{
		list<Command*>::iterator iter;
		iter = find(orders.begin(), orders.end(), command);//find分为stl中的find和各容器自己的find，list没有自己的find调用stl中的find
		if (iter != orders.end())
		{
			orders.remove(*iter);
		}
		/*
		for (iter = orders.begin(); iter != orders.end(); ++iter)
		{
			if ((*iter) == command)
			{
				orders.remove(*iter);
			}
		}
		*/
	}
	//通知执行
	void Notify()
	{
		list<Command*>::iterator iter;
		for (iter = orders.begin(); iter != orders.end(); ++iter)
		{
			(*iter)->ExcuteCommand();
		}
	}
};

int main()
{
	//开店前准备,设置各材料基数
	Barbecuer* man = new Barbecuer();
	man->SetMuttonValue(1);
	man->SetChickenValue(1);
	//客人下单
	Command* bakeMuttonCommand1 = new BakeMuttonCommand(man);
	Command* bakeMuttonCommand2 = new BakeMuttonCommand(man);
	Command* bakeChickenWingCommand1 = new BakeChickenWingCommand(man);
	


	Waiter* woman = new Waiter();

	//开门营业
	woman->SetOrder(bakeMuttonCommand1);
	woman->SetOrder(bakeMuttonCommand2);
	woman->SetOrder(bakeChickenWingCommand1);


	//点菜完毕通知厨房
	woman->Notify();

	woman->CancelOrder(bakeMuttonCommand1);
	woman->Notify();

	return 0;
}