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

// 设备自动销毁控制
@property (nonatomic, assign) BOOL autoDestroyEnabled;

+ (instancetype)shared;

/// 开启对讲，目前只有会诊需要
///  - Parameters:
///   - clientid:客户端标识符，目前使用的是用户id
///   - volcRoomId: 会议的 room id
///   - buzid: Volc businnessID
///   - closeOtherTaling: 是否关闭其他对讲
- (int)openTalking:(int)clientid
          deviceid:(uint32_t)deviceid
        volcRoomId:(NSString *)volcRoomId
             buzid:(NSString *)buzid
  closeOtherTaling:(BOOL)closeOtherTaling;

- (void)closeTalking:(uint32_t)deviceid;

/// 异步获取HDevice - 专业版本
/// - Parameters:
///   - deviceId: 设备id
///   - rabbitmq: rabbitmq配置
///   - completion: 异步回调，在后台队列中执行
- (void)getHDeviceForDeviceId:(int)deviceId 
                     rabbitmq:(MVDRabbitmqModel *)rabbitmq 
                   completion:(void(^)(void * _Nonnull device))completion;

/// 释放HDevice引用 - 专业版本
/// - Parameters:
///   - deviceId: 设备id
///   - rabbitmq: rabbitmq配置
- (void)releaseHDeviceForDeviceId:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq;

/// 获取HDeivce - 已废弃，请使用异步版本
/// - Parameters:
///   - deviceId 设备id
- (void*)getHDevice:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq __deprecated_msg("Use getHDeviceForDeviceId:rabbitmq:completion: instead");


/// 同步创建单个HDevice（保持兼容性）
/// - Parameters:
///   - deviceId: 设备id
///   - rabbitmq: 通道数据
- (void)createHDevice:(int)deviceId rabbitmq:(MVDRabbitmqModel *)rabbitmq;

/// 批量创建多个HDevice - 推荐使用
/// - Parameters:
///   - rabbitmqs: 设备配置数组
///   - completion: 完成回调 - allSuccess: 是否全部成功, failedKeys: 失败的设备key数组
- (void)createMultipleHDevices:(NSArray<MVDRabbitmqModel *> *)rabbitmqs 
                    completion:(void(^)(BOOL allSuccess, NSArray<NSString *> *failedKeys))completion;

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

/// 流程控制相关方法
/// 检查是否启用了标准流程控制
- (BOOL)isStandardFlowEnabled;

/// 检查是否已完成openAllRealPlay步骤
- (BOOL)hasCompletedOpenAllRealPlay;

/// 重置流程控制状态（用于特殊情况）
- (void)resetFlowControlState;

@end

NS_ASSUME_NONNULL_END
