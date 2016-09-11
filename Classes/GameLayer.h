#ifndef _Game_Layer_
#define _Game_Layer_

#include"cocos2d.h"
#include"SnakeHead.h"

USING_NS_CC;

class GameLayer : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	SnakeHead* head;
	Vector<Snake*>body;


	void SetAppearance();
	void SetDirection(Ref* pSender, Direction direc);
	void PauseGame();
	/*void StartGame();*/

	void SetSnake();

	void MoveStep();
	void MoveBody();
	virtual void update(float dt);


	Sprite* food;
	Vec2 lastbodyposi;

	void SetFood();
	Vec2 RandomPosition();
	bool ifCollideBody(Vec2 pos);
	bool ifGetFood();
	void AddBody();

	MenuItemImage* replaybutton;
	Layer* gameover;

	bool ifgameover;

	bool OutofRange();
	/*bool HeadCollideBody(Direction headdirec);*/
	void GameOver();
	/*void SetSnakeVisible(bool value);*/

	// implement the "static create()" method manually
	CREATE_FUNC(GameLayer);
};


#endif