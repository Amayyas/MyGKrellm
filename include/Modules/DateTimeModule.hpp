/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** DateTimeModule
*/

#ifndef DATETIMEMODULE_HPP_
#define DATETIMEMODULE_HPP_

#include "IModule.hpp"
#include <string>
#include <vector>

namespace Krell
{
    class DateTimeModule : public IModule
    {
    public:
        DateTimeModule();
        ~DateTimeModule();

        std::string getName() const override;
        void update() override;
        std::vector<std::string> getData() const override;

    private:
        std::string _dateTime;
    };
}

#endif /* !DATETIMEMODULE_HPP_ */
