#include "engine.hpp"
#include "widgets.hpp"
using namespace ci;
using namespace ci::app;
using namespace std;

class TestModule : public Module {
public:
	enum ParamIds { LKNOB_PARAM, RKNOB_PARAM, SLIDER_PARAM, NUM_PARAMS };
  	enum InputIds { PITCH_INPUT, NUM_INPUTS };
  	enum OutputIds { OUT1_OUTPUT, NUM_OUTPUTS };

  	TestModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
  	
	void step() override { 		
		if (inputs[0].isReady()) {
			outputs[0].setValue(inputs[0].getValue());
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
