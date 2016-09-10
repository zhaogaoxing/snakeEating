#ifndef _Game_Layer_
#define _Game_Layer_
#include"cocos2d.h"
USING_NS_CC;

class GameLayer : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(GameLayer);
};


#endif