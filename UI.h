#pragma once
#include <easyx.h>
#include <string>
#include "characters.h"
using namespace std;

//角色指令框的阶段
enum class GameState { Idle, ShowCommand, DoneMov, WaitingForMovTarget, WaitingForAtkTarget, WaitingForActTarget};

//文字绘制
void drawText(std::string a, int x, int y);

// 按钮类
class Button
{
protected:
	int chang, kuan;
	int left, top;
	std::string text;
public:
	Button(int a, int b, int c, int d, std::string e);
	//鼠标是否在按钮区域
	bool isMouseInButton(int x, int y);
	//绘制按钮
	virtual void  printButton();
	//返回按钮文字
	string getbuttontext();
};

//人物按钮类
class CharacButton : public Button
{
public:
	IMAGE bk;
	CharacButton(int a, int b, int c, int d, std::string e);
	void printButton() override;
	bool isMouseInMov(int x, int y);
	bool isMouseInAttack(int x, int y);
	bool isMouseInAct(int x, int y);
	bool isMouseInStandby(int x, int y);
	bool isMouseInQuit(int x, int y);
	//删除按钮
	void deleteButton();
};

//移动网格线，bool c决定是绘制还是消除
void movline(bool c, IMAGE d);

//显示角色面板
//void showtable(Character a, int x, int y, IMAGE bk);

