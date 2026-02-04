/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** UptimeModule
*/

#ifndef UPTIMEMODULE_HPP_
#define UPTIMEMODULE_HPP_

#include "IModule.hpp"
#include <vector>
#include <string>

namespace Krell
{
    class UptimeModule : public IModule
    {
    public:
        UptimeModule();
        ~UptimeModule();

        std::string getName() const override;
        void update() override;
        std::vector<std::string> getData() const override;

    private:
        long _uptimeSeconds;
        std::string _formattedUptime;

        void updateLinux();
        void updateMacOS();
        std::string formatUptime(long seconds) const;
    };
}

#endif /* !UPTIMEMODULE_HPP_ */
