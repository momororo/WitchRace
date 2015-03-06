//
//  NSObject+AppbankSSP.m
//  WitchRace
//
//  Created by yasutomo on 2015/03/06.
//
//

#import "AppbankSSP.h"


@implementation AppbankSSP

+(void) setAppbankSSP{
    
    ADGManagerViewController *adg;

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

@end
