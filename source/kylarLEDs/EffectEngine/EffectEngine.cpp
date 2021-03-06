#include "EffectEngine.h"
#include <stdio.h>
#include <cstdlib>
EffectEngine::EffectEngine(){

}

void EffectEngine::clear() {
    for (Effect* eff : effects) {
        delete(eff);
    }
    for (Effect* eff : effectsQueue){
        delete(eff);
    }
    effects.clear();
    effectsQueue.clear();
}

void EffectEngine::apply(Effect *effect) {
	effects.push_back(effect);
    //printf("effect vector size= %d\n", sizeof(Effect *)*effects.size());
}

void EffectEngine::queueApply(Effect *effect) {
    effectsQueue.push_back(effect);
}

void EffectEngine::run() {
    // This function essentially just calls run on every effect
    // It will also remove the effects that are "done"
    std::vector<Effect *>::iterator it = effects.begin();
    while (it != effects.end())
    {
        Effect* effect = *it;
        if (effect->isDone()) {
            // erase() invalidates the iterator, use returned iterator
            delete effect;
            //delete(effect);
            it = effects.erase(it);
            continue;
        } else {
            effect->run();
            it++;
        }
        
        
    }
    for (Effect* eff : effectsQueue) {
        effects.push_back(eff);
    }
    effectsQueue.clear();
}