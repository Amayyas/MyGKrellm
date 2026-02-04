/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** HostUserModule
*/

#include "HostUserModule.hpp"
#include <cstdlib>
#include <unistd.h>
#include <limits.h>

namespace Krell
{
    HostUserModule::HostUserModule()
    {
        update();
    }

    void HostUserModule::update()
    {
        const char* user = std::getenv("USER");
        if (user != nullptr) {
            _username = user;
        } else {
            _username = "unknown";
        }

        char buffer[256];
        int result = gethostname(buffer, sizeof(buffer));
        if (result == 0) {
            _hostname = buffer;
        } else {
            _hostname = "unknown";
        }
    }

    std::string HostUserModule::getName() const
    {
        return "Host & User Info";
    }

    std::vector<std::string> HostUserModule::getData() const
    {
        std::vector<std::string> lines;

        lines.push_back("User: " + _username);
        lines.push_back("Host: " + _hostname);

        return lines;
    }
}
