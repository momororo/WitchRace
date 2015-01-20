//
//  TutorialScene.cpp
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/20.
//
//

#include "TutorialScene.h"
#include "TitleScene.h"
#include <string.h>

//画面サイズの取得および設定
#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;
using namespace CocosDenshion;


//画面生成
Scene *TutorialScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = TutorialScene::create();
    scene -> addChild(layer);
    
    return scene;
    
}

//初期画面作成
bool TutorialScene::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    auto tutorialBg = Sprite::create("tutorialBg.png");
    tutorialBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this -> addChild(tutorialBg);
    
    setBackBt();
        
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(TutorialScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(TutorialScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(TutorialScene::onTouchEnded,this);
    
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

bool TutorialScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
    
    return true;
    
}

#pragma mark-
#pragma mark touchMoved

void TutorialScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}


#pragma mark-
#pragma mark touchEnded

void TutorialScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}

void TutorialScene::setBackBt(){
    
    //戻るボタンの作成
    auto backBt = Sprite::create("backBt.png");
    auto backBtTaped = Sprite::create("backBt.png");
    backBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(backBt, backBtTaped, [](Ref *ref){
        
        Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, TitleScene::createScene(), 1));
    
    });
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを配置
    startMenu->setPosition(Vec2(selfFrame.width/2,100 + backBt->getContentSize().height/2));
    this->addChild(startMenu);
    
}