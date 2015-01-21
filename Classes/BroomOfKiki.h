//
//  BroomOfKiki.h
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/21.
//
//

#ifndef __WitchRace__BroomOfKiki__
#define __WitchRace__BroomOfKiki__

#include "cocos2d.h"
#include "Zorder.h"


using namespace cocos2d;



class BroomOfKiki : public cocos2d::Sprite
{
private:
    //変数
    //クラス
    static BroomOfKiki *broomOfKikiInstance;
    
    
    //自分の箒に乗ったキキ
    Sprite *broomOfKiki;
    //自分の箒に乗ったキキ影
    Sprite *broomOfKikiShadow;
    
    Sprite *broom;
    
    //重力値
    int pGravity = 0;
    
    
    ParticleSystemQuad* endParticle;
    ParticleSystemQuad* broomOfKikiParticle;
    
    
    
    //メソッド
    //コンストラクタ(初期化)
    BroomOfKiki();
    
    
    
public:
    //メソッド
    //プレイヤーは一体だけなのでシングルトン
    static BroomOfKiki* getInstance();
    //削除シングルトン削除
    static void destroyInstance();
    
    CREATE_FUNC(BroomOfKiki);
    
    //getter
    Sprite* getCharacter();
    
    
    
    //自分の箒に乗ったキキの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    void characterUpdate(bool tappedFlag);
    
    
    //自分の箒に乗ったキキの動作開始
    void startCharacter();
    
    //自分の箒に乗ったキキの動作停止
    void stopCharacter();
    
    //gameOverの処理
    void makeGameOver();
    
    
    
};


#endif /* defined(__WitchRace__BroomOfKiki__) */
