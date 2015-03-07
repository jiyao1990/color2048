#import <UIKit/UIKit.h>

#import <GoogleMobileAds/GoogleMobileAds.h>
#import "UMSocial.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GADInterstitialDelegate,UMSocialUIDelegate> {
    UIWindow *window;
    int adCounts;
}

@property(nonatomic, readonly) RootViewController* viewController;


+ (BOOL)showInterstitial;
+ (void)share:(NSString*)imgPath ShareText:(NSString*)text;
+ (void)screenShot;
+ (void)saveData:(NSString*)name value:(NSString*)value;
+ (NSString*)readData:(NSString *)name;
+ (NSString*)getUMParams:(NSString*)key;
@end

