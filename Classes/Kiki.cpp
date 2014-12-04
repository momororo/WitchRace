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

//キキちゃんのタップ状態の変更
void Kiki::setTappedFlagOfKiki(bool flag){
    tappedFlag = flag;
    return;
}



//キキちゃんの初期設定
Kiki::Kiki(){
 
    //キャラクタースプライトの生成
    kiki = Sprite::create("kiki.png");
    
    //キャラクタースプライトの大きさ
    kiki -> setScale(0.5);
    
    //ポジションの設定
    kiki->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    kiki->setPositionZ(zPositionOfKiki);
    
    //タグつけ
    kiki->setName("kiki");
    
    //物理体の生成
    auto kikiMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    auto kikiBody = PhysicsBody::createCircle((kiki->getContentSize().width/2),kikiMaterial);
    //重力による影響の可否
    kikiBody->setGravityEnable(false);
    //まじない
    kikiBody->setDynamic(true);
    kikiBody->setEnable(true);
    
    //ビットマスクはてきとう
    kikiBody->setCategoryBitmask(0x01);
    kikiBody->setCollisionBitmask(0);
    kikiBody->setContactTestBitmask(0x02);
    
    kiki->setPhysicsBody(kikiBody);


}

//キキちゃんの1フレーム毎の処理
void Kiki::kikiUpdate(){
    
    //タップされている場合は上昇！
        if (tappedFlag == true) {
            
            if (pGravity>1000) {
                
                pGravity = 1000;
                
            }else{
                
                pGravity+= 8;
                
            }
            
            
            kiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
        }else{
            
    //タップされていない場合は下降！
            if (pGravity<-1000) {
                
                pGravity = -1000;
                
            }else{
                
                pGravity -= 5;
                
            }
            kiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
            
        }
        
}
