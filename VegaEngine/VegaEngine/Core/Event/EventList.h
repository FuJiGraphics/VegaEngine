#pragma once
#include "Core/Core.h"
#include "Event.h"
#include "LayerList.h"

namespace fz {

    class EventList
    {
        using iter = std::vector<Event>::iterator;
        using const_iter = std::vector<Event>::const_iterator;

    public:
        explicit EventList();
        virtual ~EventList();
        
        void        DispatchTo(const LayerArray& layers);
        void        push(const sf::Event& event);
        bool        empty() const;
        int         size() const;
        iter        begin();
        iter        end();

    private:
        std::vector<Event>  m_eventQueue;
    };

} // namespace fz