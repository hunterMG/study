#ifndef __MYACTION_SCENE_H__
#define __MYACTION_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HRocker.h"
#include "Hero.h"

class MyAction : public cocos2d::Layer
{
	Layer *gameView;//将_player和_tileMap添加到这一个节点中，方便滚动地图时同时改变位置，同时摇杆位置不动
	HRocker *rocker;
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _end;
	cocos2d::Sprite *_player;
	Hero *hero;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//判断是否到达终点
	bool isEnded(Vec2 pos);
	virtual void update(float delta);
	/*virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);*/

	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);

	void menuCloseCallback(Ref * pSender);

	// a selector callback
	

	// implement the "static create()" method manually
	CREATE_FUNC(MyAction);
};

#endif // __HELLOWORLD_SCENE_H__

