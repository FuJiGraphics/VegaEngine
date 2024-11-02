#include "pch.h"
#include "Renderer2D.h"

namespace fz {

	sf::RenderWindow* Renderer2D::s_RenderWindow = nullptr;
	fz::CameraController* Renderer2D::s_RenderCamera = nullptr;

	void Renderer2D::Init(sf::RenderWindow* renderWindow)
	{
		if (renderWindow == nullptr)
		{
			Log.Error("Renderer2D를 초기화할 수 없습니다. RenderWindow가 nullptr입니다.");
			return;
		}
		s_RenderWindow = renderWindow;
	}

	void Renderer2D::Release()
	{
		s_RenderWindow = nullptr;
	}

	void Renderer2D::Reset()
	{
		s_RenderWindow = nullptr;
	}

	void Renderer2D::BeginScene(CameraController* camera)
	{
		if (s_RenderWindow == nullptr || camera == nullptr || s_RenderCamera != nullptr)
		{
			if (camera == nullptr)
				Log.Error("Renderer2D를 사용할 수 없습니다. 카메라를 찾을 수 없습니다.");
			else if (s_RenderWindow == nullptr)
				Log.Error("Renderer2D를 사용할 수 없습니다. 초기화되지 않은 Renderer2D 입니다.");
			else if (s_RenderCamera != nullptr)
				Log.Error("Renderer2D를 사용할 수 없습니다. 이미 BeginScene이 호출되었습니다.");
			return;
		}

		s_RenderCamera = camera;
	}

	void Renderer2D::EndScene()
	{
		if (s_RenderWindow == nullptr || s_RenderCamera == nullptr)
		{
			if (s_RenderWindow)
				Log.Error("Renderer2D를 사용할 수 없습니다. 카메라를 찾을 수 없습니다.");
			else
				Log.Error("Renderer2D를 사용할 수 없습니다. BeginScene이 호출되지 않았습니다.");
			return;
		}

		s_RenderCamera = nullptr;
	}

	void Renderer2D::Draw(const sf::Drawable& target)
	{
		if (s_RenderWindow == nullptr || s_RenderCamera == nullptr)
		{
			if (s_RenderWindow)
				Log.Error("Renderer2D를 사용할 수 없습니다. Begin Scene이 호출되지 않았습니다.");
			else
				Log.Error("Renderer2D를 사용할 수 없습니다. 초기화되지 않은 Renderer2D 입니다.");
			return;
		}
		s_RenderWindow->setView(s_RenderCamera->GetOrthoCamera().GetView());
		s_RenderWindow->draw(target);
	}
} // namespace fz

