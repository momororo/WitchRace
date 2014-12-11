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
    
    //backGround2を設定
    //背景色
    auto backGround2 = Sprite::create();
    backGround2->setTextureRect(Rect(0,0,1280,1136));
    backGround2->setOpacity(0);
    backGround2->setPosition(Vec2(selfFrame.width*3, selfFrame.height/2));
    backGround2->setPositionZ(zPositionOfBackGround);
    
    //配列に入れておく
    backGrounds->pushBack(backGround1);
    backGrounds->pushBack(backGround2);
    
}

//backGroundの動作開始
void BackGround::startBackGround(){
    
    
//ここで背景にスプライトを埋め込む
    auto house1 = Sprite::create("house1.png");
    
    house1->setPosition(Vec2(0,house1->getContentSize().height/2));
    
    backGrounds->at(0)->addChild(house1);
    
    auto house2 = Sprite::create("house2.png");

    house2->setPosition(Vec2(0,house2->getContentSize().height/2));
    
    backGrounds->at(1)->addChild(house2);



//ここで背景にスプライトを埋め込む終


//backGround1の動作
    auto moveGround1 = MoveTo::create(3, Vec2(-(selfFrame.width), selfFrame.height/2));
    
    auto remove1 = RemoveSelf::create();
    
    auto sequence1 = Sequence::create(moveGround1,remove1, NULL);

    backGrounds->at(0)->runAction(sequence1);

    
//backGround2の動作
    auto moveGround2 = MoveTo::create(6, Vec2(-(selfFrame.width), selfFrame.height/2));
    
    auto remove2 = RemoveSelf::create();
    
    auto sequence2 = Sequence::create(moveGround2,remove2, NULL);
    
    backGrounds->at(1)->runAction(sequence2);
    
    
}

//backGroundの動作停止
void BackGround::stopBackGround(){
    
    for (int idx = 0; idx < backGrounds->size(); idx++){
        
        backGrounds->at(idx)->stopAllActions();
    }
    
}



/**
 * 備忘録
 * １、配列から取り出すとリファレンスカウンタの都合によりオブジェクトがreleaseされる模様
 * なのでretain()を入れてカウンタを上げることでreleaseを防止してます
 *
 * ２、配列から取り出して配列内のオブジェクトを削除すると親シーンとのリンクが消える模様
 * なので返り値にLayerを返してます。(配列の入れ替えをしない時はNULLを返す)
 * 呼び出し元で、NULLなら放置、NULLじゃない場合はaddchilすることで対応してます。
 * なんて糞処理！！
 */
//キキちゃんの1フレーム毎の処理(GameSceneのUpdateで呼んでね！)
Sprite* BackGround::backGroundUpdate(){
    

    //配列の先頭がアクションを持っていない=ゴールに到達したと判定して
    //末尾に移動する
    if(backGrounds->at(0)->getNumberOfRunningActions() == 0){
        
        //配列から取り出す
        Sprite* backGround = backGrounds->at(0);
        backGround->retain();
        
        //配列から当該レイヤを削除
        backGrounds->erase(0);
        
#pragma mark -
#pragma mark ここにスプライトを乗っけ直す処理を入れる
#pragma mark -
        
        
        //ポジションの設定
        backGround->setPosition(Vec2(selfFrame.width*3, selfFrame.height/2));
        
        //zポジションを設定しなおす
//        backGround->setPositionZ(zPositionOfBackGround);
        
        //backGroundの動作
        auto moveGround = MoveTo::create(6, Vec2(-(selfFrame.width), selfFrame.height/2));
        
        auto remove = RemoveSelf::create();
        
        auto sequence = Sequence::create(moveGround,remove, NULL);
        
        backGround->runAction(sequence);
        
        //配列の末尾に入れなおす
        backGrounds->pushBack(backGround);
        

        return backGround;
        
    }
    
    return NULL;
    
    
    
}