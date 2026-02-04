/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** NcursesDisplay
*/

#ifndef NCURSESDISPLAY_HPP_
#define NCURSESDISPLAY_HPP_

#include "IDisplay.hpp"
#include <ncurses.h>

namespace Krell
{
    class NcursesDisplay : public IDisplay
    {
    public:
        NcursesDisplay();
        ~NcursesDisplay();

        bool init() override;
        void render(const std::vector<IModule*>& modules) override;
        void handleEvents() override;
        void clear() override;
        void close() override;
        bool isOpen() const override;

    private:
        bool _running;
    };
}

#endif /* !NCURSESDISPLAY_HPP_ */
