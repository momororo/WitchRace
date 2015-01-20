//
//  SelectCharacterScene.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#include "SelectCharacterScene.h"
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
    
    bg->setPosition(Vec2(selfFrame.width/2,selfFrame.height/2));
    bg->setName("bg");
    
//ボタンの作成(for文で回す？？)
    
    
    
    

    
    
    
    return true;
    
}