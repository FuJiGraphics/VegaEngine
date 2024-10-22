#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace fz {

    class EventList
    {
    //// Delete, Enum, Using
    protected:
        EventList(EventList&) = delete;
        void operator=(EventList&) = delete;

    public:
        EventList();
        virtual ~EventList();
        
        void        push(const sf::Event& event);
        bool        empty() const;
        int         size() const;
        iter        begin();
        iter        end();

    private:
        std::vector<Event>  m_eventQueue;
    };

} // namespace fz