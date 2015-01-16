//
//  NSObject+NativeLauncher.m
//  WitchRace
//
//  Created by yasutomo on 2015/01/16.
//
//

#include "NativeLauncher.h"

//レビューに誘導
void NativeLauncher::openReview(){
    
    //IDを入れてね
    NSURL *reivewURL = [NSURL URLWithString:[NSString stringWithFormat:@"https://itunes.apple.com/jp/app/reindoroppu-luochiru-nawo/id%d?mt=8&ign-mpt=uo%%3D4",952698855]];
    [[UIApplication sharedApplication] openURL:reivewURL];
    
}