#pragma once

#include "Core/Core.h"

namespace sf {
	class Event;
}

namespace fz {

	// Forwards
	class Object;

	class ObjectStack
	{
	protected:
		// Using
		using Super	= fz::ObjectStack;
		using Iter = std::vector<Object*>::iterator;
		using Const_iter = std::vector<Object*>::const_iterator;
		using Reverse_iter = std::vector<Object*>::reverse_iterator;
		using Const_reverse_iter = std::vector<Object*>::const_reverse_iterator;
		// Delete
		FZ_DELETE_COPY(ObjectStack)

	public:
		ObjectStack();
		virtual ~ObjectStack();

		void Release();

		void PushObject(Object* object);
		void PushOverlay(Object* overlay);
		void PopObject(Object* object);
		void PopOverlay(Object* object);

		inline unsigned int size() const			{ return m_Objects.size(); }
		inline bool empty() const					{ return m_Objects.empty(); }

		inline Iter begin()							{ return m_Objects.begin(); }
		inline Iter end()							{ return m_Objects.end(); }
		inline Reverse_iter rbegin()				{ return m_Objects.rbegin(); }
		inline Reverse_iter rend()					{ return m_Objects.rend(); }

		inline Const_iter begin() const				{ return m_Objects.begin(); }
		inline Const_iter end() const				{ return m_Objects.end(); }
		inline Const_reverse_iter rbegin() const	{ return m_Objects.rbegin(); }
		inline Const_reverse_iter rend() const		{ return m_Objects.rend(); }

	private:
		std::vector<Object*>	m_Objects;
		unsigned int			m_InsertIndex;
	};
} // namespace fz