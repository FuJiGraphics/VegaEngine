#pragma once
#include "Core.h"

namespace fz {

	class System
	{	
	//// Delete, Enum, Using
	protected:
		// Delete
		System(const System&) = delete;
		System& operator=(const System&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		System();
		virtual ~System();

		// Impl
		void Create(int width, int height, const std::string& title);
		void Release();
		void Run();

	//// Member Variables
	private:
		Window* m_Window;
		bool m_IsPause;
		float m_TimeScale;
	};

} // namespace fz