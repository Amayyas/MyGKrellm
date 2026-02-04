/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** SFMLDisplay
*/

#include "SFMLDisplay.hpp"
#include <sstream>
#include <iostream>
#include <cstdint>

namespace Krell
{
    SFMLDisplay::SFMLDisplay() : _window(nullptr), _running(true)
    {
    }

    SFMLDisplay::~SFMLDisplay()
    {
        close();
        if (_window) {
            delete _window;
            _window = nullptr;
        }
    }

    bool SFMLDisplay::init()
    {
        _window = new sf::RenderWindow(sf::VideoMode({800u, 950u}), "MyGKrellm - System Monitor");
        _window->setFramerateLimit(60);
        
        bool fontLoaded = false;
        
        if (_font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
            fontLoaded = true;
        else if (_font.openFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"))
            fontLoaded = true;
        else if (_font.openFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf"))
            fontLoaded = true;
        else if (_font.openFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf"))
            fontLoaded = true;
        else if (_font.openFromFile("/System/Library/Fonts/Helvetica.ttc"))
            fontLoaded = true;
        
        if (!fontLoaded) {
            std::cerr << "Error: Cannot load font!" << std::endl;
            return false;
        }
        
        return true;
    }

    void SFMLDisplay::handleEvents()
    {
        while (auto event = _window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                _running = false;
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    _running = false;
            }
        }
    }

    void SFMLDisplay::clear()
    {
        if (_window)
            _window->clear(sf::Color(30, 30, 30));
    }

    void SFMLDisplay::close()
    {
        if (_window && _window->isOpen())
            _window->close();
    }

    void SFMLDisplay::render(const std::vector<IModule*>& modules)
    {
        handleEvents();
        clear();
        
        float y = 20.0f;
        
        for (const auto& module : modules) {
            
            std::vector<std::string> lines = module->getData();
            float moduleHeight = 35.0f + (lines.size() * 25.0f) + 20.0f;
            
            sf::RectangleShape background(sf::Vector2f(760.0f, moduleHeight));
            background.setPosition(sf::Vector2f(20.0f, y));
            background.setFillColor(sf::Color(50, 50, 50, 200));
            background.setOutlineThickness(2.0f);
            background.setOutlineColor(sf::Color(100, 100, 100));
            _window->draw(background);
            
            sf::Text title(_font);
            title.setString(module->getName());
            title.setCharacterSize(24);
            title.setFillColor(sf::Color(255, 200, 0));
            title.setStyle(sf::Text::Bold);
            title.setPosition(sf::Vector2f(30.0f, y + 10.0f));
            _window->draw(title);
            
            float dataY = y + 45.0f;
            
            for (const auto& line : lines) {
                sf::Text text(_font);
                text.setString(line);
                text.setCharacterSize(16);
                text.setFillColor(sf::Color(220, 220, 220));
                text.setPosition(sf::Vector2f(40.0f, dataY));
                _window->draw(text);
                
                dataY += 25.0f;
            }
            y += moduleHeight + 15.0f;
        }
        _window->display();
    }

    bool SFMLDisplay::isOpen() const
    {
        return _running && _window && _window->isOpen();
    }
}