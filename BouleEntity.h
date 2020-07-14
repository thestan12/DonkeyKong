#pragma once

#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H
#include "MovableEntity.h"
#endif


class BouleEntity : public MovableEntity{
public:
	BouleEntity();
public:
	bool goRight = false;
	int step = 0;
	int speedEntity = 75;

	std::shared_ptr<BouleEntity> m_fille;

	bool collisionWithOtherEntity(std::shared_ptr<Entity> entity);
	bool EnabledGravity();
	bool GoRight();
	bool GoLeft();

	std::string Animate();
};