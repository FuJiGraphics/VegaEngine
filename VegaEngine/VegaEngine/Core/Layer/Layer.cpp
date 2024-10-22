#include "Core/stdafx.h"
#include "Layer.h"
#include "LayerArray.h"
#include "Collider.h"
#include "ColliderManager.h"

namespace fz {

    unsigned int Layer::s_numOfLayers = 0;

    Layer::Layer()
        : m_body(nullptr)
    {
        s_numOfLayers++;
    }

    Layer::~Layer()
    {
        s_numOfLayers--;
        if (m_body)
        {
            auto& colManager = ColliderManager::GetInstance();
            m_body->Activate(false, "", nullptr);
            colManager.Detach(&m_body);
        }
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

    void Layer::OnDraw(sf::RenderTexture& device)
    {
        // Empty
    }

    void Layer::OnUI(sf::RenderTexture& device)
    {
        // Empty
    }

    void Layer::OnImGui()
    {
        // Empty
    }

    void Layer::OnCollide(Layer* pLayer, const std::string& className)
    {
        // Empty
    }

    std::string Layer::GetName() const
    {
        return ("null");
    }

    unsigned int Layer::GetCount()
    {
        return (s_numOfLayers);
    }

    bool Layer::IsActivatedCollider() const
    {
        if (m_body)
            return (m_body->IsActivated());
        else
            return (false);
    }

    void Layer::ActivateCollider(bool flags, const std::string& className)
    {
        if (this->IsActivatedCollider())
            return;

        auto& colManager = ColliderManager::GetInstance();
        if (flags)
        {
            colManager.Attach(&m_body);
            m_body->Activate(flags, className, this);
        }
        else
        {
            m_body->Activate(flags, "", nullptr);
            colManager.Detach(&m_body);
        }
    }

    void Layer::SetCollider(const sf::Vector2f& origin, const sf::FloatRect& rect, const sf::Vector2f& scale)
    {
        sf::FloatRect tRec;
        tRec.left = rect.left + origin.x;
        tRec.top = rect.top + origin.y;
        tRec.width = rect.width;
        tRec.height = rect.height;
        m_body->Set(origin, tRec, scale);
    }

    void Layer::SetColliderDisplayMode(bool enabled)
    {
        m_body->SetDisplay(enabled);
    }

} // namespace fz
