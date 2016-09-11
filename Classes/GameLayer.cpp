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

	bool bRect = false;
	do{
		ifgameover = false;
		SetAppearance();
		SetSnake();
		SetFood();
		this->schedule(schedule_selector(GameLayer::update), 0.6);
		bRect = true;
	} while (0);
	

	return bRect;
}

void GameLayer::SetAppearance()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("tan2.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background,0);//±³¾°

	MenuItemImage* butup = MenuItemImage::create("button/redbutton.png", "button/bluebutton.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, up));
	butup->setPosition(Vec2(visibleSize.width - 100, visibleSize.height / 2 - 270));
	
	MenuItemImage* butdown = MenuItemImage::create("button/bluebutton.png", "button/redbutton.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, down));
	butdown->setPosition(Vec2(visibleSize.width - 100, visibleSize.height / 2 - 320));

	MenuItemImage* butright = MenuItemImage::create("button/greenbutton.png", "button/yellowbutton.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, right));
	butright->setPosition(Vec2(visibleSize.width - 50, visibleSize.height / 2 - 295));

	MenuItemImage* butleft = MenuItemImage::create("button/yellowbutton.png", "button/greenbutton.png",
		CC_CALLBACK_1(GameLayer::SetDirection, this, left));
	butleft->setPosition(Vec2(visibleSize.width - 150, visibleSize.height / 2 - 295));

	/*MenuItemImage* pausebutton = MenuItemImage::create("button/yellowbutton.png", "button/greenbutton.png",
		CC_CALLBACK_0(GameLayer::PauseGame, this));
	pausebutton->setPosition(Vec2(visibleSize.width - pausebutton->getContentSize().width-50, visibleSize.height - pausebutton->getContentSize().height - 50));
*/
	/*auto replaybutton = MenuItemImage::create("button/redbutton.png", "button/bluebutton.png",
		CC_CALLBACK_0(GameLayer::StartGame, this));
	replaybutton->setPosition(Vec2(visibleSize.width - replaybutton->getContentSize().width - 50, visibleSize.height - replaybutton->getContentSize().height - 200));
	replaybutton->setVisible(false);
*/


	Menu* menu = Menu::create(butup, butdown, butright, butleft, /*pausebutton, replaybutton,*/ NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	
	Label* gameover = Label::createWithSystemFont("Game Over !!!", "Arial", 100);
	gameover->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	gameover->setColor(Color3B::BLUE);
	gameover->setVisible(false);
	this->addChild(gameover, 2);


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

void GameLayer::SetSnake()
{
	body.clear();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	head = SnakeHead::create();
	head->setNode(Sprite::create("ball/allballblacksmall.png"));
	head->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 100));
	this->addChild(head, 1);

	for (int i = 1; i < 4; i++)
	{
		Snake* bodynode = Snake::create();
		bodynode->setNode(Sprite::create("ball/allballyellowsmall.png"));
		bodynode->setPosition(Vec2(head->getPosition().x + i*bodynode->getNode()->getContentSize().width,
			head->getPosition().y + i*bodynode->getNode()->getContentSize().height));
		body.pushBack(bodynode);
		this->addChild(bodynode);
	}
}

void GameLayer::MoveBody()
{
	int n = body.size();
	Vec2 HeadPosition = head->getPosition();
	Vec2 a, temp;

	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			a = body.at(i)->getPosition();
			body.at(i)->setPosition(HeadPosition);
		}
		else
		{
			temp = a;
			a = body.at(i)->getPosition();
			body.at(i)->setPosition(temp);
		}
	}
}

void GameLayer::MoveStep()
{
	Direction temp = head->getDirec();
	Vec2 po = head->Node::getPosition();
	switch (temp)
	{
	case up:
		po.y += 10;
		break;
	case down:
		po.y -= 10;
		break;
	case left:
		po.x -= 10;
		break;
	case right:
		po.x += 10;
		break;
	default:
		break;
	}
	MoveBody();
	head->setPosition(po);
}

void GameLayer::update(float dt)
{
	if (/*!HeadCollideBody(head->getDirec()) &&*/ !OutofRange())
	{
		MoveStep();
		if (ifGetFood())
		{
			AddBody();
			SetFood();
		}
		lastbodyposi = body.at(body.size() - 1)->getPosition();
	}
	else
	{
		GameOver();
	}
}

void GameLayer::SetFood()
{
	this->removeChild(food);
	Vec2 foodposi = RandomPosition();
	Vec2 headposi = head->getPosition();
	while (foodposi == headposi || ifCollideBody(foodposi))
	{
		foodposi = RandomPosition();
	} 
	food = Sprite::create("CloseNormal.png");
	food->setPosition(foodposi);
	this->addChild(food);
}

Vec2 GameLayer::RandomPosition()
{
	int x = (random() % 10);
	int y = (random() % 20);
	Vec2 position = Vec2(x * 20 + 10, y * 20 + 10);
	return position;
}

bool GameLayer::ifCollideBody(Vec2 pos)
{
	bool value = false;
	Snake* node;
	for (int i = 0; i < body.size(); i++)
	{
		node = body.at(i);
		Vec2 nodepos = node->getPosition();
		if (nodepos == pos)
		{
			value = true;
		}
	}
	return value;
}

bool GameLayer::ifGetFood()
{
	bool value = false;
	if (food->getPosition() == head->getPosition())
	{
		value = true;
	}
	return value;
}

void GameLayer::AddBody()
{
	head->setPosition(food->getPosition());
	Snake* node = Snake::create();
	node->setNode(Sprite::create("ball/allballblacksmall.png"));
	node->setPosition(lastbodyposi);
	body.pushBack(node);
	this->addChild(node);
}

bool GameLayer::OutofRange()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 po = head->getPosition();
	if (po.x < 0 || po.x>visibleSize.width || po.y<0 || po.y > visibleSize.height)
	{
		return true;
	}
	return false;
}

//bool GameLayer::HeadCollideBody(Direction headdirec)
//{
//	float x = head->getPosition().x;
//	float y = head->getPosition().y;
//	bool  iscollide = false;
//	switch (headdirec)
//	{
//	case up:
//		y += 10;
//		break;
//	case down:
//		y -= 10;
//		break;
//	case right:
//		x += 10;
//		break;
//	case left:
//		x -= 10;
//		break;
//	default:
//		break;
//	}
//	Vec2 headnextpos = Vec2(x, y);
//	iscollide = ifCollideBody(headnextpos);
//	return iscollide;
//}

void GameLayer::GameOver()
{
	PauseGame();
	/*SetSnakeVisible(false);*/
	/*replaybutton->setVisible(true);*/
	gameover->setVisible(true);
	ifgameover = true;
}

void GameLayer::PauseGame()
{
	this->pause();
	/*SetSnakeVisible(false);
	replaybutton->setVisible(true);*/
}

//void GameLayer::SetSnakeVisible(bool value)
//{
//	food->setVisible(value);
//	head->getNode()->setVisible(value);
//	for (int i = 0; i < body.size(); i++)
//	{
//		body.at(i)->setVisible(value);
//	}
//}

//void GameLayer::StartGame()
//{
//	if (!ifgameover)
//	{
//		SetSnakeVisible(true);
//		this->resume();
//		replaybutton->setVisible(false);
//	}
//	else
//	{
//		this->unscheduleAllSelectors();
//		this->removeAllChildren();
//		body.clear();
//		this->init();
//	}
//}


