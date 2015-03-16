//
//  NSObject+AppbankSSP.h
//  WitchRace
//
//  Created by yasutomo on 2015/03/06.
//
//

#import <Foundation/Foundation.h>
#import <ADG/ADGManagerViewController.h>
#import <ADG/ADGInterstitial.h>


@interface AppbankSSP : NSObject <ADGManagerViewControllerDelegate , ADGInterstitialDelegate>


+(void)setAppbankSSP;
//appBank ssp
+(void)startInterstitial;
+(void)stopInterstitial;
+(void)showInterstitial;
+(void)loadInterstitial;

@end
