//
//  BroomOfKiki.cpp
//  WitchRace
//
//  Created by 新井脩司 on 2015/01/21.
//
//

#include "BroomOfKiki.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
BroomOfKiki* BroomOfKiki::broomOfKikiInstance = NULL;

//シングルトン
BroomOfKiki* BroomOfKiki::getInstance(){
    
    if(!broomOfKikiInstance){
        broomOfKikiInstance = new BroomOfKiki();
    }
    
    
    return broomOfKikiInstance;
    
}
//デストラクタ
void BroomOfKiki::destroyInstance() {
    if (broomOfKikiInstance != NULL){
        delete broomOfKikiInstance;
        
        broomOfKikiInstance = NULL;
    }
}


//自分の箒に乗ったキキのスプライトをGET
Sprite* BroomOfKiki::getCharacter(){
    return broomOfKiki;
}


//自分の箒に乗ったキキの動作開始
void BroomOfKiki::startCharacter(){
    
    broomOfKiki->getPhysicsBody()->setEnable(true);
    broom -> getPhysicsBody()-> setEnable(true);
    
}

//自分の箒に乗ったキキの動作停止
void BroomOfKiki::stopCharacter(){
    
    broomOfKiki->getPhysicsBody()->setEnable(false);
    broom -> getPhysicsBody()-> setEnable(false);
    
}


//自分の箒に乗ったキキの初期設定
BroomOfKiki::BroomOfKiki(){
    
    //キャラクタースプライトの生成(UP時)
    broomOfKiki = Sprite::create("kiki_up.png");
    //影
    broomOfKikiShadow = Sprite::create("kiki_up_shadow.png");
    
    //キャラクタースプライトの大きさ
    broomOfKiki -> setScale(0.5);
    
    //影を実体に入れちゃう
    broomOfKiki->addChild(broomOfKikiShadow);
    //影のポジション調整
    broomOfKikiShadow->setPosition(broomOfKiki->getContentSize().width/2,broomOfKiki->getContentSize().height/2);
    //影の透明度を設定
    broomOfKikiShadow->setOpacity(180);
    broomOfKikiShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //kikiShadow -> setScale(kiki->getScale());
    
    
    //ポジションの設定
    broomOfKiki->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    broomOfKiki->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    broomOfKiki->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    broomOfKiki->setTag(1);
    
    //物理体の生成
    auto broomOfKikiMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point spritePoints[5]{
        
        Vec2(-8,-20),Vec2(-16,0),Vec2(-8,18),Vec2(13,13),Vec2(8,-18)
    
    };
    
    auto broomOfKikiBody = PhysicsBody::createPolygon(spritePoints, 5,broomOfKikiMaterial);
    
    
    //重力による影響の可否
    broomOfKikiBody->setGravityEnable(false);
    //まじない
    broomOfKikiBody->setDynamic(true);
    broomOfKikiBody->setEnable(false);
    
    //ビットマスクはてきとう
    broomOfKikiBody->setCategoryBitmask(0x01);
    broomOfKikiBody->setCollisionBitmask(0);
    broomOfKikiBody->setContactTestBitmask(0x02);
    
    broomOfKiki->setPhysicsBody(broomOfKikiBody);
    
    
    //箒の設定
    broom = Sprite::create();
    broom -> setTextureRect(Rect(0, 0, 10, 10));
    broom -> setPosition(Vec2(0,0));
    broom -> setVisible(false);
    
    auto broomMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point broomPoint[4]={
        
        Vec2(40,15), Vec2(10,25), Vec2(40,35), Vec2(120,35)
        
    };
    
    auto broomBody = PhysicsBody::createPolygon(broomPoint,4,broomMaterial);
    broomBody -> setGravityEnable(false);
    broomBody -> setDynamic(true);
    broomBody -> setEnable(false);
    
    broomBody ->setCategoryBitmask(0x01);
    broomBody ->setCollisionBitmask(0);
    broomBody ->setContactTestBitmask(0x02);
    
    broom -> setPhysicsBody(broomBody);
    
    broomOfKiki -> addChild(broom);
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    broomOfKikiParticle = ParticleSystemQuad::create("kikiparticle.plist");
    broomOfKikiParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    broomOfKikiParticle->setPosition(Vec2(3,broomOfKiki->getContentSize().height/3-6));
    broomOfKikiParticle->setName("kikiParticle");
    broomOfKikiParticle->setGlobalZOrder(zOrderOfKikiShadow);
    broomOfKiki->addChild(broomOfKikiParticle);
    
}

void BroomOfKiki::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(broomOfKiki->getPosition());
    //自分の箒に乗ったキキから親ノード(scene)取ってaddchild
    broomOfKiki->getParent()->addChild(endParticle);
    //自分の箒に乗ったキキをremove
    broomOfKiki->removeFromParent();
    
}



//自分の箒に乗ったキキの1フレーム毎の処理
void BroomOfKiki::characterUpdate(bool tappedFlag){
    
    CCLOG("重力:%d",pGravity);
    
    
    
    //タップされている場合は上昇！
    if (tappedFlag == true) {
        
        
        
        broomOfKikiParticle->cocos2d::ParticleSystem::setSpeed(500);
        
        
        
        //透明度を変更
        if(broomOfKikiShadow->getOpacity() != 255){
            
            broomOfKikiShadow->setOpacity(255);
            
        }
        
        //画像の交換(下降画像の場合のみ)
        if(broomOfKiki->getTag() == 0){
            
            broomOfKiki->setTexture("kiki_up.png");
            broomOfKikiShadow->setTexture("kiki_up_shadow.png");
            //タグを上昇状態へ変更
            broomOfKiki->setTag(1);
            
        }
        
        if (pGravity>700) {
            
            pGravity = 700;
            
        }else{
            
            //下降時はより強く
            if(pGravity < -200){
                
                pGravity+= 15;
                
            }else{
                
                pGravity+= 11;
                
                
            }
            
            
        }
        
        
        broomOfKiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        
    }else{
        
        
        //タップされていない場合は下降！
        
        //kikiParticle->cocos2d::ParticleSystem::setSpeed(300);
        
        
        
        
        //透明度を変更
        if(broomOfKikiShadow->getOpacity() != 180){
            broomOfKikiShadow->setOpacity(180);
        }
        
        
        
        //画像の交換(上昇画像の場合のみ)
        if(broomOfKiki->getTag() == 1){
            
            broomOfKiki->setTexture("kiki_down.png");
            broomOfKikiShadow->setTexture("kiki_down_shadow.png");
            //タグを下降状態へ変更
            broomOfKiki->setTag(0);
        }
        
        
        if (pGravity<-700) {
            
            pGravity = -700;
            
        }else{
            
            //上昇時はより強く
            if(pGravity > 200){
                
                pGravity -= 15;
                
            }else{
                
                pGravity -= 10;
                
            }
            
            
        }
        
        broomOfKiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
        
        
        
    }
    
}
