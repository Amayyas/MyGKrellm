/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** MonitorCore
*/

#ifndef MONITORCORE_HPP
#define MONITORCORE_HPP

#include <vector>
#include <memory>
#include "IModule.hpp"
#include "IDisplay.hpp"

namespace Krell
{
    class MonitorCore
    {
    public:
        MonitorCore();
        ~MonitorCore();

        void setDisplay(IDisplay* display);

        void addModule(IModule* module);
        void removeModule(const std::string& name);

        void run();

    private:
        std::vector<IModule*> _modules;
        IDisplay* _display;
    };
}

#endif /* !MONITORCORE_HPP_ */
