#pragma once
#include"GutKink/Application.h"
#include"Core/Input/EulerInput.h"
#include"Core/Input/InputCodes.h"
#include"Core/Layer/EulerLayer.h"
#include"Core/Logs/EulerLog.h"
#include"Core/EulerTimer.h"
#include"Core/EulerInstrumentor.h"
#include"ImGui/ImGuiLayer.h"
#include"Render/Vertices/EulerVertices.h"
#include"Render/Renderer/RendererAPI.h"
#include"Render/Renderer/Renderer.h"
#include"Render/Renderer/Renderer2D.h"
#include"Render//Renderer/RenderCmd.h"
#include"Render/EulerBuffer.h"
#include"Render/EulerShader.h"
#include"Render/VertexArray.h"
#include"Render/EulerMaterial.h"
#include"Render/EulerTexture.h"
#include"Render/FrameBuffer.h"
#include"Resource/ResourceLibrary.h"

#include"Render/Camera/EulerCamera.h"
#include"Render/Camera/CameraController.h"

#include"World/EulerScene.h"
#include"World/Component/Component.h"
#include"World/EulerObject.h"
#include"World/EulerBehaviour.h"

#include<../ImGui/imgui.h>

#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
//++++++++++++++++++++++++++++++++entry point+++++++++++++++++++++++++++