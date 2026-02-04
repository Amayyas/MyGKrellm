/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** BatteryModule
*/

#include "BatteryModule.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstdio>

namespace Krell
{
    BatteryModule::BatteryModule() : _capacity(0), _status("Unknown"), _hasBattery(false)
    {
        #ifdef __APPLE__
            FILE* pipe = popen("pmset -g batt | grep -q 'Battery'", "r");
            if (pipe) {
                int result = pclose(pipe);
                _hasBattery = (result == 0);
            }
        #else
            std::string batteryPath = "/sys/class/power_supply/BAT0";
            if (!std::filesystem::exists(batteryPath))
                batteryPath = "/sys/class/power_supply/BAT1";

            _hasBattery = std::filesystem::exists(batteryPath);
        #endif
    }

    BatteryModule::~BatteryModule()
    {
    }

    std::string BatteryModule::getName() const
    {
        return "Battery";
    }

    void BatteryModule::update()
    {
        if (!_hasBattery) {
            _capacity = 0;
            _status = "No battery";
            return;
        }

        #ifdef __APPLE__
            updateMacOS();
        #else
            updateLinux();
        #endif
    }

    void BatteryModule::updateMacOS()
    {
        FILE* pipe = popen("pmset -g batt | grep -Eo '[0-9]+%' | head -1 | tr -d '%'", "r");
        if (pipe) {
            char buffer[16];
            if (fgets(buffer, sizeof(buffer), pipe)) {
                _capacity = std::stoi(buffer);
            }
            pclose(pipe);
        }

        pipe = popen("pmset -g batt | grep -o 'charging\\|discharging\\|charged\\|AC Power'", "r");
        if (pipe) {
            char buffer[64];
            if (fgets(buffer, sizeof(buffer), pipe)) {
                std::string status(buffer);
                if (!status.empty() && status.back() == '\n')
                    status.pop_back();

                if (status == "charging")
                    _status = "Charging";
                else if (status == "discharging")
                    _status = "Discharging";
                else if (status == "charged")
                    _status = "Charged";
                else if (status == "AC Power")
                    _status = "AC Power";
                else
                    _status = status;
            }
            pclose(pipe);
        }
    }

    void BatteryModule::updateLinux()
    {
        std::string batteryPath = "/sys/class/power_supply/BAT0";
        if (!std::filesystem::exists(batteryPath + "/capacity"))
            batteryPath = "/sys/class/power_supply/BAT1";

        std::ifstream capacityFile(batteryPath + "/capacity");
        if (capacityFile.is_open()) {
            capacityFile >> _capacity;
            capacityFile.close();
        }

        std::ifstream statusFile(batteryPath + "/status");
        if (statusFile.is_open()) {
            std::getline(statusFile, _status);
            statusFile.close();
        }
    }

    std::vector<std::string> BatteryModule::getData() const
    {
        std::vector<std::string> res;

        if (!_hasBattery) {
            res.push_back("No battery detected");
            return res;
        }

        std::string bar = "[";
        int filled = _capacity / 10;
        for (int i = 0; i < 10; i++) {
            if (i < filled)
                bar += "=";
            else
                bar += " ";
        }
        bar += "]";

        res.push_back("Level: " + std::to_string(_capacity) + "% " + bar);
        res.push_back("Status: " + _status);

        return res;
    }
}
