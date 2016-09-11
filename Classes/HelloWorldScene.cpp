#include "HelloWorldScene.h"
#include <iostream>
USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("tan1.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

	auto playbutton = MenuItemImage::create(
		"button/startred.png",
		"button/startred_on.png",
		CC_CALLBACK_0(HelloWorld::ChangeScene, this));

	playbutton->setPosition(Vec2(visibleSize.width/2,
		visibleSize.height/2-300));

	auto menu = Menu::create(playbutton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

    return true;
}

void HelloWorld::ChangeScene()
{
	Director::getInstance()->replaceScene(GameLayer::createScene());
	//Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.5f, GameLayer::GameScene()));
}
