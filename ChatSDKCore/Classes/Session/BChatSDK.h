//
//  BChatSDK.h
//  AFNetworking
//
//  Created by Ben on 11/7/17.
//

#import <Foundation/Foundation.h>
#import <ChatSDK/BNetworkFacade.h>
@class TabbarVC;
@class BConfiguration;
@class RXPromise;
@class BBackgroundPushNotificationQueue;
@class BInternetConnectivity;

@protocol PInterfaceFacade;
@protocol PUser;
@protocol BStorageAdapter;

@interface BChatSDK : NSObject {
    BConfiguration * _configuration;
    id<PInterfaceFacade> _interfaceManager;
    BBackgroundPushNotificationQueue * _pushQueue;
}

@property (nonatomic, readonly) BConfiguration * configuration;
@property (nonatomic, readwrite) id<PInterfaceFacade> interfaceManager;

+(BChatSDK *) shared;
+(BConfiguration *) config;

// Application lifecycle methods - should be called from App Delegate
+(void) initialize: (BConfiguration *) config app:(UIApplication *)application options:(NSDictionary *)launchOptions;
+(void) initialize: (BConfiguration *) config app:(UIApplication *)application options:(NSDictionary *)launchOptions interfaceAdapter: (id<PInterfaceFacade>) adapter;

+(BOOL) application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;
+(BOOL) application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;
+(void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;
+(void) application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

// Integration helper methods

// Authenticate using a Firebase token
+(RXPromise *) authenticateWithToken: (NSString *) token;

// Update the username image and image url safely i.e. this method will wait until
// the user has been authenticated correctly by using the post auth hook
+(void) updateUserWithName: (NSString *) name image: (UIImage *) image url: (NSString *) url;

// Logout
+(RXPromise *) logout;

// This is used if we get a push notification while the user isn't authenticated. We add it to the
// queue then check the queue when we launch the main activity and trigger the push handling
-(BBackgroundPushNotificationQueue *) pushQueue;

// API Methods
+(id<PCoreHandler>) core;
+(id<PAuthenticationHandler>) auth;
+(id<PUploadHandler>) upload;
+(id<PVideoMessageHandler>) videoMessage;
+(id<PAudioMessageHandler>) audioMessage;
+(id<PImageMessageHandler>) imageMessage;
+(id<PLocationMessageHandler>) locationMessage;
+(id<PPushHandler>) push;
+(id<PContactHandler>) contact;
+(id<PTypingIndicatorHandler>) typingIndicator;
+(id<PModerationHandler>) moderation;
+(id<PSearchHandler>) search;
+(id<PPublicThreadHandler>) publicThread;
+(id<PBlockingHandler>) blocking;
+(id<PLastOnlineHandler>) lastOnline;
+(id<PNearbyUsersHandler>) nearbyUsers;
+(id<PReadReceiptHandler>) readReceipt;
+(id<PStickerMessageHandler>) stickerMessage;
+(id<PSocialLoginHandler>) socialLogin;
+(id<PUser>) currentUser;
+(id) handler: (NSString *) name;
+(id<PHookHandler>) hook;
+(id<PUsersHandler>) users;
+(BOOL) isMe: (id<PUser>) user;
+(id<PInterfaceFacade>) ui;
+(id<BStorageAdapter>) db;
+(id<PFileMessageHandler>) fileMessage;
+(id<PEncryptionHandler>) encryption;
+(id<PInternetConnectivityHandler>) connectivity;

@end
