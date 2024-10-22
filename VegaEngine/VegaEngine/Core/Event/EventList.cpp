#include "Core/stdafx.h"
#include "EventList.h"

namespace fz {

	EventList::EventList()
	{
		// Empty
	}

	EventList::~EventList()
	{
		// Empty
	}

	void EventList::push_back(const Event& event)
	{
		Super::insert(event, Section::Right);
	}

	Event EventList::pop_front()
	{
		Event ev = (*Super::begin());
		Super::remove(ev, Section::Right);
		return ev;
	}

} // namespace fz
