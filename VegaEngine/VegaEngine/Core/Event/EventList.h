#pragma once
#include "Core/Core.h"
#include "Core/Array.h"
#include "Event.h"

namespace fz {

    class EventList final : public Array<Event>
    {
    //// Delete, Enum, Using
    protected:
        // Delete
        EventList(const EventList&) = delete;
        void operator=(const EventList&) = delete;

    //// Member Functions
    public:
        // Constructor, Destructor
        EventList();
        virtual ~EventList();

        // Impl
        void push_back(const Event& event);
        Event pop_front();
    };

} // namespace fz