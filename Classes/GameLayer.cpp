#include "GameLayer.h"
#include <iostream>
USING_NS_CC;

Scene* GameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	SetAppearance();

	return true;
}

void GameLayer::SetAppearance()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background,0);//±³¾°

	MenuItemImage* butup = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, up));
	butup->setPosition(Vec2(visibleSize.width - 100, visibleSize.height / 2 - 100));
	
	MenuItemImage* butdown = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, down));
	butdown->setPosition(Vec2(visibleSize.width - 100, visibleSize.height / 2 - 150));

	MenuItemImage* butright = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, right));
	butright->setPosition(Vec2(visibleSize.width - 50, visibleSize.height / 2 - 125));

	MenuItemImage* butleft = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, left));
	butleft->setPosition(Vec2(visibleSize.width - 150, visibleSize.height / 2 - 125));



	Menu* menu = Menu::create(butup, butdown, butright, butleft, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);


}

void GameLayer::SetDirection(Ref* pSender, Direction direc)
{
	Direction headdir = head->getDirec();
	switch (direc)
	{
	case up:
		if (headdir == left || headdir == right)
		{
			head->setDirec(up);
		}
		break;
	case down:
		if (headdir == left || headdir == right)
		{
			head->setDirec(down);
		}
		break;
	case right:
		if (headdir == up || headdir == down)
		{
			head->setDirec(right);
		}
		break;
	case left:
		if (headdir == up || headdir == down)
		{
			head->setDirec(left);
		}
		break;
	default:
		break;
	}
}