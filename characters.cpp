#include "characters.h"
#include <locale>

// 初始化静态成员
std::vector<Character*> Character::allCharacters;
std::vector<Character*> Character::allyCharacters;
std::vector<Character*> Character::enemyCharacters;

//人物类构造函数
Character::Character(int a, int b, int c, int d, string e, int f, int g, int atk, int h, int i, double atkRan, Kind kin, Faction j)
{
	isdeath = false; 
	chang = a;
	kuan = b;
	mx = (c / 32) * 32 + 16;
	my = (d / 32) * 32 + 16;
	gobackX = mx;
	gobackY = my;
	name = e;  //角色名字
	life = f;   //角色生命值
	energy = g; //角色体力
	ATK = atk;  //角色攻击力
	movement = h; //角色移动力
	agility = i;  //角色敏捷
	atkran = atkRan;//角色攻击范围
	kind = kin;  //角色职业
	faction = j;  //角色阵营
	allCharacters.push_back(this); // 将该角色添加到全局数组
	if (j == Faction::ally)
	{
		allyCharacters.push_back(this);
	}
	else
	{
		enemyCharacters.push_back(this);
	}
}

//死亡函数
void Character::death()
{
	//还原角色所在背景
	IMAGE a = wholebk0;
	BeginBatchDraw();
	putimage(0, 0, &wholebk0);
	getimage(&a, mx - chang / 2, my - kuan / 2, chang, kuan);
	putimage(0, 0, &wholebk);
	putimage(mx - chang / 2, my - kuan / 2, &a);
	getimage(&wholebk, 0, 0, getwidth(), getheight());
	EndBatchDraw();

	//从全体数组中移除自身
	auto it = std::find(allCharacters.begin(), allCharacters.end(), this);
	if (it != allCharacters.end()) 
	{
		allCharacters.erase(it);
	}
	//从我方数组中移除自身（如果是我方）
	it = std::find(allyCharacters.begin(), allyCharacters.end(), this);
	if (it != allyCharacters.end())
	{
		allyCharacters.erase(it);
	}
	//从敌方数组中移除自身（如果是敌方）
	it = std::find(enemyCharacters.begin(), enemyCharacters.end(), this);
	if (it != enemyCharacters.end())
	{
		enemyCharacters.erase(it);
	}
	isdeath = true;
}

//给出mx
 int Character::getmx()
{
	 return mx;
}
	
//给出my	
 int Character::getmy()
 {
	 return my;
 }

 //给出gobackX
 int Character::getgobackX()
 {
	 return gobackX;
 }

 //给出gobackY
 int Character::getgobackY()
 {
	 return gobackY;
 }

//给出chang
int Character:: getchang()
{
		return chang;
}
//给出kuan
int Character::getkuan()
	{
		return kuan;
	}

//给出右边界
int Character::getright()
{
	return mx + chang / 2;
}
//给出上边界
int Character::gettop()
{
	return my - kuan / 2;
}

Kind Character::getkind()
{
	return kind;
}

Faction Character::getfaction()
{
	return faction;
}
string Character::getname()
{
	return name;
}
int Character::getlife()
{
	return life;
}
int Character::getenergy()
{
	return energy;
}
int Character::getmovement()
{
	return movement;
}
int Character::getagility()
{
	return agility;
}

//设置mx
void Character::setmx(int a)
{
	mx = a;
}
//设置my
void Character::setmy(int a)
{
	my = a;
}
//新的回合设置所有我（敌）方的roundmov与rounddone为false，角色体力加1
void Character::setroundval(Faction f) 
{
	//筛选器
	std::vector<Character*> filteredCharacters; 

	if (f == Faction::ally) 
	{
		std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
			[](Character* c) { return c->faction == Faction::ally; });
		for (Character* c : filteredCharacters) 
		{
			c->roundmov = false;
			c->rounddone = false;
			if (c->energy < 10)
			c->energy++; 
		}
	}
	else if (f == Faction::enemy) 
	{
		std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
			[](Character* c) { return c->faction == Faction::enemy; });
		for (Character* c : filteredCharacters) {
			c->roundmov = false;
			c->rounddone = false;
			if (c->energy < 10)
			c->energy++;
		}
	}
}

//绘制人物
void Character::paintCharacter()
{
	mx = (mx / 32) * 32 + 16;
	my = (my / 32) * 32 + 16;
	setfillcolor(YELLOW);
	solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //无填充矩形
	getimage(&wholebk, 0, 0, getwidth(), getheight());
}

//人物移动
void Character::characmov(int x, int y)
{
	x = (x / 32) * 32 + 16;
	y = (y / 32) * 32 + 16;
	gobackX = mx;
	gobackY = my;
	IMAGE bk = wholebk;
	IMAGE partimage = wholebk0;
	////////////////////////
	//人物移动前把背景设置为不含人物的背景
	putimage(0, 0, &wholebk0);
	getimage(&partimage, mx - chang / 2, my - kuan / 2, chang + 1, kuan + 1);
	putimage(0, 0, &wholebk);
	putimage(mx - chang / 2, my - kuan / 2, &partimage);
	//setfillcolor(LIGHTBLUE);
	//solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //无填充矩形
	getimage(&bk, 0, 0, getwidth(), getheight());   //当前bk为不含人物的背景
	////////////////////////
	if (mx == x && my == y)
	{
		BeginBatchDraw();
		//保持除移动人物外的一切不变
		putimage(0, 0, &bk);
		setfillcolor(YELLOW);
		solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //无填充矩形
		EndBatchDraw();
	}
	while (mx != x || my != y)
	{
		if (mx != x && my != y)
		{
			if (x > mx && y > my)
			{
				mx += 1;
				my += 1;
			}
			else if (x < mx && y > my)
			{
				mx -= 1;
				my += 1;
			}
			else if (x > mx && y < my)
			{
				mx += 1;
				my -= 1;
			}
			else if (x < mx && y < my)
			{
				mx -= 1;
				my -= 1;
			}
		}
		else if (mx != x && my == y)
		{
			if (x < mx)
			{
				mx -= 1;
			}
			else if (x > mx)
			{
				mx += 1;
			}
}
		else if (mx == x && my != y)
		{
			if (y < my)
			{
				my -= 1;
			}
			else if (y > my)
			{
				my += 1;
			}
		}
		BeginBatchDraw();
		//保持除移动人物外的一切不变
		putimage(0, 0, &bk);
		setfillcolor(YELLOW);
		solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //无填充矩形
		EndBatchDraw();
	}
	if (energy > 0)
	energy--;//体力减1
	getimage(&bk, 0, 0, getwidth(), getheight());
	wholebk = bk;
}
	//选中人物
	bool Character::isMouseInCharacter(int x, int y)
	{
		if ((x > mx - chang / 2 + 5 && x < mx + chang / 2 - 5) && (y > my - kuan / 2 + 5 && y < my + kuan / 2 - 5))
			return true;
		return false;
	}

	bool Character::allrounddone(Faction f)
	{
		std::vector<Character*> filteredCharacters;

		if (f == Faction::ally)
		{
			// 使用 std::copy_if 筛选出满足条件的对象
			std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
				[](Character* c) { return c->faction == Faction::ally; });
			//如果该轮还有没行动的角色返回false
			for (Character* c : filteredCharacters)
			{
				if (!(c->rounddone))
				{
					return false;
				}
			}
			return true; //全部我方角色已行动完毕
		}
		else if (f == Faction::enemy)
		{
			// 使用 std::copy_if 筛选出满足条件的对象
			std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
				[](Character* c) { return c->faction == Faction::enemy; });
			//如果该轮还有没行动的角色返回false
			for (Character* c : filteredCharacters)
			{
				if (!(c->rounddone))
				{
					return false;
				}
			}
			return true; //全部我方角色已行动完毕
		}

	}


	//攻击函数
    bool Character::attack(Character* a)
	{
		//srand(time(0)); // 设置随机数种子
		IMAGE temp;

		int TargetX = a->mx;
		int TargetY = a->my;
		// 计算横向和纵向的网格差
		int deltaX = (TargetX - mx) / 32;
		int deltaY = (TargetY - my) / 32;
		// 计算欧几里得距离（网格单位）
		double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
		int atk = ATK + rand() % 5 - 2;//攻击力浮动
		double missrate = double(a->getagility() - 1);//定义闪避几率 
		srand(time(0)); // 设置随机数种子

			if (energy == 0)//如果体力不足无法攻击
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//绘制提醒按钮
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //矩形
				drawText("角色体力不足", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;//角色此轮动作未结束
			}
			else//体力充足可以攻击
			{
				if (a->faction == this->faction && this != a)//不可以攻击友军
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 735, 350); //矩形
					drawText("不可以攻击友军", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
				else if (this == a)//不可以攻击自己
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 735, 350); //矩形
					drawText("不可以攻击自己", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
				else
				{
					if (gridDistance <= 1.5)//双方紧贴，进行肉搏
					{
						movline(1, wholebk);
						if (a->energy == 0)
						{
							a->death();
							rounddone = true;
							return true;
						}
						a->life = a->life - energy - agility + rand() % 11 - 5;
						this->life = this->life - a->energy - a->agility + rand() % 11 - 5;
						a->energy = 0;
						energy = 0;
						if (a->life <= 0)
						{
							a->death();
						}
						if (this->life <= 0)
						{
							this->death();
						}
						rounddone = true;
						return true;
					}
					else if (gridDistance <= atkran && gridDistance > 1.5)//双方有一定距离，进行远程攻击
					{
						if (rand() >= missrate && rand() % 100 <= missrate)//远程攻击但是发生闪避
						{
							movline(1, wholebk);
							if (this->faction == Faction::ally)
							{
								getimage(&temp, 0, 0, getwidth(), getheight());
								//绘制提醒按钮
								setfillcolor(WHITE);
								solidrectangle(560, 288, 715, 350); //矩形
								drawText("哎呀！没打中！", 580, 308);
								Sleep(700);
								putimage(0, 0, &temp);
							}							
							rounddone = true;
							energy--;
							return true;
						}
						else//没有闪避，正常远程攻击
						{
							movline(1, wholebk);
							if (atk >= a->life)
							{
								a->death();
								//delete a;
								rounddone = true;
								energy--;
								return true;
							}
							a->life -= atk;
							rounddone = true;
							energy--;
							return true;
						}
					}
					else//超出攻击范围
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //矩形
						drawText("超出攻击范围", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}
				}
			}
	}
	bool Character::action(Character* a)
	{
		IMAGE temp;

		int TargetX = a->mx;
		int TargetY = a->my;
		// 计算横向和纵向的网格差
		int deltaX = (TargetX - mx) / 32;
		int deltaY = (TargetY - my) / 32;
		// 计算欧几里得距离（网格单位）
		double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

		//4个角色对应4个动作
		if (kind == Kind::medic)//医疗兵
		{
			if (gridDistance <= 1.5)//必须紧贴才能生效
			{
				if (a->faction == this->faction && a != this)
				{
					movline(1, wholebk);
					a->life += 10;
					rounddone = true;
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 715, 350); //矩形
					drawText("成功治疗友军！", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return true;
				}
				else if (a->faction == this->faction && a == this)
				{
					movline(1, wholebk);
					a->life += 10;
					rounddone = true;
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 715, 350); //矩形
					drawText("成功治疗自己！", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return true;
				}
				else
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 790, 350); //矩形
					drawText("不能以敌军作为目标！", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
				
			}
			else//超出距离则提示
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//绘制提醒按钮
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //矩形
				drawText("目标超出距离！", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;
			}

		}
		else if (kind == Kind::infantry)//步兵
		{

		}
		else if (kind == Kind::scout)//侦察兵
		{

		}
		else if (kind == Kind::sniper)//狙击手
		{

		}
	}

