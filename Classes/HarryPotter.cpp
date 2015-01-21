//
//  HarryPotter.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "HarryPotter.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
HarryPotter* HarryPotter::harryPotterInstance = NULL;

//シングルトン
HarryPotter* HarryPotter::getInstance(){
    
    if(!harryPotterInstance){
        harryPotterInstance = new HarryPotter();
    }
    
    
    return harryPotterInstance;
    
}
//デストラクタ
void HarryPotter::destroyInstance() {
    if (harryPotterInstance != NULL){
        delete harryPotterInstance;
        
        harryPotterInstance = NULL;
    }
}


//キキちゃんのスプライトをGET
Sprite* HarryPotter::getCharacter(){
    return harryPotter;
}


//キキちゃんの動作開始
void HarryPotter::startCharacter(){
    
    harryPotter->getPhysicsBody()->setEnable(true);
    broom -> getPhysicsBody()-> setEnable(true);
    
}

//キキちゃんの動作停止
void HarryPotter::stopCharacter(){
    
    harryPotter->getPhysicsBody()->setEnable(false);
    broom -> getPhysicsBody()-> setEnable(false);
    
}


//キキちゃんの初期設定
HarryPotter::HarryPotter(){
 
    //キャラクタースプライトの生成(UP時)
    harryPotter = Sprite::create("harryPotter.png");
    //影
    harryPotterShadow = Sprite::create("kiki_up_shadow.png");
    
    //キャラクタースプライトの大きさ
    harryPotter -> setScale(0.5);
    
    //影を実体に入れちゃう
    harryPotter->addChild(harryPotterShadow);
    //影のポジション調整
    harryPotterShadow->setPosition(harryPotter->getContentSize().width/2,harryPotter->getContentSize().height/2);
    //影の透明度を設定
    harryPotterShadow->setOpacity(180);
    harryPotterShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //harryPotterShadow -> setScale(harryPotter->getScale());

    
    //ポジションの設定
    harryPotter->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    harryPotter->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    harryPotter->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    harryPotter->setTag(1);
    
    //物理体の生成
    auto harryPotterMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    //auto harryPotterBody = PhysicsBody::createCircle((harryPotter->getContentSize().width/2),harryPotterMaterial);

    
    
    Point spritePoints[5]={
    
        //Vec2(-10,-22),Vec2(-18,0),Vec2(-10,20),Vec2(15,15),Vec2(10,-20)
        Vec2(-8,-20),Vec2(-16,0),Vec2(-8,18),Vec2(13,13),Vec2(8,-18)
    
    };
    
    auto harryPotterBody = PhysicsBody::createPolygon(spritePoints, 5,harryPotterMaterial);
    
    //重力による影響の可否
    harryPotterBody->setGravityEnable(false);
    //まじない
    harryPotterBody->setDynamic(true);
    harryPotterBody->setEnable(false);

    //ビットマスクはてきとう
    harryPotterBody->setCategoryBitmask(0x01);
    harryPotterBody->setCollisionBitmask(0);
    harryPotterBody->setContactTestBitmask(0x02);
    
    harryPotter->setPhysicsBody(harryPotterBody);
    
    
    //箒の設定
    broom = Sprite::create();
    broom -> setTextureRect(Rect(0, 0, 10, 10));
    broom -> setPosition(Vec2(0,0));
    broom -> setVisible(false);
    
    auto broomMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point broomPoint[3]={
        
        //Vec2(0,0), Vec2(0,40), Vec2(180,35)
        Vec2(10,5), Vec2(10,35), Vec2(160,35),
    
    };
    
    auto broomBody = PhysicsBody::createPolygon(broomPoint,3,broomMaterial);
    broomBody -> setGravityEnable(false);
    broomBody -> setDynamic(true);
    broomBody -> setEnable(false);
    
    broomBody ->setCategoryBitmask(0x01);
    broomBody ->setCollisionBitmask(0);
    broomBody ->setContactTestBitmask(0x02);
    
    broom -> setPhysicsBody(broomBody);
    
    harryPotter -> addChild(broom);
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    harryPotterParticle = ParticleSystemQuad::create("kikiparticle.plist");
    harryPotterParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    harryPotterParticle->setPosition(Vec2(3,harryPotter->getContentSize().height/3-6));
    harryPotterParticle->setName("kikiParticle");
    harryPotterParticle->setGlobalZOrder(zOrderOfKikiShadow);
    harryPotter->addChild(harryPotterParticle);
    
}

void HarryPotter::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(harryPotter->getPosition());
    //キキから親ノード(scene)取ってaddchild
    harryPotter->getParent()->addChild(endParticle);
    //キキをremove
    harryPotter->removeFromParent();

}



//キキちゃんの1フレーム毎の処理
void HarryPotter::characterUpdate(bool tappedFlag){
    
    CCLOG("重力:%d",pGravity);

    
    
    //タップされている場合は上昇！
        if (tappedFlag == true) {
            
            
            
            harryPotterParticle->cocos2d::ParticleSystem::setSpeed(500);
            
            
            
            //透明度を変更
            if(harryPotterShadow->getOpacity() != 255){
            
                harryPotterShadow->setOpacity(255);
            
            }

            //画像の交換(下降画像の場合のみ)
            if(harryPotter->getTag() == 0){

                harryPotter->setTexture("harryPotter.png");
                harryPotterShadow->setTexture("kiki_up_shadow.png");
                //タグを上昇状態へ変更
                harryPotter->setTag(1);
            
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
            
            
            harryPotter->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
        }else{
            
            
            //タップされていない場合は下降！
        
            //harryPotterParticle->cocos2d::ParticleSystem::setSpeed(300);


            
            
            //透明度を変更
            if(harryPotterShadow->getOpacity() != 180){
                harryPotterShadow->setOpacity(180);
            }


            
            //画像の交換(上昇画像の場合のみ)
            if(harryPotter->getTag() == 1){
                
                harryPotter->setTexture("harryPotter.png");
                harryPotterShadow->setTexture("kiki_down_shadow.png");
                //タグを下降状態へ変更
                harryPotter->setTag(0);
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
            
            harryPotter->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));

            
            
        }
        
}
