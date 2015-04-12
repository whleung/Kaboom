#pragma once

#include <Windows.h>

#include <osg/Node>

#include "Component.h"
#include "GameStateData.h"

class SceneNodeComponent : public Component {
public:
    SceneNodeComponent(osg::Node *node);
    ~SceneNodeComponent();

    virtual void update(const GameStateData &gameState);

    osg::Node *getNode() const;
    void setNode(osg::Node *node);

private:
    osg::Node *node;
};
