//职责链模式：使多个对象都有机会处理请求，从而避免请求的发送者和接受者之间的耦合关系。将这个对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。
#include<string>
#include<iostream>

using namespace std;

class Request
{
private:
	string requestType;
	string requestContent;
	int number;
public:
	void SetType(string value) { this->requestType = value; }
	string GetType() { return this->requestType; }
	void SetContent(string value) { this->requestContent = value; }
	string GetContent() { return this->requestContent; }
	void SetNumber(int value) { this->number = value; }
	int GetNumber() { return this->number; }
};

//抽象管理者
class Manager
{
protected:
	string name;
	Manager* superior;	//管理者上级
public:
	Manager(string name) { this->name = name; }
	//设置管理的上级
	void SetSuperior(Manager* superior)
	{
		this->superior = superior;
	}
	//申请请求
	virtual void RequestApplications(Request request)=0;
};

//经理
class CommonManger :public Manager
{
public:
	CommonManger(string name) :Manager(name) {};
	void RequestApplications(Request request)override
	{
		if ((request.GetType() == "Ask for leave")&&(request.GetNumber() <= 2))//经理所能有的权限下
		{
			cout << request.GetContent() <<" for "<< request.GetNumber() << " Days " << "is allowed. " << endl;
		}
		else//其余的申请需转到上级
		{
			if (superior != nullptr)
			{
				superior->RequestApplications(request);
			}
		}
	}
};

//总监
class Majordomo :public Manager
{
public:
	Majordomo(string name) :Manager(name) {};
	void RequestApplications(Request request)override
	{
		if ((request.GetType() == "Ask for leave")&&(request.GetNumber() <= 5))
		{
			cout << request.GetContent() <<" for "<< request.GetNumber() << " Days " << "is allowed. " << endl;
		}
		else
		{
			if (superior != nullptr)
			{
				superior->RequestApplications(request);
			}
		}
	}
};

//总经理
class GeneralManager :public Manager
{
public:
	GeneralManager(string name) :Manager(name) {};
	void RequestApplications(Request request)override
	{
		if (request.GetType() == "Ask for leave")
		{
			cout << request.GetContent() << " for " << request.GetNumber() << " Days " << "is allowed. " << endl;
		}
		else if((request.GetType()=="Salary increase")&&(request.GetNumber()<=500))//要求加薪在500以内
		{
			cout << request.GetContent() << " for " << request.GetNumber() << " yuan " << "is allowed. " << endl;
		}
		else if((request.GetType() == "Salary increase")&&(request.GetNumber() > 500))//超过500，考虑一下
		{
			cout << "Reconsider, reply later."<< endl;
		}
	}
};

int main()
{
	CommonManger* jinli = new CommonManger("金立") ;
	Majordomo* zongjian = new Majordomo("宗剑");
	GeneralManager* zhongjingli = new GeneralManager("钟精励");
	//设置上级，可以根据实际需求来更改设置
	jinli->SetSuperior(zongjian);
	zongjian->SetSuperior(zhongjingli);

	//客户端申请都是由"经理"发起
	Request request;
	request.SetType("Ask for leave");
	request.SetContent("Ken ask for leave");
	request.SetNumber(1);
	jinli->RequestApplications(request);

	Request request2;
	request2.SetType("Ask for leave");
	request2.SetContent("Ken ask for leave");
	request2.SetNumber(4);
	jinli->RequestApplications(request2);

	Request request3;
	request3.SetType("Salary increase");
	request3.SetContent("Ken ask for Salary increase");
	request3.SetNumber(500);
	jinli->RequestApplications(request3);

	Request request4;
	request4.SetType("Salary increase");
	request4.SetContent("Ken ask for Salary increase");
	request4.SetNumber(1000);
	jinli->RequestApplications(request4);
	
	return 0;
}