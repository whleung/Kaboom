#pragma once

#include <ostream>

#include "Component.h"
enum EntityType{
	UNINITIATED = 0,
	PLAYER = 1,
	BOMB=2
};
class CharacteristicComponent : public Component {
public:
	CharacteristicComponent();
	CharacteristicComponent(EntityType,int);
	~CharacteristicComponent();
	void setType(EntityType);
	EntityType getType();
	void setFeature(int);
	int getFeature();

	friend std::ostream& operator<<(std::ostream &os, const CharacteristicComponent &o) {
		os << "CharacteristicComponent: {" << std::endl;
		os << "    type: " << o.type << std::endl;
		os << "    feature: " << o.feature<< std::endl;
		os << "}";
		return os;
	}
private:
	EntityType type;
	int feature;
};