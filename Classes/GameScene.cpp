//
//  GameScene.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "GameScene.h"
#include "LoadScene.h"
#include "NendInterstitialModule.h"
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
    this -> addChild(BackGround::getInstance()->getStaticBackGround(),0);
    
    //backGroundの追加
    this -> addChild(BackGround::getInstance()->getBackGround1(),1);
    this -> addChild(BackGround::getInstance()->getBackGround2(),1);
    this -> addChild(BackGround::getInstance()->getBackGround3(),1);
//背景処理終
    
//キャラクター処理
    
    auto userDef = UserDefault::getInstance();

    selectCharacter = userDef->getIntegerForKey("selectCharacter");

    //分岐
    this->addChild(CharacterSwitch::getInstance()->getCharacter());
//キャラクター処理終

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
    
//プレイ回数を加算(解析用)
    auto str = StringUtils::format("playCountFor%d", userDef->getIntegerForKey("selectStory"));
    auto playCount = userDef->getIntegerForKey(str.c_str());
    playCount++;
    userDef->setIntegerForKey(str.c_str(), playCount);
    
    return true;
    
}



#pragma mark-
#pragma mark タッチ判定
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){

    
    
    if (CharacterSwitch::getInstance()->getGamePlayFlag() == false && CharacterSwitch::getInstance()->getGameOverFlag() == false) {
        
        CharacterSwitch::getInstance()->startCharacter();
        
        BackGround::getInstance()->startBackGround();
        
#pragma mark デバッグ用
        struct timeval time;
        gettimeofday(&time, NULL);
        startTime = time.tv_sec * 1000ull + time.tv_usec / 1000ull;


        
    }
    
    //ポイントの取得
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    
//キキ処理
    //キキのタップフラグをtrue
    CharacterSwitch::getInstance()->setTappedFlagOfCharacter(true);
//キキ処理終
    
    
    return true;
    
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    
    
    
    
    
    
    
    return;
    
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
    

//キキ処理
    //キキのタップフラグをfalse
    CharacterSwitch::getInstance()->setTappedFlagOfCharacter(false);
//キキ処理終

    
    
    
    return;
    
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event){
    
    
}


 #pragma mark-
 #pragma mark 衝突判定
 bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact){
     
     
     
     if (CharacterSwitch::getInstance()->getGamePlayFlag() == true && CharacterSwitch::getInstance()->getGameOverFlag() == false) {

     
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
    CharacterSwitch::getInstance()->characterUpdate();
//キキ処理終

//背景処理
    //背景の1フレーム毎の処理(Layerが帰ってきたらaddchildする)
    BackGround::getInstance()->backGroundUpdate();
//背景処理終
    
//クリアか判定
    //30で全障害物設置完了
    //全障害物を通り抜けたらゲームクリア
    if(BackGround::getInstance()->getReplaceCount() > 30){
        //ゲームクリア
        this->makeGameClear();
    }
    
if(CharacterSwitch::getInstance()->getGamePlayFlag() == true){
#pragma  mark デバッグ用
    
    //時間の計測
    struct timeval time2;
    gettimeofday(&time2, NULL);
    unsigned long long currentTime = time2.tv_sec * 1000ull + time2.tv_usec / 1000ull;
    currentTime = currentTime - startTime;
    
    //秒数を取り出す
    unsigned long sec = currentTime / 1000;
    //ミリ秒を取り出す
    unsigned long mSec = (currentTime % 1000) / 10;
    
    //分を作る
    unsigned long min = (int)sec / 60;
    
    //分の量だけ秒から削る
    sec = sec - (min * 60);
    
    //CCLOG("時間 %02lu:%02lu:%02lu",min,sec,mSec);
    //CCLOG("%d",BackGround::getInstance()->getReplaceCount());
}
    
    
    
}

#pragma mark-
#pragma mark ゲームオーバーの処理
void GameScene::makeGameOver(){
    
    //nend表示
    NendInterstitialModule::showNADInterstitialView();
    
    
    //スケジュールの停止
    this->unscheduleUpdate();
    
    //キキちゃんのgameOver処理
    CharacterSwitch::getInstance()->makeGameOver();
    
    
    //背景の処理
    BackGround::getInstance()->stopBackGround();
    BackGround::getInstance()->makeGameOver();
    

    //gameOver画面の生成
    auto gameOverBg = Sprite::create("pause_gameBg.png");
    gameOverBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverBg -> setGlobalZOrder(0);
    gameOverBg -> setOpacity(255);
    this -> addChild(gameOverBg,2);

    
    //gameOverのlabel用スプライト
    auto gameOverOfLabel = Sprite::create();
    gameOverOfLabel -> setTextureRect(Rect( 0,0,selfFrame.width,selfFrame.height));
    gameOverOfLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverOfLabel -> setOpacity(0);
    gameOverOfLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    this -> addChild(gameOverOfLabel,3);

/*
    auto testSprite = Sprite::create();
    testSprite ->setColor(Color3B::WHITE);
    testSprite -> setOpacity(125);
    testSprite -> setTextureRect(Rect(0,0,selfFrame.width,selfFrame.height));
    testSprite -> setGlobalZOrder(0);
    testSprite -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/4*3));
    this -> addChild(testSprite);
*/
    
    
    
    
    
    
    //gameOver画面のparticle
    auto gameOverParticle = ParticleSystemQuad::create("particle_gameOver.plist");
    gameOverParticle -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    gameOverParticle -> setGlobalZOrder(0/*zOrderOfPause*/);
    gameOverBg -> addChild(gameOverParticle);
    
    
    //リトライボタン作成
    auto retryBt = Sprite::create("retryBt.png");
    retryBt -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto retryBtTaped = Sprite::create("retryBt.png");
    retryBtTaped -> setOpacity(150);
    retryBtTaped -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto retryBtnItem = MenuItemSprite::create(retryBt, retryBtTaped,[](Ref *ref){
    
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("GameScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    retryBtnItem -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto retryMenu = Menu::create(retryBtnItem, NULL);
    
    retryMenu->setPosition(Vec2(selfFrame.width*3/4, selfFrame.height/3));
    retryMenu->setGlobalZOrder(zOrderOfPauseLabel);
    retryMenu->setColor(Color3B::BLACK);

    this ->addChild(retryMenu);
    
    
    //ホームボタン作成
    auto homeBt = Sprite::create("homeBt.png");
    homeBt -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto homeBtTaped = Sprite::create("homeBt.png");
    homeBtTaped -> setOpacity(150);
    homeBtTaped -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto homeBtnItem = MenuItemSprite::create(homeBt, homeBtTaped,[](Ref *ref){
        
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("TitleScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    homeBtnItem -> setGlobalZOrder(zOrderOfPauseLabel);
    
    auto homeMenu = Menu::create(homeBtnItem, NULL);
    
    homeMenu->setPosition(Vec2(selfFrame.width/4, selfFrame.height/3));
    homeMenu->setGlobalZOrder(zOrderOfPauseLabel);
    homeMenu->setColor(Color3B::BLACK);
    this -> addChild(homeMenu);
    
    
    //「Game Over」ラベル作成
    auto gameOverLabel = Label::createWithSystemFont("Game Over", "MagicSchoolOne", 150);
    gameOverLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    gameOverLabel -> setColor(Color3B::BLACK);
    gameOverOfLabel -> addChild(gameOverLabel);
    
    gameOverOfLabel -> setGlobalZOrder(300);
        
}

#pragma mark-
#pragma mark ゲームクリアの処理

void GameScene::makeGameClear(){
    
    //nend表示
    NendInterstitialModule::showNADInterstitialView();
    
    //スケジュールの停止
    this->unscheduleUpdate();
    
    //キキちゃんのgameOver処理
    CharacterSwitch::getInstance()->makeGameOver();
    
    
    //背景の処理
    BackGround::getInstance()->stopBackGround();
    BackGround::getInstance()->makeGameOver();
    
//ゲームクリア特有の処理
    //選択したステージとクリアステージを比べ、イコールの場合は次のステージを解放
    //ただし変数が4の場合は全ステージクリア済のため、何もしない
    auto userDef = UserDefault::getInstance();
    auto clearStory = userDef->getIntegerForKey("clearStory");
    auto selectStory = userDef->getIntegerForKey("selectStory");
    if (clearStory == selectStory && clearStory != 4) {
        clearStory++;
        //クリアステージの記憶変数に挿入
        userDef->setIntegerForKey("clearStory", clearStory);
    }
    
    //クリア回数に登録
    auto str = StringUtils::format("clearCountFor%d",selectStory);
    auto clearCount = userDef->getIntegerForKey(str.c_str());
    clearCount++;
    userDef->setIntegerForKey(str.c_str(), clearCount);
    
    
//終
    
    
    //gameClear画面の生成
    auto gameOverBg = Sprite::create("pause_gameClear.png");
    gameOverBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverBg -> setGlobalZOrder(0);
    gameOverBg -> setOpacity(255);
    this -> addChild(gameOverBg,2);
    
    
    //gameClearのlabel用スプライト
    auto gameOverOfLabel = Sprite::create();
    gameOverOfLabel -> setTextureRect(Rect( 0,0,selfFrame.width,selfFrame.height));
    gameOverOfLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    gameOverOfLabel -> setOpacity(0);
    gameOverOfLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    this -> addChild(gameOverOfLabel,3);
    /*
     auto testSprite = Sprite::create();
     testSprite ->setColor(Color3B::WHITE);
     testSprite -> setOpacity(125);
     testSprite -> setTextureRect(Rect(0,0,selfFrame.width,selfFrame.height));
     testSprite -> setGlobalZOrder(0);
     testSprite -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/4*3));
     this -> addChild(testSprite);
     */
    
    //gameClear画面のparticle
    auto gameOverParticle = ParticleSystemQuad::create("particle_gameClear.plist");
    gameOverParticle -> setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    gameOverParticle -> setGlobalZOrder(0/*zOrderOfPause*/);
    gameOverOfLabel -> addChild(gameOverParticle,1);
    
//全ステージクリアの場合、今のところボタン生成の処理をスキップします
    if(selectStory != 4){
        //ネクストボタン作成
        auto nextBt = Sprite::create("nextBt.png");
        nextBt ->setGlobalZOrder(zOrderOfPauseLabel);
        
        auto nextBtTaped = Sprite::create("nextBt.png");
        nextBtTaped -> setOpacity(150);
        nextBtTaped ->setGlobalZOrder(zOrderOfPauseLabel);
        
        auto nextBtnItem = MenuItemSprite::create(nextBt, nextBtTaped,[](Ref *ref){
            
            //セレクトステージに1足し込み(次のステージへ)
            auto userDef = UserDefault::getInstance();
            auto selectStory = userDef->getIntegerForKey("selectStory");
            selectStory++;
            userDef->setIntegerForKey("selectStory", selectStory);
            
            Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("GameScene"));
            
            Director::getInstance()->replaceScene(nextScene);
            
        });
        nextBtnItem ->setGlobalZOrder(zOrderOfPauseLabel);
        
        auto nextMenu = Menu::create(nextBtnItem, NULL);
        
        nextMenu->setPosition(Vec2(selfFrame.width*3/4, selfFrame.height/3));
        nextMenu ->setGlobalZOrder(zOrderOfPauseLabel);
        nextMenu->setColor(Color3B(255, 255, 177));
        
        gameOverOfLabel->addChild(nextMenu,2);
        
    }
    
    
    //ホームボタン作成
    auto homeBt = Sprite::create("homeBt.png");
    
    auto homeBtTaped = Sprite::create("homeBt.png");
    homeBtTaped -> setOpacity(150);
    
    auto homeBtnItem = MenuItemSprite::create(homeBt, homeBtTaped,[](Ref *ref){
        
        Scene* nextScene = CCTransitionFade::create(0.5f, LoadScene::createScene("TitleScene"));
        
        Director::getInstance()->replaceScene(nextScene);
        
    });
    
    auto homeMenu = Menu::create(homeBtnItem, NULL);
    
    homeMenu->setPosition(Vec2(selfFrame.width/4, selfFrame.height/3));
    homeMenu->setColor(Color3B(255, 255, 177));
    gameOverOfLabel->addChild(homeMenu,2);
    
    
    //「Game Clear」ラベル作成
    auto gameOverLabel = Label::createWithSystemFont("Game Clear", "MagicSchoolOne", 150);
    gameOverLabel -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/3));
    gameOverLabel -> setColor(Color3B(255, 255, 177));
    gameOverLabel -> setGlobalZOrder(zOrderOfPauseLabel);
    gameOverOfLabel -> addChild(gameOverLabel,3);
    
    
}
