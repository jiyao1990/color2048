#import <UIKit/UIKit.h>

#import <GoogleMobileAds/GoogleMobileAds.h>
#import "UMSocial.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GADInterstitialDelegate,UMSocialUIDelegate> {
    UIWindow *window;
    int adCounts;
}

@property(nonatomic, readonly) RootViewController* viewController;


+ (void)showInterstitial;
+ (void)share:(NSString*)imgPath ShareText:(NSString*)text;
+ (void)screenShot;
+ (void)saveScore:(NSString*)score;
+ (NSString*)readScore;
@end

