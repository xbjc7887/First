#include "UI.h"

//文字绘制
void drawText(std::string a, int x, int y)
{
	settextstyle(20, 10, "微软雅黑");
	setbkcolor(WHITE);
	settextcolor(BLACK);
	outtextxy(x, y, a.c_str());
}

// 按钮类
Button::Button(int a, int b, int c, int d, std::string e)
{
	chang = a;
	kuan = b;
	left = c;
	top = d;
	text = e;
}
//鼠标是否在按钮区域
bool Button::isMouseInButton(int x, int y)
{
	if ((x > left && (x < left + chang)) && (y > top && y < (top + kuan)))
		return true;
	return false;
}
//绘制按钮
void  Button::printButton()
{
	setfillcolor(WHITE);
	solidrectangle(left, top, left + chang, top + kuan);//无边框矩形
	drawText(text, left, top);
}

//返回按钮文字
string Button::getbuttontext()
{
	return text;
}

//人物按钮类
CharacButton::CharacButton(int a, int b, int c, int d, std::string e) : Button(a, b, c, d, e)
{

}
void CharacButton::printButton() 
{
	getimage(&bk, 0, 0, getwidth(), getheight());
	setfillcolor(WHITE);
	solidrectangle(left, top, left + chang, top + kuan);
	drawText("移动", left, top);
	drawText("攻击", left , top + 20);
	drawText("动作", left , top + 40);
	drawText("待命", left , top + 60);
	drawText("退出", left , top + 80);
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLACK);
	line(left, top + 20, left + chang, top + 20);
	line(left, top + 40, left + chang, top + 40);
	line(left, top + 60, left + chang, top + 60);
	line(left, top + 80, left + chang, top + 80);
}
//鼠标在移动区域
bool CharacButton::isMouseInMov(int x, int y)
{
	if (x > left && x<left + chang && y>top && y < top + 20)
		return true;
	return false;
}
//鼠标在攻击区域
bool CharacButton::isMouseInAttack(int x, int y)
{
	if (x > left && x<left + chang && y>top + 20 && y < top + 40)
		return true;
	return false;
}
//鼠标在动作区域
bool CharacButton::isMouseInAct(int x, int y)
{
	if (x > left && x<left + chang && y>top + 40 && y < top + 60)
		return true;
	return false;
}
//鼠标在待命区域
bool CharacButton::isMouseInStandby(int x, int y)
{
	if (x > left && x<left + chang && y>top + 60 && y < top + 80)
		return true;
	return false;
}
//鼠标在退出区域
bool CharacButton::isMouseInQuit(int x, int y)
{
	if (x > left && x<left + chang && y>top + 80 && y < top + kuan)
		return true;
	return false;
}
//删除按钮
void CharacButton::deleteButton()
{
	putimage(0, 0, &bk);	
}

//行动网格线
void movline(bool c, IMAGE d)
{
	if (c == 0)
	{
		int a = 0;
		int b = 0;
		setlinestyle(PS_SOLID, 1);
		setlinecolor(BLACK);
		while (a != 22)
		{
			a++;
			line(0, 32 * a, getwidth(), 32 * a);
		}
		while (b != 39)
		{
			b++;
			line(32 * b, 0, 32 * b, getheight());
		}
	}
	else
	{
		putimage(0, 0, &d);
	}
	
	
}

////显示角色面板
//void showtable(Character a, int x, int y, IMAGE bk)
//{
//	if (a.isMouseInCharacter(x, y))
//	{
//		//绘制矩形
//		BeginBatchDraw();
//		setfillcolor(WHITE);
//		solidrectangle(a.getright()+20, a.gettop()+20, a.getright() + 80, a.gettop() + 80);//矩形
//		EndBatchDraw();
//	}
//	else if(!a.isMouseInCharacter(x, y))
//	{
//		getimage(&bk, a.getright() + 20, a.gettop() + 20, 60, 60);
//		putimage(a.getright() + 20, a.gettop() + 20, &bk);
//	}
//}

