#pragma once
#include "Stage.h"

class EndStage : public Stage {
public:
	EndStage() :Stage("End") {}
	void render(Image& Fb, float time, GameMap3& map, Vector2& camera_movenemt);
	void update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed);
};