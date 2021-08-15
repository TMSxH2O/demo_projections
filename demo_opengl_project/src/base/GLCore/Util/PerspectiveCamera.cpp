#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

GLCore::Utils::PerspectiveCamera::PerspectiveCamera(
	const glm::vec3& front, const glm::vec3& right, const glm::vec3& position, float zoom, float aspect)
	: m_Front(glm::normalize(front)), m_Up(glm::normalize(glm::cross(right, front))), m_Right(glm::normalize(right)),
	m_ViewMatrix(glm::lookAt(position, position + m_Front, m_Up)),
	m_ProjectionMatrix(glm::perspective(glm::radians(zoom), aspect, 0.1f, 100.f)),
	m_ViewProjectionMatrix(m_ProjectionMatrix* m_ViewMatrix) 
{
	m_WorldUp = m_Up;
}

GLCore::Utils::PerspectiveCamera::PerspectiveCamera(
	const glm::vec3& position, float zoom, float aspect)
	: PerspectiveCamera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), position, zoom, aspect) {}

GLCore::Utils::PerspectiveCamera::~PerspectiveCamera() {}

void GLCore::Utils::PerspectiveCamera::SetViewMatrix(const glm::vec3& position, const glm::vec3& rotation)
{
	// Quatenrnion Matrix
	glm::qua<float> q(glm::radians(rotation));
	glm::mat4 rotMatrix = glm::mat4_cast(q);

	m_Front = glm::normalize(glm::vec3(rotMatrix * glm::vec4(m_Front, 0.0f)));
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

	m_ViewMatrix = glm::lookAt(position, position + m_Front, m_Up);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void GLCore::Utils::PerspectiveCamera::SetProjectionMatrix(float zoom, float aspect)
{
	m_ProjectionMatrix = glm::perspective(zoom, aspect, 0.1f, 100.f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
