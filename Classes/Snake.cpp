#include "Snake.h"

Sprite* Snake::getNode()
{
	return this->snakenode;
}

void Snake::setNode(Sprite* node)
{
	this->snakenode = node;
	this->addChild(snakenode);
}

bool Snake::init()
{
	return true;
}