/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <vector>
#include "IModule.hpp"

namespace Krell
{
    class IDisplay
    {
    public:
        virtual ~IDisplay() {}

        virtual bool init() = 0;
        virtual void render(const std::vector<Krell::IModule*>& modules) = 0;
        virtual void handleEvents() = 0;
        virtual void clear() = 0;
        virtual void close() = 0;
        virtual bool isOpen() const = 0;
    };
}

#endif /* !IDISPLAY_HPP_ */
