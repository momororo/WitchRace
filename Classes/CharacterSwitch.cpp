//
//  CharacterSwitch.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#include "CharacterSwitch.h"
#include "Kiki.h"
#include "PetitKiki.h"
#include "HarryPotter.h"
#define selfFrame Director::getInstance()->getWinSize()
#define origin Director::getInstance()->getVisibleOrigin()

//おまじない
USING_NS_CC;


//初期値NULL
CharacterSwitch* CharacterSwitch::characterInstance = NULL;

//シングルトン
CharacterSwitch* CharacterSwitch::getInstance(){
    
    if(!characterInstance){
        
        
        characterInstance = new CharacterSwitch();
    }
    
    
    return characterInstance;
    
}
//デストラクタ
void CharacterSwitch::destroyInstance() {
    
    
    //キャラクターのフラグを設定
    auto userDef = UserDefault::getInstance();
    auto destroyFlag = userDef->getIntegerForKey("selectCharacter");

    
    //分岐
    switch (destroyFlag) {
        case 0:Kiki::getInstance()->destroyInstance();break;
        case 1:PetitKiki::getInstance()->destroyInstance();break;
        case 2:HarryPotter::getInstance()->destroyInstance();break;
        case 3:Kiki::getInstance()->destroyInstance();break;
        case 4:Kiki::getInstance()->destroyInstance();break;
        default: break;
    }
    
    
    if (characterInstance != NULL){
        delete characterInstance;
        
        characterInstance = NULL;
    }
    
    
}


//キキちゃんのスプライトをGET
Sprite* CharacterSwitch::getCharacter(){

    
    //分岐
    switch (characterFlag) {
        case 0:return Kiki::getInstance()->getKiki();break;
        case 1:return Kiki::getInstance()->getKiki();break;
        case 2:return Kiki::getInstance()->getKiki();break;
        case 3:return Kiki::getInstance()->getKiki();break;
        case 4:return Kiki::getInstance()->getKiki();break;
        default: break;
    }
    
    
    return NULL;
    

}




//キキちゃんのタップ状態の変更
void CharacterSwitch::setTappedFlagOfCharacter(bool flag){
    tappedFlag = flag;
    return;
}

//キキちゃんの動作開始
void CharacterSwitch::startCharacter(){
    
    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->startKiki();break;
        case 1:Kiki::getInstance()->startKiki();break;
        case 2:Kiki::getInstance()->startKiki();break;
        case 3:Kiki::getInstance()->startKiki();break;
        case 4:Kiki::getInstance()->startKiki();break;
        default: break;
    }
    
    gamePlayFlag = true;


    
}

//キキちゃんの動作停止
void CharacterSwitch::stopCharacter(){
    
    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->stopKiki();break;
        case 1:Kiki::getInstance()->stopKiki();break;
        case 2:Kiki::getInstance()->stopKiki();break;
        case 3:Kiki::getInstance()->stopKiki();break;
        case 4:Kiki::getInstance()->stopKiki();break;
        default: break;
    }
    
    gamePlayFlag = false;
    
    
}

bool CharacterSwitch::getGamePlayFlag(){
    
    return gamePlayFlag;
    
}

bool CharacterSwitch::getGameOverFlag(){
    
    return gameOverFlag;
}



//キキちゃんの初期設定
CharacterSwitch::CharacterSwitch(){
    

    //キャラクターのフラグを設定
    auto userDef = UserDefault::getInstance();
    characterFlag = userDef->getIntegerForKey("selectCharacter");
    
    
    
    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance();break;
        case 1:Kiki::getInstance();break;
        case 2:Kiki::getInstance();break;
        case 3:Kiki::getInstance();break;
        case 4:Kiki::getInstance();break;
        default:break;
    }

}

void CharacterSwitch::makeGameOver(){
    

    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->makeGameOver();break;
        case 1:Kiki::getInstance()->makeGameOver();break;
        case 2:Kiki::getInstance()->makeGameOver();break;
        case 3:Kiki::getInstance()->makeGameOver();break;
        case 4:Kiki::getInstance()->makeGameOver();break;
        default: break;
    }
    
    gamePlayFlag = false;
    gameOverFlag = true;
    


    
}



//キキちゃんの1フレーム毎の処理
void CharacterSwitch::characterUpdate(){
    
    
    
    //ゲームプレイ中ではない場合は何もせず終了
    if(gamePlayFlag != true){
        
        return;
        
    }

    //分岐
    switch (characterFlag) {
        case 0:Kiki::getInstance()->kikiUpdate(tappedFlag);break;
        case 1:Kiki::getInstance()->kikiUpdate(tappedFlag);break;
        case 2:Kiki::getInstance()->kikiUpdate(tappedFlag);break;
        case 3:Kiki::getInstance()->kikiUpdate(tappedFlag);break;
        case 4:Kiki::getInstance()->kikiUpdate(tappedFlag);break;
        default: break;
    }

}
