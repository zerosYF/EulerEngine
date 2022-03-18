#pragma once
#ifndef GAME
#include<GLFW/glfw3.h>
#include<glm/gtc/type_ptr.hpp>
enum GameState{
	GAME_ACTIVE,
	GAME_INIT,
	GAME_WIN
};

class Game {
public:
	GameState state;
	GLboolean Keys[1024];
	GLuint Width;
	GLuint Height;
	Game(GLuint width,GLuint height);
	~Game();
	void Init();
	void ProcessInput(GLfloat);
	void Update(GLfloat);
	void Render();
};
#endif