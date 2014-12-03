//
//  GameScene.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#ifndef __WitchRace__GameScene__
#define __WitchRace__GameScene__

#include "cocos2d.h"
#include "Kiki.h"

using namespace cocos2d;

class GameScene : public Layer
{
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__WitchRace__GameScene__) */
