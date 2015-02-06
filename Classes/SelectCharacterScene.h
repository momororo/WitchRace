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
    void setBackBt();
    void backBtCallBack(cocos2d::Ref *pSender);
    CREATE_FUNC(SelectCharacterScene);
    
    //配列(透明度の一括管理のため)
    Vector<Sprite*> *characters = new Vector<Sprite*>;
    Label *charaNameText;
    Label *charaExText;
    label *charaLockText;
    

};

#endif /* defined(__WitchRace__SelectCharacterScene__) */
