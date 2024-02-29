//
//  MVDViewController.m
//  MVDPlayerSDK
//
//  Created by 511721487@qq.com on 02/28/2024.
//  Copyright (c) 2024 511721487@qq.com. All rights reserved.
//

#import "MVDViewController.h"
#import <MVDPlayer/MVDPlayerImpl.h>

@interface MVDViewController ()<MVDPlayerDelegate>
@property (nonatomic, strong) UIView *sourceView;
@property (nonatomic, strong) MVDPlayer *player;
@end

@implementation MVDViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    _sourceView = [[UIView alloc]initWithFrame:CGRectMake(0, 100, 200, 200/16*9)];
    _sourceView.backgroundColor = UIColor.redColor;
    [self.view addSubview:_sourceView];
    [self requestNetworkPermission];
    
}

- (void)requestNetworkPermission {
    // 这里可以使用合适的方式请求网络权限，比如使用NSURLSession发起一个简单的网络请求
    NSURL *url = [NSURL URLWithString:@"https://www.example.com"];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    
    NSURLSession *session = [NSURLSession sharedSession];
    NSURLSessionDataTask *dataTask = [session dataTaskWithRequest:request
                                                completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        // 处理请求的结果，这里可以根据需要进行具体的处理
        if (error) {
            NSLog(@"Failed to request network permission: %@", error);
        } else {
            NSLog(@"Network permission granted successfully!");
            [self connectDevice];
        }
    }];

    [dataTask resume];
}

- (void)connectDevice {
    
    self.player = [[MVDPlayer alloc] init];
    self.player.preView = _sourceView;
    self.player.delegate = self;
    [self.player connectWithDeviceId:1 channel:33];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onPlayerEvent:(MVDPlayer *)player eventType:(MVDEventType)eventType {
    NSLog(@"链接状态 %lu", (unsigned long)eventType);
}

- (void)onError:(MVDPlayer *)player errorType:(MVDPlayerError)errorType {
    NSLog(@"出现错误 %lu", (unsigned long)errorType);
}

@end
