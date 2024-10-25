#pragma once

#include "Core.h"

namespace fz {

	class System
	{
	protected:
		// Using
		using Super = fz::System;
		// Delete
		FZ_DELETE_COPY(System)

	public:
		System();
		virtual ~System();

		bool Init();
		bool Release();
		bool Reset();

		void Run();

		inline bool IsOpened() const	{ return this->IsOpen; }

	protected:
		bool	IsOpen;
	};

	/*
	* @brief 클라이언트에서 재정의하여 시스템을 생성합니다.
	* @return System*: 생성한 시스템의 주소
	*/
	System* CreateSystem();
}
