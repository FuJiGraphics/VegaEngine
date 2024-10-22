#pragma once

#include "Core.h"

namespace fz {

    class Event
    {
    public:
        explicit Event(const sf::Event& event);
        explicit Event(const Event& other);
        virtual ~Event();

        sf::Event&   get();
        void         use();
        bool         empty() const;

    private:
        sf::Event    m_event;
        bool         m_used;
    };

} // namespace fz