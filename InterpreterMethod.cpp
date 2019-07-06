//������ģʽ������һ�����ԣ����������ķ���һ�ֱ�ʾ��������һ�������������������ʹ�øñ�ʾ�����������еľ���
//������ʽ��������һ��Ӧ��

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Context������������֮���һЩȫ����Ϣ
class Context
{
private:
	string input;
	string output;
public:
	string GetInput()
	{
		return input;
	}
	void SetInput(string input)
	{
		this->input = input;
	}

	string GetOutput()
	{
		return output;
	}

	void SetOutput(string output)
	{
		this->output = output;
	}
};

//������ʽ������һ������Ľ��Ͳ���������ӿ�Ϊ�����﷨�������еĽڵ�������
class AbstractExpression
{
public:
	virtual void Interpret(Context context)=0;
};

//�ս�����ʽ��ʵ�����ķ��е��ս��������Ľ��Ͳ���
class TerminalExpression : public AbstractExpression
{
public:
	void Interpret(Context context) override
	{
		cout << "Terminal Expression" << endl;
	}
};

//���ս����Ϊ�ķ��еķ��ս��ʵ�ֽ��Ͳ���
class NonterminalExpression :public AbstractExpression
{
public:
	void Interpret(Context context) override
	{
		cout << "Nonterminal Expression" << endl;
	}
};


int main()
{
	Context context;
	vector<AbstractExpression*> list;
	list.push_back(new TerminalExpression());
	list.push_back(new NonterminalExpression());
	list.push_back(new TerminalExpression());
	list.push_back(new TerminalExpression());

	vector<AbstractExpression*>::iterator iter;
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		(*iter)->Interpret(context);
	}

	return 0;
}