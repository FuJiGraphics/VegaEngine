#include "Core/stdafx.h"
#include "EventQueue.h"

namespace fz {

    EventQueue::EventQueue()
        : m_eventQueue()
    {
        // Empty
    }

    EventQueue::~EventQueue()
    {
        // Empty
    }

    void EventQueue::DispatchTo(const LayerArray& layers)
    {
        for (auto& event : m_eventQueue)
        {
            for (auto& layer : layers)
            {
                if (!event.empty())
                    layer->OnEvent(event);
                else
                    break;
            }
        }
    }

    void EventQueue::push(const sf::Event& event)
    {
        m_eventQueue.push_back(Event(event));
    }

    bool EventQueue::empty() const
    {
        return (m_eventQueue.empty());
    }

    int EventQueue::size() const
    {
        return (static_cast<int>(m_eventQueue.size()));
    }

    EventQueue::iter EventQueue::begin()
    {
        return (m_eventQueue.begin());
    }

    EventQueue::iter EventQueue::end()
    {
        return (m_eventQueue.end());
    }

} // namespace fz
