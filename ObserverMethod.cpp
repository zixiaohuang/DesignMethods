//
// Created by ken on 19-4-27.
//
#include <string>
#include <list>
#include <iostream>

using namespace std;
//前置声明
class Isubject;
//观察者模式：又叫发布-订阅模式，定义对象间的一种一对多的依赖关系,当一个对象的状态发生改变时,所有依赖它的对象都得到通知并被自动更新

//抽象观察者：在得到主题的通知时更新自己,这个接口叫做更新接口
class Observer
{
protected:
    string name;
    Isubject* sub;
public:
    virtual ~Observer(){};
    Observer(){};
    Observer(string name, Isubject* sub)
    {
        this->name=name;
        this->sub=sub;
    }
    virtual void Update(){};
};

//抽象通知者接口
class Isubject
{
public:
    virtual ~Isubject(){};
    virtual void Attach(Observer* observer)=0;//添加观察者
    virtual void Detach(Observer* observer)=0;//移除观察者
    virtual void Notify()=0;
    virtual void SetState(string s)=0;//设置状态
    virtual string GetState()=0;//获得状态
};

//同事不一定只有看股票，还有其他类
//观察者：看股票的同事
class StockObserver : public Observer
{
public:
    StockObserver(string name,Isubject* sub):Observer(name,sub){};//抽象的通知者
    void Update()override
    {
        cout<<Observer::sub->GetState()<< Observer::name<<endl;
    }
};

//观察者：看NBA的同事
class NBAObserver : public Observer
{
public:
    NBAObserver(string name,Isubject* sub):Observer(name,sub){};//抽象的通知者
    void Update()override
    {
        cout<<Observer::sub->GetState()<< Observer::name<<endl;
    }
};


//具体通知者：通知者不一定是秘书,可以定义不同的类
class Secretary:public Isubject
{
private:
    list<Observer*>m_observers;//观察者链表
    string action;
public:
    //增加
    void Attach(Observer* observer) override
    {
        m_observers.push_back(observer);
    }
    //减少
    void Detach(Observer* observer) override
    {
        m_observers.remove(observer);
    }
    //通知
    void Notify() override
    {
        list<Observer*>::iterator iter = m_observers.begin();
        for(;iter!=m_observers.end();++iter)
        {
            (*iter)->Update();
        }
    }
    //状态
    void SetState(string s) override
    {
        this->action=s;
    }

    string GetState() override
    {
        return this->action;
    }

};

int main()
{
    //秘书
    Secretary* susan = new Secretary();

    //看股票的同事
    StockObserver* colleague1 = new StockObserver("Tom", susan);
    //看NBA的同事
    NBAObserver* colleague2 = new NBAObserver("John",susan);

    susan->Attach(colleague1);
    susan->Attach(colleague2);

    susan->SetState("Boss is coming, ");
    susan->Notify();

    susan->Detach(colleague2);
    susan->SetState("Boss is leaving, ");
    susan->Notify();



}