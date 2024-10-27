#include "pch.h"
#include "ObjectStack.h"

namespace fz {

	ObjectStack::ObjectStack()
		: m_Objects()
		, m_InsertIndex(0)
	{
		// Empty
	}

	ObjectStack::~ObjectStack()
	{
		for (Object* obj : m_Objects)
		{
			obj->OnDetach();
			delete obj;
			obj = nullptr;
		}
	}

	void ObjectStack::Release()
	{
		if (m_Objects.empty())
			return;

		for (Object* obj : m_Objects)
		{
			if (obj != nullptr)
			{
				obj->OnDetach();
				delete obj;
				obj = nullptr;
			}
		}
		m_Objects.clear();
	}

	void ObjectStack::PushObject(Object* object)
	{
		m_Objects.emplace(m_Objects.begin() + m_InsertIndex, object);
		m_InsertIndex++;
		object->OnAttach();
	}

	void ObjectStack::PushOverlay(Object* overlay)
	{
		m_Objects.emplace_back(overlay);
		overlay->OnAttach();
	}

	void ObjectStack::PopObject(Object* object)
	{
		auto it = std::find(m_Objects.begin(), m_Objects.begin() + m_InsertIndex, object);
		if (it != m_Objects.begin() + m_InsertIndex)
		{
			object->OnDetach();
			m_Objects.erase(it);
			m_InsertIndex--;
		}
	}

	void ObjectStack::PopOverlay(Object* overlay)
	{
		auto it = std::find(m_Objects.begin() + m_InsertIndex, m_Objects.end(), overlay);
		if (it != m_Objects.end())
		{
			overlay->OnDetach();
			m_Objects.erase(it);
		}
	}

} // namespace fz