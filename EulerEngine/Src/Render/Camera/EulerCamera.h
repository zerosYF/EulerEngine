#pragma once
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include"GutKink/Core.h"
namespace EulerEngine {
	const float SPEED = 0.7f;
	const float FOV = 45.0f;
	const float MIN_FOV = 10.0F;
	const float MAX_FOV = 89.0f;

	enum CameraType {
		PERSPECTIVE = 0,
		ORTHOGRAPHIC = 1,
	};
	class EulerCamera {
	public:
		EulerCamera() {
			m_ProjectionType = CameraType::PERSPECTIVE;
			UpdateView();
			UpdateProjection();
		}
		EulerCamera(CameraType type)
			:m_ProjectionType(type) {
			UpdateView();
			UpdateProjection();
		}
		CameraType GetCameraType() const{
			return m_ProjectionType;
		}
		void SetCameraType(CameraType type) {
			m_ProjectionType = type;
			UpdateProjection();
		}

		glm::mat4 GetProjectionMatrix() const{
			return m_ProjectionMatrix;
		}
		glm::mat4 GetViewMatrix() const{
			return m_ViewMatrix;
		}


		const glm::vec3& GetPosition() const {
			return m_Position;
		}
		const void SetPosition(const glm::vec3& position) {
			m_Position = position;
			UpdateView();
		}
		const glm::vec3& GetRotation() const {
			return m_Rotation;
		}
		const void SetRotation(const glm::vec3& rotation) {
			m_Rotation = glm::radians(glm::degrees(rotation) + glm::vec3(0.0f, -90.0f, 0.0f));
			UpdateView();
		}
		
		const float GetAspectRatio() const {
			return m_AspectRatio;
		}
		const void SetViewportSize(float width, float height) {
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			m_AspectRatio = width / height;
			UpdateProjection();
		}
		const std::pair<float, float> GetViewportSize() const {
			return std::make_pair(m_ViewportWidth, m_ViewportHeight);
		}

		//Perspective Camera
		const float GetFovAngle() const {
			return m_PerspectiveCameraData.FovAngle;
		}
		const void SetFovAngle(float fovAngle) {
			m_PerspectiveCameraData.FovAngle = glm::clamp(fovAngle, MIN_FOV, MAX_FOV);
			UpdateProjection();
		}
		const float GetPerspectiveNearClip() const {
			return m_PerspectiveCameraData.NearClip;
		}
		const void SetPerspectiveNearClip(float nearClip) {
			m_PerspectiveCameraData.NearClip = nearClip;
			UpdateProjection();
		}
		const float GetPerspectiveFarClip() const {
			return m_PerspectiveCameraData.FarClip;
		}
		const void SetPerspectiveFarClip(float farClip) {
			m_PerspectiveCameraData.FarClip = farClip;
			UpdateProjection();
		}
		//Orthographic Camera
		const float GetZoomLevel() const {
			return m_OrthographicCameraData.ZoomLevel;
		}
		const void SetZoomLevel(float zoomLevel) {
			m_OrthographicCameraData.ZoomLevel = zoomLevel;
			UpdateProjection();
		}
		const float GetOrthographicNearClip() const {
			return m_OrthographicCameraData.NearClip;
		}
		const void SetOrthographicNearClip(float nearClip) {
			m_OrthographicCameraData.NearClip = nearClip;
			UpdateProjection();
		}
		const float GetOrthographicFarClip() const {
			return m_OrthographicCameraData.FarClip;
		}
		const void SetOrthographicFarClip(float farClip) {
			m_OrthographicCameraData.FarClip = farClip;
			UpdateProjection();
		}

		const glm::vec3 GetRight() const {
			return m_Right;
		}
		const glm::vec3 GetUp() const {
			return m_Up;
		}
		const glm::vec3 GetFront() const {
			return m_Front;
		}

	protected:
		void UpdateView();
		void UpdateProjection();
	protected:
		CameraType m_ProjectionType = CameraType::PERSPECTIVE;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, glm::radians(- 90.0f), 0.0f);

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		float m_AspectRatio = 1.0f;
		float m_ViewportWidth = 1280.0f;
		float m_ViewportHeight = 720.0f;
		struct PerspectiveCameraData {
			float FovAngle = FOV;
			float NearClip = 0.1f;
			float FarClip = 100.0f;
		};
		struct OrthographicCameraData {
			float ZoomLevel = 1.0f;
			float NearClip = -1.0f;
			float FarClip = 1.0f;
		};
		PerspectiveCameraData m_PerspectiveCameraData;
		OrthographicCameraData m_OrthographicCameraData;
	};
}