//
//  StorySelect.cpp
//  WitchRace
//
//  Created by 新井脩司 on 2014/12/16.
//
//

#include "StorySelect.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <string.h>

//画面サイズの取得および設定
#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;
using namespace CocosDenshion;


//画面生成
Scene *StorySelect::createScene(){
    
    auto scene = Scene::create();
    auto layer = StorySelect::create();
    scene -> addChild(layer);
    
    return scene;
    
}

//初期画面作成
bool StorySelect::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    auto titleBk = Sprite::create("titleBg.png");
    titleBk -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this -> addChild(titleBk);
    
    auto ssLabel = Label::createWithSystemFont("story select", "MagicSchoolOne", 100);
    ssLabel ->setPosition(Vec2(selfFrame.width/2,selfFrame.height-ssLabel->getContentSize().height/2));
    ssLabel -> setColor(Color3B::BLACK);
    this -> addChild(ssLabel);
    
    auto upperOrnament = Sprite::create("ssUpperOrnament.png");
    upperOrnament -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*0.82));
    this -> addChild(upperOrnament);
    
    auto downerOrnament = Sprite::create("ssDownerOrnament.png");
    downerOrnament -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*2/9));
    this -> addChild(downerOrnament);
    
    
    setBackBt();
    
    setSelectButton();


    
    
    
    
    
    /* 効果音の設定
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("cursor1.mp3");
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("decision7.mp3");
     SimpleAudioEngine::getInstance()->setEffectsVolume(0.6f);
     */
    
    
    /* BGMの設定
     SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmShelling.mp3",true);
     音量
     SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
     */
    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(StorySelect::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(StorySelect::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(StorySelect::onTouchEnded,this);
    
    //イベントディスパッチャようにリスナーを追加する
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
    
    /*************　　タッチイベント設定  終 ****************/
    
    
    //MARK::nendの設定
    //ネンドの呼び出し(ヘッダー)
    /*char apiKey[] = "5aa579f521da85a055c5076641efc68202d5e8e2";
     char spotID[] = "262876";
     NendModule::createNADViewBottom(apiKey, spotID);
     
     //ネンドの呼び出し(飛び出す)
     char interstitialApiKey[] = "6b027f392e0cf11d378908fc4027f1755d6422ad";
     char interstitialSpotID[] = "266067";
     NendInterstitialModule::createNADInterstitial(interstitialApiKey, interstitialSpotID);
     */
    
    
    
    return true;
    
    
}


#pragma mark-
#pragma mark touchBegan

bool StorySelect::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    
    return true;
    
}

#pragma mark-
#pragma mark touchMoved

void StorySelect::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}


#pragma mark-
#pragma mark touchEnded

void StorySelect::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}


void StorySelect::setSelectButton(){
    
    
    
    auto userDef = UserDefault::getInstance();
    auto clearStory = userDef->getIntegerForKey("clearStory");
    
    
    for (int idx = 0 ; idx <= clearStory ; idx++){
        
        //セレクトボタン作成
        auto button = Label::createWithSystemFont("story" + StringUtils::format("%d",idx + 1), "MagicSchoolOne", 100);
        button -> setColor(Color3B::BLACK);
        
        auto tappedButton = Label::createWithSystemFont("story" + StringUtils::format("%d",idx + 1), "MagicSchoolOne", 100);
        tappedButton -> setColor(Color3B::BLACK);
        tappedButton -> setOpacity(150);
        
        //メニューアイテムの作成
        auto pBtnItem = MenuItemSprite::create(button, tappedButton, CC_CALLBACK_1(StorySelect::selectStoryCallBack, this));
        
        /**
         *  コールバックのメソッドでgetTagする用に設定
         *  なお、メニューアイテムをコールバックする際の引数は上記変数
         */
        pBtnItem->setTag(idx);

        
        //メニューの作成　pMenuの中にpBtnItemを入れる
        auto startMenu = Menu::create(pBtnItem, NULL);
        
        //pMenuを配置(適当)
        startMenu->setPosition(Vec2(selfFrame.width/2, selfFrame.height*7/8 - selfFrame.height/5*4 / 7 * (idx + 1)));
        startMenu->setName("startMenu");
        
        this->addChild(startMenu);
        
        
        
    }
    
    nextScene = true;
    
    
    
}

void StorySelect::selectStoryCallBack(cocos2d::Ref *pSender){
    
    //Director::getInstance()->replaceScene(GameScene::createScene());
    if (nextScene == true) {
        
        /**
         *  pSenderをMenuItemにキャスト
         *  なお、中身はpBtnItem
         */
        MenuItem* button = (MenuItem*)pSender;
        

        
        //選択したステージの値を保存しておく
        auto userDef = UserDefault::getInstance();
        userDef->setIntegerForKey("selectStory",button->getTag());

        
    
        Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::createScene(), Color3B::WHITE));
        nextScene = false;
        
    }else{
        
        return;
    
    }
    
}

void StorySelect::setBackBt(){
    
    //戻るボタンの作成
    auto backBt = Sprite::create("backBt.png");
    auto backBtTaped = Sprite::create("backBt.png");
    backBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(backBt, backBtTaped, CC_CALLBACK_1(StorySelect::backBtCallBack, this));
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを配置
    startMenu->setPosition(Vec2(selfFrame.width/2,100 + backBt->getContentSize().height/2));
    this->addChild(startMenu);
    
}

void StorySelect::backBtCallBack(cocos2d::Ref *pSender){

    Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, TitleScene::createScene(), 1));
    
}