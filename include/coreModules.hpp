#pragma once
#include "plugins.hpp"
#include "cinder/app/App.h"
#include "cinder/Log.h"

extern "C" {
    void loadPlugin() {
		CI_LOG_D( "Plugin!" );
    } 
}

class CoreModulesPlugin : public Plugin {

};

