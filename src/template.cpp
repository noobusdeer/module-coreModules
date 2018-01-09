#include "engine.hpp"
#include "widgets.hpp"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Batch.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TestModule : public Module {
public:
	enum ParamIds { LKNOB_PARAM, RKNOB_PARAM, SLIDER_PARAM, NUM_PARAMS };
  	enum InputIds { PITCH_INPUT, NUM_INPUTS };
  	enum OutputIds { OUT1_OUTPUT, NUM_OUTPUTS };

	gl::FboRef			mFbo;
	static const int	FBO_WIDTH = 1920, FBO_HEIGHT = 1080;
	gl::GlslProgRef		mGlsl;
	gl::TextureRef		mTexture;
	gl::BatchRef		mBox;
	mat4				mRotation;

  	TestModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
		mGlsl = gl::GlslProg::create( gl::GlslProg::Format()
			.vertex(	CI_GLSL( 150,
				uniform mat4	ciModelViewProjection;
				in vec4			ciPosition;
				in vec2			ciTexCoord0;
				out vec2		TexCoord0;
		
				void main( void ) {
					gl_Position	= ciModelViewProjection * ciPosition;
					TexCoord0 = ciTexCoord0;
				}
			) )
			.fragment(	CI_GLSL( 150,
				uniform vec4		uColor;
				uniform sampler2D	uTex0;
				in vec2				TexCoord0;
				out vec4			oColor;

				void main( void ) {
					oColor = texture( uTex0, TexCoord0 );
				}
			) ) );

		//	mBox = gl::Batch::create( geom::Cube(), mGlsl );

			gl::Fbo::Format format;
			format.setSamples( 4 );
			mFbo = gl::Fbo::create( FBO_WIDTH, FBO_HEIGHT, format.depthTexture());
			gl::enableDepthRead();
			gl::enableDepthWrite();

			mRotation = mat4( 1 );
	  	}
  	
	void step() override { 		
		if (inputs[0].isReady()) {
			mRotation *= rotate( 0.06f * params[2].getValue() * 0.1f, normalize( vec3( params[0].getValue(), params[1].getValue(), 0.666f ) ) );
			mTexture = inputs[0].getValue();
			mTexture->bind(0);
			gl::ScopedFramebuffer fboScope( mFbo );
			gl::clear();
			gl::ScopedViewport viewportScope( ivec2( 0 ), mFbo->getSize() );
			gl::ScopedMatrices matScope;
			gl::draw(mTexture);
			CameraPersp cam( mFbo->getWidth(), mFbo->getHeight(), 60.0f );
			cam.setPerspective( 30, mFbo->getAspectRatio(), 1, 1000 );
			cam.lookAt( vec3( 2.8f, 1.8f, -2.8f ), vec3( 0 ));
			gl::setMatrices( cam );
			gl::multModelMatrix( mRotation );
			
		//	mBox->draw();
			gl::ScopedGlslProg shaderScp(mGlsl);
			gl::drawCube( vec3(), vec3( params[2].getValue() * 0.1f ) );
			gl::enableDepthRead();
			gl::enableDepthWrite();
			outputs[0].setValue(mFbo->getColorTexture());
		}
   	}
};

class TestWidget : public ModuleWidget {

public:
  	TestWidget(vec2 pos) : ModuleWidget(pos, vec2(200, 250), "VIDEO INP") {
    	module = make_shared<TestModule>();
    	setModule(module);
    	addParam(make_unique<RangeKnob>("LKNOB", module, TestModule::LKNOB_PARAM, vec2(10, 50), vec2(0, 10)));
    	addParam(make_unique<TwoSideRangeKnob>("RKNOB", module, TestModule::RKNOB_PARAM, vec2(140, 50), 20));
    	addParam(make_unique<HorizontalSlider>("SLIDE", module, TestModule::SLIDER_PARAM, vec2(10, 170), vec2(0, 15), 200));
    	addOutput(make_unique<Port>("OUT", module, TestModule::OUT1_OUTPUT, Port::OUTPUT, vec2(150, 210)));
    	addOutput(make_unique<Port>("IN", module, TestModule::PITCH_INPUT, Port::INPUT, vec2(30, 210)));
	}
  	void draw(unique_ptr<cinder::nvg::Context> &vg) { ModuleWidget::draw(vg); }
};
