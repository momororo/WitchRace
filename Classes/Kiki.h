//
//  Kiki.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#ifndef __WitchRace__Kiki__
#define __WitchRace__Kiki__

#include "cocos2d.h"

using namespace cocos2d;

class Kiki : public cocos2d::Sprite
{
private:
//変数
    //クラス
    static Kiki *kikiInstance;
    
    //キキちゃん
    Sprite *kiki;
    
//メソッド
    //コンストラクタ(初期化)
    Kiki();
    
    
public:
//メソッド
    //プレイヤーは一体だけなのでシングルトン
    static Kiki* getInstance();
    
    CREATE_FUNC(Kiki);
    
    //getter
    Sprite* getKiki();

};

#endif /* defined(__WitchRace__Kiki__) */
