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
- (void*)getHDevice:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq ;

/// 关闭信号
- (void)close:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq streamId:(int)streamId;


/// 删除某个 streamid
/// - Parameters:
///   - channelId: 通道id
///   - deviceId: 设备id
- (void)removeStreamIdWithChannelId:(int)channelId deviceId:(int)deviceId;

/// 获取 streamId
/// - Parameters:
///   - channelId: 通道id
///   - deviceId: 设备id
- (NSDictionary*)getStreamIdWithChannelId:(int)channelId deviceId:(int)deviceId;

/// 批量创建 streamId
/// - Parameters:
///   - rabbitmqs:所有通道数据集合
///   - deviceId: 当前设备id
- (void)openAllRealPlay:(NSArray<MVDRabbitmqModel *>*)rabbitmqs;



- (void)closeAll;

@end

NS_ASSUME_NONNULL_END
