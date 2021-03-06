/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "MobClick.h"
#import "UMSocial_Sdk_Extra_Frameworks/Sina/UMSocialSinaHandler.h"
#import "UMSocial_Sdk_Extra_Frameworks/UMSocial_ScreenShot_Sdk/UMSocialScreenShoter.h"
#import "../../Classes/MainMenuScene.h"
#import "ConfigHeader.h"

@implementation AppController

static GADInterstitial *interstitial;
static RootViewController *viewController;
static UIImage *screenShotImg;
#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    viewController = _viewController;
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    app->run();
    
    //友盟统计
    [MobClick startWithAppkey:@"54f7ecf7fd98c5404e000c53" reportPolicy:BATCH channelId:@""];
    [UMSocialData setAppKey:@"54f7ecf7fd98c5404e000c53"];
    //友盟参数
    [MobClick updateOnlineConfig];
//    [MobClick getConfigParams:@"AdSwitch"];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onlineConfigCallBack:) name:UMOnlineConfigDidFinishedNotification object:nil];
    //admob
    adCounts = 0;
    [self loadAdmob];
    
    //微博sso
    [UMSocialSinaHandler openSSOWithRedirectURL:@"http://sns.whalecloud.com/sina2/callback"];
    
    [NSThread sleepForTimeInterval:1.0];   //设置进程停止1秒
    
    //初始化有米
    [YouMiNewSpot initYouMiDeveloperParams:@"ceb691b5a2423ca2" YM_SecretId:@"fce90660104f61e8"];
    [YouMiNewSpot initYouMiDeveLoperSpot:kSPOTSpotTypePortrait];
    
    return YES;
}

- (void)onlineConfigCallBack:(NSNotification *)notification {
    NSLog(@"online config has fininshed and params = %@", notification.userInfo);
    if ([[notification.userInfo objectForKey:@"AdSwitch"] isEqual:@"open"]) {
        
        gGlobal->isHomeAdSwitch = true;
        
    }else{
        
        gGlobal->isHomeAdSwitch = false;
        
    }
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
    if (gGlobal->isHomeAdSwitch) {
        [AppController showInterstitial];
    }
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}

+ (void)showInterstitial {

    if ([interstitial isReady]) {
        [interstitial presentFromRootViewController:viewController];
    }else{
        [YouMiNewSpot showYouMiSpotAction:^(BOOL flag){
            if (flag) {
                NSLog(@"log添加展示成功的逻辑");
            }
            else{
                NSLog(@"log添加展示失败的逻辑");
            }
        }];
    }
}


- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
    
}

- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
{
    if ([error code]  == kGADErrorNetworkError || [error code] == kGADErrorInternalError) {
        [self loadAdmob];
    }
}

#pragma mark Display-Time Lifecycle Notifications
- (void)interstitialWillPresentScreen:(GADInterstitial *)ad
{
    
}

- (void)interstitialWillDismissScreen:(GADInterstitial *)ad
{
    
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad
{
    [self loadAdmob];
}

- (void)interstitialWillLeaveApplication:(GADInterstitial *)ad
{
    
}

- (void)loadAdmob{
    adCounts ++;
    interstitial = [[GADInterstitial alloc] init];
    if (adCounts % 3 == 0) {
        interstitial.adUnitID = @"ca-app-pub-9911143712135979/8942918444";
    }else{
        interstitial.adUnitID = @"ca-app-pub-1771996690526222/5470976596";
    }
    [interstitial setDelegate:self];
    GADRequest *request = [GADRequest request];
    [interstitial loadRequest:request];
}

+ (void)share:(NSString*)imgPath ShareText:(NSString*)text
{
    
    UIImage* img = [UIImage imageWithContentsOfFile:imgPath] ;
    

    [[UMSocialControllerService defaultControllerService] setShareText:text shareImage:img socialUIDelegate:self];
    if (gGlobal->isChinese) {
        
        //设置分享内容和回调对象
        [UMSocialSnsPlatformManager getSocialPlatformWithName:UMShareToSina].snsClickHandler(viewController,[UMSocialControllerService defaultControllerService],YES);
    }else
    {
        
        //设置分享内容和回调对象
        [UMSocialSnsPlatformManager getSocialPlatformWithName:UMShareToTwitter].snsClickHandler(viewController,[UMSocialControllerService defaultControllerService],YES);
    }
}

+ (void)screenShot
{
    screenShotImg = [[UMSocialScreenShoterDefault screenShoter] getScreenShot];
}

+ (void)saveData:(NSString*)name value:(NSString*)value
{
    NSUserDefaults *defaults =[NSUserDefaults standardUserDefaults];
    [defaults setObject:value forKey:name];
}

+ (NSString*)readData:(NSString *)name
{
    NSUserDefaults *defaults =[NSUserDefaults standardUserDefaults];
    NSString *value = [defaults objectForKey:name];
    return value;
}

+ (NSString*)getUMParams:(NSString*)key
{
    return [MobClick getConfigParams:@"AdSwitch"];
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    return  [UMSocialSnsService handleOpenURL:url];
}
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation
{
    return  [UMSocialSnsService handleOpenURL:url];
}

@end
