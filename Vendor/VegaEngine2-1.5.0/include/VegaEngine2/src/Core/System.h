#pragma once

#include "Core.h"

namespace fz {

	class Window;
	class LayerStack;
	class LayerPool;

	class System
	{
	protected:
		// Using
		using Super = fz::System;
		// Delete
		FZ_DELETE_COPY(System)

	public:
		System(int width, int height, const std::string& title);
		virtual ~System();

		bool Init();
		bool Release();
		bool Reset();

		void Run();
		void OnEvent(fz::Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		bool OnWindowClose(WindowCloseEvent e);
		bool OnWindowResize(WindowResizeEvent e);

		inline bool IsOpened() const	{ return this->IsOpen; }

	private:
		bool GenerateWindow();
		bool GenerateLayerStack();
		bool ReleaseLayerStack();

	protected:
		bool				IsInit;
		bool				IsOpen;
		int					Width;
		int					Height;
		std::string			Title;
		Shared<LayerPool>	LayerGenerator;

	private:
		Shared<Window>			m_Window;
		Shared<LayerStack>		m_LayerStack;
		Shared<RenderContext>	m_RenderContext;
	};

	/*
	* @brief 클라이언트에서 재정의하여 시스템을 생성합니다.
	* @return System*: 생성한 시스템의 주소
	*/
	System* CreateSystem();
}
