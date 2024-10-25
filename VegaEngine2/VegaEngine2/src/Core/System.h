#pragma once

namespace fz {

	class System
	{
	protected:
		// Using
		using Super = fz::System;

		// Delete
		System(const System&) = delete;
		System& operator=(const System&) = delete;

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
