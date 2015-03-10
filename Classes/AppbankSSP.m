//
//  NSObject+AppbankSSP.m
//  WitchRace
//
//  Created by yasutomo on 2015/03/06.
//
//

#import "AppbankSSP.h"


@implementation AppbankSSP
ADGManagerViewController *adg = nil;
+(void) setAppbankSSP{

    // Banner
    float y = [UIScreen mainScreen].applicationFrame.origin.y;
    NSDictionary *adgparam = @{
                               @"locationid" : @"10723",
                               @"adtype" : @(kADG_AdType_Sp),
                               @"originx" : @(0),
                               @"originy" : @(y)
                               };
    
    UIViewController* rootController = [UIApplication sharedApplication].keyWindow.rootViewController;

    adg = [[ADGManagerViewController alloc]initWithAdParams :adgparam :rootController.view];
    adg.delegate = self;
    [adg loadRequest];
    
}

//インタースティシャル用変数
ADGInterstitial *adgInterstitial = nil;
+(void)startInterstitial{
    adgInterstitial = [[ADGInterstitial alloc] init]; // インスタンスの生成
    adgInterstitial.delegate = self; // デリゲートの代入
    [adgInterstitial setLocationId:@"広告枠ID"]; //枠IDの設定
    //頻度の設定(25%に)
    [adgInterstitial setSpan:25 isPercentage:YES];
    //プリロードをしておく
    [adgInterstitial preload];
}

+(void)stopInterstitial{
    // 画面を離れるタイミングで必ず破棄すること
    [adgInterstitial dismiss]; // 動作中の処理のキャンセル
    [adgInterstitial setDelegate:nil];
    [adgInterstitial release];
    adgInterstitial = nil;
}

+(void)showInterstitial{
    [adgInterstitial show];
}


@end
