#pragma once
#include "Entity.h"
#include "PlayerEntity.h"

#include "BouleEntity.h"



class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	static std::vector<std::shared_ptr<BouleEntity>> GetBoules();

public:
	static std::vector<std::shared_ptr<Entity>> m_Entities;

	static std::shared_ptr<BouleEntity> m_boule;

	static std::shared_ptr<PlayerEntity> m_player;
	
	static std::shared_ptr<PlayerEntity> GetPlayer();

	static void InitCollisions();
	static void InitJump();
	static void InitGravity();
	static void BouleEntityFactory();
	static void AddBoule(std::shared_ptr<BouleEntity> boule);
};

