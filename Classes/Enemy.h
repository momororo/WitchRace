//
//  Enemy.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/05.
//
//

#ifndef __WitchRace__Enemy__
#define __WitchRace__Enemy__

#include "cocos2d.h"
#include "Zorder.h"


using namespace cocos2d;



class Enemy : public cocos2d::Sprite
{
private:
    
    //クラス
    static Enemy *enemyInstance;

    
    //コンストラクタ
    Enemy();
    
public:
    
    
    //シングルトン
    static Enemy* getInstance();
    //デストラクタ
    static void deleteInstance();

    
    //enemyの管理
    void addEnemyManager(Sprite* backGround);
    
    //1面の的追加
    void addEnemy1(Sprite* backGround);

    //2面の的追加
    void addEnemy2(Sprite* backGround);

    //3面の的追加
    void addEnemy3(Sprite* backGround);

    //4面の的追加
    void addEnemy4(Sprite* backGround);

    //5面の的追加
    void addEnemy5(Sprite* backGround);

    
    

    CREATE_FUNC(Enemy);
    
    
};

#endif /* defined(__WitchRace__Enemy__) */
