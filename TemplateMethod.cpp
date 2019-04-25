//
// Created by ken on 19-4-24.
//
#include <iostream>
#include <string>

using namespace std;

//模板方法：定义一个操作中的算法的骨架,而将一些步骤延迟到子类中.
// 模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤
//原始设计
class TestPaperA_origin
{
public:
    //试题1
    void TestQuestion1()
    {
        printf("1+1=[]? a.2 b.3 c.1 d.5\n");
        cout<<"Answer: "<<"b"<<endl;
    }
    //试题2
    void TestQuestion2()
    {
        printf("1*1=[]? a.2 b.3 c.1 d.5\n");
        cout<< "Answer: "<<"c"<<endl;
    }
    //试题3
    void TestQuestion3()
    {
        printf("1/1=[]? a.2 b.3 c.1 d.5\n");
        cout<<"Answer: "<<"d"<<endl;
    }
};

class TestPaperB_origin
{
public:
    void TestQuestion1()
    {
        printf("1+1=[]? a.2 b.3 c.1 d.5\n");
        cout<<"Answer: "<<"c"<<endl;
    }

    void TestQuestion2()
    {
        printf("1*1=[]? a.2 b.3 c.1 d.5\n");
        cout<< "Answer: "<<"a"<<endl;
    }

    void TestQuestion3()
    {
        printf("1/1=[]? a.2 b.3 c.1 d.5\n");
        cout<<"Answer: "<<"d"<<endl;
    }
};

//老师制定试题
class TestPaper
{
protected:
    virtual string Answer1(){return "";}//变动的部分抽象,推迟到子类中实现
    virtual string Answer2(){return "";}
    virtual string Answer3(){return "";}
public:
    void TestQuestion1()//题目都一样,变化的是答案部分,把重复的部分放到父类
    {
        printf("1+1=[]? a.2 b.3 c.1 d.5\n");
        cout<<"Answer: "<<Answer1()<<endl;
    }

    void TestQuestion2()
    {
        printf("1*1=[]? a.2 b.3 c.1 d.5\n");
        cout<< "Answer: "<<Answer2()<<endl;
    }

    void TestQuestion3()
    {
        printf("1/1=[]? a.2 b.3 c.1 d.5\n");
        cout<<"Answer: "<<Answer3()<<endl;
    }
};

//学生甲抄写的试卷
class TestPaperA : public TestPaper
{
protected:
    string Answer1() override
    {
        return "b";
    }

    string Answer2() override
    {
        return "c";
    }

    string Answer3() override
    {
        return "d";
    }
};

//学生乙抄写的试卷
class TestPaperB : public TestPaper
{
protected:
    string Answer1() override
    {
        return "c";
    }

    string Answer2() override
    {
        return "a";
    }

    string Answer3() override
    {
        return "d";
    }
};

int main()
{
    printf("The paper of Student A ");
    TestPaper* studentA = new TestPaperA();
    studentA->TestQuestion1();
    studentA->TestQuestion2();
    studentA->TestQuestion3();

    printf("The paper of Student B ");
    TestPaper* studentB = new TestPaperB();
    studentB->TestQuestion1();
    studentB->TestQuestion2();
    studentB->TestQuestion3();
}