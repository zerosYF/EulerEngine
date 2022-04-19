#pragma once
#ifndef GAME
#include"GLCamera.h"
enum GameState{
	GAME_ACTIVE,
	GAME_INIT,
	GAME_WIN
};
class EulerGame {
public:
	GameState state;
	EulerGame() {
	}
	void Update();
};
#endif