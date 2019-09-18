//
//  ViewController.m
//  KJAspectsDemo
//
//  Created by 杨科军 on 2019/9/10.
//  Copyright © 2019 杨科军. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

+ (NSInteger)testWithA:(NSString*)a B:(NSInteger)b{
    NSInteger i = [a integerValue] + b;
    NSLog(@"\nnum = %ld",i);
    return i;
}

- (void)xxxxWithA:(NSString*)a B:(NSString*)b{
    NSLog(@"\n-----实例方法:%@  %@",a,b);
}

@end
