#pragma once
#include "Core/Window/Window.h"

// forwards
namespace sf {
	class Window;
	struct ContextSettings;
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

		void Init() override;
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

		void SetContext(unsigned int depthBits, unsigned int stencilBits, unsigned int antialiaslevel) override;
		void SetVSync(bool enabled) override; 
		void SetEventCallback(const EventCallbackFn& callback) override;

	protected:
		Unique<sf::RenderWindow>		m_Window;
		Shared<RenderContext>			m_Context;
		sf::ContextSettings				m_ContextSetting;
		fz::WindowMode					m_Mode;
		EventCallbackFn					m_CallbackFn;
		bool							m_IsVSync;
	};

} // namespace fz