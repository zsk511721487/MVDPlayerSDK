//
//  MVDHDeviceManager.h
//  MVDPlayerSDK
//
//  Created by 张少康 on 2024/2/18.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MVDRabbitmqModel;

@interface MVDHDeviceManager : NSObject

+ (instancetype)shared;

/// 获取HDeivce
/// - Parameters:
///   - deviceId 设备id
- (void*)getHDevice:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq queue:(dispatch_queue_t)queue;

/// 关闭信号
- (void)close:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq;

- (void)closeAll;
@end

NS_ASSUME_NONNULL_END
