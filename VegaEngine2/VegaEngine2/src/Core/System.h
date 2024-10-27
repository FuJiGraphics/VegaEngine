#pragma once

#include "Core.h"

namespace fz {

	class Window;

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

		inline bool IsOpened() const	{ return this->IsOpen; }
		bool OnWindowClose(WindowCloseEvent e);

	protected:
		bool		IsOpen;
		int			Width;
		int			Height;
		std::string	Title;

	private:
		Shared<Window> m_Window;
	};

	/*
	* @brief 클라이언트에서 재정의하여 시스템을 생성합니다.
	* @return System*: 생성한 시스템의 주소
	*/
	System* CreateSystem();
}
