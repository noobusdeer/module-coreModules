#include "engine.hpp"
#include "widgets.hpp"
#include "cinder/ImageIo.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class Video : public Module {
public:
  	enum ParamIds { NUM_PARAMS };
  	enum InputIds { NUM_INPUTS };
  	enum OutputIds { OUT_OUTPUT, NUM_OUTPUTS };

  	gl::TextureRef	mTexture;
  	Video() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
    	fs::path path = getAssetPath( "t.jpg");
	  	if( ! path.empty() ) 
		  	mTexture = gl::Texture::create( loadImage( path ) );
  	}

	void step() override { 
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