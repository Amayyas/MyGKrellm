/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** DateTimeModule
*/

#include "DateTimeModule.hpp"
#include <ctime>

namespace Krell
{
    DateTimeModule::DateTimeModule()
    {
    }

    DateTimeModule::~DateTimeModule()
    {
    }

    std::string DateTimeModule::getName() const
    {
        return "Date & Time";
    }

    void DateTimeModule::update()
    {
        std::time_t now = std::time(nullptr);
        _dateTime = std::ctime(&now);
        _dateTime.pop_back();
    }

    std::vector<std::string> DateTimeModule::getData() const
    {
        return {_dateTime};
    }
}
