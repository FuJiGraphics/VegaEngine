#include "Core/stdafx.h"
#include "Event.h"

namespace fz {

    Event::Event(const sf::Event& event)
        : m_event(event)
        , m_used(false)
    {
        // Empty
    }

    Event::Event(const Event& other)
        : m_event(other.m_event)
        , m_used(other.m_used)
    {
        // Empty
    }

    Event::~Event()
    {
        // Empty
    }

    sf::Event& Event::get()
    {
        return (m_event);
    }

    void Event::use()
    {
        m_used = true;
    }

    bool Event::empty() const
    {
        return (m_used);
    }

} // namespace fz