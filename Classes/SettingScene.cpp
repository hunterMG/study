#include "SettingScene.h"

USING_NS_CC;

Scene* Setting::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Setting::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Setting::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Setting::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...
	auto *bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	addChild(bg);

	//音效
	auto soundOnMenuItem = MenuItemImage::create("on.png", "on.png");
	auto soundOffMenuItem = MenuItemImage::create("off.png", "off.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), soundOnMenuItem, soundOffMenuItem, NULL);
	auto center = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	soundToggleMenuItem->setPosition(center.x,center.y+50);
	//音乐
	auto musicOnMenuItem = MenuItemImage::create("on.png", "on.png");
	auto musicOffMenuItem = MenuItemImage::create("off.png", "off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this), musicOnMenuItem, musicOffMenuItem, NULL);
	musicToggleMenuItem->setPosition(center.x, center.y);
	//OK按钮
	auto okMenuItem = MenuItemImage::create("ok-down.png", "ok-up.png", CC_CALLBACK_1(Setting::menuOkCallback, this));
	okMenuItem->setPosition(center.x, center.y - 50);
	Menu * mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	addChild(mn);
	return true;
}

void Setting::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Setting::menuSoundToggleCallback(cocos2d::Ref * pSender)
{
}

void Setting::menuMusicToggleCallback(cocos2d::Ref * pSender)
{
}

void Setting::menuOkCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

