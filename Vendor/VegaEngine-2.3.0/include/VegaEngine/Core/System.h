#pragma once
#include "Core.h"
#include "Event.h"
#include "Layer.h"

namespace fz {
	namespace _internal {
		class App;
	}
	class Window;
	class LayerArray;

	struct WindowInfo
	{
		int			Width;
		int			Height;
		std::string	Title;
	};

	class System
	{
		friend _internal::App;

	public:
		static System&		GetInstance();
		static void			AttachLayer(Layer* pLayer);
		static void			AttachOverlay(Layer* pOverlay);
		static void			DetachLayer(Layer* ppLayer);
		static void			DetachOverlay(Layer* ppOverlay);
		static Layer*		FindLayer(const std::string& className);
		static void			SetPause(bool enabled);
		static void			SetReset(bool enabled);
		static bool			IsReset();
		static bool			IsPaused();
		static void			ExitProgram();

		int					GetWidth();
		int					GetHeight();

	protected:
		System();
		virtual ~System();

		void	Init(const WindowInfo& info);
		void	Run();
		void	Reset();

	private:
		void	ReleaseWindow();
		void	CreateLayerArray();
		void	ReleaseLayerArray();

	private:
		Window*				m_window;
		int					m_width;
		int					m_height;
		LayerArray*			m_layerArray;
		bool				m_isPause;
		bool				m_isPlaying;
		bool				m_isReset;
		sf::RenderTexture	m_RenderTarget;
		static float		s_timeScale;
	};

	WindowInfo	CreateApplication();
	void		Runtime();

} // namespace fz