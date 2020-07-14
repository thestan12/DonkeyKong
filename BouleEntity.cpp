#include "pch.h"
#include "BouleEntity.h"

std::shared_ptr<BouleEntity> m_fille = nullptr;

BouleEntity::BouleEntity()
{

}

bool BouleEntity::collisionWithOtherEntity(std::shared_ptr<Entity> entity)
{
	bool retour = this->CollisionWithThisEntity(entity);

	if (m_fille != nullptr) {
		retour = retour && m_fille->collisionWithOtherEntity(entity);
	}

	return retour;
}

bool BouleEntity::EnabledGravity()
{
	bool retour = false;

	if ((!this->isCollisionWithBlock() && !this->isCollisionWithEchelle())) {
		retour = true;
	}

	if (isCollisionWithBlockBottom()) {
		retour = false;
	}


	if (this->isCollisionWithEchelle()) {
		retour = true;
	}

	this->GravitySpeed = 0;

	if (retour) {
		this->GravitySpeed = 75;
	}

	return retour;
}

bool BouleEntity::GoRight()
{
	return this->GravitySpeed == 0 && step <= 1 || step == 5;
}

bool BouleEntity::GoLeft()
{
	return this->GravitySpeed == 0  && !GoRight();
}

std::string BouleEntity::Animate()
{
	return "";
}


