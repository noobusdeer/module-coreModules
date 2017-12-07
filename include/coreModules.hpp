#pragma once
#include "plugins.hpp"
#include "cinder/app/App.h"


class CoreModulesPlugin : public Plugin {

public:
    CoreModulesPlugin() {
        pluginName = "core";
    }
};

extern "C" {
    void loadPlugin(std::unique_ptr<Plugin>& ct) {
        std::cout<<"plug connected";
        ct = std::make_unique<CoreModulesPlugin>();
    } 
}

