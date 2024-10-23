#pragma once
#include "Core.h"
#include "Scene/SceneList.h"

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

		// Inlines
		inline bool IsClosed() const			{ return m_IsClosed; }

	//// Member Variables
	private:
		Window* m_Window;
		bool m_IsPause;
		bool m_IsClosed;
		float m_TimeScale;
	};

} // namespace fz