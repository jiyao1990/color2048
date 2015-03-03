#import <UIKit/UIKit.h>

#import <GoogleMobileAds/GoogleMobileAds.h>
@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GADInterstitialDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;


+ (void)showInterstitial;

@end

