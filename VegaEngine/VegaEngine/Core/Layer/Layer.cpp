#include "Core/stdafx.h"
#include "Layer.h"

namespace fz {

    Layer::Layer()
        : m_IsActivate(true)
        , m_Origin(0.0f, 0.0f)
        , m_Pos(0.0f, 0.0f)
        , m_Scale(0.0f, 0.0f)
        , m_Size(0, 0)
    {
        // Empty
    }

    Layer::~Layer()
    {
        // Empty
    }

    void Layer::OnAttach()
    {
        // Empty
    }

    void Layer::OnDetach()
    {
        // Empty
    }

    void Layer::OnEvent(Event& event)
    {
        // Empty
    }

    void Layer::OnUpdate(float dt)
    {
        // Empty
    }

    void Layer::OnDraw(Camera& camera)
    {
        // Empty
    }

    void Layer::OnGui()
    {
        // Empty
    }

    void Layer::OnCollide(const HitData& hit)
    {
        // Empty
    }

} // namespace fz
