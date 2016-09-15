
#include "Hero.h"

USING_NS_CC;

Hero::Hero()
{
	IsRunning = false;
	HeroDirection = false;
	Hero_name = NULL;
}

Hero::~Hero()
{

}

void Hero::InitHeroSprite(char *hero_name)
{
	Hero_name = hero_name;
	this->m_HeroSprite = Sprite::create(hero_name);
	this->addChild(m_HeroSprite);
}

//动画播放，可以是跑、攻击、死亡、受伤等
void Hero::SetAnnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num, bool run_direction)
{
	if (HeroDirection != run_direction)
	{
		HeroDirection = run_direction;
		m_HeroSprite->setFlippedX(run_direction);
	}
	if (IsRunning)
		return;

	//将图片加载到精灵帧缓存池
	SpriteFrameCache *m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile(name_plist, name_png);
	//用一个列表保存所有的CCSpriteFrameCache
	Vector<SpriteFrame*> frameArray;
	unsigned int i;
	for (i = 1; i <= num; i++)
	{
		SpriteFrame *frame = m_frameCache->getSpriteFrameByName(__String::createWithFormat("%s%d.png", name_each, i)->getCString());
		frameArray.pushBack(frame);
	}

	//使用列表创建动画对象
	Animation *animation = Animation::createWithSpriteFrames(frameArray);
	if (HeroDirection != run_direction)
	{
		HeroDirection = run_direction;
	}
	//表示无限循环播放
	animation->setLoops(-1);
	//每两张图片的时间隔，图片数目越少，间隔最小就越小
	animation->setDelayPerUnit(0.1f);

	//将动画包装成一个动作
	Animate *animate = Animate::create(animation);
	m_HeroSprite->runAction(animate);
	IsRunning = true;

}

void Hero::StopAnimation()
{
	if (!IsRunning)
	{
		return;
	}
	m_HeroSprite->stopAllActions();

	//恢复精灵原来的初始化贴图
	//把原来的精灵删除掉
	this->removeChild(m_HeroSprite, true);

	//恢复精灵原来的贴图样子
	m_HeroSprite = CCSprite::create(Hero_name);//恢复精灵原来的贴图样子
	m_HeroSprite->setFlippedX(HeroDirection);
	this->addChild(m_HeroSprite);
	IsRunning = false;
}