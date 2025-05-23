#pragma once
#include"GutKink/Application.h"
#include"Core/IO/EulerInput.h"
#include"Core/IO/EulerInputCodes.h"
#include"Core/Layer/EulerLayer.h"
#include"Core/Logs/EulerLog.h"
#include"Core/Global/EulerTimer.h"
#include"Core/EulerInstrumentor.h"
#include"ImGui/ImGuiLayer.h"
#include"Render/RawData/EulerVertices.h"
#include"Render/Renderer/RendererAPI.h"
#include"Render/Renderer/Renderer.h"
#include"Render//Renderer/RenderCmd.h"
#include"Render/EulerBuffer.h"
#include"Render/EulerShader.h"
#include"Render/VertexArray.h"
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerMaterial2D.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/RawData/EulerTexture.h"
#include"Render/RawData/SubTexture2D.h"
#include"Render/FrameBuffer.h"
#include"Resource/ResourceLibrary.h"

#include"Render/Camera/EulerCamera.h"
#include"Render/Camera/CameraController.h"

#include"World/EulerScene.h"
#include"World/Component/Component.h"
#include"World/EulerObject.h"
#include"World/EulerBehaviour.h"
#include"World/EulerSerialize.h"

#include"Utils/PlatformUtils.h"

#include"Script/ScriptEngine.h"
#include"Script/ScriptClass.h"
#include"Script/ScriptInstance.h"

#include"Project/EulerProject.h"

#include<../ImGui/imgui.h>

#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

//++++++++++++++++++++++++++++++++entry point+++++++++++++++++++++++++++