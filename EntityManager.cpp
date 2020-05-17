#include "pch.h"
#include "EntityManager.h"
#include "BouleEntity.h"

std::vector<std::shared_ptr<Entity>> EntityManager::m_Entities;

std::shared_ptr<PlayerEntity> EntityManager::m_player;

std::shared_ptr<BouleEntity> EntityManager::m_boule = nullptr;

EntityManager::EntityManager()
{


}


EntityManager::~EntityManager()
{
}

std::vector<std::shared_ptr<BouleEntity>> EntityManager::GetBoules()
{
	std::vector<std::shared_ptr<BouleEntity>> entity;

	std::vector<std::shared_ptr<Entity>> retour;
	std::shared_ptr <BouleEntity> currentBoule = EntityManager::m_boule;

	while (currentBoule != nullptr)
	{
		entity.push_back(currentBoule);

		currentBoule = currentBoule->m_fille;

	}

	return entity;
}


std::shared_ptr<PlayerEntity> EntityManager::GetPlayer()
{
	return m_player;
}



void EntityManager::InitCollisions()
{
	m_player->ColEchelle = nullptr;
	m_player->ColBlock = nullptr;

	if (m_boule != nullptr) {
		for (std::shared_ptr<BouleEntity> boule : EntityManager::GetBoules()) {
			boule->ColEchelle = nullptr;
			boule->ColBlock = nullptr;
			m_player->CollisionWithThisEntity(boule);
		}
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if(entity->m_type != EntityType::player)
		m_player->CollisionWithThisEntity(entity);

		if (m_boule != nullptr) {
			for (std::shared_ptr<BouleEntity> boule : EntityManager::GetBoules()) {
				boule->collisionWithOtherEntity(entity);
			}
		}
	}
}

void EntityManager::InitJump() {
	
	if (m_player->JumpSpeed == 0 || m_player->JumpSpeed > 250) {
		m_player->JumpSpeed = 0;
		return;
	}

	m_player->JumpSpeed += 5;
}

void EntityManager::InitGravity()
{

	if (m_player->EnabledGravity()) {
		if (m_player->GravitySpeed < 64) {
			if (m_player->GravitySpeed == 0) {
				m_player->GravitySpeed = 1;
			}
			m_player->GravitySpeed *= 2;
		}
		return;
	}

	m_player->GravitySpeed = 0;

	for (std::shared_ptr<BouleEntity> boule : EntityManager::GetBoules()) {
		int gravitySpeed = boule->GravitySpeed;
		boule->EnabledGravity();
		if (gravitySpeed > 0 && boule->GravitySpeed == 0) {
			boule->step += 1;
			std::cout << boule->step;
		}
	}
}

void EntityManager::BouleEntityFactory()
{
		
}


void EntityManager::AddBoule(std::shared_ptr <BouleEntity> boule) {
	if (m_boule != nullptr) {
		boule->m_fille = m_boule;
	}
	
	m_boule = boule;
}

