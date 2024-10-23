#include "Core/stdafx.h"
#include "Event.h"

namespace fz {

    Event::Event()
        : m_event(sf::Event())
        , m_used(false)
        , m_isEmpty(true)
    {
        // Empty
    }

    Event::Event(const sf::Event& other)
        : m_event(other)
        , m_used(false)
        , m_isEmpty(false)
    {
        // Empty
    }

    Event::Event(const Event& other)
        : m_event(other.m_event)
        , m_used(other.m_used)
        , m_isEmpty(false)
    {
        // Empty
    }


    Event::Event(Event&& other) noexcept
        : m_event(other.m_event)
        , m_used(other.m_used)
        , m_isEmpty(false)
    {
        other.m_event = sf::Event();
        other.m_used = false;
        other.m_isEmpty = true;
    }

    Event::~Event()
    {
        m_event = sf::Event();
        m_used = false;
        m_isEmpty = true;
    }

    Event& Event::operator=(const Event& other)
    {
        m_event = other.m_event;
        m_used = other.m_used;
        m_isEmpty = false;
        return (*this);
    }

    Event& Event::operator=(Event&& other) noexcept
    {
        m_event = other.m_event;
        m_used = other.m_used;
        m_isEmpty = false;
        other.m_event = sf::Event();
        other.m_used = false;
        other.m_isEmpty = true;
        return (*this);
    }

    bool Event::operator==(const Event& other)
    {
        return m_event.type == other.m_event.type;
    }

    bool Event::operator==(const Event&& other)
    {
        return m_event.type == other.m_event.type;
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
        return (m_isEmpty || m_used);
    }

} // namespace fz