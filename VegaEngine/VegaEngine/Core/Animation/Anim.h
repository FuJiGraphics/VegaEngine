#pragma once

#include "Core/Core.h"

namespace fz {

    class Camera;

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
        Anim();
        Anim(sf::Sprite& target);
        virtual ~Anim();
        void AddFrame(const Frame& frame);
        void Update(double elapsed);
        void Reset();
        void Draw(Camera& camera);

        // TODO: юс╫ц
        inline sf::Sprite* GetSprite() { return m_Target; }
        inline sf::Sprite* GetSprite() const { return m_Target; }

    private:
        std::vector<Frame> m_Frames;
        double m_TotalLength;
        double m_TotalProgress;
        sf::Sprite* m_Target;
    };

    /*
    sf::Sprite myCharacter;
    // Load the image...
    // do this for as many frames as you need

    // In your main loop:
    animation.update(elapsed);
    window.draw(myCharacter);
    */

} // namespace fz