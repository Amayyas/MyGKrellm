/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** OSKernelModule
*/

#include "OSKernelModule.hpp"
#include <fstream>
#include <sstream>
#include <sys/utsname.h>

namespace Krell
{

    OSKernelModule::OSKernelModule()
    {
        update();
    }

    OSKernelModule::~OSKernelModule()
    {
    }

    std::string OSKernelModule::getName() const
    {
        return "OS & Kernel info";
    }

    void OSKernelModule::update()
    {
        struct utsname info;
        uname(&info);
        _kernel = info.release;
    
        std::ifstream file("/etc/os-release");
        if(file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (line.find("PRETTY_NAME=") == 0) {
                    size_t start = line.find('"') + 1;
                    size_t end = line.rfind('"');
                    _os = line.substr(start, end - start);
                    break;
                }
            }
            file.close();
        } else {
            _os = std::string(info.sysname);
            if (_os == "Darwin")
                _os = "macOS";
            }
        }

    std::vector<std::string> OSKernelModule::getData() const
    {
        std::vector<std::string> lines;

        lines.push_back("OS: " + _os);
        lines.push_back("Kernel: " + _kernel);
    
        return lines;
    }
}
