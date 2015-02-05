#import <Foundation/Foundation.h>#import "ADGManagerViewController.h"@interface ADGConnectionObjC : NSObject<ADGManagerViewControllerDelegate>{    ADGManagerViewController *adg_;    NSDictionary *adgparam_;}- (void)initADG:(NSString*)adid type:(NSString*)type x:(int)x y:(int)y width:(int)width height:(int)height scale:(double)scale earlyOS:(Boolean)earlyOS landscape:(Boolean)landscape func:(void (*)(const char * , const char *))func;- (void)pauseADG;- (void)resumeADG;- (void)showADG;- (void)hideADG;- (void)changeLocationADG:(int)x y:(int)y;- (void)setScaleADG:(float)scale;@property (nonatomic, retain) ADGManagerViewController *adg;@end