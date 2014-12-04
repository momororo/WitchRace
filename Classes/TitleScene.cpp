#include "TitleScene.h"
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
    
    auto scene = Scene::create();//WithPhysics();   ←物理設定の場合
    auto layer = TitleScene::create();
    scene -> addChild(layer);
    
    
    /* 物理設定
    auto world = scene -> getPhysicsWorld();
    cocos2d::Vect gravity;
    gravity.setPoint(0, -50);
    world -> setGravity(gravity);
    */
    
    //物理体の可視化
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    
    return scene;
    
}

//初期画面作成
bool TitleScene::init(){
    
    
    if (!Layer::init()) {
        return false;
    }
    
    //背景色のグラデーション
    auto bgColor = LayerColor::create(Color4B(255,246,213,255));
    this -> addChild(bgColor);
    
   
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



#pragma mark-
#pragma mark:フレーム管理

void TitleScene::update( float frame )
{
    
}
