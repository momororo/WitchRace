//
//  GameScene.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "GameScene.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

Scene* GameScene::createScene()
{

    
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene -> addChild(layer);
    // return the scene
    return scene;
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //背景色のグラデーション
    auto bgColor = LayerColor::create(Color4B::ORANGE);
    this -> addChild(bgColor);
    
    //キキちゃんの追加
    this->addChild(Kiki::getInstance()->getKiki());
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    listener -> onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/
    
    
    /*************　  衝突イベント設定   ****************/
    
     auto contactListener = EventListenerPhysicsContact::create();
     contactListener -> onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,this);
     
     _eventDispatcher -> addEventListenerWithSceneGraphPriority(contactListener,this);
    
    /*************　  衝突イベント設定  終 ****************/


    
    this->scheduleUpdate();
    
    return true;
    
}



#pragma mark-
#pragma mark タッチ判定
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    
    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    //キキのタップフラグをtrue
    Kiki::getInstance()->setTappedFlagOfKiki(true);
    
    
    return true;
    
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    
    
    
    
    
    
    
    return;
    
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    //キキのタップフラグをfalse
    Kiki::getInstance()->setTappedFlagOfKiki(false);

    
    
    
    return;
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    //タッチキャンセル
    CCLOG("touchCancelled");
    
}


 #pragma mark-
 #pragma mark 衝突判定
 bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact){
 
// auto nodeA = contact.getShapeA()->getBody()->getNode();
// auto nodeB = contact.getShapeB()->getBody()->getNode();
 
 return true;
 }
 
#pragma mark-
#pragma mark:フレーム管理

void GameScene::update( float frame )
{
    //キキちゃんの1フレーム毎の処理
    Kiki::getInstance()->kikiUpdate();
    
}
