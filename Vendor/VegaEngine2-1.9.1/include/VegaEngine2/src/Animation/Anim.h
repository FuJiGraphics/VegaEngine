#pragma once
#include <memory>

namespace fz {

    struct Frame
    {
        sf::IntRect Rect;
        double Duration;
    };

    class Anim
    {
    public:
        bool Activated;
        bool Repeat;

    public:
        Anim(const std::string& name = "Anim");
        virtual ~Anim();
        void AddFrame(const Frame& frame);
        
        void SetSprite(sf::Sprite* sprite);
        void SetName(const std::string& name);
        void SetPosition(const sf::Vector2f& pos);
        void SetScale(const sf::Vector2f& scale);
        void SetScale(float scaleX, float scaleY);
        void SetFlipX(bool enabled);
        void SetFlipY(bool enabled);

        std::string GetName() const;
        sf::Vector2f GetPosition() const;
        sf::Vector2f GetScale() const;
        bool IsFlipX() const;
        bool IsFlipY() const;
        bool IsFrameEnd() const;

        void AddAnimSequence(const sf::IntRect& rect, int stride, const std::vector<double>& durations, int count);
        void AddAnimSequenceRev(const sf::IntRect& rect, int stride, const std::vector<double>& durations, int count);
        void AddAnimSequence(const sf::IntRect& rect, int stride, double duration, int count);
        void AddAnimSequenceRev(const sf::IntRect& rect, int stride, double duration, int count);

        void SetAnimSequence(const sf::IntRect& rect, int stride, const std::vector<double>& durations, int count);
        void SetAnimSequenceRev(const sf::IntRect& rect, int stride, const std::vector<double>& durations, int count);
        void SetAnimSequence(const sf::IntRect& rect, int stride, double duration, int count);
        void SetAnimSequenceRev(const sf::IntRect& rect, int stride, double duration, int count);

        void Update(float dt);
        void Reset();
        void Draw(sf::RenderWindow& window);
        void ClearSequence();

    private:
        std::string                     m_Name;
        sf::Sprite*                     m_Sprite;
        sf::Texture*                    m_Texture;
        std::vector<Frame>              m_Frames;
        bool                            m_Flips[2];
        float                           m_Scale[2];
        double                          m_TotalLength;
        double                          m_TotalProgress;
        bool                            m_IsEnd;
    };

} // namespace fz