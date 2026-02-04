/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** CPU_Module
*/

#include "CPU_Module.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <thread>      // Pour hardware_concurrency()
#include <cstdio>      // Pour popen(), pclose()

namespace Krell
{
    CPU_Module::CPU_Module() : _model("Unknown"), _nbCores(0), _cpuUsage(0.0), prevIdle(0), prevTotal(0)
    {
        update();
    }

    std::string CPU_Module::getName() const
    {
        return "CPU Info";
    }

    std::vector<std::string> CPU_Module::getData() const
    {
        std::vector<std::string> lines;

        lines.push_back("Model: " + _model);
        lines.push_back("Cores: " + std::to_string(_nbCores));
        lines.push_back("Usage: " + std::to_string(static_cast<int>(_cpuUsage)) + "%");

        return lines;
    }

    void CPU_Module::update()
    {
        #ifdef __APPLE__
            updateMacOS();
        #elif __linux__
            updateLinux();
        #else
            _model = "Unknown";
            _nbCores = 0;
            _cpuUsage = 0.0;
        #endif
    }

    void CPU_Module::updateMacOS()
    {
        FILE* pipe1 = popen("sysctl -n machdep.cpu.brand_string", "r");
        char buffer1[256];
        if (pipe1 && fgets(buffer1, sizeof(buffer1), pipe1)) {
            _model = buffer1;
            // Remove trailing newline
            if (!_model.empty() && _model.back() == '\n')
                _model.pop_back();
        }
        if (pipe1) pclose(pipe1);

        FILE* pipe2 = popen("sysctl -n hw.ncpu", "r");
        char buffer2[32];
        if (pipe2 && fgets(buffer2, sizeof(buffer2), pipe2)) {
            _nbCores = std::stoi(buffer2);
        }
        if (pipe2) pclose(pipe2);

        FILE* pipe3 = popen("ps -A -o %cpu | awk '{s+=$1} END {print s}'", "r");
        char buffer3[32];
        if (pipe3 && fgets(buffer3, sizeof(buffer3), pipe3)) {
            _cpuUsage = std::stod(buffer3);
        }
        if (pipe3) pclose(pipe3);
    }

    void CPU_Module::updateLinux()
    {
        std::ifstream cpuinfo("/proc/cpuinfo");
        std::string line;
        while (std::getline(cpuinfo, line)) {
            if (line.find("model name") != std::string::npos) {
                size_t pos = line.find(':') + 2;
                _model = line.substr(pos);
                break;
            }
        }
        cpuinfo.close();

        _nbCores = std::thread::hardware_concurrency();

        std::ifstream stat("/proc/stat");
        std::string statLine;
        std::getline(stat, statLine);
        stat.close();

        unsigned long long user, nice, system, idle;
        sscanf(statLine.c_str(), "cpu %llu %llu %llu %llu", &user, &nice, &system, &idle);

        unsigned long long total = user + nice + system + idle;

        unsigned long long totalDiff = total - prevTotal;
        unsigned long long idleDiff = idle - prevIdle;

        if (totalDiff != 0)
            _cpuUsage = 100.0 * (1.0 - (double)idleDiff / totalDiff);
        
        prevTotal = total;
        prevIdle = idle;
    }
}
