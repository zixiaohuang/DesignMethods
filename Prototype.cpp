//
// Created by ken on 19-4-23.
//

#include <string>
#include <iostream>

using namespace std;

//ԭ��ģʽ
//ԭʼ�汾�ļ�����
class Resume
{
private:
    string name;
    string sex;
    string age;
    string timeArea;
    string company;
public:
    Resume()
    {
        this->name="";
        this->sex = "";
        this->age="";
        this->timeArea="";
        this->company="";
    };
    Resume(string name){this->name = name;}
    //���ø�����Ϣ
    void SetPersonalInfo(string sex, string age)
    {
        this->sex = sex;
        this->age = age;
    }

    //���ù�������
    void SetWorkExperience(string timeArea, string company)
    {
        this->timeArea = timeArea;
        this->company = company;
    }

    //��ʾ
    void Display()
    {
        cout<< name << sex << age << endl;
        cout<< "��������: " << timeArea << company << endl;
    }
};

/*
//ԭʼ�汾,ÿ����һ�ݼ�������Ҫʵ����һ�Σ���������ͬ�ļ�����Ҫʵ�������
int main()
{
    Resume a = Resume("Tom");
    a.SetPersonalInfo("Man","29");
    a.SetWorkExperience("1998-2000","A company");

    Resume b = Resume("Scott");
    b.SetPersonalInfo("Man","30");
    b.SetWorkExperience("2000-2007","B company");

    return 0;
}
 */

//ԭ��ģʽ����һ�������ٴ�������һ���ɶ��ƵĶ��󣬶��Ҳ���Ҫ֪���κδ�����ϸ��
//����һ���ӿ�
class WorkExperience
{
public:
    string workDate;
    string company;

public:
    WorkExperience(const WorkExperience &other){this->workDate=other.workDate;this->company=other.company;}
    WorkExperience(){workDate="";company="";}
    void SetValue(string value1, string value2)
    {
        this->workDate = value1;
        this->company = value2;
    }
};

class NewResume
{
private:
    string name;
    string sex;
    string age;
    WorkExperience work;
    //string timeArea;
    //string company;
public:
    NewResume()
    {
        this->name="";
        this->sex = "";
        this->age="";
        //this->timeArea="";
        //this->company="";
    };

    NewResume(string name){this->name = name;}


    //�������캯��
    NewResume(const NewResume &other){
        this->name=other.name;
        this->sex = other.sex;
        this->age = other.age;
        work = other.work;
        //this->timeArea = other.timeArea;
        //this->company = other.company;
    }

    void SetPersonalInfo(string sex, string age)
    {
        this->sex = sex;
        this->age = age;
    }

    void SetWorkExperience(string timeArea, string company)
    {
        work.SetValue(timeArea,company);
        //this->timeArea = timeArea;
        //this->company = company;
    }

    void Display()
    {
        cout<< name << " "<<sex <<" "<< age << endl;
        //cout<< "��������: " << timeArea << " "<<company << endl;
        cout<<"��������: "<< work.workDate <<" "<<work.company<<endl;
    }

    //���ÿ������캯��
    NewResume* Clone(){
        return new NewResume(*this);
    }
};

int main()
{
    NewResume* a = new NewResume("Tom");
    a->SetPersonalInfo("Man","30");
    a->SetWorkExperience("1998-2000","A company");

    NewResume* b = a->Clone();
    b->SetWorkExperience("2000-2007","B company");

    NewResume* c = a->Clone();
    c->SetPersonalInfo("Woman","25");
    c->SetWorkExperience("2010-2107","C company");

    a->Display();
    b->Display();
    c->Display();
}