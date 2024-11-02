#include "pch.h"
#include "Renderer2D.h"

namespace fz {

	sf::RenderWindow* Renderer2D::s_RenderWindow = nullptr;

	void Renderer2D::Init(sf::RenderWindow* renderWindow)
	{
		if (renderWindow == nullptr)
		{
			Log.Error("Renderer2D�� �ʱ�ȭ�� �� �����ϴ�. RenderWindow�� nullptr�Դϴ�.");
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
			Log.Error("Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
			return;
		}
	}

	void Renderer2D::EndScene()
	{
		if (s_RenderWindow == nullptr)
		{
			Log.Error("Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
			return;
		}
		s_RenderWindow->display();
	}

	void Renderer2D::Draw(const sf::Drawable& target)
	{
		if (s_RenderWindow == nullptr)
		{
			Log.Error("Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
			return;
		}
		s_RenderWindow->draw(target);
	}
} // namespace fz

