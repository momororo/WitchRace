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

//キキちゃんの動作開始
void Kiki::startKiki(){
    
    kiki->getPhysicsBody()->setEnable(true);
    gamePlayFlag = true;
    
}

//キキちゃんの動作停止
void Kiki::stopKiki(){
    
    kiki->getPhysicsBody()->setEnable(false);
    gamePlayFlag = false;

    
}

bool Kiki::getGamePlayFlag(){
    
    return gamePlayFlag;

}


//キキちゃんの初期設定
Kiki::Kiki(){
 
    //キャラクタースプライトの生成(UP時)
    kiki = Sprite::create("kiki_up.png");
    //影
    kikiShadow = Sprite::create("kiki_up_shadow.png");
    
    //キャラクタースプライトの大きさ
    kiki -> setScale(0.5);
    
    //影を実体に入れちゃう
    kiki->addChild(kikiShadow);
    //影のポジション調整
    kikiShadow->setPosition(kiki->getContentSize().width/2,kiki->getContentSize().height/2);
    //影の透明度を設定
    kikiShadow->setOpacity(180);
    
    //影の大きさ(実体のスケールをgetしてます)※特にスケールせずにぴったり入りました(謎)
    //kikiShadow -> setScale(kiki->getScale());

    
    //ポジションの設定
    kiki->setPosition(Vec2(selfFrame.width/4, selfFrame.height/2));
    
    //zポジションの設定
    kiki->setGlobalZOrder(zOrderOfKiki);
    
    
    //タグつけ
    kiki->setName("kiki");
    
    //タグで上昇か下降か判断してみる(1は上昇、0は下降)
    kiki->setTag(1);
    
    //物理体の生成
    auto kikiMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    //auto kikiBody = PhysicsBody::createCircle((kiki->getContentSize().width/2),kikiMaterial);

    
    
    Point spritePoints[5]={
        
        Vec2(-30,-30),Vec2(-40,0),Vec2(-4,40),Vec2(30,30),Vec2(6,-20)
    
    };
    
    auto kikiBody = PhysicsBody::createPolygon(spritePoints, 5,kikiMaterial);
    

    
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
    
    endParticle = ParticleSystemQuad::create("particleFlower.plist");
    //retainしないと勝手に解放されて後々エラーへ
    endParticle->retain();

    
}

void Kiki::makeGameOver(){
    
    
    //ゲームプレイのフラグをオフに
    gamePlayFlag=false;
    
    //パーティクルの設定
    endParticle->setAutoRemoveOnFinish(true);
    endParticle->setPosition(kiki->getPosition());
    //キキから親ノード(scene)取ってaddchild
    kiki->getParent()->addChild(endParticle);
    //キキをremove
    kiki->removeFromParent();

    
}



//キキちゃんの1フレーム毎の処理
void Kiki::kikiUpdate(){
    
    //ゲームプレイ中ではない場合は何もせず終了
    if(gamePlayFlag != true){
        return;
    }
    
    //タップされている場合は上昇！
        if (tappedFlag == true) {
            
            
            //透明度を変更
            if(kikiShadow->getOpacity() != 255){
                kikiShadow->setOpacity(255);
            }

            //画像の交換(下降画像の場合のみ)
            if(kiki->getTag() == 0){

                kiki->setTexture("kiki_up.png");
                kikiShadow->setTexture("kiki_up_shadow.png");
                //タグを上昇状態へ変更
                kiki->setTag(1);
            }
            
            if (pGravity>1000) {
                
                pGravity = 1000;
                
            }else{
                
                pGravity+= 8;
                
            }
            
            
            kiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
        }else{
            
            
            //タップされていない場合は下降！
            
            //透明度を変更
            if(kikiShadow->getOpacity() != 180){
                kikiShadow->setOpacity(180);
            }


            
            //画像の交換(上昇画像の場合のみ)
            if(kiki->getTag() == 1){
                
                kiki->setTexture("kiki_down.png");
                kikiShadow->setTexture("kiki_down_shadow.png");
                //タグを下降状態へ変更
                kiki->setTag(0);
            }

            
            if (pGravity<-1000) {
                
                pGravity = -1000;
                
            }else{
                
                pGravity -= 5;
                
            }
            
            kiki->getPhysicsBody()->setVelocity(Vec2(0,pGravity));
            
            
        }
        
}
