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
- (void*)getHDevice:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq;

/// 关闭所有信号
- (void)closeAll;

@end

NS_ASSUME_NONNULL_END
