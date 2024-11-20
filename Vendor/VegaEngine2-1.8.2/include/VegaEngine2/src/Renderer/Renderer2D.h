#pragma once

namespace fz {
	
	class Framebuffer;
	class OrthoCamera;
	class Window;

	struct RenderFrame
	{
		sf::Sprite* Sprite;
		sf::Transform* Transform;
	};

	class Renderer2D
	{
	public:
		static void Init(sf::RenderWindow* renderWindow);
		static void Release();
		static void Reset();

		static void BeginScene(OrthoCamera& camera, Shared<Framebuffer>& framebuffer);
		static void BeginScene(OrthoCamera& camera, const sf::Transform& transform, Shared<Framebuffer>& framebuffer);
		static void EndScene();

		static void Draw(int order, sf::Sprite& target, sf::Transform& transform);
		
	private:
		static sf::Sprite s_Spirte;
		static sf::RenderWindow* s_RenderWindow;
		static Weak<Framebuffer> s_FrameBuffer;
		static OrthoCamera* s_OrthoCamera;
		static sf::Vector2f s_PrevCameraPos;
		static std::multimap<int, RenderFrame> s_CommandBuffer;
	};

} // namespace fz