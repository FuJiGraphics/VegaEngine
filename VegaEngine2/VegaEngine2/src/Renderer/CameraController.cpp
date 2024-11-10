#include "pch.h"
#include "CameraController.h"

namespace fz {

	CameraController::CameraController(const sf::Vector2f& size, bool rotation)
		: m_CameraMoveSpeed(100.f)
		, m_CameraRotateSpeed(100.f)
		, m_CameraZoomFactor(0.1f)
		, m_MousePrevPos(0.0f, 0.0f)
		, m_MousePos(0.0f, 0.0f)
		, m_IsMouseButtonPressed(false)
		, m_ActivatedRotation(rotation)
		, m_Camera(nullptr)
	{
		sf::Vector2f pos{ size.x * 0.5f, size.y * 0.5f };
		m_Camera = CreateShared<fz::OrthoCamera>(pos, size);
	}

	void CameraController::SetSize(float width, float height)
	{
		m_Camera->SetSize(width, height);
	}

	void CameraController::SetViewport(float x, float y, float width, float height)
	{
		if ((x >= width) || (y >= height))
		{
			Log.Error("카메라 컨트롤러의 뷰포트를 설정할 수 없습니다. 잘못된 뷰포트 설정 값 입니다.");
			return;
		}
		sf::FloatRect rect;
		rect.left = x / width;
		rect.top = y / height;
		rect.width = (x + width) / width;
		rect.height = (y + height) / height;
		m_Camera->SetViewport(rect);
	}

	void CameraController::OnUpdate(float dt)
	{
		if (!m_ActivatedController)
			return;

		if (InputManager::IsKeyPressed(KeyType::A))
			m_Camera->Move(m_CameraMoveSpeed * -1.0f * dt, 0.0f);
		else if (InputManager::IsKeyPressed(KeyType::D))
			m_Camera->Move(m_CameraMoveSpeed * dt, 0.0f);

		if (InputManager::IsKeyPressed(KeyType::W))
			m_Camera->Move(0.0f, m_CameraRotateSpeed * -1.0f * dt);
		else if (InputManager::IsKeyPressed(KeyType::S))
			m_Camera->Move(0.0f, m_CameraRotateSpeed * dt);

		if (m_ActivatedRotation)
		{
			if (InputManager::IsKeyPressed(KeyType::Q))
				m_Camera->Rotate(m_CameraRotateSpeed * dt);
			else if (InputManager::IsKeyPressed(KeyType::E))
				m_Camera->Rotate(m_CameraRotateSpeed * -1.0f * dt);
		}
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dis(e);
		dis.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(CameraController::OnMouseScrolled));
		dis.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(CameraController::OnWindowResized));
		dis.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(CameraController::OnMouseButtonPressed));
		dis.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(CameraController::OnMouseButtonReleased));
		dis.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(CameraController::OnMouseMoved));
	}

	OrthoCamera& CameraController::GetOrthoCamera()
	{
		return *m_Camera;
	}

	void CameraController::SetActivated(bool enabled)
	{
		m_ActivatedController = enabled;
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (!m_ActivatedController)
			return false;

		float offset = e.GetYOffset();
		if (offset < 0)
			m_Camera->Zoom(1.0f + m_CameraZoomFactor);
		else
			m_Camera->Zoom(1.0f - m_CameraZoomFactor);
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Camera->SetSize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

	bool CameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == MouseButtonType::Left)
		{
			m_IsMouseButtonPressed = true;
		}

		return false;
	}

	bool CameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == MouseButtonType::Left)
		{
			m_IsMouseButtonPressed = false;
		}
		return false;
	}

	bool CameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		m_MousePrevPos = m_MousePos;
		m_MousePos.x = e.GetX();
		m_MousePos.y = e.GetY();
		if (m_IsMouseButtonPressed && m_ActivatedController)
		{
			float dx = (m_MousePos.x - m_MousePrevPos.x) * -1.0f;
			float dy = (m_MousePos.y - m_MousePrevPos.y) * -1.0f;
			const sf::Vector2f& cenPos = m_Camera->GetCenter();
			m_Camera->SetCenter(cenPos.x + dx, cenPos.y + dy);
		}
		return false;
	}

} // namespace fz