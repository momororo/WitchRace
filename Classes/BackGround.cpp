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
    staticBackGround->setGlobalZOrder(zOrderOfStaticBackGround);
    

    
    //backGround1を設定
    //背景色
    auto backGround1 = Sprite::create();
    backGround1->setTextureRect(Rect(0,0,1280,1136));
    backGround1->setOpacity(0);
    backGround1->setPosition(Vec2(selfFrame.width, selfFrame.height/2));
    backGround1->setGlobalZOrder(zOrderOfBackGround);
    
    //物理体の生成
    auto backGround1Material = PHYSICSBODY_MATERIAL_DEFAULT;
    auto backGround1Body = PhysicsBody::createBox(Size((backGround1->getContentSize().width),selfFrame.height/8),backGround1Material);
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
    backGround2->setGlobalZOrder(zOrderOfBackGround);
    
    //物理体の設定
    auto backGround2Material = PHYSICSBODY_MATERIAL_DEFAULT;
    auto backGround2Body = PhysicsBody::createBox(Size((backGround1->getContentSize().width),selfFrame.height/8),backGround2Material);
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
    house1->setOpacity(150);
    
    backGrounds->at(0)->addChild(house1);
    
    auto house2 = Sprite::create("house1.png");
    
    house2->setPosition(Vec2(house2->getContentSize().width/2,house2->getContentSize().height/2));
    house2->setOpacity(150);
    
    backGrounds->at(1)->addChild(house2);
    
    
    //最初のスプライトを入れる終
    
    //コウモリの画像をキャッシュしておく
    SpriteFrameCache::getInstance() -> addSpriteFramesWithFile("bad.plist");


    
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
 //   backGround->retain();
    
    //配列から当該レイヤを削除
    backGrounds->erase(0);
    
#pragma mark -
#pragma mark ここにスプライトを乗っけ直す処理を入れる

    //初回のみスプライト生成(init時に生成して、hideさせられるならその処理に変更すること)
    if(backGround->getChildByName("bad") == NULL){
        
        
        //physicsbody用
        Sprite *badForPhysics = Sprite::createWithSpriteFrameName("bad_1.png");
        //透明に
        badForPhysics->setOpacity(255);
        badForPhysics->setName("badForPhysics");


        //物理体の設定
        //auto badMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto badBody = PhysicsBody::createBox(Size(100,100));//(badForPhysics->getContentSize().width/2),badMaterial);
        //重力による影響の可否
        badBody->setGravityEnable(false);
        //まじない
        badBody->setDynamic(false);
        badBody->setEnable(true);

        //カテゴリビットマスク
        badBody->setCategoryBitmask(0x02);
        badBody->setCollisionBitmask(0);
        badBody->setContactTestBitmask(0x01);
    /*
        //カテゴリビットマスク
        badBody->setCategoryBitmask(0);
        badBody->setCollisionBitmask(0);
        badBody->setContactTestBitmask(0);
*/
    
        //追加
        //badForPhysics->setPhysicsBody(badBody);

        backGround->addChild(badForPhysics);
 
        //乱数により位置をランダムにしてみる(参考)
        auto randYPosition = arc4random_uniform(5) + 1;
        badForPhysics -> setPosition(Vec2(backGround->getContentSize().width/2,backGround->getContentSize().height/(randYPosition)));
        badForPhysics -> setGlobalZOrder(zOrderOfBad);


/*
        //コウモリのスプライトを作成
        Sprite *bad = Sprite::createWithSpriteFrameName("bad_1.png");
        bad->setName("bad");
        badForPhysics -> addChild(bad);
        
        //position
        bad->setPosition(bad->getContentSize().width/2,bad->getContentSize().height/2);
        

    
        //アニメーション用配列を用意
        auto  badFrames = new Vector<SpriteFrame*>();
        
        //画像２枚を配列にセットする
        //画像をすべて(2枚)を取り出せるよう、ループ文を使用
        for (int i = 1; i < 3;i++ ) {
            std::string badName = StringUtils::format("bad_%i.png",i);
            SpriteFrame *spBadFrame = SpriteFrameCache::getInstance()-> getSpriteFrameByName(badName.c_str());
            badFrames -> pushBack(spBadFrame);
            

        }
        
        //アニメーションの設定
        Animation *badAnimation = Animation::createWithSpriteFrames(*badFrames,0.1f);
        Animate *badAnimate = Animate::create(badAnimation);
        RepeatForever *repeat = RepeatForever::create(badAnimate);
        bad -> runAction(repeat);
        delete badFrames;
 */
        
    }



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
    
    if(backGrounds->at(0)->getChildByName("badForPhysics") != NULL){
        Node* bad = backGrounds->at(0)->getChildByName("badForPhysics");
        //CCLOG("xは%f、yは%f",bad->getPositionX(),bad->getPositionY());
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