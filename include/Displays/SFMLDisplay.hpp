/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** SFMLDisplay
*/

#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_

#include "IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Krell
{
    class SFMLDisplay : public IDisplay
    {
    public:
        SFMLDisplay();
        ~SFMLDisplay();

        bool init() override;
        void render(const std::vector<IModule*>& modules) override;
        void handleEvents() override;
        void clear() override;
        void close() override;
        bool isOpen() const override;

    private:
        sf::RenderWindow* _window;
        sf::Font _font;
        bool _running;
    };
}

#endif /* !SFMLDISPLAY_HPP_ */
