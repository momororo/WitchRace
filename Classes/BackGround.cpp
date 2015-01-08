//
//  BackGround.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/04.
//
//

#include "BackGround.h"

#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()
//#define zPositionOfBackGround 10

//おまじない
USING_NS_CC;



//初期値NULL
BackGround* BackGround::backGroundInstance = NULL;

//シングルトン
BackGround* BackGround::getInstance(){
    
    if(backGroundInstance == NULL){
        
        backGroundInstance = new BackGround();
    }
    
    return  backGroundInstance;
}

void BackGround::destroyInstance() {
    if (backGroundInstance != NULL){
        delete backGroundInstance;
    
        backGroundInstance = NULL;
    }
}

//getStacicBackGround
Sprite* BackGround::getStaticBackGround(){
    return staticBackGround;
}

//getter1
Sprite* BackGround::getBackGround1(){
    
    return backGrounds->at(0);
    
}

//getter2
Sprite* BackGround::getBackGround2(){
    
    return backGrounds->at(1);
    
}

//getter3
Sprite* BackGround::getBackGround3(){
    
    return backGrounds->at(2);
    
}

//countGetter
int BackGround::getReplaceCount(){
    return count;
}


//コンストラクタ(初期化)
BackGround::BackGround(){
    
//共通のパーツを作成
    
    //backGround1を設定
    //背景色
    auto backGround1 = Sprite::create();
    backGround1->setTextureRect(Rect(0,0,640,1136));
    backGround1->setOpacity(0);
    backGround1->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    backGround1->setGlobalZOrder(zOrderOfBackGround);
    
    //backGround2を設定
    //背景色
    auto backGround2 = Sprite::create();
    backGround2->setTextureRect(Rect(0,0,640,1136));
    backGround2->setOpacity(0);
    backGround2->setPosition(Vec2(backGround1->getPositionX() + backGround2->getContentSize().width, selfFrame.height/2));
    backGround2->setGlobalZOrder(zOrderOfBackGround);
    
    auto backGround3 = Sprite::create();
    backGround3->setTextureRect(Rect(0,0,640,1136));
    backGround3->setOpacity(0);
    backGround3->setPosition(Vec2(backGround2->getPositionX() + backGround3->getContentSize().width, selfFrame.height/2));
    backGround3->setGlobalZOrder(zOrderOfBackGround);
    
    //配列に入れておく
    backGrounds->pushBack(backGround1);
    backGrounds->pushBack(backGround2);
    backGrounds->pushBack(backGround3);
    
    

    
    
//ステージごとに呼び出すスプライトを変える
    
    //呼び出す画像をステージ別に分岐させるために、Stringの変数を作成しておく。
    std::string bgName;
    
    auto userDef = UserDefault::getInstance();
    auto selectStory = userDef->getIntegerForKey("selectStory");
    
    /**
     *  早見表
     *  ステージ1:forest
     *  ステージ2:village
     *  ステージ3:factory
     *  ステージ4:town
     *  ステージ5:field
     */
    switch (selectStory) {
        case 0:bgName = "forest";   break;
        case 1:bgName = "village";  break;
        case 2:bgName = "factory";  break;
        case 3:bgName = "town";     break;
        case 4:bgName = "field";    break;
        default:break;
    }

    //諸々プリロード(敵オブジェクトも含めて)
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(bgName + ".plist");

    
    //StaticBackGround
    staticBackGround = Sprite::create(bgName + "_gameBg.png");
    staticBackGround->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    staticBackGround->setGlobalZOrder(zOrderOfStaticBackGround);
    
    //背景1
    auto sprite1 = Sprite::create(bgName + "_1.png");
    sprite1->setPosition(Vec2(sprite1->getContentSize().width/2,sprite1->getContentSize().height/2));
    sprite1->setGlobalZOrder(zOrderOfBackGroundParts);
    backGrounds->at(0)->addChild(sprite1);
    
    //背景2
    auto sprite2 = Sprite::create(bgName + "_2.png");
    sprite2->setPosition(Vec2(sprite2->getContentSize().width/2,sprite2->getContentSize().height/2));
    sprite2->setGlobalZOrder(zOrderOfBackGroundParts);

    backGrounds->at(1)->addChild(sprite2);
    
    //背景3
    auto sprite3 = Sprite::create(bgName + "_3.png");
    sprite3->setPosition(Vec2(sprite3->getContentSize().width/2 ,sprite3->getContentSize().height/2));
    sprite3->setGlobalZOrder(zOrderOfBackGroundParts);
    backGrounds->at(2)->addChild(sprite3);
        
}

//backGroundの動作開始
void BackGround::startBackGround(){
    
    gamePlayFlag = true;
    
    
}

//backGroundの動作停止
void BackGround::stopBackGround(){
    

    gamePlayFlag = false;
    
}



/**
 * 備忘録
 * １、配列から取り出すとリファレンスカウンタの都合によりオブジェクトがreleaseされる模様
 * なのでretain()を入れてカウンタを上げることでreleaseを防止してます
 *
 */
//CallBackで呼ばれなくなりました
void BackGround::replaceBackGround(){
    
    //配列から取り出す
    Sprite* backGround = backGrounds->at(0);
    //backGround->retain();
    
    //配列から当該レイヤを削除
    backGrounds->erase(0);
    
#pragma mark -
#pragma mark ここにスプライトを乗っけ直す処理を入れる
    Enemy::getInstance()->addEnemyManager(backGround);
#pragma mark -
    
    
    //ポジションの設定
    backGround->setPosition(Vec2(backGrounds->at(backGrounds->size()-1)->getPosition().x + backGround->getContentSize().width,backGrounds->at(backGrounds->size()-1)->getPositionY()));

    
    
    
    //配列の末尾に入れなおす
    backGrounds->pushBack(backGround);
    
    //カウント足し込み
    count++;

/*
    //デバッグ用
    if(backGrounds->at(0)->getPosition().x + backGrounds->at(0)->getContentSize().width/2  < backGrounds->at(1)->getPosition().x - backGrounds->at(1)->getContentSize().width/2){
        
        auto test = (backGrounds->at(0)->getPosition().x + backGrounds->at(0)->getContentSize().width/2)  - (backGrounds->at(1)->getPosition().x - backGrounds->at(1)->getContentSize().width/2);

        
        CCLOG("%fずれてる！",test);
    }
*/
    
}

void BackGround::makeGameOver(){
    
    gamePlayFlag = false;
    
    gameOverFlag = true;
    
}

//キキちゃんの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
void BackGround::backGroundUpdate(){
    
    //ゲームプレイ中かフラグで判定
    if(gamePlayFlag !=  true){
        return;
    }


    
    
    //地面の移動を行う
    for(int idx = ((int)backGrounds->size() - 1) ; idx >= 0 ;idx--){
        backGrounds->at(idx)->setPosition(backGrounds->at(idx)->getPositionX() - 4, backGrounds->at(idx)->getPositionY());

    }

    
    //入れ替えの判定を行う
    if(backGrounds->at(0)->getPosition().x < -(selfFrame.width/2)){
        //入れ替えを行う
        this->replaceBackGround();
    }
    
}