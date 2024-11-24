#include "pch.h"
#include "Renderer2D.h"

namespace fz {

	sf::Sprite Renderer2D::s_Spirte;
	sf::RenderWindow* Renderer2D::s_RenderWindow = nullptr; 
	Weak<Framebuffer> Renderer2D::s_FrameBuffer = nullptr;
	OrthoCamera* Renderer2D::s_OrthoCamera = nullptr;
	sf::Vector2f Renderer2D::s_PrevCameraPos = { 0.0f, 0.0f };
	std::multimap<int, RenderFrame> Renderer2D::s_CommandBuffer;

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

	void Renderer2D::BeginScene(OrthoCamera& camera, Shared<Framebuffer>& framebuffer)
	{
		FZLOG_ASSERT(s_RenderWindow, "Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
		FZLOG_ASSERT(framebuffer, "Renderer2D�� ����� �� �����ϴ�. ������ ���۸� ã�� �� �����ϴ�.");
		FZLOG_ASSERT(!s_OrthoCamera, "Renderer2D�� ����� �� �����ϴ�. �̹� ȣ��� BeginScene�Դϴ�.");

		s_FrameBuffer = framebuffer;
		s_OrthoCamera = &camera;
		s_PrevCameraPos = s_OrthoCamera->GetCenter();
		if (s_FrameBuffer)
		{
			s_FrameBuffer->Clear();
			s_FrameBuffer->GetBuffer().setView(*s_OrthoCamera);
		}
	}

	void Renderer2D::BeginScene(OrthoCamera& camera, const sf::Transform& transform, Shared<Framebuffer>& framebuffer)
	{
		FZLOG_ASSERT(s_RenderWindow, "Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
		FZLOG_ASSERT(framebuffer, "Renderer2D�� ����� �� �����ϴ�. ������ ���۸� ã�� �� �����ϴ�.");
		FZLOG_ASSERT(!s_OrthoCamera, "Renderer2D�� ����� �� �����ϴ�. �̹� ȣ��� BeginScene�Դϴ�.");

		s_FrameBuffer = framebuffer;
		s_OrthoCamera = &camera;
		s_PrevCameraPos = s_OrthoCamera->GetCenter();
		// �ϴ� ī�޶� ������Ʈ�� �����Ǹ� ���󰡰� �ϵ��� ����
		s_OrthoCamera->SetCenter(transform * s_OrthoCamera->GetCenter());
		// s_OrthoCamera->SetRotation(transform.GetRotation());
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
			for (auto& it : s_CommandBuffer)
			{
				RenderFrame& renderFrame = it.second;
				sf::RenderStates state;
				state.transform = *renderFrame.Transform * renderFrame.subTranform;
				if (renderFrame.Sprite)
				{
					state.texture = renderFrame.Sprite->getTexture();
					s_FrameBuffer->GetBuffer().draw(*renderFrame.Sprite, state);
				}
				if (renderFrame.RectangleShape)
				{
					s_FrameBuffer->GetBuffer().draw(*renderFrame.RectangleShape, state);
					delete renderFrame.RectangleShape;
					renderFrame.RectangleShape = nullptr;
				}
				if (renderFrame.CircleShape)
				{
					s_FrameBuffer->GetBuffer().draw(*renderFrame.CircleShape, state);
					delete renderFrame.CircleShape;
					renderFrame.CircleShape = nullptr;
				}
			}

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
		s_CommandBuffer.clear();
	} 

	void Renderer2D::Draw(int order, sf::Sprite& target, const sf::Transform& transform, const sf::Transform& subTransform)
	{
		FZLOG_ASSERT(s_RenderWindow, "Renderer2D�� ����� �� �����ϴ�. �ʱ�ȭ���� ���� Renderer2D �Դϴ�.");
		FZLOG_ASSERT(s_OrthoCamera, "Renderer2D�� ����� �� �����ϴ�. BeginScene�� ȣ����� �ʾҽ��ϴ�.");

		RenderFrame renderFrame = { &target, &transform, nullptr, nullptr, subTransform };
		s_CommandBuffer.insert({ order, renderFrame });
	}

	void Renderer2D::Draw(sf::RectangleShape* target, const sf::Transform& transform, const sf::Transform& subTransform)
	{
		const auto& lastElement = *s_CommandBuffer.rbegin();
		RenderFrame renderFrame = { nullptr, &transform, target, nullptr, subTransform };
		s_CommandBuffer.insert({ lastElement.first + 1, renderFrame });
	}

} // namespace fz

 