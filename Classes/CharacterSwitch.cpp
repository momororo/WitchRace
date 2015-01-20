//
//  CharacterSwitch.cpp
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#include "CharacterSwitch.h"

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
    if (characterInstance != NULL){
        delete characterInstance;
        
        characterInstance = NULL;
    }
    
    //分岐(各キャラクターを削除するように)
    
}


//キキちゃんのスプライトをGET
Sprite* CharacterSwitch::getCharacter(){
    //分岐
}




//キキちゃんのタップ状態の変更
void CharacterSwitch::setTappedFlagOfCharacter(bool flag){
    tappedFlag = flag;
    return;
}

//キキちゃんの動作開始
void CharacterSwitch::startCharacter(){
    
    //分岐
    
}

//キキちゃんの動作停止
void CharacterSwitch::stopCharacter(){
    
    //分岐
    
    
}

bool CharacterSwitch::getGamePlayFlag(){
    
    return gamePlayFlag;
    
}

bool CharacterSwitch::getGameOverFlag(){
    
    return gameOverFlag;
}



//キキちゃんの初期設定
CharacterSwitch::CharacterSwitch(){
    

    //分岐
}

void CharacterSwitch::makeGameOver(){
    

    //分岐
    
}



//キキちゃんの1フレーム毎の処理
void CharacterSwitch::characterUpdate(){
    
    
    
    //ゲームプレイ中ではない場合は何もせず終了
    if(gamePlayFlag != true){
        
        return;
        
    }

    //分岐
}
