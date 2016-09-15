#include "MyActionScene.h"
#include "HelloWorldScene.h"
#include "Hero.h"
USING_NS_CC;

Scene* MyAction::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MyAction::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MyAction::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("visibleSize(%f, %f)", visibleSize.width, visibleSize.height);
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MyAction::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 4);
	menu->setTag(123);
	/////////////////////////////
	// 3. add your codes below...

	gameView = Layer::create();
	//瓦片地图
	_tileMap = TMXTiledMap::create("map/maze01.tmx");
	gameView->addChild(_tileMap, 0, 100);
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("ninja");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	/*_player = Sprite::create("ninja.png");
	_player->setPosition(Vec2(x, y));
	gameView->addChild(_player, 2, 200);
	this->addChild(gameView, 0);*/
	
	hero = Hero::create();
	hero->InitHeroSprite("run1.png");
	hero->setPosition(ccp(x, y));
	gameView->addChild(hero, 1);

	this->addChild(gameView, 0);
	this->scheduleUpdate();

	_end = _tileMap->getLayer("end");
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

	//摇杆  
	rocker = HRocker::createHRocker("rocker.png", "rockerbg.png", Vec2(60, 60));
	this->addChild(rocker,2);
	rocker->startRoker(true);
	
	setTouchEnabled(true);
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}
void MyAction::update(float delta)
{
	Point pos = hero->getPosition();
	int dis = 3;
	switch (rocker->rockerDirection)
	{
	case 1:
		pos.x += dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 2, false);
		break;
	case 2:
		pos.y += dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 2, false);
		break;
	case 3:
		pos.x -= dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 2, false);
		break;
	case 4:
		pos.y -= dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 2, false);
		break;
	default:
		hero->StopAnimation();
		break;
	}
	this->setPlayerPosition(pos);
}
bool MyAction::isEnded(Vec2 position)
{
	int dis = 20;
	Point pos1 = Vec2(position.x - dis, position.y - dis);
	Point pos2 = Vec2(position.x - dis, position.y + dis);
	Point pos3 = Vec2(position.x + dis, position.y - dis);
	Point pos4 = Vec2(position.x + dis, position.y + dis);

	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord1 = this->tileCoordFromPosition(pos1);
	Vec2 tileCoord2 = this->tileCoordFromPosition(pos2);
	Vec2 tileCoord3 = this->tileCoordFromPosition(pos3);
	Vec2 tileCoord4 = this->tileCoordFromPosition(pos4);

	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//获得瓦片的GID

	int tileGid1 = _end->getTileGIDAt(tileCoord1);
	int tileGid2 = _end->getTileGIDAt(tileCoord2);
	int tileGid3 = _end->getTileGIDAt(tileCoord3);
	int tileGid4 = _end->getTileGIDAt(tileCoord4);

	if (tileGid1 > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid1);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["end"].asString();

		if (collision == "true") { //碰撞检测成功
			log("Success!!!");

			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return true;
		}
	}
	if (tileGid2 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid2);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["end"].asString();

		if (collision == "true") { //碰撞检测成功
			log("Success!!!");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return true;
		}
	}
	if (tileGid3 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid3);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["end"].asString();

		if (collision == "true") { //碰撞检测成功
			log("Success!!!");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return true;
		}
	}
	if (tileGid4 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid4);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["end"].asString();

		if (collision == "true") { //碰撞检测成功
			log("Success!!!");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return true;
		}
	}
	return false;
}
void MyAction::setPlayerPosition(Vec2 position)
{
	//log("playerPos(%f, %f)", position.x, position.y);
	if (isEnded(position)) 
	{
		log("end");
		Director::getInstance()->popScene();
		return;
	}
	int dis = 20;
	Point pos1 = Vec2(position.x - dis, position.y - dis);
	Point pos2 = Vec2(position.x - dis, position.y + dis);
	Point pos3 = Vec2(position.x + dis, position.y - dis);
	Point pos4 = Vec2(position.x + dis, position.y + dis);

	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord1 = this->tileCoordFromPosition(pos1);
	Vec2 tileCoord2 = this->tileCoordFromPosition(pos2);
	Vec2 tileCoord3 = this->tileCoordFromPosition(pos3);
	Vec2 tileCoord4 = this->tileCoordFromPosition(pos4);

	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//获得瓦片的GID

	int tileGid1 = _collidable->getTileGIDAt(tileCoord1);
	int tileGid2 = _collidable->getTileGIDAt(tileCoord2);
	int tileGid3 = _collidable->getTileGIDAt(tileCoord3);
	int tileGid4 = _collidable->getTileGIDAt(tileCoord4);

	if (tileGid1 > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid1);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //碰撞检测成功
			log("collision!!!");
			
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}
	if (tileGid2 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid2);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //碰撞检测成功
			log("collision!!!");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}
	if (tileGid3 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid3);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //碰撞检测成功
			log("collision!!!");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}
	if (tileGid4 > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid4);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { //碰撞检测成功
			log("collision!!!");
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}

	//移动精灵
	//_player->setPosition(position);
	hero->setPosition(position);
	//滚动地图
	this->setViewpointCenter(hero->getPosition());
}

Vec2 MyAction::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

void MyAction::setViewpointCenter(Vec2 position)
{
	//log("setViewpointCenter");
	//log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//可以防止，视图左边超出屏幕之外。
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//可以防止，视图右边超出屏幕之外。
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);
	//log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	//log("offset (%f ,%f) ", offset.x, offset.y);
	gameView->setPosition(offset);

}

void MyAction::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
/*
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif
*/

}

