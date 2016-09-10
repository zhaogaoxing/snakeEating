#include "SnakeHead.h"

bool SnakeHead::init()
{
	return true;
}

SnakeHead::SnakeHead()
{
	this->direction = up;
}

SnakeHead::~SnakeHead()
{
}

void SnakeHead::setDirec(Direction di)
{
	this->direction = di;
}

Direction SnakeHead::getDirec()
{
	return this->direction;
}