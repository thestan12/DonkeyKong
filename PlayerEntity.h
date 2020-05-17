#pragma once
#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H
#include "MovableEntity.h"
#endif


class PlayerEntity : public MovableEntity
{

public:
	
	int JumpSpeed = 0;
	bool lastDirIsRight = true;

	bool CanMoveDown();
	bool CanMoveUp();

	bool EnabledGravity();
	std::string Animate();

	bool CanJump();

	void Jump();

private:

};
