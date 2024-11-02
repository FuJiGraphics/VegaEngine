#pragma once

namespace fz {
	
	class CameraController;
	class OrthoCamera;
	class Window;

	class Renderer2D
	{
	public:
		static void Init(sf::RenderWindow* renderWindow);
		static void Release();
		static void Reset();

		static void BeginScene(CameraController* camera);
		static void EndScene();

		static void Draw(const sf::Drawable& target);
		
	private:
		static sf::RenderWindow* s_RenderWindow;
		static fz::CameraController* s_RenderCamera;
	};

} // namespace fz