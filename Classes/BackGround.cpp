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

//getter3
Sprite* BackGround::getBackGround3(){
    
    return backGrounds->at(2);
    
}

//getter4
Sprite* BackGround::getBackGround4(){
    
    return backGrounds->at(3);
    
}




//コンストラクタ(初期化)
BackGround::BackGround(){
    
    //StaticBackGround
    staticBackGround = Sprite::create("gameBg.png");
    staticBackGround->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    staticBackGround->setPositionZ(zPositionOfStaticBackGround);
    

    
    //backGround1を設定
    //背景色
    auto backGround1 = Sprite::create("house1.png");
    backGround1->setOpacity(150);
    backGround1->setAnchorPoint(Vec2(0.5,0));
    backGround1->setPosition(Vec2(selfFrame.width, 50));
    backGround1->setPositionZ(zPositionOfBackGround);
    
    //backGround2を設定
    //背景色
    auto backGround2 = Sprite::create("house2.png");
    backGround2->setOpacity(150);
    backGround2->setAnchorPoint(Vec2(0.5,0));
    backGround2->setPosition(Vec2(selfFrame.width*3, 50));
    backGround2->setPositionZ(zPositionOfBackGround);

    //backGround3を設定
    //背景色
    auto backGround3 = Sprite::create("house1.png");
    backGround3->setOpacity(150);
    backGround3->setAnchorPoint(Vec2(0.5,0));
    backGround3->setPosition(Vec2(selfFrame.width*5, 50));
    backGround3->setPositionZ(zPositionOfBackGround);
    
    //backGround4を設定
    //背景色
    auto backGround4 = Sprite::create("house2.png");
    backGround4->setOpacity(150);
    backGround4->setAnchorPoint(Vec2(0.5,0));
    backGround4->setPosition(Vec2(selfFrame.width*7, 50));
    backGround4->setPositionZ(zPositionOfBackGround);

    
    //配列に入れておく
    backGrounds->pushBack(backGround1);
    backGrounds->pushBack(backGround2);
    backGrounds->pushBack(backGround3);
    backGrounds->pushBack(backGround4);

    
}

//backGroundの動作開始
void BackGround::startBackGround(){


//backGround1の動作
    auto moveGround1 = MoveTo::create(3, Vec2(-(selfFrame.width), 50));
    
    auto remove1 = RemoveSelf::create();
    
    auto sequence1 = Sequence::create(moveGround1,remove1, NULL);

    backGrounds->at(0)->runAction(sequence1);

    
//backGround2の動作
    auto moveGround2 = MoveTo::create(6, Vec2(-(selfFrame.width), 50));
    
    auto remove2 = RemoveSelf::create();
    
    auto sequence2 = Sequence::create(moveGround2,remove2, NULL);
    
    backGrounds->at(1)->runAction(sequence2);
    
//backGround3の動作
    auto moveGround3 = MoveTo::create(9, Vec2(-(selfFrame.width), 50));
    
    auto remove3 = RemoveSelf::create();
    
    auto sequence3 = Sequence::create(moveGround3,remove3, NULL);
    
    backGrounds->at(2)->runAction(sequence3);

//backGround4の動作
    auto moveGround4 = MoveTo::create(12, Vec2(-(selfFrame.width), 50));
    
    auto remove4 = RemoveSelf::create();
    
    auto sequence4 = Sequence::create(moveGround4,remove4, NULL);
    
    backGrounds->at(3)->runAction(sequence4);
    
    
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
        backGround->setPosition(Vec2(selfFrame.width*7, 50));
        
        //zポジションを設定しなおす
//        backGround->setPositionZ(zPositionOfBackGround);
        
        //backGroundの動作
        auto moveGround = MoveTo::create(12, Vec2(-(selfFrame.width), 50));
        
        auto remove = RemoveSelf::create();
        
        auto sequence = Sequence::create(moveGround,remove, NULL);
        
        backGround->runAction(sequence);
        
        //配列の末尾に入れなおす
        backGrounds->pushBack(backGround);
        

        return backGround;
        
    }
    
    return NULL;
    
    
    
}