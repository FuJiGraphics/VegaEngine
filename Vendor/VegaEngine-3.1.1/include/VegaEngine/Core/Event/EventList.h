#pragma once
#include "Core/Core.h"
#include "Core/Array.h"

namespace fz {

    class Event;

    class EventList final : public Array<fz::Event*>
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
        void push_back(fz::Event& event);
        void pop_front();
    };

} // namespace fz