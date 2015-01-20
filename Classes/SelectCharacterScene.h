//
//  SelectCharacterScene.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#ifndef __WitchRace__SelectCharacterScene__
#define __WitchRace__SelectCharacterScene__

#include "cocos2d.h"

using namespace cocos2d;

class SelectCharacterScene : public cocos2d::Layer
{
public:

    
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(SelectCharacterScene);

};

#endif /* defined(__WitchRace__SelectCharacterScene__) */
