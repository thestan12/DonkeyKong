#include "Entity.h"

class MovableEntity : public Entity {
	
public:
	MovableEntity() {};
	~MovableEntity() { };

	int GravitySpeed = 0;

	std::shared_ptr<Entity> ColEchelle;
	std::shared_ptr<Entity> ColBlock;

	std::string currentAnimation;
	bool gameOver = false;
	bool winGame = false;

	bool isCollisionWithEchelle();
	bool isCollisionWithBlock();

	bool isCollisionWithBlockBottom();

	bool isOutOfMapLeft();
	bool isOutOfMapRight();

	bool isCollisionWithEchelleTop();
	bool reachLadderTop();
	bool reachLadderBottom();
	bool EnabledGravity() ;

	bool CollisionWithThisEntity(std::shared_ptr<Entity> entity);

	std::string Animate();
};