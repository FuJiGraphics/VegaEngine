#include "Core/stdafx.h"
#include "Anim.h"

namespace fz {
    Anim::Anim()
        : m_Frames()
        , m_TotalLength(0.0)
        , m_TotalProgress(0.0)
        , m_Target(nullptr)
        , Activated(false)
        , Repeat(false)
    {
        // Empty
    }

    Anim::Anim(sf::Sprite& sprite)
        : m_Frames()
        , m_TotalLength(0.0)
        , m_TotalProgress(0.0)
        , m_Target(&sprite)
        , Activated(false)
        , Repeat(false)
    {
        // Empty
    }

    Anim::~Anim()
    {
        // Empty
    }

    void Anim::AddFrame(const Frame& frame)
    {
        if (m_Target == nullptr)
            return;

        m_Frames.push_back(std::move(frame));
        m_TotalLength += frame.Duration;
    }

    void Anim::Update(double elapsed)
    {
        m_TotalProgress += elapsed;

        double progress = m_TotalProgress;
        for (const auto& frame : m_Frames)
        {
            progress -= (frame).Duration;
            if (progress <= 0.0)
            {
                m_Target->setTextureRect((frame).Rect);
                break;
            }
            else if (&(frame) == &m_Frames.back())
            {
                if (Repeat || Activated)
                    this->Reset();
                else
                    m_Target->setTextureRect(m_Frames.front().Rect);
            }
        }
    }

    void Anim::Reset()
    {
        m_TotalProgress = 0.0;
    }

    void Anim::Draw(Camera& camera)
    {
        camera.draw(*m_Target);
    }

} // namespace fz
