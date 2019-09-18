//
//  AppDelegate.m
//  KJAspectsDemo
//
//  Created by 杨科军 on 2019/9/10.
//  Copyright © 2019 杨科军. All rights reserved.
//

#import "AppDelegate.h"
#import "KJAspectsTool.h"
#import "ViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    /// AOP
    [self kj_AopAspects];
    
    return YES;
}

/// AOP
- (void)kj_AopAspects{
    [KJAspectsTool kj_AspectsWithClassName:@"ViewController" Selector:@selector(testWithA:B:) Options:(KJAspectPositionAfter) UsingBlock:^(KJAspectsTool * _Nonnull info, NSError * _Nonnull error) {
        NSLog(@"\n类方法:instance == %@\narguments == %@\n", NSStringFromClass([info.kj_instance class]),info.kj_arguments);
    }];
    [ViewController testWithA:@"1" B:1];

    ViewController *vc = [ViewController new];
    [KJAspectsTool kj_AspectsWithMetalClass:vc Selector:@selector(xxxxWithA:B:) Options:(KJAspectPositionInstead) UsingBlock:^(KJAspectsTool * _Nonnull info, NSError * _Nonnull error) {
        NSLog(@"\n实例方法:instance == %@\narguments == %@", NSStringFromClass([info.kj_instance class]),info.kj_arguments);
    }];
    /// 调用私有方法
    [vc performSelector:@selector(xxxxWithA:B:) withObject:@"3" withObject:@"33"];
    // objc_msgSend(vc, @selector(xxxxWithA:B:), @"1", @"2");
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
