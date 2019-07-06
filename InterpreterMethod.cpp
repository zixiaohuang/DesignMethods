//解释器模式：给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子
//正则表达式就是它的一个应用

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Context：包含解释器之外的一些全局信息
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

//抽象表达式：声明一个抽象的解释操作，这个接口为抽象语法树中所有的节点所共享
class AbstractExpression
{
public:
	virtual void Interpret(Context context)=0;
};

//终结符表达式：实现与文法中的终结符相关联的解释操作
class TerminalExpression : public AbstractExpression
{
public:
	void Interpret(Context context) override
	{
		cout << "Terminal Expression" << endl;
	}
};

//非终结符表达：为文法中的非终结符实现解释操作
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