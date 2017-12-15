#pragma once
#include "plugins.hpp"
#include "cinder/app/App.h"
#include "../src/template.cpp"
#include "../src/video.cpp"

using namespace ci;

class CoreModulesPlugin : public Plugin {
public:
    CoreModulesPlugin() {
        pluginName = "core";
        moduleWidgetsNames.push_back("Template"); 
        moduleWidgetsNames.push_back("Video"); 
    }

    std::unique_ptr<ModuleWidget> createModuleWidget(std::string widgetName, vec2 mousePos) {
        if(moduleWidgetsNames[0] == widgetName) return std::make_unique<TestWidget>(mousePos);  
        else return std::make_unique<VideoWidget>(mousePos);  
    }
};

extern "C" {
    void loadPlugin(std::unique_ptr<Plugin>& plug) {
        plug = std::make_unique<CoreModulesPlugin>();
    } 
}

