/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** UptimeModule
*/

#include "UptimeModule.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <ctime>

namespace Krell
{
    UptimeModule::UptimeModule() : _uptimeSeconds(0)
    {
        update();
    }

    UptimeModule::~UptimeModule()
    {
    }

    std::string UptimeModule::getName() const
    {
        return "Uptime";
    }

    void UptimeModule::update()
    {
        #ifdef __APPLE__
            updateMacOS();
        #elif __linux__
            updateLinux();
        #else
            _uptimeSeconds = 0;
            _formattedUptime = "Unknown";
        #endif
    }

    void UptimeModule::updateLinux()
    {
        std::ifstream uptimeFile("/proc/uptime");
        
        if (uptimeFile.is_open()) {
            double uptime;
            uptimeFile >> uptime;
            _uptimeSeconds = static_cast<long>(uptime);
            uptimeFile.close();
        } else {
            _uptimeSeconds = 0;
        }
        
        _formattedUptime = formatUptime(_uptimeSeconds);
    }

    void UptimeModule::updateMacOS()
    {
        FILE* pipe = popen("sysctl -n kern.boottime | awk '{print $4}' | tr -d ','", "r");
        
        if (pipe) {
            char buffer[64];
            if (fgets(buffer, sizeof(buffer), pipe)) {
                long bootTime = std::stol(buffer);
                _uptimeSeconds = std::time(nullptr) - bootTime;
            }
            pclose(pipe);
        } else {
            _uptimeSeconds = 0;
        }
        
        _formattedUptime = formatUptime(_uptimeSeconds);
    }

    std::string UptimeModule::formatUptime(long seconds) const
    {
        long days = seconds / 86400;
        long hours = (seconds % 86400) / 3600;
        long minutes = (seconds % 3600) / 60;
        long secs = seconds % 60;

        std::ostringstream oss;
        
        if (days > 0) {
            oss << days << "d ";
        }
        if (hours > 0 || days > 0) {
            oss << hours << "h ";
        }
        if (minutes > 0 || hours > 0 || days > 0) {
            oss << minutes << "m ";
        }
        oss << secs << "s";

        return oss.str();
    }

    std::vector<std::string> UptimeModule::getData() const
    {
        std::vector<std::string> res;
        res.push_back("System uptime: " + _formattedUptime);
        return res;
    }
}
