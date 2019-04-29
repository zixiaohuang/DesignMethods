//
// Created by ken on 19-4-27.
//
#include <string>
#include <list>
#include <iostream>

using namespace std;
//ǰ������
class Isubject;
//�۲���ģʽ���ֽз���-����ģʽ�����������һ��һ�Զ��������ϵ,��һ�������״̬�����ı�ʱ,�����������Ķ��󶼵õ�֪ͨ�����Զ�����

//����۲��ߣ��ڵõ������֪ͨʱ�����Լ�,����ӿڽ������½ӿ�
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

//����֪ͨ�߽ӿ�
class Isubject
{
public:
    virtual ~Isubject(){};
    virtual void Attach(Observer* observer)=0;//��ӹ۲���
    virtual void Detach(Observer* observer)=0;//�Ƴ��۲���
    virtual void Notify()=0;
    virtual void SetState(string s)=0;//����״̬
    virtual string GetState()=0;//���״̬
};

//ͬ�²�һ��ֻ�п���Ʊ������������
//�۲��ߣ�����Ʊ��ͬ��
class StockObserver : public Observer
{
public:
    StockObserver(string name,Isubject* sub):Observer(name,sub){};//�����֪ͨ��
    void Update()override
    {
        cout<<Observer::sub->GetState()<< Observer::name<<endl;
    }
};

//�۲��ߣ���NBA��ͬ��
class NBAObserver : public Observer
{
public:
    NBAObserver(string name,Isubject* sub):Observer(name,sub){};//�����֪ͨ��
    void Update()override
    {
        cout<<Observer::sub->GetState()<< Observer::name<<endl;
    }
};


//����֪ͨ�ߣ�֪ͨ�߲�һ��������,���Զ��岻ͬ����
class Secretary:public Isubject
{
private:
    list<Observer*>m_observers;//�۲�������
    string action;
public:
    //����
    void Attach(Observer* observer) override
    {
        m_observers.push_back(observer);
    }
    //����
    void Detach(Observer* observer) override
    {
        m_observers.remove(observer);
    }
    //֪ͨ
    void Notify() override
    {
        list<Observer*>::iterator iter = m_observers.begin();
        for(;iter!=m_observers.end();++iter)
        {
            (*iter)->Update();
        }
    }
    //״̬
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
    //����
    Secretary* susan = new Secretary();

    //����Ʊ��ͬ��
    StockObserver* colleague1 = new StockObserver("Tom", susan);
    //��NBA��ͬ��
    NBAObserver* colleague2 = new NBAObserver("John",susan);

    susan->Attach(colleague1);
    susan->Attach(colleague2);

    susan->SetState("Boss is coming, ");
    susan->Notify();

    susan->Detach(colleague2);
    susan->SetState("Boss is leaving, ");
    susan->Notify();



}