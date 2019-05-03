#include <cstdio>
#include <iostream>

using namespace std;

//原始代码
class Work1
{
private:
	int hour;
	bool finish = false;

public:
	void SetHour(int value)
	{
		hour = value;
	}
	int GetHour()
	{
		return hour;
	}
	void SetState(bool value)
	{
		finish = value;
	}
	bool GetState()
	{
		return finish;
	}
	void WriteProgram()
	{
		if (hour < 12)
		{
			printf("当前时间： %d点 上午工作，精神百倍\n", hour);
		}
		else if (hour < 13)
		{
			printf("当前时间： %d点 饿了，午饭；犯困，午休\n", hour);
		}
		else if (hour < 17)
		{
			printf("当前时间： %d点 下午状态还不错，继续努力\n", hour);
		}
		else
		{
			if (finish) { printf("当前时间: %d点 下班回家了\n", hour); }
			else {
				if (hour < 21)
				{
					printf("当前时间： %d点 加班哦，疲惫至极\n", hour);
				}
				else
				{
					printf("当前时间： %d点 不行了，睡着了\n", hour);
				}
			}
		}
	}
};

//方法过长其实极有可能是有坏味道。很多的判断分支
//很多的判断分支，意味着它的责任过大
//面向对象设计其实就是希望做到代码责任分解
int main1()
{
	Work1 emergencyProjects;
	emergencyProjects.SetHour(9);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(10);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(12);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(13);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(14);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(17);

	emergencyProjects.SetState(false);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(19);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(22);
	emergencyProjects.WriteProgram();

	return 0;
};


//状态模式：当一个对象的内在状态改变时允许改变其行为，这个对象看起来像是改变了其类。把状态的判断逻辑转移到表示不同状态的一系列类当中
class Work;

class State
{
public:
	virtual void WriteProgram(Work* w) {};
};

//上午工作状态
class ForenoonState :public State
{
public:
	void WriteProgram(Work* w)override;
};

//中午工作状态
class NoonState : public State
{
public:
	void WriteProgram(Work* w)override;
};

//下午工作状态
class AfternoonState :public State
{
public:
	void WriteProgram(Work* w)override;
};

//晚上工作状态
class EveningState :public State
{
public:
	void WriteProgram(Work* w)override;
};

//睡眠状态
class SleepingState :public State
{
public:
	void WriteProgram(Work* w)override;
};

class RestState :public State
{
public:
	void WriteProgram(Work* w)override;
};

class Work
{
private:
	State* current;
	int hour;
	bool finish = false;

public:
	Work() { current = new ForenoonState(); }
	int GetHour() { return hour; }
	void SetHour(int value) { hour = value; }
	bool TaskFinish_Get() { return finish; }
	void TaskFinish_Set(bool value) { finish = value; }
	void SetState(State* s) { current = s; }
	void WriteProgram() { current->WriteProgram(this); }
};

void ForenoonState::WriteProgram(Work* w)
{
	{
		if (w->GetHour() < 12) { cout << "当前时间: " << w->GetHour() << "点 上午工作，精神百倍" << endl; }
		else { w->SetState(new NoonState()); w->WriteProgram(); }
	}
};

void NoonState::WriteProgram(Work* w)
{
	if (w->GetHour() < 13) { cout << "当前时间: " << w->GetHour() << "点 饿了，午饭；犯困，午休" << endl; }
	else { w->SetState(new AfternoonState()); w->WriteProgram(); }
}

void AfternoonState::WriteProgram(Work* w)
{
	if (w->GetHour() < 17) { cout << "当前时间: " << w->GetHour() << "点 下午状态还不错，继续努力" << endl; }
	else { w->SetState(new EveningState()); w->WriteProgram(); }
};

void EveningState::WriteProgram(Work* w)
{
	if (w->TaskFinish_Get())
	{
		w->SetState(new RestState());
		w->WriteProgram();
	}
	else
	{
		if (w->GetHour() < 21) { cout << "当前时间: " << w->GetHour() << "点 加班哦，疲惫至极" << endl; }
		else { w->SetState(new SleepingState()); w->WriteProgram(); }
	}
}

void SleepingState::WriteProgram(Work* w)
{
	cout << "当前时间: " << w->GetHour() << "点 不行了，睡着了" << endl;
}

void RestState::WriteProgram(Work* w)
{
	cout << "当前时间: " << w->GetHour() << "点 下班回家了" << endl;
}

int main()
{
	Work emergencyProjects;
	emergencyProjects.SetHour(9);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(10);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(12);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(13);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(14);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(17);

	emergencyProjects.TaskFinish_Set(false);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(19);
	emergencyProjects.WriteProgram();
	emergencyProjects.SetHour(22);
	emergencyProjects.WriteProgram();

	return 0;
}