/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** MonitorCore
*/

#include "MonitorCore.hpp"
#include <algorithm>
#include <unistd.h>

namespace Krell {

    MonitorCore::MonitorCore() : _display(nullptr)
    {
    }

    MonitorCore::~MonitorCore()
    {
        for (IModule* module : _modules)
            delete module;

        delete _display;
    }

    void MonitorCore::setDisplay(IDisplay* display)
    {
        if (_display)
            delete _display;

        _display = display;
    }

    void MonitorCore::addModule(IModule* module)
    {
        _modules.push_back(module);
    }

    void MonitorCore::removeModule(const std::string& name)
    {
        for (auto it = _modules.begin(); it != _modules.end();) {
            if ((*it)->getName() == name) {
                delete *it;
                it = _modules.erase(it);
            } else {
                ++it;
            }
        }
    }

    void MonitorCore::run()
    {
        if (!_display)
            return;

        if (!_display->init())
            return;

        while (_display->isOpen()) {
            _display->handleEvents();
            for (auto module: _modules) {
                module->update();
            }
            _display->clear();
            _display->render(_modules);
            usleep(100000);
        }
        _display->close();
    }
}
