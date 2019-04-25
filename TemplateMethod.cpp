//
// Created by ken on 19-4-24.
//
#include <iostream>
#include <string>

using namespace std;

//ģ�巽��������һ�������е��㷨�ĹǼ�,����һЩ�����ӳٵ�������.
// ģ�巽��ʹ��������Բ��ı�һ���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض�����
//ԭʼ���
class TestPaperA_origin
{
public:
    //����1
    void TestQuestion1()
    {
        printf("1+1=[]? a.2 b.3 c.1 d.5\n");
        cout<<"Answer: "<<"b"<<endl;
    }
    //����2
    void TestQuestion2()
    {
        printf("1*1=[]? a.2 b.3 c.1 d.5\n");
        cout<< "Answer: "<<"c"<<endl;
    }
    //����3
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

//��ʦ�ƶ�����
class TestPaper
{
protected:
    virtual string Answer1(){return "";}//�䶯�Ĳ��ֳ���,�Ƴٵ�������ʵ��
    virtual string Answer2(){return "";}
    virtual string Answer3(){return "";}
public:
    void TestQuestion1()//��Ŀ��һ��,�仯���Ǵ𰸲���,���ظ��Ĳ��ַŵ�����
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

//ѧ���׳�д���Ծ�
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

//ѧ���ҳ�д���Ծ�
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