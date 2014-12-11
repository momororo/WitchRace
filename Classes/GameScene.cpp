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
    
    
//背景処理
    //staticBackGroundの追加
    this -> addChild(BackGround::getInstance()->getStaticBackGround());
    
    //backGroundの追加
    this -> addChild(BackGround::getInstance()->getBackGround1());
    this -> addChild(BackGround::getInstance()->getBackGround2());
    this -> addChild(BackGround::getInstance()->getBackGround3());
    this -> addChild(BackGround::getInstance()->getBackGround4());
//背景処理終

    
//キキ処理
    //キキちゃんの追加
    this->addChild(Kiki::getInstance()->getKiki());
//キキ処理終

//イベント系処理
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
    
//イベント系処理終
    
    
//デバッグ
    BackGround::getInstance()->startBackGround();
//デバッグ終


    
    return true;
    
}



#pragma mark-
#pragma mark タッチ判定
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    
    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    
//キキ処理
    //キキのタップフラグをtrue
    Kiki::getInstance()->setTappedFlagOfKiki(true);
//キキ処理終
    
    
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

//キキ処理
    //キキのタップフラグをfalse
    Kiki::getInstance()->setTappedFlagOfKiki(false);
//キキ処理終

    
    
    
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
    
//キキ処理
    //キキちゃんの1フレーム毎の処理
    Kiki::getInstance()->kikiUpdate();
//キキ処理終

//背景処理
    //背景の1フレーム毎の処理(Layerが帰ってきたらaddchildする)
    Sprite *groundLayer = BackGround::getInstance()->backGroundUpdate();
    if(groundLayer != NULL){
        addChild(groundLayer);
    }
//背景処理終
    
    
    
}
