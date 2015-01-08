//
//  GameScene.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "GameScene.h"
#include "LoadScene.h"
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
    this -> addChild(BackGround::getInstance()->getBackGround3());
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
    /********************* 上下に壁を用意 終 ************************/

    
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

    
    
    if (Kiki::getInstance()->getGamePlayFlag() == false && Kiki::getInstance()->getGameOverFlag() == false) {
        
        Kiki::getInstance()->startKiki();
        
        BackGround::getInstance()->startBackGround();

        
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
    
    
    
    
    
    
    
    
    return;
    
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
    

//キキ処理
    //キキのタップフラグをfalse
    Kiki::getInstance()->setTappedFlagOfKiki(false);
//キキ処理終

    
    
    
    return;
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    
}


 #pragma mark-
 #pragma mark 衝突判定
 bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact){
     
     
     
     if (Kiki::getInstance()->getGamePlayFlag() == true && Kiki::getInstance()->getGameOverFlag() == false) {

     
     //ゲームオーバーの処理へ
     makeGameOver();
         
         
     }
     
 
 return true;
 
 }
 
#pragma mark-
#pragma mark フレーム管理

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

#pragma mark-
#pragma mark ゲームオーバーの処理
void GameScene::makeGameOver(){
    
    
    //キキちゃんのgameOver処理
    Kiki::getInstance()->makeGameOver();
    
    
    //背景の処理
    BackGround::getInstance()->stopBackGround();
    
    
    //gameOver画面の生成
    auto gameOverBg = Sprite::create("pause_gameBg.png");
    gameOverBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverBg -> setGlobalZOrder(zOrderOfPause);
    this -> addChild(gameOverBg);
    
    
    //gameOverのlabel用スプライト
    auto gameOverOfLabel = Sprite::create();
    gameOverOfLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverOfLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    this -> addChild(gameOverOfLabel);
    
    
    
    
    
    //gameOver画面のparticle
    auto gameOverParticle = ParticleSystemQuad::create("particle_gameOver.plist");
    gameOverParticle -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    //gameOverParticle -> setGlobalZOrder(zOrderOfPause);
    gameOverBg -> addChild(gameOverParticle);
    
    
    //リトライボタン作成
    auto retryBt = Label::createWithSystemFont("Back", "MagicSchoolOne", 100);
    retryBt -> setColor(Color3B::BLACK);
    
    auto retryBtTaped = Label::createWithSystemFont("Back", "MagicSchoolOne", 100);
    retryBtTaped-> setColor(Color3B::BLACK);
    retryBtTaped -> setOpacity(150);
    
    auto retryBtnItem = MenuItemSprite::create(retryBt, retryBtTaped,[](Ref *ref){
    
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("GameScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    auto retryMenu = Menu::create(retryBtnItem, NULL);
    
    retryMenu->setPosition(Vec2(selfFrame.width/4, selfFrame.height/3));

    gameOverOfLabel->addChild(retryMenu);
    
    
    //ホームボタン作成
    auto homeBt = Label::createWithSystemFont("Home", "MagicSchoolOne", 100);
    homeBt -> setColor(Color3B::BLACK);
    
    auto homeBtTaped = Label::createWithSystemFont("Home", "MagicSchoolOne", 100);
    homeBtTaped-> setColor(Color3B::BLACK);
    homeBtTaped -> setOpacity(150);
    
    auto homeBtnItem = MenuItemSprite::create(homeBt, homeBtTaped,[](Ref *ref){
        
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("TitleScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    auto homeMenu = Menu::create(homeBtnItem, NULL);
    
    homeMenu->setPosition(Vec2(selfFrame.width*3/4, selfFrame.height/3));
    gameOverOfLabel->addChild(homeMenu);
    
    
    //「Game Over」ラベル作成
    auto gameOverLabel = Label::createWithSystemFont("Game Over", "MagicSchoolOne", 150);
    gameOverLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    gameOverLabel -> setColor(Color3B::BLACK);
    gameOverOfLabel -> addChild(gameOverLabel);
    
}
