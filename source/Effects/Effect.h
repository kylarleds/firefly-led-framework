#pragma once
#include "../kylarLEDs/LEDInterface/LEDs.h"
#include "../kylarLEDs/EffectEngine/EffectEngine.h"
#include <cstdlib>
class EffectEngine;
class Effect {
    /*
        • Effect object is parent, user creates subclasses
        • Have LED write control
        • Use generators, LEDOutput

        Rules for creating new effects:
            Make sure to "queueApply" as effects cannot be added to the effectEngine while the engine is running
            Effect::engine->queueApply((new SingleTime(LEDs))->init(blueprint));
    */
    public:
        Effect();
        virtual ~Effect();
        virtual void run() = 0; // Rules for run: When done, just set done = 1, do not call release()! It will cause memory to be freed twice!
        virtual void init() = 0;
        static void giveEngine(EffectEngine * effectEngine);
        static EffectEngine *engine;
        int isDone();
        int ID = -1;
    protected:
        int done = 0;
        int initialized = 0;
        
};
