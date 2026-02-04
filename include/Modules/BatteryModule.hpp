/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** BatteryModule
*/

#ifndef BATTERYMODULE_HPP_
#define BATTERYMODULE_HPP_

#include "IModule.hpp"
#include <vector>
#include <string>

namespace Krell
{
    class BatteryModule : public IModule
    {
    public:
        BatteryModule();
        ~BatteryModule();

        std::string getName() const override;
        void update() override;
        std::vector<std::string> getData() const override;

    private:
        int _capacity;
        std::string _status;
        bool _hasBattery;

        void updateMacOS();
        void updateLinux();
    };
}

#endif /* !BATTERYMODULE_HPP_ */
