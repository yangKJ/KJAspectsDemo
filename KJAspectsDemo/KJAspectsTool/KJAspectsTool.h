//
//  KJAspectsTool.h
//  KJAspectsDemo
//
//  Created by 杨科军 on 2019/9/10.
//  Copyright © 2019 杨科军. All rights reserved.
//  AOP(面向切面编程) 相关的一款 Aspects 封装工具

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
//#import <Aspects.h>   /// Aspects 封装工具 - 由于需要引入三方库略显麻烦，故将作者代码直接拷贝过来方便使用
#import <objc/runtime.h>
#import <objc/message.h>
/// Aspects 相关文档:https://www.jianshu.com/p/891c7ce7304e
/** Aspects 方法说明：
 /// 对象调用时，放回对象
 - (id)instance;
 NSString *className = NSStringFromClass([info.instance class]);
 /// 方法的原始实现
 - (NSInvocation *)originalInvocation;
 /// 原方法调用的参数
 - (NSArray *)arguments;
 
 官方的一个实用例子：
 [PSPDFDrawView aspect_hookSelector:@selector(shouldProcessTouches:withEvent:) withOptions:AspectPositionInstead usingBlock:^(id<AspectInfo> info, NSSet *touches, UIEvent *event) {
 // Call original implementation.
 BOOL processTouches;
 NSInvocation *invocation = info.originalInvocation;
 [invocation invoke];
 [invocation getReturnValue:&processTouches];
 
 if (processTouches) {
 processTouches = pspdf_stylusShouldProcessTouches(touches, event);
 [invocation setReturnValue:&processTouches];
 }
 } error:NULL];
 */

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, KJAspectOptions) {
    KJAspectPositionAfter   = 0,            /// 在原方法调用完成以后进行调用
    KJAspectPositionInstead = 1,            /// 取代原方法
    KJAspectPositionBefore  = 2,            /// 在原方法调用前执行
    KJAspectOptionAutomaticRemoval = 1 << 3 /// 在调用了一次后清除(只能在对象方法中使用) 执行一次后移除Hook
};

@protocol AspectToken;
@interface KJAspectsTool : NSObject
/// xcode消除Undeclared selector 警告
#pragma GCC diagnostic ignored "-Wundeclared-selector"
/// 出现Category is implementing a method which will also be implemented by its primary class警告的处理方法
#pragma clang diagnostic ignored "-Wobjc-protocol-method-implementation"

/********************** 仅在回调中使用有效 **********************/
/// 当前Hook的实例
@property(nonatomic,strong,readonly) id kj_instance;
/// 被 Hook 方法的原始 invocation  NSInvocation相关文档:https://www.jianshu.com/p/06b832b10283
@property(nonatomic,strong,readonly) NSInvocation *kj_originalInvocation;
/// 被 Hook 方法的所有参数装箱 这是懒惰的(懒加载的)
@property(nonatomic,strong,readonly) NSArray *kj_arguments;
/********************** 仅在回调中使用有效 **********************/

/**替换所有类对象的方法实现
 @param class_name 类名
 @param selector   原始方法的sel
 @param options    执行block时机选项，可以在原始方法执行前，执行后，或者进行替换
 @param block      需要注入的方法执行  error 如果出现异常，则该值不为空
 @return 返回服从AspectToken协议的对象，可以进行移除等操作  [aspect remove];
 */
+ (id<AspectToken>)kj_AspectsWithClassName:(NSString*)class_name Selector:(SEL)selector Options:(KJAspectOptions)options UsingBlock:(void (^_Nullable)(KJAspectsTool *info, NSError *error))block;

/**替换某个类对象的方法实现
 @param metalClass 类对象
 @param selector   原始方法的sel
 @param options    执行block时机选项，可以在原始方法执行前，执行后，或者进行替换
 @param block      需要注入的方法执行  error 如果出现异常，则该值不为空
 @return 返回服从AspectToken协议的对象，可以进行移除等操作  [aspect remove];
 */
+ (id<AspectToken>)kj_AspectsWithMetalClass:(id)metalClass Selector:(SEL)selector Options:(KJAspectOptions)options UsingBlock:(void (^_Nullable)(KJAspectsTool *info, NSError *error))block;

@end

NS_ASSUME_NONNULL_END
