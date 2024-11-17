#include "pch.h"
#include "Renderer2D.h"

namespace fz {

	sf::Sprite Renderer2D::s_Spirte;
	sf::RenderWindow* Renderer2D::s_RenderWindow = nullptr; 
	Weak<Framebuffer> Renderer2D::s_FrameBuffer = nullptr;
	OrthoCamera* Renderer2D::s_OrthoCamera = nullptr;
	sf::Vector2f Renderer2D::s_PrevCameraPos = { 0.0f, 0.0f };

	void Renderer2D::Init(sf::RenderWindow* renderWindow)
	{
		FZLOG_ASSERT(renderWindow, "Renderer2D�� �ʱ�ȭ�� �� �����ϴ�.RenderWindow�� nullptr�Դϴ�.");
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

	void Renderer2D::BeginScene(OrthoCamera& camera, fz::Transform& transform, Shared<Framebuffer>& framebuffer)
	{
		FZLOG_ASSERT(s_RenderWindow, "Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
		FZLOG_ASSERT(framebuffer, "Renderer2D�� ����� �� �����ϴ�. ������ ���۸� ã�� �� �����ϴ�.");
		FZLOG_ASSERT(!s_OrthoCamera, "Renderer2D�� ����� �� �����ϴ�. �̹� ȣ��� BeginScene�Դϴ�.");

		s_FrameBuffer = framebuffer;
		s_OrthoCamera = &camera;
		s_PrevCameraPos = s_OrthoCamera->GetCenter();
		// �ϴ� ī�޶� ������Ʈ�� �����Ǹ� ���󰡰� �ϵ��� ����
		s_OrthoCamera->SetCenter(transform * s_OrthoCamera->GetCenter());
		s_OrthoCamera->SetRotation(transform.GetRotation());
		if (s_FrameBuffer)
		{
			s_FrameBuffer->Clear();
			s_FrameBuffer->GetBuffer().setView(*s_OrthoCamera);
		}
	}

	void Renderer2D::EndScene()
	{
		FZLOG_ASSERT(s_RenderWindow, "Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
		FZLOG_ASSERT(s_OrthoCamera, "Renderer2D�� ����� �� �����ϴ�. BeginScene�� ȣ����� �ʾҽ��ϴ�.");

		if (s_FrameBuffer)
		{
			auto& renderBuffer = s_FrameBuffer->GetBuffer();
			renderBuffer.display();
			s_RenderWindow->clear();
			sf::Sprite sprite;
			sprite.setTexture(renderBuffer.getTexture());
			s_RenderWindow->draw(sprite);
		}
		// Ʈ������ �ݺ� ������ ���ؼ� ī�޶� ���� ��ġ�� ����
		if (s_OrthoCamera)
		{
			s_OrthoCamera->SetCenter(s_PrevCameraPos);
		}
		s_FrameBuffer = nullptr;
		s_OrthoCamera = nullptr;
	} 

	void Renderer2D::Draw(sf::Sprite& obj, fz::Transform& transform)
	{
		FZLOG_ASSERT(s_RenderWindow, "Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
		FZLOG_ASSERT(s_OrthoCamera, "Renderer2D�� ����� �� �����ϴ�. BeginScene�� ȣ����� �ʾҽ��ϴ�.");

		sf::RenderStates state;
		state.transform = transform;
		state.texture = obj.getTexture();
		if (s_FrameBuffer)
			s_FrameBuffer->GetBuffer().draw(obj, state);
	}
} // namespace fz

