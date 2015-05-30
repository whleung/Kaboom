#include "PlayerStatusEventHandler.h"

#include <components/PlayerStatusComponent.h>
#include "../components/ModelComponent.h"
#include "../components/SoundComponent.h"
#include <components/PositionComponent.h>
#include <components/RotationComponent.h>
#include <core/Entity.h>
#include <network/PlayerStatusEvent.h>

#include "../core/Game.h"

PlayerStatusEventHandler::PlayerStatusEventHandler(Game *game)
        : game(game) {
}

void PlayerStatusEventHandler::handle(const Event &e) const {
    const PlayerStatusEvent &evt = static_cast<const PlayerStatusEvent &>(e);

    Entity *entity = game->getEntityManager().getEntity(evt.getEntityId());

    auto playerStatusComp = entity->getComponent<PlayerStatusComponent>();
    playerStatusComp->setAlive(evt.isAlive());
    playerStatusComp->setRunning(evt.isRunning());
    playerStatusComp->setJumping(evt.isJumping());
    playerStatusComp->setAttacking(evt.isAttacking());
    playerStatusComp->setDamaged(evt.isDamaged());
	EntityType type = entity->getType();
	Entity *player = game->getCurrentPlayer()->getEntity();
	auto bombPos = entity->getComponent<PositionComponent>()->getPosition();
	auto playerRot = player->getComponent<RotationComponent>()->getRotation();
	auto playerPos = player->getComponent<PositionComponent>()->getPosition();
	game->getSoundManager().setListenerPosition(playerPos);
	game->getSoundManager().setListenerRotation(playerRot);
	auto soundComp = entity->getComponent<SoundComponent>();
	if (evt.isRunning()&&!evt.isJumping()){
		//game->getSoundManager().playSound(SoundType::WALKING, bombPos);
		
		soundComp->setListenerPosition(playerPos);
		soundComp->setListenerRotation(playerRot);
		soundComp->playSound(bombPos);
	}
	else{
		soundComp->stopSound();
	}
	if (evt.isJumping()&&!playerStatusComp->getJumped()){
		game->getSoundManager().playSound(SoundType::KABOOM_FIRE, bombPos);
	}
	
		playerStatusComp->setJumped(evt.isJumping());
	

	auto modelComp = entity->getComponent<ModelComponent>();
	Model* model = modelComp->getModel();

	if (evt.isRunning()) {
		model->playAnimation(RUNNING);
	}
	else {
		model->playAnimation(IDLE);
	}
}
