#include "pch.h"
#include "PlayerEntity.h"


bool PlayerEntity::CanJump() {
	return this->GravitySpeed == 0 && !this->isCollisionWithEchelleTop() && this->isCollisionWithBlockBottom();
}

void PlayerEntity::Jump()
{
	if(CanJump()) this->JumpSpeed += 1;
}

bool PlayerEntity::CanMoveDown(){
	return (this->isCollisionWithEchelleTop() && !isCollisionWithBlockBottom()) || (!this->isCollisionWithEchelleTop() && isCollisionWithEchelle());
}

bool PlayerEntity::CanMoveUp()
{
	return this->isCollisionWithEchelle();
}

bool PlayerEntity::CanMoveSideway() {
	return !this->isCollisionWithEchelle() || (this->isCollisionWithBlockBottom() && (this->reachLadderBottom() || this->reachLadderTop()));
}

bool PlayerEntity::EnabledGravity(){

	bool retour = false;

	if (this->JumpSpeed > 0) {
		return false;
	}


	if (!this->isCollisionWithBlock() && !this->isCollisionWithEchelle()) {
		retour = true;
	}

	if (this->isCollisionWithBlock() && !this->isCollisionWithBlockBottom() && !this->isCollisionWithEchelle()) {
		retour = true;
	}

	return retour;
}

std::string PlayerEntity::Animate() {
	std::string retour = "Media/Textures/Mario_small_transparent_L.png";

	if (this->lastDirIsRight) {
		retour = "Media/Textures/Mario_small_transparent.png";
	}

	if (this->JumpSpeed != 0) {
		retour = "Media/Textures/Mario_jump_L.png";
		if (this->lastDirIsRight) {
			retour = "Media/Textures/Mario_jump.png";
		}
	}

	if (this->GravitySpeed != 0) {
		retour = "Media/Textures/Mario_jump_L.png";
		if (this->lastDirIsRight) {
			retour = "Media/Textures/Mario_jump.png";
		}
	}

	return retour;
}
