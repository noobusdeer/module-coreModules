#include "engine.hpp"
#include "widgets.hpp"
#include "cinder/qtime/QuickTimeGl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Video : public Module {
public:
  	enum ParamIds { NUM_PARAMS };
  	enum InputIds { NUM_INPUTS };
  	enum OutputIds { OUT_OUTPUT, NUM_OUTPUTS };
	qtime::MovieGlRef   mMovie;
  	gl::TextureRef	mTexture;
  	Video() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
    	fs::path path = getAssetPath( "HEXXX (loop).mov");
	  	if( ! path.empty() ) {
		  	mMovie = qtime::MovieGl::create( path );
        	mMovie->play();
			mMovie->setLoop(true);
			mMovie->setVolume(0);
	  	}
  	}

	void step() override { 
		mTexture = mMovie->getTexture();
    	outputs[0].setValue(mTexture);
  	}
};

class VideoWidget : public ModuleWidget {
public:
    VideoWidget(vec2 pos) : ModuleWidget(pos, vec2(120, 80), "VIDEO") {
    	module = make_shared<Video>();
    	setModule(module);
    	addOutput(make_unique<Port>("OUT", module, Video::OUT_OUTPUT, Port::OUTPUT, vec2(70, 30)));
    }
};
