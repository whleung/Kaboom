#include "FiringSystem.h"

#include <core/Entity.h>

#include "../components/InputComponent.h"
#include "../components/MessageHandlerComponent.h"
#include "../messaging/Attack1Message.h"
#include "../messaging/Attack2Message.h"
#include "../messaging/MessageHandler.h"
#include "../messaging/NoAttackMessage.h"
#include "../messaging/MessageHandler.h"

FiringSystem::FiringSystem(Game *game)
        : game(game) {
}

bool FiringSystem::checkEntity(Entity *entity) {
    return entity->hasComponent<InputComponent>() &&
            entity->hasComponent<MessageHandlerComponent>();
}

void FiringSystem::processEntity(Entity *entity) {
    auto inputComp = entity->getComponent<InputComponent>();
    auto handlerComp = entity->getComponent<MessageHandlerComponent>();

    if (!inputComp->isAttacking1() && !inputComp->isAttacking2()) {
        NoAttackMessage message(game, entity);
        handlerComp->getHandler()->handle(message);
    } else {
        if (inputComp->isAttacking1()) {
            Attack1Message message(game, entity);
            handlerComp->getHandler()->handle(message);
        }

        if (inputComp->isAttacking2()) {
            Attack2Message message(game, entity);
            handlerComp->getHandler()->handle(message);
        }
    }
}
