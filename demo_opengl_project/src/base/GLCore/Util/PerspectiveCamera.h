#pragma once

#include <glm/glm.hpp>

namespace GLCore {
	namespace Utils {

		class PerspectiveCamera
		{
		public:
			PerspectiveCamera(const glm::vec3& front, const glm::vec3& right, const glm::vec3& position, float zoom, float aspect);
			PerspectiveCamera(const glm::vec3& position, float zoom, float aspect);
			~PerspectiveCamera();

			void SetViewMatrix(const glm::vec3& position, const glm::vec3& rotation);
			void SetProjectionMatrix(float zoom, float aspect);
			
			inline const glm::vec3& GetFront() const { return m_Front; }
			inline const glm::vec3& GetRight() const { return m_Right; }
			inline const glm::vec3& GetUp() const { return m_Up; }

			inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
			inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
			inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		private:
			glm::vec3 m_Front, m_Up, m_Right;
			glm::vec3 m_WorldUp{ 0.0f, 1.0f, 0.0f };

			glm::mat4 m_ViewMatrix, m_ProjectionMatrix, m_ViewProjectionMatrix;
		};

	}
}
