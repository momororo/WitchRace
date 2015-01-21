//
//  SelectCharacterScene.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#include "SelectCharacterScene.h"
#include "TitleScene.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()


Scene* SelectCharacterScene::createScene()
{
    
    
    auto scene = Scene::createWithPhysics();
    auto layer = SelectCharacterScene::create();
    scene -> addChild(layer);
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // return the scene
    return scene;
}

bool SelectCharacterScene::init()

{
    
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//型枠の作成
    auto bg = Sprite::create("character_Bg.png");
    
    bg->setName("bg");
    bg->setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    this->addChild(bg);
    
//ボタンの作成(for文で回す？？)
    
    for(int idx = 0; idx < 5;idx++){
        

        //ユーザーデフォルトを呼び出してキャラクターフラグを確認
        auto userDef = UserDefault::getInstance();
        //デバグ
        userDef->setBoolForKey("characterFlag1", true);
        
        auto characterFlag = userDef->getBoolForKey(StringUtils::format("characterFlag%d",idx).c_str());

        //スプライトの呼び出し
        Sprite *character;

//スプライトの呼び出し
        if(characterFlag == true){
            //キャラクターの画像に
            switch (idx) {
                case 0:character = Sprite::create("character_broomOfKiki.png"); break;
                case 1:character = Sprite::create("character_sPhysicsOfKiki.png"); break;
                case 2:character = Sprite::create("character_harryPotter.png"); break;
                case 3:character = Sprite::create("character_fordAnglia.png"); break;
                case 4:character = Sprite::create("character_porcoRosso.png"); break;
                default:break;
            }
        }else{
            //はてなの画像を呼び出し
            character = Sprite::create("character_lock.png");
        }
        
        //タップ後のボタンの透明度を変更する
        character->setOpacity(128);
        
        //後で一括して透明度変更する際に配列つかうことにしました
        characters->pushBack(character);
        
//タップ後のスプライトの呼び出し
        
        Sprite *tappedCharacter;
        
        //スプライトの呼び出し
        if(characterFlag == true){
            //キャラクターの画像に
            switch (idx) {
                case 0:tappedCharacter = Sprite::create("character_broomOfKiki.png"); break;
                case 1:tappedCharacter = Sprite::create("character_sPhysicsOfKiki.png"); break;
                case 2:tappedCharacter = Sprite::create("character_harryPotter.png"); break;
                case 3:tappedCharacter = Sprite::create("character_fordAnglia.png"); break;
                case 4:tappedCharacter = Sprite::create("character_porcoRosso.png"); break;
                default:break;
            }

            //タップ後のボタンの透明度を変更する
            tappedCharacter->setOpacity(255);

        }else{
            //はてなの画像を呼び出し
            tappedCharacter = Sprite::create("character_lock.png");
            //タップ後のボタンの透明度を変更する
            tappedCharacter->setOpacity(128);
        }

        
//メニューボタンを作成していく
        MenuItemSprite *pBtnItem;
        
        if(characterFlag == true){
        //メニューアイテムの作成
            pBtnItem = MenuItemSprite::create(character, tappedCharacter, [&](Ref *ref){
            
            
            
                /**
                 *  pSenderをMenuItemにキャスト
                 *  なお、中身はpBtnItem
                 */
                MenuItem* button = (MenuItem*)ref;

                
                //フラグの設定
                userDef->setIntegerForKey("selectCharacter",button->getTag());
                CCLog("%d",button->getTag());
                
                //透明度を一括変更
                for(auto character : *characters){
                    character->setOpacity(128);
                }
                //対象のボタンの透明度を変更
                characters->at(button->getTag())->setOpacity(255);
                

            
            });
        
        }else{
            
            pBtnItem = MenuItemSprite::create(character, tappedCharacter,NULL);
            
        }
        
        pBtnItem->setTag(idx);
        
        //メニューの作成　pMenuの中にpBtnItemを入れる
        auto Menu = Menu::create(pBtnItem, NULL);
        

        //ポジションを設定
        switch (idx) {
            case 0:Menu->setPosition(Vec2(selfFrame.width/6*1,selfFrame.height/10*5));break;
            case 1:Menu->setPosition(Vec2(selfFrame.width/6*2,selfFrame.height/10*7));break;
            case 2:Menu->setPosition(Vec2(selfFrame.width/6*3,selfFrame.height/10*5));break;
            case 3:Menu->setPosition(Vec2(selfFrame.width/6*4,selfFrame.height/10*7));break;
            case 4:Menu->setPosition(Vec2(selfFrame.width/6*5,selfFrame.height/10*5));break;
            default:break;

        
        }
        
        bg->addChild(Menu);
        
        //キキの色を黒に(初期位置設定)
        if(idx == 0){
            character->setOpacity(255);
        }
        
        
    }
    
    
    
    
    this->setBackBt();
    
    

    
    
    
    return true;
    
}


void SelectCharacterScene::setBackBt(){
    
    //戻るボタンの作成
    auto backBt = Sprite::create("backBt.png");
    auto backBtTaped = Sprite::create("backBt.png");
    backBtTaped -> setOpacity(150);
    
    //メニューアイテムの作成
    auto pBtnItem = MenuItemSprite::create(backBt, backBtTaped, CC_CALLBACK_1(SelectCharacterScene::backBtCallBack, this));
    
    //メニューの作成　pMenuの中にpBtnItemを入れる
    auto startMenu = Menu::create(pBtnItem, NULL);
    
    //pMenuを配置
    startMenu->setPosition(Vec2(selfFrame.width/20*15,selfFrame.height/20*3));
    
    this->getChildByName("bg")->addChild(startMenu);
    
}

void SelectCharacterScene::backBtCallBack(cocos2d::Ref *pSender){
    
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, TitleScene::createScene(), 1));
    
}