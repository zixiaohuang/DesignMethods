//
// Created by ken on 19-4-26.
//
#include <string>
#include <iostream>

using namespace std;

//������ģʽ����һ�����Ӷ���Ĺ��������ı�ʾ���룬ʹ��ͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ
//����Ľ����˵��࣬����������ȶ�ס�������κ����������е�ÿһ������
class PersonBuilder1
{
protected:
    string Person_name;
public:
    virtual void PrintName()=0;
    virtual void BuildHead()=0;
    virtual void BuildBody()=0;
    virtual void BuildArmLeft()=0;
    virtual void BuildArmRight()=0;
    virtual void BuildLegLeft()=0;
    virtual void BuildLegRight()=0;

};

//�̳г����࣬������д��Щ������ķ����������������ͨ��
class PersonThinBuilder1 : public PersonBuilder1
{
public:
    explicit PersonThinBuilder1(string name)//explicit�ؼ�������������Ĺ��캯���������εĹ��캯�����࣬���ܷ�����Ӧ����ʽ����ת��
    {this->Person_name=std::move(name);}

    void PrintName()override
    {
        cout<<Person_name<<" is building"<<endl;
    }

    void BuildHead() override
    {
        cout<<"build thin head "<<endl;
    }

    void BuildBody() override
    {
        cout<<"build thin body "<<endl;
    }

    void BuildArmLeft() override
    {
        cout<<"build thin leftarm "<<endl;
    }

    void BuildArmRight() override
    {
        cout<<"build thin rightarm "<<endl;
    }

    void BuildLegLeft() override
    {
        cout<<"build thin leftleg "<<endl;
    }

    void BuildLegRight() override
    {
        cout<<"build thin rightleg"<<endl;
    }

};

class PersonFatBuilder1 : public PersonBuilder1
{
public:
    void PrintName()override
    {
        cout<<Person_name<<" is building"<<endl;
    }

    explicit PersonFatBuilder1(string name)
    {this->Person_name=std::move(name);}

    void BuildHead() override
    {
        cout<<"build fat head "<<endl;
    }

    void BuildBody() override
    {
        cout<<"build fat body "<<endl;
    }

    void BuildArmLeft() override
    {
        cout<<"build fat leftarm "<<endl;
    }

    void BuildArmRight() override
    {
        cout<<"build fat rightarm "<<endl;
    }

    void BuildLegLeft() override
    {
        cout<<"build fat leftleg "<<endl;
    }

    void BuildLegRight() override
    {
        cout<<"build fat rightleg"<<endl;
    }

};

//ָ�����������ƽ�����̣����������û��뽨����̵Ĺ���
//�������
class PersonDirector1
{
private:
    PersonBuilder1* pb;
public:
    PersonDirector1(PersonBuilder1 *pb)//����ָ���ߣ�����Ҫʲô����С��
    {
        this->pb = pb;
    }

    void CreatePerson()
    {
        pb->PrintName();
        pb->BuildHead();
        pb->BuildBody();
        pb->BuildArmLeft();
        pb->BuildArmRight();
        pb->BuildLegLeft();
        pb->BuildLegRight();
    }
};

int main1()
{
    PersonBuilder1* ptb = new PersonThinBuilder1("Tom");
    PersonDirector1* pdThin = new PersonDirector1(ptb);
    pdThin->CreatePerson();

    PersonBuilder1* pfd = new PersonFatBuilder1("Susan");
    PersonDirector1* pdFat = new PersonDirector1(pfd);
    pdFat->CreatePerson();
}

//PersonThinBuilder���PersonFatBuilder���д����ظ��Ĵ��룬�ɷ���templateģʽ��һ�����ƣ�

class Builder
{
protected:
    string Person_name;
public:
    virtual void PrintName()=0;
    virtual void BuildHead()=0;
    virtual void BuildBody()=0;
    virtual void BuildArmLeft()=0;
    virtual void BuildArmRight()=0;
    virtual void BuildLegLeft()=0;
    virtual void BuildLegRight()=0;
};

//����ģ��ģʽ�̳г����࣬���干ͬ���ֵĴ��룬��дһ���麯��BodyType��̬�̳�������仯�Ĳ���
class PersonBuilder2:public Builder
{
protected:
    virtual string BodyType()
    {
        return "";
    }
public:
    explicit PersonBuilder2(string name)//explicit�ؼ�������������Ĺ��캯���������εĹ��캯�����࣬���ܷ�����Ӧ����ʽ����ת��
    {this->Person_name=std::move(name);}

    void PrintName()override
    {
        cout<<Person_name<<" is building,please wait......"<<endl;
    }

    void BuildHead() override
    {
        cout<<"building "<<  BodyType() <<" head "<<endl;
    }

    void BuildBody() override
    {
        cout<<"building "<< BodyType() <<" body "<<endl;
    }

    void BuildArmLeft() override
    {
        cout<<"building "<< BodyType() <<" leftarm "<<endl;
    }

    void BuildArmRight() override
    {
        cout<<"building "<< BodyType() <<" rightarm "<<endl;
    }

    void BuildLegLeft() override
    {
        cout<<"building "<< BodyType() <<" leftleg "<<endl;
    }

    void BuildLegRight() override
    {
        cout<<"building "<< BodyType() <<" rightleg"<<endl;
    }

    void Finsh()
    {
        cout<<"Body Building of "<<Person_name<<" is Done"<<endl;
    }
};

class PersonThinBuilder2:public PersonBuilder2
{
public:
    PersonThinBuilder2(string name):PersonBuilder2(std::move(name)){};
protected:
    string BodyType()override
    {
        return "Thin";
    }
};

class PersonFatBuilder2:public PersonBuilder2
{
public:
    PersonFatBuilder2(string name):PersonBuilder2(std::move(name)){};
protected:
    string BodyType()override
    {
        return "Fat";
    }
};

class PersonDirector2
{
private:
    PersonBuilder2* m_pBuilder;
public:
    PersonDirector2(PersonBuilder2 *pb)
    {
        this->m_pBuilder = pb;
    };

    void CreatePerson()
    {
        m_pBuilder->PrintName();
        m_pBuilder->BuildHead();
        m_pBuilder->BuildBody();
        m_pBuilder->BuildArmLeft();
        m_pBuilder->BuildArmRight();
        m_pBuilder->BuildLegLeft();
        m_pBuilder->BuildLegRight();
        m_pBuilder->Finsh();
    }

};

int main()
{
    PersonBuilder2* ptb = new PersonThinBuilder2("Tom");
    PersonDirector2* pdThin = new PersonDirector2(ptb);
    pdThin->CreatePerson();

    PersonBuilder2* pfd = new PersonFatBuilder2("Susan");
    PersonDirector2* pdFat = new PersonDirector2(pfd);
    pdFat->CreatePerson();
}