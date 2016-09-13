#include "HRocker.h"
const double PI = 3.1415;

HRocker::HRocker(void)
{
	rockerRun = false;
}

HRocker::~HRocker(void)
{

}

HRocker* HRocker::createHRocker(const char *rockerImageName, const char *rockerBGImageName, Vec2 position)
{
	HRocker *layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	//CC_SAFE_DELETE(layer);
	return NULL;
}

void HRocker::rockerInit(const char *rockerImageName, const char *rockerBGImageName, Vec2 position)
{
	auto spRokerBG = Sprite::create(rockerBGImageName);
	spRokerBG->setPosition(position);
	spRokerBG->setVisible(false);
	addChild(spRokerBG, 0, tag_rockerBG);

	auto spRoker = Sprite::create(rockerImageName);
	spRoker->setPosition(position);
	spRoker->setVisible(false);
	addChild(spRoker, 1, tag_rocker);

	rockerBGPosition = position;
	rockerBGR = spRokerBG->getContentSize().width * 0.5;
	rockerDirection = -1;
}

void HRocker::startRoker(bool _isStopOther)
{
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void HRocker::stopRocker()
{
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	_eventDispatcher->removeEventListenersForTarget(this);
}

float HRocker::getRad(Vec2 pos1, Vec2 pos2)
{
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;

	//得到两点x的距离
	float x = px2 - px1;
	//得到两点y的距离
	float y = py2 - py1;
	//算出斜边长度
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	//算出这个角的余弦值（通过三角函数中的定理：角度余弦值 = 邻边 / 斜边）
	float cosAngle = x / xie;
	//通过反余弦定理获取到角度的弧度
	float rad = acos(cosAngle);
	//注意：当触屏的位置Y坐标<摇杆的Y坐标，我们要取反值-0 ~ -180
	if (py2 < py1)
	{
		rad = -rad;
	}
	return rad;
}

Vec2 getAnglePosition(float r, float angle)
{
	return Vec2(r*cos(angle), r*sin(angle));
}

bool HRocker::onTouchBegan(Touch *touch, Event *unused_event)
{
	Vec2 point = touch->getLocation();
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	if (rocker->getBoundingBox().containsPoint(point))
	{
		isCanMove = true;
		CCLOG("begin");
	}
	return true;
}

void HRocker::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (!isCanMove)
	{
		return;
	}

	Vec2 point = touch->getLocation();
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	//得到摇杆与触屏点所形成的角度
	float angle = getRad(rockerBGPosition, point);
	//判断两个圆的圆心距是否大于摇杆背景的半径
	if (sqrt(pow(rockerBGPosition.x - point.x, 2) + pow(rockerBGPosition.y - point.y, 2)) >= rockerBGR)
	{
		rocker->setPosition(ccpAdd(getAnglePosition(rockerBGR, angle), rockerBGPosition));
	}
	else
	{
		//当没有超过，让摇杆跟随用户触屏点移动即可
		rocker->setPosition(point);
	}

	//判断方向
	if (angle >= -PI / 4 && angle < PI / 4)
	{
		rockerDirection = rocker_right;
		rockerRun = false;
	}
	else if (angle >= PI / 4 && angle < 3 * PI / 4)
	{
		rockerDirection = rocker_up;
	}
	else if ((angle >= 3 * PI / 4 && angle <= PI) || angle >= -PI && angle < -3 * PI / 4)
	{
		rockerDirection = rocker_left;
		rockerRun = true;
	}
	else if (angle >= -3 * PI / 4 && angle < -PI / 4)
	{
		rockerDirection = rocker_down;
	}
}

void HRocker::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (!isCanMove)
	{
		return;
	}

	auto rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->stopAllActions();
	rocker->runAction(CCMoveTo::create(0.08f, rockerBGPosition));
	isCanMove = false;
	rockerDirection = rocker_stay;
}