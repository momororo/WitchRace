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
    cocos2d::Vector<Sprite*> *backGrounds = new cocos2d::Vector<Sprite*>;
    
    //staticBackGround
    cocos2d::Sprite* staticBackGround;
    
    //プレイフラグ
    bool gamePlayFlag;
    
    
//メソッド
    //コンストラクタ(初期化)
    BackGround();
    
    
public:
    //メソッド
    //シングルトン
    static BackGround* getInstance();
        
    //getter1
    cocos2d::Sprite* getBackGround1();
    
    //getter2
    cocos2d::Sprite* getBackGround2();
    
    //staticGackGround
    cocos2d::Sprite* getStaticBackGround();
    
    //backGroundの動作開始
    void startBackGround();
    
    //backGroundの動作停止
    void stopBackGround();
    
    //BackGroundの位置を入れ替え
    void replaceBackGround();
    
    //backGroundの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
    void backGroundUpdate();
    
    CREATE_FUNC(BackGround);

    
    
};


#endif /* defined(__WitchRace__BackGround__) */
