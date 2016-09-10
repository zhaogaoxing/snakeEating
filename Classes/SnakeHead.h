#ifndef __Snake__SnakeHead__
#define __Snake__SnakeHead__

#include <iostream>

#include "cocos2d.h"
#include "Snake.h"

USING_NS_CC;

enum Direction{
	up = 0,
	down = 1,
	left = 2,
	right = 3,
};

class SnakeHead :public Snake
{
private:
	Direction direction;
public:
	virtual bool init();
	SnakeHead();
	~SnakeHead();
	void setDirec(Direction di);
	Direction getDirec();
	CREATE_FUNC(SnakeHead);
};



#endif