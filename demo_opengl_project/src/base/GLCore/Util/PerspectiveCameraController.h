#pragma once

#include <glm/glm.hpp>

#include "GLCore/Core/Timestep.h"

#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/MouseEvent.h"
#include "GLCore/Events/KeyEvent.h"

#include "PerspectiveCamera.h"

namespace GLCore {
	namespace Utils {

		class PerspectiveCameraController
		{
		public:
			PerspectiveCameraController(
				const glm::vec3& position, const glm::vec3& front, const glm::vec3& right, 
				float zoom, float aspect);
			PerspectiveCameraController(float winWidth, float winHeight);
			PerspectiveCameraController(float aspect);

			void OnUpdate(const Timestep& ts);
			void OnEvent(Event& e);

			inline PerspectiveCamera& GetCamera() { return m_Camera; }
			inline float GetZoom() const { return m_CameraZoom; }
		private:
			bool OnMouseScrolled(MouseScrolledEvent& event);
			bool OnWindowResized(WindowResizeEvent& event);
		private:
			float m_CameraZoom, m_AspectRatio;
			glm::vec3 m_Position, m_Rotation;

			PerspectiveCamera m_Camera;
		};

	}
}
