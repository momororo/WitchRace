//
//  Enemy.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/05.
//
//

#include "Enemy.h"

//初期値NULL
Enemy* Enemy::enemyInstance = NULL;

//シングルトン
Enemy* Enemy::getInstance(){
    
    if(enemyInstance == NULL){
        
        enemyInstance = new Enemy();
    }
    
    return  enemyInstance;
}

//デストラクタ
void Enemy::destroyInstance() {
    if (enemyInstance != NULL){
        delete enemyInstance;
        
        enemyInstance = NULL;
    }
}



//コンストラクタ(初期化)
Enemy::Enemy(){
    
    //ステージごとのプリロードをする
    auto userDef = UserDefault::getInstance();
    auto point = userDef->getIntegerForKey("selectStory");
    switch (point) {
            //1面の読込
        case 0:
            
            
            
            break;
            
            //2面の読込
        case 1:
            
            
            break;
            
            
        default:
            break;
    }

    


    

    
    
    
}

//backGroundにenemyを追加
void Enemy::addEnemyManager(Sprite* backGround){
    

    //backGroundのお掃除
    
    backGround->removeChildByName("enemy");


    //ステージごとに敵を追加するメソッドを分岐
    auto userDef = UserDefault::getInstance();
    auto point = userDef->getIntegerForKey("selectStory");
    switch (point) {
        //1面の読込
        case 0:
            
            this->addEnemy1(backGround);
            
            break;
            
        //2面の読込
        case 1:
            
            this->addEnemy2(backGround);
            
            break;
            
        
        default:
            break;
    }

    
}

//1面の的追加
void Enemy::addEnemy1(Sprite* backGround){
    
//badを生成するラムダ
auto addBad = [](){
    
        //コウモリのスプライトを予め作成
        Sprite *bad = Sprite::createWithSpriteFrameName("bad_1.png");
        bad->setName("enemy");
        bad->setGlobalZOrder(zOrderOfBad);
    
        //物理体の設定
        auto badMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto badBody = PhysicsBody::createBox(bad->getContentSize()*0.9,badMaterial);
        
        //重力による影響の可否
        badBody->setGravityEnable(false);
        //まじない
        badBody->setDynamic(false);
        badBody->setEnable(true);
        
        //カテゴリビットマスク
        badBody->setCategoryBitmask(0x02);
        badBody->setCollisionBitmask(0);
        badBody->setContactTestBitmask(0x01);
        
        //Bodyの追加
        bad->setPhysicsBody(badBody);
        
        
        //アニメーション用配列を用意
        auto  badFrames = new Vector<SpriteFrame*>();
        
        //画像２枚を配列にセットする
        //画像をすべて(2枚)を取り出せるよう、ループ文を使用
        for (int i = 1; i < 3;i++ ) {
            std::string badName = StringUtils::format("bad_%i.png",i);
            SpriteFrame *spBadFrame = SpriteFrameCache::getInstance()-> getSpriteFrameByName(badName.c_str());
            badFrames -> pushBack(spBadFrame);
            
            
        }
        
        //アニメーションの設定
        Animation *badAnimation = Animation::createWithSpriteFrames(*badFrames,0.1f);
        Animate *badAnimate = Animate::create(badAnimation);
        RepeatForever *repeat = RepeatForever::create(badAnimate);
        bad -> runAction(repeat);
        delete badFrames;

    
        return bad;
    
};
    
    
//木のスプライトを作成するラムダ
auto addtree = [](){

    //木のスプライトを作成
    Sprite *tree = Sprite::createWithSpriteFrameName("enemy_tree.png");
    tree->setName("enemy");
    tree->setGlobalZOrder(zOrderOfBad);
    
    //物理体の設定
    auto treeMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
    auto treeBody = PhysicsBody::createBox(tree->getContentSize()*0.9,treeMaterial);
    
    //重力による影響の可否
    treeBody->setGravityEnable(false);
    //まじない
    treeBody->setDynamic(false);
    treeBody->setEnable(true);
    
    //カテゴリビットマスク
    treeBody->setCategoryBitmask(0x02);
    treeBody->setCollisionBitmask(0);
    treeBody->setContactTestBitmask(0x01);
    
    //Bodyの追加
    tree->setPhysicsBody(treeBody);
    
    return tree;
    
};
    
    
//xの値を先に決めとく(後で一括変更するのがラクダから)
    int positionX = backGround->getContentSize().width/10;
    
    
//乱数を発生させて配置を決定していく
    int positionRnd = arc4random_uniform(4);


    //0の場合(木がどーん！)
    if(positionRnd == 0){
        //ポジションで合わせる(アンカーでは合わせられず)
        auto tree = addtree();
        tree->setPosition(Vec2(positionX, tree->getContentSize().height/2));
        
        backGround->addChild(tree);
        
        return;
        
    }
    
    
    
    //1の場合(コウモリが3匹上にどーん！)
    if(positionRnd == 1){
        
        Vector<Sprite*> *bads = new Vector<Sprite*>();
        
        //コウモリを3匹生成(面倒なので配列)
        for (int idx = 0; idx < 3 ;idx++){
            
            bads->pushBack(addBad());
            backGround->addChild(bads->at(idx));
        }
        
        //positionの調整
        for (int idx = 0; idx < 3 ;idx++){
            
            //0の時は上に位置を合わせる
            if(idx == 0){

                bads->at(idx)->setPosition(Vec2(positionX,backGround->getContentSize().height - bads->at(idx)->getContentSize().height/2));



            }else{
                

                bads->at(idx)->setPosition(Vec2(positionX,bads->at(idx-1)->getPositionY() - bads->at(idx)->getContentSize().height));
                
                
            }
            
        }
        
        return;
        
    }
    
    
    
    //2の場合(コウモリ1匹上に、木が下に(2/3くらい出てる感じ))
    if(positionRnd == 2){
        
        //コウモリの生成
        auto bad = addBad();
        //ポジション
        bad->setPosition(Vec2(positionX,backGround->getContentSize().height - bad->getContentSize().height/2));

        //追加
        backGround->addChild(bad);
        
        //木の生成
        auto tree = addtree();
        //ポジション
        tree->setPosition(Vec2(positionX, tree->getContentSize().height/2 - tree->getContentSize().height/3*1));
        
        //追加
        backGround->addChild(tree);
        
        
        return;
        
        
    }
    
    
    
    //3の場合(コウモリ2匹上に、木が下に(1/3くらい出てる感じ))
    if(positionRnd == 3){
        
        //コウモリを2匹生成するのは面倒なので上の配列使いました。
        
        Vector<Sprite*> *bads = new Vector<Sprite*>();
        
        //コウモリを2匹生成(面倒なので配列)
        for (int idx = 0; idx < 2 ;idx++){
            
            bads->pushBack(addBad());
            backGround->addChild(bads->at(idx));
        }
        
        //positionの調整
        for (int idx = 0; idx < 2 ;idx++){
            
            //0の時は上に位置を合わせる
            if(idx == 0){
                
                bads->at(idx)->setPosition(Vec2(positionX,backGround->getContentSize().height - bads->at(idx)->getContentSize().height/2));
                
                
                
            }else{
                
                
                bads->at(idx)->setPosition(Vec2(positionX,bads->at(idx-1)->getPositionY() - bads->at(idx)->getContentSize().height));
                
                
            }
            
        }

        
        //木の生成
        auto tree = addtree();
        //ポジション
        tree->setPosition(Vec2(positionX, tree->getContentSize().height/2 - tree->getContentSize().height/3*2));
        
        //追加
        backGround->addChild(tree);


        
        return;
        
    }

}

void Enemy::addEnemy2(Sprite* backGround){
//enemy_witchを生成するラムダ
    auto addWitch = [](){
        
        //witchのスプライトを予め作成
        Sprite *enemy = Sprite::createWithSpriteFrameName("enemy_witch.png");
        enemy->setName("enemy");
        enemy->setGlobalZOrder(zOrderOfBad);
        enemy->setScale(0.5f);
        
        //物理体の設定
        auto enemyMaterial = PHYSICSBODY_MATERIAL_DEFAULT;
        auto enemyBody = PhysicsBody::createBox(enemy->getContentSize()* enemy->getScale()*0.9,enemyMaterial);
        
        //重力による影響の可否
        enemyBody->setGravityEnable(false);
        //まじない
        enemyBody->setDynamic(false);
        enemyBody->setEnable(true);
        
        //カテゴリビットマスク
        enemyBody->setCategoryBitmask(0x02);
        enemyBody->setCollisionBitmask(0);
        enemyBody->setContactTestBitmask(0x01);
        
        //witchの追加
        enemy->setPhysicsBody(enemyBody);
        
        
        return enemy;
        
    };
    
    
    
//ランダムで配置を行う
    //x軸の移動に利用(X軸を4分割)
    for(int idxX = 0 ; idxX < 4 ; idxX++){
 
        //Y軸の分割数をランダムで生成
        auto rndNumberY = arc4random_uniform(5);
        //0が出たらエラーになるため、1を足し込む
        rndNumberY = rndNumberY + 5;

        //更に分散しているように見せるために乱数を追加
        int rnd = arc4random_uniform(120);

        
        //4体ずつランダムで置いていく
        for(int count = 0; count < 5; count++){
            
            
            //乱数を生成
            int rndPositionY = arc4random_uniform(rndNumberY);
            auto enemy = addWitch();
            
            
            
            //ポジションの設定
            enemy->setPosition(Vec2(backGround->getContentSize().width / 5 * idxX + backGround->getContentSize().width/5/2 , backGround->getContentSize().height / rndNumberY * rndPositionY + backGround->getContentSize().height/rndNumberY / 2 + rnd ));
            
            backGround->addChild(enemy);
            
        }
        
    }

}


void Enemy::addEnemy3(Sprite* backGround){
}
void Enemy::addEnemy4(Sprite* backGround){
}
void Enemy::addEnemy5(Sprite* backGround){
}

//各面のプリロード
void preLoad1(){
    
}
void preLoad2(){
    
    
}
void preLoad3(){
    
}
void preLoad4(){
    
}
void preLoad5(){
    
}


