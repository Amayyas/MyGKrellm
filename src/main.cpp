/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** main
*/

#include "MonitorCore.hpp"
#include "NcursesDisplay.hpp"
#include "SFMLDisplay.hpp"
#include "HostUserModule.hpp"
#include "OSKernelModule.hpp"
#include "DateTimeModule.hpp"
#include "CPU_Module.hpp"
#include "RAM_Module.hpp"
#include "BatteryModule.hpp"
#include "UptimeModule.hpp"
#include <iostream>
#include <cstring>

static void printUsage(const char* progName)
{
    std::cout << "USAGE: " << progName << " [OPTIONS]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  -h, --help         Display this help message" << std::endl;
    std::cout << "  -g, --graphical    Use SFML graphical display (required)" << std::endl;
    std::cout << "  -t, --text         Use ncurses text display (required)" << std::endl;
    std::cout << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "  MyGKrellm is a system monitor inspired by GKrellM (GNU Krell Monitor)" << std::endl;
    std::cout << "  that displays various system information in real-time." << std::endl;
    std::cout << std::endl;
    std::cout << "  You MUST specify either -g (graphical) or -t (text) mode to run." << std::endl;
    std::cout << std::endl;
    std::cout << "CONTROLS:" << std::endl;
    std::cout << "  In text mode:      Press 'q' to quit" << std::endl;
    std::cout << "  In graphical mode: Close the window to quit" << std::endl;
}

int main(int argc, char* argv[])
{
    bool useGraphical = false;
    bool modeSpecified = false;

    // Si aucun argument n'est donné, afficher l'aide et retourner 84
    if (argc == 1) {
        printUsage(argv[0]);
        return 84;
    }

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        }
        if (std::strcmp(argv[i], "-g") == 0 || std::strcmp(argv[i], "--graphical") == 0) {
            useGraphical = true;
            modeSpecified = true;
        }
        if (std::strcmp(argv[i], "-t") == 0 || std::strcmp(argv[i], "--text") == 0) {
            useGraphical = false;
            modeSpecified = true;
        }
    }

    // Si ni -g ni -t n'a été spécifié, afficher l'aide et retourner 84
    if (!modeSpecified) {
        std::cerr << "Error: You must specify -g (graphical) or -t (text) mode." << std::endl;
        std::cerr << std::endl;
        printUsage(argv[0]);
        return 84;
    }

    Krell::MonitorCore core;

    Krell::IDisplay* display = nullptr;

    if (useGraphical) {
        display = new Krell::SFMLDisplay();
        std::cout << "Mode: Graphical (SFML)" << std::endl;
    } else {
        display = new Krell::NcursesDisplay();
        std::cout << "Mode: Text (NCurses)" << std::endl;
    }

    core.setDisplay(display);

    core.addModule(new Krell::HostUserModule());
    core.addModule(new Krell::OSKernelModule());
    core.addModule(new Krell::DateTimeModule());
    core.addModule(new Krell::CPU_Module());
    core.addModule(new Krell::RAM_Module());
    core.addModule(new Krell::BatteryModule());
    core.addModule(new Krell::UptimeModule());

    core.run();

    return 0;
}