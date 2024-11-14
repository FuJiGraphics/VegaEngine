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

		static void BeginScene(CameraController& controller, Shared<Framebuffer>& framebuffer);
		static void BeginScene(OrthoCamera& camera, fz::Transform& transform, Shared<Framebuffer>& framebuffer);
		static void EndScene();

		static void Draw(sf::Sprite& target, fz::Transform& transform);
		
	private:
		static sf::Sprite s_Spirte;
		static sf::RenderWindow* s_RenderWindow;
		static Weak<Framebuffer> s_FrameBuffer;
		static CameraController* s_CameraController;
		static OrthoCamera* s_OrthoCamera;
		static sf::Vector2f s_PrevCameraPos;
	};

} // namespace fz