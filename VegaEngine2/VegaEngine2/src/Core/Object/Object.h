#pragma once

#include "Core/Core.h"

namespace fz {

	class Object
	{
	protected:
		// Using
		using Super = fz::Object;
		// Delete
		FZ_DELETE_COPY(Object)

	public:
		Object(const std::string& name);
		virtual ~Object();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(fz::Event& ev) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string	m_DebugName;
	};

} // namespace fz