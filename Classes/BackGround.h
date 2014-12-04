//
//  BackGround.h
//  WitchRace
//
//  Created by yasutomo on 2014/12/04.
//
//

#ifndef __WitchRace__BackGround__
#define __WitchRace__BackGround__
#include "GameScene.h"
#include "cocos2d.h"
#include "Zpositions.h"

using namespace cocos2d;

class BackGround : public cocos2d::Layer
{
private:

//変数
    //クラス
    static BackGround *backGroundInstance;
    
    

    //配列
    cocos2d::Vector<Layer*> *backGrounds = new cocos2d::Vector<Layer*>;
    
    
//メソッド
    //コンストラクタ(初期化)
    BackGround();
    
    
public:
    //メソッド
    //プレイヤーは一体だけなのでシングルトン
    static BackGround* getInstance();
        
    //getter1
    cocos2d::Layer* getBackGround1();
    
    //getter2
    cocos2d::Layer* getBackGround2();

    //getter3
    cocos2d::Layer* getBackGround3();

    //getter4
    cocos2d::Layer* getBackGround4();
    
    //backGroundの動作開始
    void startBackGround();
    
    //backGroundの動作停止
    void stopBackGround();
    
    //backGroundの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    cocos2d::Layer* backGroundUpdate();
    
    CREATE_FUNC(BackGround);

    
    
};


#endif /* defined(__WitchRace__BackGround__) */
