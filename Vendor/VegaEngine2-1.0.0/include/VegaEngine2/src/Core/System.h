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
	* @brief Ŭ���̾�Ʈ���� �������Ͽ� �ý����� �����մϴ�.
	* @return System*: ������ �ý����� �ּ�
	*/
	System* CreateSystem();
}
