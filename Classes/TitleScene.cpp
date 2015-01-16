#include "TitleScene.h"
#include "StorySelect.h"
#include "GameScene.h"
#include <string.h>
//#include "NendModule.h"
//#include "NendInterstitialModule.h"
//#include "AppCCloudPlugin.h"

//画面サイズの取得および設定
#define selfFrame Director::getInstance() -> getWinSize()

USING_NS_CC;
using namespace CocosDenshion;

//保存先の生成
//UserDefault *userDef = UserDefault::getInstance();

//画面生成
Scene *TitleScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene -> addChild(layer);
    
    return scene;
    
}

//初期画面作成
bool TitleScene::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    auto titleBg = Sprite::create("titleBg.png");
    titleBg -> setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this -> addChild(titleBg);
    /*
    auto titleSignboard = Sprite::create("titleObject.png");
    titleSignboard -> setPosition(Vec2(selfFrame.width/2,selfFrame.height*3/4));
    this -> addChild(titleSignboard);
    */
    setStartBt();
    setTutorialBt();
    setRankingBt();
    setCharactorBt();
    setTwitterBt();
    setOtherBt();
    
    
    
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
    
    
    //didsimulate
    this->scheduleUpdate();
    
    //MARK::ゲームセンターログイン
    //GameCenterBridge::loginGameCenter();


    
    
    
    /**************　タッチイベント設定  ******************/
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    //listener -> setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割り当て
    listener -> onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan,this);
    listener -> onTouchMoved = CC_CALLBACK_2(TitleScene::onTouchMoved,this);
    listener -> onTouchEnded = CC_CALLBACK_2(TitleScene::onTouchEnded,this);
    
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

//MARK::AppCCloudの設定と削除
/*
void TitleScene::setAppCCloud(){
    
    appCCloudBt = Sprite::create("other.png");
    appCCloudBt -> setPosition(Vec2((selfFrame.width)-(appCCloudBt->getContentSize().width*2/3),(selfFrame.height)-(appCCloudBt->getContentSize().height*2/3)));
    this -> addChild(appCCloudBt);
    
    appFlag = true;

}

void TitleScene::removeAppCCloud(){
    
    appCCloudBt -> removeFromParent();
    
    appFlag = false;

}
*/


#pragma mark-
#pragma mark touchBegan

bool TitleScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //タップ開始時の処理
    CCLOG("touchBegan");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);

    
    return true;
    
}

#pragma mark-
#pragma mark touchMoved

void TitleScene::onTouchMoved(Touch *touch, Event *unused_event){
    
    //スワイプ中の処理
    CCLOG("touchMoved");
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}


#pragma mark-
#pragma mark touchEnded

void TitleScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    //タップ終了時
    CCLOG("touchEnded");
    
    Point touchPoint = Vec2(touch->getLocation().x,touch->getLocation().y);
    
}

//MARK::ストーリーボタン
void TitleScene::setStartBt(){

    
    //ストーリーボタン作成
    auto startBt = Sprite::create("storyBt.png");
    
    auto startBtTaped = Sprite::create("storyBt.png");
    startBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(startBt, startBtTaped, [](Ref *ref){
        
        Director::getInstance()->replaceScene(TransitionPageTurn::create(1, StorySelect::createScene(), 0));
        
    });
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを画面中央に配置
    startMenu->setPosition(Vec2(selfFrame.width/2+selfFrame.width/40, selfFrame.height*0.48));
    this->addChild(startMenu);
    
}

//MARK::チュートリアルボタン
void TitleScene::setTutorialBt(){
    
    //チュートリアル作成
    auto tutorialBt = Sprite::create("tutorialBt.png");
    
    auto tutorialBtTaped = Sprite::create("tutorialBt.png");
    tutorialBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(tutorialBt, tutorialBtTaped, [](Ref *ref){
        
        //遊び方を呼び出すメソッド
        CCLOG("激ムズの糸と同じ操作方法だよ〜！");
        
    });
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto tutorialMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを画面中央に配置
    tutorialMenu->setPosition(Vec2(selfFrame.width*3/4+selfFrame.width/40, selfFrame.height*0.36));
    this->addChild(tutorialMenu);
    
}

//MARK::ランキングボタン
void TitleScene::setRankingBt(){
    
    
    // ランキングボタン作成
    auto rankingBt = Sprite::create("rankingBt.png");
    
    auto rankingBtTaped = Sprite::create("rankingBt.png");
    rankingBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(rankingBt, rankingBtTaped, [](Ref *ref){
        
        //ランキング呼び出すメソッド
        CCLOG("アチーブメントになるのかな？");
        
    });
    
    //メニューの作成
    auto rankingMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    rankingMenu->setPosition(Vec2(selfFrame.width/4+selfFrame.width/40, selfFrame.height*0.36));
    this->addChild(rankingMenu);
    
}

//MARK::その他のゲームボタン
void TitleScene::setOtherBt(){
    
    //その他のゲームボタン作成
    auto otherBt = Sprite::create("otherBt.png");
    
    auto otherBtTaped = Sprite::create("otherBt.png");
    otherBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(otherBt, otherBtTaped, [](Ref *ref){
        
        //appCCloudのメソッド
        CCLOG("誰かインストールしてちょ");
        
    });
    
    //メニューの作成
    auto otherMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    otherMenu->setPosition(Vec2(selfFrame.width/3+selfFrame.width/40, selfFrame.height*0.196));
    this->addChild(otherMenu);
    
}

//MARK::キャラクター購入ボタン
void TitleScene::setCharactorBt(){
    
    
    //キャラクター購入ボタン作成
    auto charactorBt = Sprite::create("charactorBt.png");
    
    auto charactorBtTaped = Sprite::create("charactorBt.png");
    charactorBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(charactorBt, charactorBtTaped, [](Ref *ref){
        
        //キャラクター購入画面を呼び出すメソッド
        CCLOG("キャラクター購入でhappy!!");
        
    });
    
    //メニューの作成
    auto charactorMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    charactorMenu->setPosition(Vec2(selfFrame.width/2+selfFrame.width/40, selfFrame.height*0.32));
    this->addChild(charactorMenu);
    
}

//MARK::ツイッターボタン
void TitleScene::setTwitterBt(){
    
    
    //ツイッターボタン作成
    auto twitterBt = Sprite::create("twitterBt.png");
    
    auto twitterBtTaped = Sprite::create("twitterBt.png");
    twitterBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(twitterBt, twitterBtTaped, [](Ref *ref){
        
        //ツイッター呼び出し
        CCLOG("ツイートしちゃうぞ♪");
        
    });
    
    //メニューの作成
    auto twitterMenu = Menu::create(pBtnItem, NULL);
    
    //Menuを画面中央に配置
    twitterMenu->setPosition(Vec2(selfFrame.width*2/3+selfFrame.width/40, selfFrame.height*0.196));
    this->addChild(twitterMenu);
    
}





#pragma mark-
#pragma mark:フレーム管理

void TitleScene::update( float frame )
{
    
}
