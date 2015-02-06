//
//  NSObject+NativeLauncher.m
//  WitchRace
//
//  Created by yasutomo on 2015/01/16.
//
//

#include "NativeLauncher.h"
#include "GameCenter.h"

//レビューに誘導
void NativeLauncher::openReview(){
    
    //IDを入れてね
    NSURL *reivewURL = [NSURL URLWithString:[NSString stringWithFormat:@"https://itunes.apple.com/jp/app/reindoroppu-luochiru-nawo/id%d?mt=8&ign-mpt=uo%%3D4",952698855]];
    [[UIApplication sharedApplication] openURL:reivewURL];
    
}

void NativeLauncher::loginGameCenter()
{
    [GameCenter loginGameCenter];
}
// Leaderboard表示
void NativeLauncher::openRanking()
{
    [GameCenter openRanking];
}
// ハイスコアを送信
void NativeLauncher::postHighScore(std::string key,int score)
{
    [GameCenter postHighScore:[[[NSString alloc] initWithCString:key.c_str() encoding:NSUTF8StringEncoding] autorelease] score:score];
    
}
