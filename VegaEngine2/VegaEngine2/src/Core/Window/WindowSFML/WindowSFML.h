#pragma once
#include "Core/Window/Window.h"

// forwards
namespace sf {
	class Window;
}

namespace fz {

	class WindowSFML : public Window
	{
	protected:
		WindowSFML(WindowSFML&) = delete;
		WindowSFML& operator=(WindowSFML&) = delete;

	public:
		WindowSFML(const fz::WindowMode& mode);
		virtual ~WindowSFML();

		void Init(bool isActiveOpenGL = true) override;
		void Release() override;

		void OnEvent() override;
		void OnUpdate() override;

		int GetWidth() const override;
		int GetHeight() const override;
		std::string GetTitle() const override;
		void* GetNativeWindow() const override;
		bool IsFocus() const override;
		bool IsVSync() const override;
		bool IsOpen() const override;

		void SetVSync(bool enabled) override; 
		void SetEventCallback(const EventCallbackFn& callback) override;

	protected:
		std::unique_ptr<sf::RenderWindow>	m_Window;
		fz::WindowMode						m_Mode;
		bool								m_IsVSync;
		EventCallbackFn						m_CallbackFn;
	};

} // namespace fz