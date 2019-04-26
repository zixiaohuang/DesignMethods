//
// Created by ken on 19-4-26.
//
#include <string>
#include <iostream>

using namespace std;

//建造者模式：将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示
//抽象的建造人的类，把这个过程稳定住，不让任何人遗忘当中的每一个步骤
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

//继承抽象类，必须重写这些抽象类的方法，否则编译器不通过
class PersonThinBuilder1 : public PersonBuilder1
{
public:
    explicit PersonThinBuilder1(string name)//explicit关键字用来修饰类的构造函数，被修饰的构造函数的类，不能发生相应的隐式类型转换
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

//指挥者用来控制建造过程，用来隔离用户与建造过程的关联
//建造过程
class PersonDirector1
{
private:
    PersonBuilder1* pb;
public:
    PersonDirector1(PersonBuilder1 *pb)//告诉指挥者，我需要什么样的小人
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

//PersonThinBuilder类和PersonFatBuilder类有大量重复的代码，可否用template模式进一步改善？

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

//利用模板模式继承抽象类，定义共同部分的代码，并写一个虚函数BodyType动态继承来满足变化的部分
class PersonBuilder2:public Builder
{
protected:
    virtual string BodyType()
    {
        return "";
    }
public:
    explicit PersonBuilder2(string name)//explicit关键字用来修饰类的构造函数，被修饰的构造函数的类，不能发生相应的隐式类型转换
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