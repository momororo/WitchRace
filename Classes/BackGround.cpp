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

void BackGround::deleteInstance() {
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


//コンストラクタ(初期化)
BackGround::BackGround(){
    
    //StaticBackGround
    staticBackGround = Sprite::create("gameBg_stage1.png");
    staticBackGround->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    staticBackGround->setGlobalZOrder(zOrderOfStaticBackGround);
    
    
    

    
    //backGround1を設定
    //背景色
    auto backGround1 = Sprite::create();
    backGround1->setTextureRect(Rect(0,0,640,1136));
    backGround1->setOpacity(0);
    backGround1->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    backGround1->setGlobalZOrder(zOrderOfBackGround);
/*
    //物理体の生成
    auto backGround1Material = PHYSICSBODY_MATERIAL_DEFAULT;
//    auto backGround1Body = PhysicsBody::createCircle((backGround1->getContentSize().width/2),backGround1Material);
        auto backGround1Body = PhysicsBody::createCircle(0,backGround1Material);

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
*/
    
    //backGround2を設定
    //背景色
    auto backGround2 = Sprite::create();
    backGround2->setTextureRect(Rect(0,0,640,1136));
    backGround2->setOpacity(0);
    backGround2->setPosition(Vec2(selfFrame.width*3/2, selfFrame.height/2));
    backGround2->setGlobalZOrder(zOrderOfBackGround);
/*
    //物理体の設定
    auto backGround2Material = PHYSICSBODY_MATERIAL_DEFAULT;
    auto backGround2Body = PhysicsBody::createCircle((backGround1->getContentSize().width/2),backGround2Material);
    
    auto backGround2Body = PhysicsBody::createCircle(0,backGround2Material);

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
*/
    auto backGround3 = Sprite::create();
    backGround3->setTextureRect(Rect(0,0,640,1136));
    backGround3->setOpacity(0);
    backGround3->setPosition(Vec2(selfFrame.width*5/2, selfFrame.height/2));
    backGround3->setGlobalZOrder(zOrderOfBackGround);
    
    //配列に入れておく
    backGrounds->pushBack(backGround1);
    backGrounds->pushBack(backGround2);
    backGrounds->pushBack(backGround3);
    
    
    
    //最初のスプライトを入れる
    auto village1 = Sprite::create("forest_1.png");

    //stage2
    //auto village1 = Sprite::create("village_1.png");
    
    village1->setPosition(Vec2(village1->getContentSize().width/2,village1->getContentSize().height/2));
    //village1->setOpacity(150);
    
    backGrounds->at(0)->addChild(village1);
    
    
    auto village2 = Sprite::create("forest_2.png");

    //stage2
    //auto village2 = Sprite::create("village_2.png");
    
    village2->setPosition(Vec2(village2->getContentSize().width/2,village2->getContentSize().height/2));
    //village2->setOpacity(150);
    
    backGrounds->at(1)->addChild(village2);
    
    auto village3 = Sprite::create("forest_3.png");
    //stage2
    //auto village3 = Sprite::create("village_3.png");
    
    village3->setPosition(Vec2(village3->getContentSize().width/2,village3->getContentSize().height/2));
    //village3->setOpacity(150);
    
    backGrounds->at(2)->addChild(village3);
    
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
    for(int idx = 0; idx < backGrounds->size();idx++){
//        backGrounds->at(idx)->getPhysicsBody()->setVelocity(Vec2(-500,0));
        backGrounds->at(idx)->setPosition(backGrounds->at(idx)->getPositionX() - 4, backGrounds->at(idx)->getPositionY());

    }
    
    //入れ替えの判定を行う
    if(backGrounds->at(0)->getPosition().x < -(selfFrame.width/2)){
        //入れ替えを行う
        this->replaceBackGround();
    }
    
}