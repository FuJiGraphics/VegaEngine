#pragma once

#include "Core/Core.h"

namespace fz {
    struct Frame 
    {
        sf::IntRect rect;
        double duration;
    };

    class Animation
    {
        std::vector<Frame> frames;
        double totalLength;
        double totalProgress;
        sf::Sprite* target;
    public:
        Animation(sf::Sprite& target)
        {
            this->target = &target;
            totalProgress = 0.0;
        }

        void addFrame(Frame& frame)
        {
            frames.push_back(std::move(frame));
            totalLength += frame.duration;
        }

        void update(double elapsed)
        {
            totalProgress += elapsed;

            double progress = totalProgress;
            for (auto frame : frames)
            {
                progress -= (frame).duration;
                if (progress <= 0.0 || &(frame) == &frames.back())
                {
                    target->setTextureRect((frame).rect);
                    break;
                }
            }
        };
    };

    /*
    sf::Sprite myCharacter;
    // Load the image...
    Animation animation(myCharacter);
    animation.addFrame({sf::IntRect(x,y,w,h), 0.1});
    // do this for as many frames as you need

    // In your main loop:
    animation.update(elapsed);
    window.draw(myCharacter);
    */

} // namespace fz