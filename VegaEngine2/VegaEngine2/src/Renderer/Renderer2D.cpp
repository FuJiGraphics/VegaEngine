#include "pch.h"
#include "Renderer2D.h"

namespace fz {

	sf::RenderWindow* Renderer2D::s_RenderWindow = nullptr;

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

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		if (s_RenderWindow == nullptr)
		{
			Log.Error("Renderer2D를 사용할 수 없습니다. 초기화되지 않은 Renderer2D 입니다.");
			return;
		}
	}

	void Renderer2D::EndScene()
	{
		if (s_RenderWindow == nullptr)
		{
			Log.Error("Renderer2D를 사용할 수 없습니다. 초기화되지 않은 Renderer2D 입니다.");
			return;
		}
		s_RenderWindow->display();
	}

	void Renderer2D::Draw(const sf::Drawable& target)
	{
		if (s_RenderWindow == nullptr)
		{
			Log.Error("Renderer2D를 사용할 수 없습니다. 초기화되지 않은 Renderer2D 입니다.");
			return;
		}
		s_RenderWindow->draw(target);
	}
} // namespace fz

