#include "DefaultExplosionMessageHandler.h"

#include <btBulletDynamicsCommon.h>

#include <components/HealthComponent.h>
#include <components/PlayerStatusComponent.h>
#include <core/Entity.h>

#include "ExplosionMessage.h"
#include "Message.h"
#include "MessageType.h"
#include "../components/PhysicsComponent.h"
#include "../components/TriggerComponent.h"
#include "../core/EntityConfigLookup.h"
#include "../core/Game.h"

bool DefaultExplosionMessageHandler::handle(const Message &message) const {
    if (message.getType() != MessageType::EXPLOSION) {
        return false;
    }

    auto &msg = static_cast<const ExplosionMessage &>(message);

    Game *game = msg.getGame();
    Entity *entity = msg.getEntity();
    const std::unordered_set<Entity *> &nearbyEntities = msg.getNearbyEntities();

    auto bombTriggerComp = entity->getComponent<TriggerComponent>();

    for (auto nearbyEntity : nearbyEntities) {
        auto charStatusComp = nearbyEntity->getComponent<PlayerStatusComponent>();
        auto charPhysicsComp = nearbyEntity->getComponent<PhysicsComponent>();
        auto charHealthComp = nearbyEntity->getComponent<HealthComponent>();

        if (charStatusComp == nullptr || charPhysicsComp == nullptr || charHealthComp == nullptr) {
            continue;
        }

        // Begin timer on knockback, during this time the player cannot move
        btVector3 explosionPos = bombTriggerComp->getGhostObject()->getWorldTransform().getOrigin();
        btVector3 playerPos = charPhysicsComp->getRigidBody()->getCenterOfMassPosition();
        printf("explosionPos : <%f,%f,%f> \n", explosionPos.getX(), explosionPos.getY(), explosionPos.getZ());
        printf("playerPos : <%f,%f,%f> \n", playerPos.getX(), playerPos.getY(), playerPos.getZ());

        btVector3 dirVec = btVector3(playerPos - explosionPos);
        dirVec.normalize();
	
        btScalar playerDistanceFromExplosion = playerPos.distance(explosionPos);

        auto &bombConfig = EntityConfigLookup::instance()[entity->getType()];
        auto &charConfig = EntityConfigLookup::instance()[nearbyEntity->getType()];

        float explosionRadius = bombConfig.getFloat("explosion-radius");
        float knockbackAmount = bombConfig.getFloat("knockback-amount");
        int knockbackDuration = bombConfig.getInt("knockback-duration");
        int maxDamage = bombConfig.getInt("max-damage");
        int minDamage = bombConfig.getInt("min-damage");
        float collisionRadius = charConfig.getFloat("collision-radius");

        float maxDistancePossible = explosionRadius + (collisionRadius + 0.3f); //0.3f is hard code fix
        float distancePercentAway = (maxDistancePossible - playerDistanceFromExplosion) / maxDistancePossible;
        btVector3 impulseVec = (knockbackAmount * distancePercentAway) * dirVec; // linear equation
        printf("playerDistanceFromExplosion : %f\n", playerDistanceFromExplosion);
        printf("maxDistancePossible : %f\n", maxDistancePossible);
        printf("distancePercentAway : %f\n", distancePercentAway);
		printf("impulseVec-> x : %f, y :%f, z :%f\n", impulseVec.getX(), impulseVec.getY(), impulseVec.getZ());

        charPhysicsComp->getRigidBody()->applyCentralImpulse(impulseVec);

        charStatusComp->getKnockBackTimer().setDuration(knockbackDuration);
        charStatusComp->getKnockBackTimer().start();
        charStatusComp->setIsKnockBacked(true); // we could do some camera shake with this

        // apply damage
        int damage = int(distancePercentAway * (maxDamage - minDamage) + minDamage);
        printf("damage taken: %d \n", damage);

        charHealthComp->subtractFromHealthAmount(damage);
        charStatusComp->getDamageTimer().setDuration(250); // TODO: this should be global
        charStatusComp->getDamageTimer().start();
        charStatusComp->setIsDamaged(true);
        printf("new Player Health: %d \n", charHealthComp->getHealthAmount());
    }

    msg.getGame()->getGameServer().sendExplosionEvent(entity);
    msg.getGame()->removeEntity(entity);

    return true;
}
