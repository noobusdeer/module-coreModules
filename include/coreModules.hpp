#pragma once
#include "plugins.hpp"
#include "cinder/app/App.h"

extern "C" {
    void loadPlugin() {
        std::cout<<"Hi";
    } 
}

class CoreModulesPlugin : public Plugin {

};

