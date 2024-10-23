#include "Core/stdafx.h"
#include "EventList.h"
#include "Event.h"

namespace fz {

	EventList::EventList()
	{
		// Empty
	}

	EventList::~EventList()
	{
		// Empty
	}

	void EventList::push_back(fz::Event& event)
	{
		Super::insert(&event, Section::Right);
	}

	void EventList::pop_front()
	{
		Super::pop_front();
	}

} // namespace fz
