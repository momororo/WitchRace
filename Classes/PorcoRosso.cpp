//
//  PorcoRosso.cpp
//  WitchRace
//
//  Created by yasutomo on 2014/12/03.
//
//

#include "PorcoRosso.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
PorcoRosso* PorcoRosso::porcoRossoInstance = NULL;

//シングルトン
PorcoRosso* PorcoRosso::getInstance(){
    
    if(!porcoRossoInstance){
        porcoRossoInstance = new PorcoRosso();
    }
    
    
    return porcoRossoInstance;
    
}
//デストラクタ
void PorcoRosso::destroyInstance() {
    if (porcoRossoInstance != NULL){
        delete porcoRossoInstance;
        
        porcoRossoInstance = NULL;
    }
}


//キキちゃんのスプライトをGET
Sprite* PorcoRosso::getCharacter(){
    return porcoRosso;
}


//キキちゃんの動作開始
void PorcoRosso::startCharacter(){
    
    porcoRosso->getPhysicsBody()->setEnable(true);
    broom -> getPhysicsBody()-> setEnable(true);
    
}

//キキちゃんの動作停止
void PorcoRosso::stopCharacter(){
    
    porcoRosso->getPhysicsBody()->setEnable(false);
    broom -> getPhysicsBody()-> setEnable(false);
    
}


//キキちゃんの初期設定
PorcoRosso::PorcoRosso(){
 
    //キャラクタースプライトの生成(UP時)
    porcoRosso = Sprite::create("porcoRosso.png");
    //影
    porcoRossoShadow = Sprite::create("porcoRosso_shadow.png");
    
    //キャラクタースプライトの大きさ
    porcoRosso -> setScale(0.5);
    
    //影を実体に入れちゃう
    porcoRosso->addChild(porcoRossoShadow);
    //影のポジション調整
    porcoRossoShadow->setPosition(porcoRosso->getContentSize().width/2,porcoRosso->getContentSize().height/2);
    //影の透明度を設定
    porcoRossoShadow->setOpacity(180);
    porcoRossoShadow->setGlobalZOrder(zOrderOfKikiShadow);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //porcoRossoShadow -> setScale(porcoRosso->getScale());

    
    //ポジションの設定
    porcoRosso->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    porcoRosso->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    porcoRosso->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    porcoRosso->setTag(1);
    
    //物理体の生成
    auto porcoRossoMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    //auto porcoRossoBody = PhysicsBody::createCircle((porcoRosso->getContentSize().width/2),porcoRossoMaterial);

    
    
    Point spritePoints[7]={
    
        Vec2(-40,-15),Vec2(-40,-10),Vec2(18,22),Vec2(50,25),Vec2(80,-15),Vec2(60,-25),Vec2(-5,-23)

    };
    
    auto porcoRossoBody = PhysicsBody::createPolygon(spritePoints, 7,porcoRossoMaterial);
    
    //重力による影響の可否
    porcoRossoBody->setGravityEnable(false);
    //まじない
    porcoRossoBody->setDynamic(true);
    porcoRossoBody->setEnable(false);

    //ビットマスクはてきとう
    porcoRossoBody->setCategoryBitmask(0x01);
    porcoRossoBody->setCollisionBitmask(0);
    porcoRossoBody->setContactTestBitmask(0x02);
    
    porcoRosso->setPhysicsBody(porcoRossoBody);
    
    
    //箒の設定
    broom = Sprite::create();
    broom -> setTextureRect(Rect(0, 0, 10, 10));
    broom -> setPosition(Vec2(0,0));
    broom -> setVisible(false);
    
    auto broomMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    
    Point broomPoint[6]={
        
        Vec2(40,25), Vec2(5,45), Vec2(45,80), Vec2(60,80), Vec2(80,45),Vec2(80,17)

    };
    
    auto broomBody = PhysicsBody::createPolygon(broomPoint,6,broomMaterial);
    broomBody -> setGravityEnable(false);
    broomBody -> setDynamic(true);
    broomBody -> setEnable(false);
    
    broomBody ->setCategoryBitmask(0x01);
    broomBody ->setCollisionBitmask(0);
    broomBody ->setContactTestBitmask(0x02);
    
    broom -> setPhysicsBody(broomBody);
    
    porcoRosso -> addChild(broom);
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();
    
    porcoRossoParticle = ParticleSystemQuad::create("particle_porcoRosso.plist");
    porcoRossoParticle->setAnchorPoint(Vec2(0.5f,0.5f));
    porcoRossoParticle->setPosition(Vec2(porcoRosso->getContentSize().width/2+20,porcoRosso->getContentSize().height*3/4+3));
    porcoRossoParticle->setName("kikiParticle");
    porcoRossoParticle->setGlobalZOrder(zOrderOfKikiShadow);
    porcoRosso->addChild(porcoRossoParticle);
    
}

void PorcoRosso::makeGameOver(){
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(porcoRosso->getPosition());
    //キキから親ノード(scene)取ってaddchild
    porcoRosso->getParent()->addChild(endParticle);
    //キキをremove
    porcoRosso->removeFromParent();

}



//キキちゃんの1フレーム毎の処理
void PorcoRosso::characterUpdate(bool tappedFlag){
    
    CCLOG("重力:%d",pGravity);

    
    
    //タップされている場合は上昇！
        if (tappedFlag == true) {
            
            
            
            //porcoRossoParticle->cocos2d::ParticleSystem::setSpeed(500);
            
            
            
            //透明度を変更
            if(porcoRossoShadow->getOpacity() != 255){
            
                porcoRossoShadow->setOpacity(255);
            
            }

            //画像の交換(下降画像の場合のみ)
            if(porcoRosso->getTag() == 0){

                porcoRosso->setTexture("porcoRosso.png");
                porcoRossoShadow->setTexture("porcoRosso_shadow.png");
                //タグを上昇状態へ変更
                porcoRosso->setTag(1);
            
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
            //MARK::上昇時の回転
            if (pRotate < -40) {
                
                pRotate = -40;
                
            }else if(pRotate > 10){
                
                pRotate -= 1;
                
            }else{
                
                pRotate -= 0.4;
                
            }
            
            
            porcoRosso->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            porcoRosso->setRotation(pRotate);
            porcoRossoParticle->setRotation(-pRotate/2);
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
        }else{
            
            
            //タップされていない場合は下降！
        
            //porcoRossoParticle->cocos2d::ParticleSystem::setSpeed(300);


        
            
            //透明度を変更
            if(porcoRossoShadow->getOpacity() != 180){
                porcoRossoShadow->setOpacity(180);
            }


            
            //画像の交換(上昇画像の場合のみ)
            if(porcoRosso->getTag() == 1){
                
                porcoRosso->setTexture("porcoRosso.png");
                porcoRossoShadow->setTexture("porcoRosso_shadow.png");
                //タグを下降状態へ変更
                porcoRosso->setTag(0);
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
            
            //MARK::下降時の回転
            if (pRotate > 40) {
                
                pRotate = 40;
                
            }if (pRotate < -10) {
                
                pRotate += 1;
                
            }else{
                
                pRotate += 0.35;
                
            }
            
            porcoRosso->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            porcoRosso->setRotation(pRotate);
            porcoRossoParticle->setRotation(-pRotate/2);
            broom->getPhysicsBody()->setVelocity(Vec2(0,pGravity));

            
            
        }
        
}
