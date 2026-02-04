/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <string>
#include <vector>

namespace Krell
{
    class IModule
    {
    public:
        virtual ~IModule() {}

        virtual std::string getName() const = 0;
        virtual void update() = 0;
        virtual std::vector<std::string> getData() const = 0;
    };
}

#endif /* !IMODULE_HPP_ */
