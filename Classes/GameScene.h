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
    
    

    //タップイベントの宣言
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    //衝突イベント
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    //1フレーム毎の処理
    void update(float delta);
};

#endif /* defined(__WitchRace__GameScene__) */
