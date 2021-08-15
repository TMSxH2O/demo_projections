#include "glpch.h"
#include "PerspectiveCameraController.h"

#include <GLFW/glfw3.h>

#include "GLCore/Core/Input.h"

GLCore::Utils::PerspectiveCameraController::PerspectiveCameraController(
	const glm::vec3& position, const glm::vec3& front, const glm::vec3& right,
	float zoom, float aspect)
	:m_CameraZoom(zoom), m_AspectRatio(aspect), m_Position(position), m_Rotation(0.0f),
	m_Camera(front, right, position, zoom, aspect) {}

GLCore::Utils::PerspectiveCameraController::PerspectiveCameraController(float aspect)
	: m_CameraZoom(45.f), m_AspectRatio(aspect),
	m_Position(glm::vec3(0.0f, 0.0f, 2.0f)), m_Rotation(0.0f),
	m_Camera(m_Position, m_CameraZoom, m_AspectRatio) {}

GLCore::Utils::PerspectiveCameraController::PerspectiveCameraController(float winWidth, float winHeight)
	:PerspectiveCameraController(winWidth/winHeight) {}

void GLCore::Utils::PerspectiveCameraController::OnUpdate(const Timestep& ts)
{
	bool hasValueChanged = true;
	if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		const auto& right = m_Camera.GetRight();
		m_Position -= right;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		const auto& right = m_Camera.GetRight();
		m_Position += right;
	} 
	else if (Input::IsKeyPressed(GLFW_KEY_W))
	{
		const auto& front = m_Camera.GetFront();
		m_Position += front;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_S))
	{
		const auto& front = m_Camera.GetFront();
		m_Position -= front;
	}
	else
	{
		hasValueChanged = false;
	}

	if (hasValueChanged)
	{
		m_Camera.SetViewMatrix(m_Position, m_Rotation);
	}
}

void GLCore::Utils::PerspectiveCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
}

bool GLCore::Utils::PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& event)
{
	m_CameraZoom -= event.GetYOffset() * 0.25f;
	m_CameraZoom = std::min(std::max(m_CameraZoom, 0.0f), 45.f);
	m_Camera.SetProjectionMatrix(m_CameraZoom, m_AspectRatio);
	return false;
}

bool GLCore::Utils::PerspectiveCameraController::OnWindowResized(WindowResizeEvent& event)
{
	m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
	m_Camera.SetProjectionMatrix(m_CameraZoom, m_AspectRatio);
	return false;
}
