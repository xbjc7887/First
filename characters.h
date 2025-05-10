#pragma once
#include <iostream>
#include <string>
#include <easyx.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

extern IMAGE wholebk0;
extern IMAGE wholebk;
extern void drawText(std::string a, int x, int y);
extern void movline(bool c, IMAGE d);


//角色阵营
enum class Faction { ally, enemy };
//角色职业（兵种）
enum class Kind { medic, infantry, scout, sniper };

//人物类
class Character
{
private:
    int chang;  // 长
    int kuan;   // 宽
    int mx;     // 中心横坐标
    int my;     // 中心纵坐标
    int gobackX;//移动前角色横坐标
    int gobackY;//移动前角色纵坐标
    string name;//角色名字
    int life;   //角色生命值
    int energy; //角色体力
    int ATK;    //角色攻击力
    int movement; //角色移动力
    int agility;  //角色敏捷
    double atkran; //角色攻击距离
    Kind kind;    //角色职业（兵种）
    Faction faction; //角色阵营（0为我方，1为敌方）
    static std::vector<Character*> allCharacters; // 静态成员：存储所有角色
    static std::vector<Character*> allyCharacters; // 静态成员：存储所有我方角色
    static std::vector<Character*> enemyCharacters; // 静态成员：存储所有敌方角色
    IMAGE character_img;    //角色图片
public:
    bool isdeath;//角色是否死亡
    bool roundmov = false; //角色该轮是否移动完毕
    bool rounddone = false; //角色该轮是否结束行动
    IMAGE tablebk; //角色的属性面板覆盖的背景
    //构造函数
    Character(int a, int b, int c, int d, string e, int atk, int f, int g, int h, int i, double atkRan, Kind kin, Faction j);
    //死亡函数
    void death();

    //获取所有角色
    static const std::vector<Character*>& getAllCharacters() 
    {
        return allCharacters;
    }

    //获取所有角色
    static const std::vector<Character*>& getAllyCharacters()
    {
        return allyCharacters;
    }

    //获取所有角色
    static const std::vector<Character*>& getEnemyCharacters()
    {
        return enemyCharacters;
    }

    //获取鼠标悬停的角色（返回第一个匹配的）
    static Character* getHoveredCharacter(int mouseX, int mouseY) 
    {
        for (Character* c : allCharacters) 
        {
            if (c->isMouseInCharacter(mouseX, mouseY)) 
            {
                return c; 
            }
        }
        return nullptr; // 未找到
    }
    //判断我（敌）方是否该轮全部行动完毕
    static bool allrounddone(Faction f);
    int getmx();
    int getmy();
    int getgobackX();
    int getgobackY();
    int getchang();
    int getkuan();
    int getright();
    int gettop();
    Kind getkind();
    Faction getfaction();
    string getname();
    int getlife();
    int getenergy();
    int getmovement();
    int getagility();
    void setmx(int a);
    void setmy(int a);
    //新的回合设置所有我（敌）方的roundmov与rounddone为false
    static void setroundval(Faction f);
    //void setbk(IMAGE a);
    //绘制人物
    void paintCharacter();
    void characmov(int x, int y);
    bool isMouseInCharacter(int x, int y);
    //攻击函数
    bool attack(Character* a);
    //动作函数
    bool action(Character* a);

};
