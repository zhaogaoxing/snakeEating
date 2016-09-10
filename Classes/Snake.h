#ifndef _Snake_Snake_
#define _Snake_Snake_

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class Snake :public Node
{
private:
	Sprite* snakenode;
public:
	void setNode(Sprite* node);
	Sprite* getNode();
	virtual bool init();
	CREATE_FUNC(Snake);
};


#endif