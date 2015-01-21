//
//  FordAnglia.h
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/21.
//
//

#ifndef __WitchRace__FordAnglia__
#define __WitchRace__FordAnglia__

#include "cocos2d.h"
#include "Zorder.h"


using namespace cocos2d;



class FordAnglia : public cocos2d::Sprite
{
private:
    //変数
    //クラス
    static FordAnglia *fordAngliaInstance;
    
    
    //空飛ぶ車
    Sprite *fordAnglia;
    //空飛ぶ車影
    Sprite *fordAngliaShadow;
    
    Sprite *broom;
    
    //重力値
    int pGravity = 0;
    
    
    ParticleSystemQuad* endParticle;
    ParticleSystemQuad* fordAngliaParticle;
    
    
    
    //メソッド
    //コンストラクタ(初期化)
    FordAnglia();
    
    
    
public:
    //メソッド
    //プレイヤーは一体だけなのでシングルトン
    static FordAnglia* getInstance();
    //削除シングルトン削除
    static void destroyInstance();
    
    CREATE_FUNC(FordAnglia);
    
    //getter
    Sprite* getFordAnglia();
    
    
    
    //空飛ぶ車の1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    void fordAngliaUpdate(bool tappedFlag);
    
    
    //空飛ぶ車の動作開始
    void startFordAnglia();
    
    //空飛ぶ車の動作停止
    void stopFordAnglia();
    
    //gameOverの処理
    void makeGameOver();
    
    
    
};

#endif /* defined(__WitchRace__FordAnglia__) */
