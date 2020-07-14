#include "pch.h"
#include "MovableEntity.h"

bool MovableEntity::CollisionWithThisEntity(std::shared_ptr<Entity> entity)
{
	bool isCollision = false;
	if (this->m_sprite.getGlobalBounds().intersects(entity->m_sprite.getGlobalBounds())) {

		isCollision = true;

		switch (entity->m_type)
		{
		case EntityType::echelle:
			this->ColEchelle = entity;
			break;
		case EntityType::block:
			this->ColBlock = entity;
			break;
		case EntityType::boule:
			if (this->m_type != EntityType::boule) {
				this->gameOver = true;
			}
			break;
		case EntityType::princesse:
			if (this->m_type != EntityType::boule) {
				this->winGame = true;
				std::cout << "salut";
			}
			break;
		default:
			break;
		}
	}
	return isCollision;
}

bool MovableEntity::isCollisionWithEchelle()
{
	return this->ColEchelle != nullptr;
}

bool MovableEntity::isCollisionWithBlock()
{
	return this->ColBlock != nullptr;
}

bool MovableEntity::isCollisionWithBlockBottom()
{
	if (isCollisionWithBlock()) {
		if (this->m_sprite.getPosition().y < this->ColBlock->m_sprite.getPosition().y) {
			return true;
		}
	}
	return false;
}

bool MovableEntity::reachLadderTop() {
	if (isCollisionWithEchelle()) {
		if (this->m_sprite.getGlobalBounds().top - this->m_sprite.getGlobalBounds().height <= this->ColEchelle->m_sprite.getGlobalBounds().top - this->ColEchelle->m_sprite.getGlobalBounds().height - 25) {
			return true;
		}
		return false;
	}
}

bool MovableEntity::reachLadderBottom() {
	if (isCollisionWithEchelle()) {
		std::cout << "\n";
		std::cout << "entity top : ";
		std::cout << this->m_sprite.getGlobalBounds().top + this->m_sprite.getGlobalBounds().height;
		std::cout << "\n";
		std::cout << "ladder top : ";
		std::cout << this->ColEchelle->m_sprite.getGlobalBounds().top + this->ColEchelle->m_sprite.getGlobalBounds().height;
		if (this->m_sprite.getGlobalBounds().top + this->m_sprite.getGlobalBounds().height >= this->ColEchelle->m_sprite.getGlobalBounds().top + this->ColEchelle->m_sprite.getGlobalBounds().height) {
			return true;
		}
		return false;
	}
}

bool MovableEntity::isCollisionWithEchelleTop()
{
	if (isCollisionWithEchelle()) {
		if (this->m_sprite.getPosition().y > this->ColEchelle->m_sprite.getPosition().y) {
			return true;
		}
	}
	return false;
}

bool MovableEntity::EnabledGravity()
{
	bool retour = false;

	if (!this->isCollisionWithBlock() && !this->isCollisionWithEchelle()) {
		retour = true;
	}

	if (this->isCollisionWithBlock() && !this->isCollisionWithBlockBottom()) {
		retour = true;
	}

	return retour;
}

std::string MovableEntity::Animate() {
	return "";
}