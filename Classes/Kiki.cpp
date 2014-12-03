//
//  Kiki.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "Kiki.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
Kiki* Kiki::kikiInstance = NULL;

//シングルトン
Kiki* Kiki::getInstance(){
    
    if(!kikiInstance){
        kikiInstance = new Kiki();
    }
    
    
    return kikiInstance;
    
}

//キキちゃんのスプライトをGET
Sprite* Kiki::getKiki(){
    return kiki;
}


//キキちゃんの初期設定
Kiki::Kiki(){
 
    //キャラクタースプライトの生成
    kiki = Sprite::create();
    kiki->setTextureRect(cocos2d::Rect(0, 0, selfFrame.width/10, selfFrame.width/10));
    
    kiki->setColor(Color3B::BLACK);
    
    //ポジションの設定
    kiki->setPosition(Vec2(selfFrame.width/2, selfFrame.height/2));
    
    //物理体の生成
    auto kikiMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    auto kikiBody = PhysicsBody::createCircle((kiki->getContentSize().width/2),kikiMaterial);
    kikiBody->setDynamic(true); // 重力の影響を受けない
    kikiBody->setEnable(true);
    
    //ビットマスクはてきとう
    kikiBody->setCategoryBitmask(0x01);
    kikiBody->setCollisionBitmask(0);
    kikiBody->setContactTestBitmask(0x02);
    
    kiki->setPhysicsBody(kikiBody);


}