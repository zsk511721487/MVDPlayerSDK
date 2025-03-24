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

/// 开启对讲，目前只有会诊需要
///  - Parameters:
///   - volcRoomId: 会议的 room id
///   - buzid: Volc businnessID
///   - closeOtherTaling: 是否关闭其他对讲
- (int)openTalking:(NSString *)volcRoomId
             buzid:(NSString *)buzid
  closeOtherTaling:(BOOL)closeOtherTaling;

/// 获取HDeivce
/// - Parameters:
///   - deviceId 设备id
- (void*)getHDevice:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq;


/// 获取HDeivce
/// - Parameters:
///   - deviceId: 设备 id
///   - rabbitmq: 创建所需要的参数
///   - completion: 成功获取的回调
- (void)getHDeviceForDeviceId:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq completion:(void (^)(void*))completion;

/// 创建设备
/// - Parameters:
///   - deviceId: 设备id
///   - rabbitmq: 通道数据
- (void)createHDevice:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq;

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


/// 移除某个信号
/// - Parameters:
///   - deviceId: 设备id
///   - channelId: 通道id
- (void)deleteStreamIdWith:(UInt32)deviceId channelId:(UInt32)channelId;

- (void)closeAll;

@end

NS_ASSUME_NONNULL_END
