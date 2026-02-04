/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** HostUserModule
*/

#ifndef HOSTUSERMODULE_HPP_
#define HOSTUSERMODULE_HPP_

#include "IModule.hpp"
#include <string>
#include <vector>

namespace Krell
{
    class HostUserModule : public IModule
    {
    public:
        HostUserModule();
        ~HostUserModule() override {};

        std::string getName() const override;
        void update() override;
        std::vector<std::string> getData() const override;

    private:
        std::string _hostname;
        std::string _username;
    };
}

#endif /* !HOSTUSERMODULE_HPP_ */
