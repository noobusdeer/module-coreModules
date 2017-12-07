#pragma once
#include "plugins.hpp"
#include "cinder/app/App.h"
#include "../src/template.cpp"

using namespace ci;

class CoreModulesPlugin : public Plugin {
public:
    CoreModulesPlugin() {
        pluginName = "core";
        moduleWidgetsNames.push_back("Template"); 
    }

    std::unique_ptr<ModuleWidget> createModuleWidget(std::string widgetName, vec2 mousePos) {
        return std::make_unique<TestWidget>(mousePos);
    }
};

extern "C" {
    void loadPlugin(std::unique_ptr<Plugin>& plug) {
        plug = std::make_unique<CoreModulesPlugin>();
    } 
}

