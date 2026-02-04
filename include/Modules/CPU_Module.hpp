/*
** EPITECH PROJECT, 2026
** G-PDG-300-MPL-3-1-PDGRUSH4-5
** File description:
** CPU_Module
*/

#ifndef CPU_MODULE_HPP_
#define CPU_MODULE_HPP_
#include "IModule.hpp"
#include <string>
#include <vector>

namespace Krell {
    class CPU_Module : public IModule {
        public:
            CPU_Module();
            ~CPU_Module() override {}

            std::string getName() const override;
            void update() override;
            std::vector<std::string> getData() const override;

        private:
            std::string _model;
            int _nbCores;
            double _cpuUsage;

            unsigned long long prevIdle;
            unsigned long long prevTotal;

            void updateMacOS();
            void updateLinux();
    };
}
#endif /* !CPU_MODULE_HPP_ */
