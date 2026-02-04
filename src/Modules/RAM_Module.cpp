/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** RAM_Module
*/

#include "RAM_Module.hpp"
#include <fstream>
#include <string>
#include <sstream>

namespace Krell
{
    RAM_Module::RAM_Module() : _total(0), _used(0), _free(0)
    {
    }

    RAM_Module::~RAM_Module()
    {
    }

    std::string RAM_Module::getName() const
    {
        return "RAM";
    }

    void RAM_Module::update()
    {
        #ifdef __APPLE__
            updateMacOS();
        #elif __linux__
            updateLinux();
        #else
            _total = 0;
            _used = 0;
            _free = 0;
        #endif
    }

    void RAM_Module::updateMacOS()
    {
        FILE* pipe = popen("sysctl -n hw.memsize", "r");
        if (pipe) {
            char buffer[64];
            fgets(buffer, sizeof(buffer), pipe);
            _total = std::stoll(buffer) / (1024 * 1024);
            pclose(pipe);
        }

        pipe = popen("ps -caxm -orss= | awk '{sum+=$1} END {print sum}'", "r");
        if (pipe) {
            char buffer[64];
            fgets(buffer, sizeof(buffer), pipe);
            _used = std::stol(buffer) / 1024;
            pclose(pipe);
        }
        _free = _total - _used;
    }

    void RAM_Module::updateLinux()
    {
        std::ifstream meminfo("/proc/meminfo");
        std::string line;
        long memTotal = 0, memFree = 0, buffers = 0, cached = 0;

        while (std::getline(meminfo, line)) {
            std::istringstream iss(line);
            std::string key;
            long value;
            std::string unit;
            iss >> key >> value >> unit;

            if (key == "MemTotal:")
                memTotal = value;
            else if (key == "MemFree:")
                memFree = value;
            else if (key == "Buffers:")
                buffers = value;
            else if (key == "Cached:")
                cached = value;
        }

        _total = memTotal / 1024;
        _free = (memFree + buffers + cached) / 1024;
        _used = _total - _free;
    }

    std::vector<std::string> RAM_Module::getData() const
    {
        std::vector<std::string> res;
        res.push_back("Total: " + std::to_string(_total) + " MB");
        res.push_back("Used: " + std::to_string(_used) + " MB");
        res.push_back("Free: " + std::to_string(_free) + " MB");
        return res;
    }
}
