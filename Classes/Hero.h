#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"

using namespace cocos2d;

class Hero :public cocos2d::Layer
{
public:
	Hero();
	~Hero();

	//根据图片创建英雄
	void InitHeroSprite(char *hero_name);
	//设置动画，num为图片数目， run_direction为精灵脸朝向, false朝右， name_each为name——png中的每一小张图片的公共名称部分
	void SetAnnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num, bool run_direction);
	//停止动画
	void StopAnimation();
	//判断是否在跑动画
	bool IsRunning;
	//英雄运动方向
	bool HeroDirection;

	CREATE_FUNC(Hero);
private:
	//精灵
	Sprite *m_HeroSprite;
	//用来保存初始状态的精灵图片名称
	char *Hero_name;
};

#endif	//__HERO_H__
#pragma once
