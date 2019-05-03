#include <iostream>
using namespace std;

//原始代码
class GameRole1
{
private:
	int vit;//生命力
	int atk;
	int def;
public:
	//生命力
	void SetVitality(int value) { vit = value; }
	int GetVitality() { return vit; }
	//攻击力
	void SetAttack(int value) { atk = value; }
	int GetAttack() { return atk; }
	//防御力
	void SetDefense(int value) { def = value; }
	int GetDefense() { return def; }

	//状态显示
	void StateDisplay()
	{
		cout << "角色当前状态： " << endl;
		cout << "体力： " << vit << endl;
		cout << "攻击力： " << atk << endl;
		cout << "防御力: " << def << endl;
		cout << " " << endl;
	}

	//获取初始状态
	void GetInitState() { vit = 100; atk = 100; def = 100; }
	//战斗
	void Fight() { vit = 0; atk = 0; def = 0; }

};

int main1()
{
	//大战之前
	GameRole1 ken;
	ken.GetInitState();
	ken.StateDisplay();

	//保存进度
	GameRole1 backup;
	backup.SetVitality(ken.GetVitality());//暴露实现细节
	backup.SetAttack(ken.GetAttack());//暴露实现细节
	backup.SetDefense(ken.GetDefense());//暴露实现细节

	//大战boss
	ken.Fight();
	ken.StateDisplay();

	//恢复之前状态
	ken.SetVitality(backup.GetVitality());//暴露实现细节
	ken.SetAttack(backup.GetAttack());//暴露实现细节
	ken.SetDefense(backup.GetDefense());//暴露实现细节

	ken.StateDisplay();

	return 0;
}
//整个游戏角色的细节暴露给了客户端，客户端职责太大，需要知道游戏角色的生命力、攻击力、防御力这些细节，还要对它进行备份
//备忘录模式：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态。

class RoleStateMemento;
//Originator(发起人):负责创建一个备忘录Memento，用以记录当前时刻它的内部状态，并可使用备忘录恢复内部状态。Originator可根据需要决定Memento存储Originator的哪些内部状态
class GameRole
{
private:
	int vit;//生命力
	int atk;
	int def;
public:
	//生命力
	void SetVitality(int value) { vit = value; }
	int GetVitality() { return vit; }
	//攻击力
	void SetAttack(int value) { atk = value; }
	int GetAttack() { return atk; }
	//防御力
	void SetDefense(int value) { def = value; }
	int GetDefense() { return def; }

	//状态显示
	void StateDisplay()
	{
		cout << "角色当前状态： " << endl;
		cout << "体力： " << vit << endl;
		cout << "攻击力： " << atk << endl;
		cout << "防御力: " << def << endl;
		cout << " " << endl;
	}

	//获取初始状态
	void GetInitState() { vit = 100; atk = 100; def = 100; }
	//战斗
	void Fight() { vit = 0; atk = 0; def = 0; }
	//新增“保存角色状态”方法，将游戏角色的三个状态值通过实例化“角色状态存储箱”返回
	RoleStateMemento SaveState();
	//新增“恢复角色状态”方法，可将外部的“角色状态存储箱”中状态箱值恢复给游戏角色
	void RecoveryState(RoleStateMemento memento);

};

//Memento（备忘录）：负责存储Originator对象的内部状态，并可防止Originator以外的其他对象访问备忘录Memento。备忘录有两个接口，Caretaker只能看到备忘录的窄接口，它只能将备忘录传递给其他对象。
//Originator能够看到一个宽接口，允许它访问回到先前状态所需的所有数据。
//角色状态存储箱类
class RoleStateMemento
{
private:
	int vit;
	int atk;
	int def;
public:
	RoleStateMemento() {};
	RoleStateMemento(int vit, int atk, int def) { this->vit = vit; this->atk = atk; this->def = def; }
	//生命力
	void SetVitality(int value) { vit = value; }
	int GetVitality() { return vit; }
	//攻击力
	void SetAttack(int value) { atk = value; }
	int GetAttack() { return atk; }
	//防御力
	void SetDefense(int value) { def = value; }
	int GetDefense() { return def; }
};


//Caretaker(管理者)：负责保存好备忘录Memento,不能对备忘录的内容进行操作或者检查
//角色状态管理者
class RoleStateCaretaker
{
private:
	RoleStateMemento memento;
public:
	RoleStateMemento GetMemento(){ return memento; }
	void SetMemento(RoleStateMemento memento) { this->memento = memento; }
};

RoleStateMemento GameRole::SaveState()
{ 
	return RoleStateMemento(vit, atk, def); 
}

void GameRole::RecoveryState(RoleStateMemento memento)
{
	this->vit = memento.GetVitality();
	this->atk = memento.GetAttack();
	this->def = memento.GetDefense();
}

int main()
{
	//大战boss前
	GameRole ken;
	ken.GetInitState();
	ken.StateDisplay();

	//保存进度
	RoleStateCaretaker stateAdmin;
	stateAdmin.SetMemento(ken.SaveState());

	//大战boss，损耗严重
	ken.Fight();
	ken.StateDisplay();

	//恢复之前状态
	ken.RecoveryState(stateAdmin.GetMemento());
	ken.StateDisplay();

	return 0;

}