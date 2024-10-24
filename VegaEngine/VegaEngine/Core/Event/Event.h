#pragma once

#include "Core/Core.h"

namespace fz {

    class Event final
    {
    //// Delete, Enum, Using
    protected:
        // Using
        using Super = Event;

    //// Member Functions
    public:
        // Constructor, Destructor
        Event();
        Event(const sf::Event& other);
        Event(const Event& other);
        Event(Event&& other) noexcept;
        virtual ~Event();

        // operator
        Event& operator=(const Event& other);
        Event& operator=(Event&& other) noexcept;
        bool operator==(const Event& other);
        bool operator==(const Event&& other);

        // Impl
        sf::Event&   get();
        void         use();
        bool         empty() const;

    //// Member Variables
    private:
        sf::Event m_event;
        bool m_used;
        bool m_isEmpty;
    };

} // namespace fz