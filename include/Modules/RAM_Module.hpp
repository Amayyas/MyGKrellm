/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** RAM_Module
*/

#ifndef RAM_MODULE_HPP_
#define RAM_MODULE_HPP_

#include "IModule.hpp"
#include <vector>
#include <string>

namespace Krell
{
    class RAM_Module : public IModule
    {
    public:
        RAM_Module();
        ~RAM_Module();

        std::string getName() const override;
        void update() override;
        std::vector<std::string> getData() const override;

    private:
        long _total;
        long _used;
        long _free;

        void updateMacOS();
        void updateLinux();
    };
}

#endif /* !RAM_MODULE_HPP_ */
