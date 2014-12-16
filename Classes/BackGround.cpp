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


//コンストラクタ(初期化)
BackGround::BackGround(){
    
    //StaticBackGround
    staticBackGround = Sprite::create("gameBg.png");
    staticBackGround->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    staticBackGround->setPositionZ(zPositionOfStaticBackGround);
    

    
    //backGround1を設定
    //背景色
    auto backGround1 = Sprite::create();
    backGround1->setTextureRect(Rect(0,0,1280,1136));
    backGround1->setOpacity(0);
    backGround1->setPosition(Vec2(selfFrame.width, selfFrame.height/2));
    backGround1->setPositionZ(zPositionOfBackGround);
    
    //物理体の生成
    auto backGround1Material = PHYSICSBODY_MATERIAL_DEFAULT;
    auto backGround1Body = PhysicsBody::createCircle((backGround1->getContentSize().width/2),backGround1Material);
    //重力による影響の可否
    backGround1Body->setGravityEnable(false);
    //まじない
    backGround1Body->setDynamic(true);
    backGround1Body->setEnable(true);
    
    //ビットマスクはてきとう
    backGround1Body->setCategoryBitmask(0);
    backGround1Body->setCollisionBitmask(0);
    backGround1Body->setContactTestBitmask(0);
    
    backGround1->setPhysicsBody(backGround1Body);

    
    //backGround2を設定
    //背景色
    auto backGround2 = Sprite::create();
    backGround2->setTextureRect(Rect(0,0,1280,1136));
    backGround2->setOpacity(0);
    backGround2->setPosition(Vec2(selfFrame.width*3, selfFrame.height/2));
    backGround2->setPositionZ(zPositionOfBackGround);
    
    //物理体の設定
    auto backGround2Material = PHYSICSBODY_MATERIAL_DEFAULT;
    auto backGround2Body = PhysicsBody::createCircle((backGround1->getContentSize().width/2),backGround2Material);
    //重力による影響の可否
    backGround2Body->setGravityEnable(false);
    //まじない
    backGround2Body->setDynamic(true);
    backGround2Body->setEnable(true);
    
    //ビットマスクはてきとう
    backGround2Body->setCategoryBitmask(0);
    backGround2Body->setCollisionBitmask(0);
    backGround2Body->setContactTestBitmask(0);
    
    backGround2->setPhysicsBody(backGround2Body);
    
    //配列に入れておく
    backGrounds->pushBack(backGround1);
    backGrounds->pushBack(backGround2);
    
    
    
    //最初のスプライトを入れる
    auto house1 = Sprite::create("house1.png");
    
    house1->setPosition(Vec2(house1->getContentSize().width/2,house1->getContentSize().height/2));
    
    backGrounds->at(0)->addChild(house1);
    
    auto house2 = Sprite::create("house1.png");
    
    house2->setPosition(Vec2(house2->getContentSize().width/2,house2->getContentSize().height/2));
    
    backGrounds->at(1)->addChild(house2);
    
    
    
    //最初のスプライトを入れる終

    
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
//CallBackで呼ばれます。
void BackGround::replaceBackGround(){
    
    //配列から取り出す
    Sprite* backGround = backGrounds->at(0);
 //   backGround->retain();
    
    //配列から当該レイヤを削除
    backGrounds->erase(0);
    
#pragma mark -
#pragma mark ここにスプライトを乗っけ直す処理を入れる
#pragma mark -
    
    
    //ポジションの設定
    backGround->setPosition(Vec2(backGrounds->at(backGrounds->size()-1)->getPosition().x + backGrounds->at(backGrounds->size()-1)->getContentSize().width/2 + backGround->getContentSize().width/2,backGrounds->at(backGrounds->size()-1)->getPositionY()));
    
    
    //配列の末尾に入れなおす
    backGrounds->pushBack(backGround);

/*
    //デバッグ用
    if(backGrounds->at(0)->getPosition().x + backGrounds->at(0)->getContentSize().width/2  < backGrounds->at(1)->getPosition().x - backGrounds->at(1)->getContentSize().width/2){
        
        auto test = (backGrounds->at(0)->getPosition().x + backGrounds->at(0)->getContentSize().width/2)  - (backGrounds->at(1)->getPosition().x - backGrounds->at(1)->getContentSize().width/2);

        
        CCLOG("%fずれてる！",test);
    }
*/
    
}


//キキちゃんの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
void BackGround::backGroundUpdate(){
    
    //ゲームプレイ中かフラグで判定
    if(gamePlayFlag !=  true){
        return;
    }
    
    //地面の移動を行う
    for(int idx = 0; idx < backGrounds->size();idx++){
        backGrounds->at(idx)->getPhysicsBody()->setVelocity(Vec2(-500,0));
    }
    
    //入れ替えの判定を行う
    if(backGrounds->at(0)->getPosition().x < -(selfFrame.width)){
        //入れ替えを行う
        this->replaceBackGround();
    }
    
}