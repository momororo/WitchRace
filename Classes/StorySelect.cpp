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
    
    auto titleBk = Sprite::create("titleBk.png");
    titleBk -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this -> addChild(titleBk);
    
    
    setStory1();
    
    setBackBt();
    
    
    
    
    
    
    
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


void StorySelect::setStory1(){
    
    
    //スタートボタン作成
    auto story1 = Label::createWithSystemFont("stage1", "MagicSchoolOne", 150);
    story1 -> setColor(Color3B::BLACK);
    
    auto story1Taped = Label::createWithSystemFont("stage1", "MagicSchoolOne", 150);
    story1Taped -> setColor(Color3B::BLACK);
    story1Taped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(story1, story1Taped, CC_CALLBACK_1(StorySelect::story1CallBack, this));
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを画面中央に配置
    startMenu->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    this->addChild(startMenu);
    
    
    
}

void StorySelect::story1CallBack(cocos2d::Ref *pSender){
    
    //Director::getInstance()->replaceScene(GameScene::createScene());
    Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::createScene(), Color3B::WHITE));
}

void StorySelect::setBackBt(){
    
    //戻るボタンの作成
    auto backBt = Label::createWithSystemFont("Back", "MagicSchoolOne", 100);
    backBt -> setColor(Color3B::BLACK);
    
    auto backBtTaped = Label::createWithSystemFont("Back", "MagicSchoolOne", 100);
    backBtTaped-> setColor(Color3B::BLACK);
    backBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(backBt, backBtTaped, CC_CALLBACK_1(StorySelect::backBtCallBack, this));
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを配置
    startMenu->setPosition(Vec2(backBt->getContentSize().width/2, selfFrame.height-backBt->getContentSize().height/2));
    this->addChild(startMenu);
    
}

void StorySelect::backBtCallBack(cocos2d::Ref *pSender){

    Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, TitleScene::createScene(), 1));
    
}