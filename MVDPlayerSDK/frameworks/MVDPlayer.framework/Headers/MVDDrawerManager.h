//
//  MVDDrawerManager.h
//  MVDPlayer
//
//  Created by 张少康 on 2025/1/10.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MVDDrawerShape;

@interface MVDDrawerManager : NSObject

@property (nonatomic, strong) MVDDrawerShape *currentShape; // 当前正在绘制的图形

@property (nonatomic, assign) BOOL isOpen; // 是否开启绘制

@property (nonatomic, assign) int32_t currentDeviceId; // 当前正在涂鸦的设备id

@property (nonatomic, strong) NSMutableDictionary<NSString*, NSNumber*> *referenceCounts;

+ (instancetype)shared;

// 设置线宽
- (void)setPenWidth:(int32_t)width;

// 设置画笔颜色
- (void)setPenColor:(uint32_t)color;

// 设置绘画形状
- (void)setDrawCmd:(int)cmd;

// 配置设备和通道
- (BOOL)configureWithclientId:(int32_t)clientId
              currentDeviceId:(int32_t)currentDeviceId;

// 开启 Scribbler
- (BOOL)openScribblerWidth:(void*)device
                   channel:(int)channel;

// 发布形状
- (BOOL)publishShapeWidth:(void*)device
                    shape:(MVDDrawerShape*)shape
                  channel:(int)channel;

// 发布文本
//- (BOOL)publishText:(const MVDTEXT *)text;

// 关闭 Scribbler
- (void)closeScribblerWidth:(void*)device
                    channel:(int)channel;

// 释放所有资源
- (void)closeAllResources;

@end

NS_ASSUME_NONNULL_END
