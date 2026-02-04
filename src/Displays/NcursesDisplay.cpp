/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** NcursesDisplay
*/

#include "NcursesDisplay.hpp"

namespace Krell
{
    NcursesDisplay::NcursesDisplay() : _running(true)
    {
    }

    NcursesDisplay::~NcursesDisplay()
    {
        close();
    }

    bool NcursesDisplay::init()
    {
        initscr();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        return true;
    }

    void NcursesDisplay::clear()
    {
        ::clear();
    }

    void NcursesDisplay::close()
    {
        endwin();
    }

    void NcursesDisplay::handleEvents()
    {
        int ch = getch();
    
        if (ch == 'q')
            _running = false;
    }

    void NcursesDisplay::render(const std::vector<IModule*>& modules)
    {
        clear();
        int y = 1;

        for (IModule* module : modules) {
            mvprintw(y++, 2, "[ %s ]", module->getName().c_str());

            for (const std::string& line : module->getData())
                mvprintw(y++, 4, "%s", line.c_str());
            y++;
        }

        mvprintw(LINES - 2, 2, "Press 'q' to quit");
        refresh();
    }

    bool NcursesDisplay::isOpen() const
    {
        return _running;
    }
}