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

@property (nonatomic, retain) ADGManagerViewController *adg;
@property (nonatomic, retain) ADGInterstitial *adgInter;


+(void)setAppbankSSP;

@end
