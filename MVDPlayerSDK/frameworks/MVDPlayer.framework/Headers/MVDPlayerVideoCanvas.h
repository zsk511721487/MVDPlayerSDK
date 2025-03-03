//
//  MVDPlayerVideoCanvas.h
//  MVDPlayer
//
//  Created by 张少康 on 2024/10/17.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MVDPlayerVideoCanvas : NSObject
/**
 * @locale zh
 * @brief 本地视图句柄
 */
@property(strong, nonatomic) UIView* _Nullable view;

/**
 * @locale zh
 * @brief 当前视频的唯一id
 */
@property(copy, nonatomic) NSString *reuseIdentifier;

/**
 * @locale zh
 * @brief 视频模式 0实时 1回放
 */
@property(assign, nonatomic) int playType;

/**
 * @locale zh
 * @brief 清晰度 0 是高清， 1 是标清
 */
@property(assign, nonatomic) int channelType;

/**
 * @locale zh
 * @brief 设备类型 根据设备类型获取视频的原始宽高
 */
@property(assign, nonatomic) int videoChannelType;
@end

NS_ASSUME_NONNULL_END
