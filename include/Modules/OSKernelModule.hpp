/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** OSKernelModule
*/

#ifndef OSKERNELMODULE_HPP_
#define OSKERNELMODULE_HPP_

#include "IModule.hpp"
#include <string>
#include <vector>

namespace Krell
{
    class OSKernelModule : public IModule
    {
    public:
        OSKernelModule();
        ~OSKernelModule();

        std::string getName() const override;
        void update() override;
        std::vector<std::string> getData() const override;

    private:
        std::string _os;
        std::string _kernel;
    };
}

#endif /* !OSKERNELMODULE_HPP_ */
