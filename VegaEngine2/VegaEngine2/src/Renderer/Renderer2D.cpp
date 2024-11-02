#include "pch.h"
#include "Renderer2D.h"

namespace fz {

	sf::Sprite Renderer2D::s_Spirte;
	sf::RenderWindow* Renderer2D::s_RenderWindow = nullptr;
	fz::CameraController* Renderer2D::s_RenderCamera = nullptr;
	fz::Framebuffer* Renderer2D::s_RenderBuffer = nullptr;

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

	void Renderer2D::BeginScene(CameraController* camera, Framebuffer* framebuffer)
	{
		if (s_RenderWindow == nullptr || camera == nullptr || s_RenderCamera != nullptr)
		{
			if (camera == nullptr)
				Log.Error("Renderer2D�� ����� �� �����ϴ�. ī�޶� ã�� �� �����ϴ�.");
			else if (s_RenderWindow == nullptr)
				Log.Error("Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
			else if (s_RenderCamera != nullptr)
				Log.Error("Renderer2D�� ����� �� �����ϴ�. �̹� BeginScene�� ȣ��Ǿ����ϴ�.");
			return;
		}
		s_RenderBuffer = (framebuffer) ? framebuffer : nullptr;
		s_RenderCamera = camera;
		if (s_RenderBuffer)
			s_RenderBuffer->Clear();
	}

	void Renderer2D::EndScene()
	{
		if (s_RenderWindow == nullptr || s_RenderCamera == nullptr)
		{
			if (s_RenderWindow)
				Log.Error("Renderer2D�� ����� �� �����ϴ�. ī�޶� ã�� �� �����ϴ�.");
			else
				Log.Error("Renderer2D�� ����� �� �����ϴ�. BeginScene�� ȣ����� �ʾҽ��ϴ�.");
			return;
		}

		if (s_RenderBuffer)
		{
			auto& renderBuffer = s_RenderBuffer->GetBuffer();
			renderBuffer.display();
			renderBuffer.setView(s_RenderCamera->GetOrthoCamera().GetView());
			s_Spirte.setTexture(renderBuffer.getTexture());
			s_RenderWindow->draw(s_Spirte);
		}
		s_RenderBuffer = nullptr;
		s_RenderCamera = nullptr;
	}

	void Renderer2D::Draw(const sf::Drawable& target)
	{
		if (s_RenderWindow == nullptr || s_RenderCamera == nullptr)
		{
			if (s_RenderWindow)
				Log.Error("Renderer2D�� ����� �� �����ϴ�. Begin Scene�� ȣ����� �ʾҽ��ϴ�.");
			else
				Log.Error("Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
			return;
		}

		if (s_RenderBuffer)
			s_RenderBuffer->GetBuffer().draw(target);
		else
		{
			s_RenderWindow->setView(s_RenderCamera->GetOrthoCamera().GetView());
			s_RenderWindow->draw(target);
		}
	}
} // namespace fz

