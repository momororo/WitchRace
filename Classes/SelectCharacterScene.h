//
//  SelectCharacterScene.h
//  WitchRace
//
//  Created by yasutomo on 2015/01/20.
//
//

#ifndef __WitchRace__SelectCharacterScene__
#define __WitchRace__SelectCharacterScene__

#include "cocos2d.h"

using namespace cocos2d;

class SelectCharacterScene : public cocos2d::Layer
{
public:

    
    virtual bool init();
    static cocos2d::Scene *createScene();
    void setBackBt();
    void backBtCallBack(cocos2d::Ref *pSender);
    CREATE_FUNC(SelectCharacterScene);
    
    //配列(透明度の一括管理のため)
    Vector<Sprite*> *characters = new Vector<Sprite*>;
    Label *charaExLabel;
    
    //キキ
    std::string kikiExText = "飛ぶのが得意なおてんば少女\n夢に向かって修行中";
    
    //おまけキキ
    std::string petitKikiExText = "飛ぶのが苦手なあなたに、まずは練習用\n\n～キャラクターボーナス～\n障害物にあたりにくくなる";
    //ハリーポッター
    std::string haryyPotterExText = "僕は生き残る！\n\n～キャラクターボーナス～\nストーリクリアポイントに10ポイント加算";
    //ポニョ
    std::string ponyoExText = "元気いっぱい！空もかけちゃお♪\n\n～キャラクターボーナス～\nストーリクリアポイント✕3ポイント加算";
    //空飛ぶ車
    std::string fordAngliaExText = "オジサンからかりた車\n\n～キャラクターボーナス～\nストーリークリアポイント✕5ポイント加算";
    //ポルコ・ロッソ
    std::string porcoRossoExText = "自由気ままに生きる、それが男！\n\n～キャラクターボーナス～\nストーリークリアポイント✕10ポイント加算";


};

#endif /* defined(__WitchRace__SelectCharacterScene__) */
