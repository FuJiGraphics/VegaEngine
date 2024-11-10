#pragma once

namespace fz {
	
	class Framebuffer;
	class CameraController;
	class OrthoCamera;
	class Window;

	class Renderer2D
	{
	public:
		static void Init(sf::RenderWindow* renderWindow);
		static void Release();
		static void Reset();

		static void BeginScene(CameraController* camera, Framebuffer* framebuffer = nullptr);
		static void EndScene();

		static void Draw(const sf::Drawable& target);
		
	private:
		static sf::Sprite s_Spirte;
		static sf::RenderWindow* s_RenderWindow;
		static fz::CameraController* s_RenderCamera;
		static fz::Framebuffer* s_RenderBuffer;
	};

} // namespace fz