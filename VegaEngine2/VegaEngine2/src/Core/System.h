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
	* @brief Ŭ���̾�Ʈ���� �������Ͽ� �ý����� �����մϴ�.
	* @return System*: ������ �ý����� �ּ�
	*/
	System* CreateSystem();
}
