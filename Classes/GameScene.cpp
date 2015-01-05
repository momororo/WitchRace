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
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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
    
    
    /********************* 上下に壁を用意 ************************/
    //上の壁
    auto upperWall = Sprite::create();
    upperWall -> setTextureRect(Rect(0, 0, selfFrame.width, 2));
    upperWall -> setPosition(Vec2(selfFrame.width/2,selfFrame.height+upperWall->getContentSize().height/2));
    auto upperBody = PhysicsBody::createBox(Size(upperWall->getContentSize()));

    //重力による影響の可否
    upperBody -> setDynamic(false);
    upperBody -> setEnable(true);
    
    //ビットマスクはてきとう
    upperBody -> setCategoryBitmask(0x02);
    upperBody -> setCollisionBitmask(0);
    upperBody -> setContactTestBitmask(0x01);
    
    upperWall -> setPhysicsBody(upperBody);
    
    this -> addChild(upperWall);
    
    //下の壁
    auto lowerWall = Sprite::create();
    lowerWall -> setTextureRect(Rect(0, 0, selfFrame.width, 2));
    lowerWall -> setPosition(Vec2(selfFrame.width/2,-(lowerWall->getContentSize().height/2)));
    
    auto lowerBody = PhysicsBody::createBox(Size(upperWall->getContentSize()));
    
    //重力による影響の可否
    lowerBody -> setDynamic(false);
    lowerBody -> setEnable(true);
    
    //ビットマスクはてきとう
    lowerBody -> setCategoryBitmask(0x02);
    lowerBody -> setCollisionBitmask(0);
    lowerBody -> setContactTestBitmask(0x01);
    
    lowerWall -> setPhysicsBody(lowerBody);
    
    this -> addChild(lowerWall);
    
    
    
/*
    //敵スプライト(今回はコウモリ)の画像アニメーションの動作作成
    //羽を上下させるため、２種類(bad_1.png,bad_2.png)の画像をzwoptexにて編集・作成
    //plistから画像データの読み込み
    SpriteFrameCache::getInstance() -> addSpriteFramesWithFile("bad.plist");
    
    //コウモリのスプライトを作成
    Sprite *bad = Sprite::createWithSpriteFrameName("bad_1.png");
    bad -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    bad -> setPositionZ(100);
    this -> addChild(bad);
    
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
    
    
    
    
    
    
    
    
    /*************　　タッチイベント設定  終 ****************/
    
    
    /*************　  衝突イベント設定   ****************/
    
     auto contactListener = EventListenerPhysicsContact::create();
     contactListener -> onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin,this);
     
     _eventDispatcher -> addEventListenerWithSceneGraphPriority(contactListener,this);
    
    /*************　  衝突イベント設定  終 ****************/


    
    this->scheduleUpdate();
    
//イベント系処理終





    
    return true;
    
}



#pragma mark-
#pragma mark タッチ判定
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){

    //スワイプ中の処理
    CCLOG("touchBegan");
    
    //デバッグ
    BackGround::getInstance()->startBackGround();
    //Kiki::getInstance()->startKiki();
    //デバッグ終
    
    if (Kiki::getInstance()->getGamePlayFlag() == false) {
        
        Kiki::getInstance()->startKiki();
        
    }
    
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
     
     
     auto nodeA = contact.getShapeA()->getBody()->getNode();
     auto nodeB = contact.getShapeB()->getBody()->getNode();
     
     CCLOG("ぶつかったよー");
     
     auto particle = ParticleSystemQuad::create("particleFlower.plist");
     Kiki::getInstance()->getKiki() -> addChild(particle);
    
 
     
 
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
    BackGround::getInstance()->backGroundUpdate();
//背景処理終
    
    
    
}

