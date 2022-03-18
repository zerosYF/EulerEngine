#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "triangle.h"
#include "cShader.h"
#include "cCamera.h"
#include "cModel.h"
#include <vector>
#include<random>
#include<ft2build.h>
#include FT_FREETYPE_H
#define GLEW_STATIC
#include<GL/glew.h>
#include"cText.h"
#include"Input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
bool shadows = true;
// ∂® ±∆˜≈‰÷√
float deltaTime = 0.0f;
float lastTime = 0.0f;
// …„œÒª˙≈‰÷√
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
Input *input = new Input();