//
//  MVDPlayerVideo.h
//  MVDPlayer
//
//  Created by 张少康 on 2024/10/17.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class  MVDPlayerVideo;
@protocol MVDPlayerVideoDelegate <NSObject>
@optional

-(void)videoOpened:(MVDPlayerVideo *_Nullable)video stramInfo:(NSString *_Nullable)stramInfo;

- (void)videoEvent:(MVDPlayerVideo *_Nullable)video ;

@end

NS_ASSUME_NONNULL_BEGIN

@class MVDRabbitmqModel, MVDPlayerVideoCanvas;
@interface MVDPlayerVideo : NSObject
@property (nonatomic, weak) id<MVDPlayerVideoDelegate> delegate;
// 是否自动播放
@property(nonatomic, assign,getter=isAutoPlay) BOOL autoPlay;

+ (instancetype)shared;

/**
 * @locale zh
 * @type api
 * @region 打开视频
 * @brief 渲染视频流时<br>
 *        如果需要解除视频的绑定视图，把 `view` 设置为空
 * @param config 远端流信息, 详见 MVDRabbitmqModel{@link #MVDRabbitmqModel}。
 * @param canvas 视图
 */
- (void)openVideoCanvas:(MVDRabbitmqModel * _Nonnull)config
             withCanvas:( MVDPlayerVideoCanvas* _Nullable)canvas NS_SWIFT_NAME(openVideoCanvas(_:withCanvas:));


/**
 * @locale zh
 * @type api
 * @region 恢复播放
 * @brief 回放视频<br>
 * @param reuseIdentifier video 的唯一标识符
 */
- (void)resumeWith:(NSString *)reuseIdentifier;

/**
 * @locale zh
 * @type api
 * @region 暂停播放
 * @brief 回放视频<br>
 * @param reuseIdentifier video 的唯一标识符
 */
- (void)pauseWith:(NSString *)reuseIdentifier;

/**
 * @locale zh
 * @type api
 * @region 恢复播放
 * @brief 回放视频<br>
 *        在视频加载成功后调用，否则无效
 * @param reuseIdentifier video 的唯一标识符
 * @param timestamp 需要更新到的时间，使用的时间戳
 */
- (void)updateStartDateWith:(NSString *)reuseIdentifier timestamp:(uint32_t)timestamp;

/**
 * @locale zh
 * @type api
 * @region 设置播放速度以播放回放视频流
 * @brief 回放视频<br>
 *         要设置的播放速度的索引。该速度索引可以从 -3 到 3，以将播放速度设置为正常播放速度的 (2 << speed_index) 倍。换句话说：
             -speed_index 为 -3，播放速度将是正常播放速度的 1/8。
             -speed_index 为 -2，播放速度将是正常播放速度的 1/4。
             -speed_index 为 -1，播放速度将是正常播放速度的 1/2。
             -speed_index 为 0，播放速度将是正常播放速度，即一倍速。
             -speed_index 为 1，播放速度将是正常播放速度的 2 倍。
             -speed_index 为 2，播放速度将是正常播放速度的 4 倍。
             -speed_index 为 3，播放速度将是正常播放速度的 8 倍。
 * @param reuseIdentifier video 的唯一标识符
 * @param speedIndex 需要设置的播放倍数
 */
- (void)setVideoSpeedWith:(NSString *)reuseIdentifier speed:(int)speedIndex;

/**
 * @locale zh
 * @type api
 * @region 开启对讲功能
 * @brief 实时视频<br>
          只会存在一个开启对讲的视频，可以根据 方法判断是否已经开启， 回调方法为
 * @param reuseIdentifier video 的唯一标识符
 * @param userId 当前用户的 id
 */
- (void)openVolcTalkingWith:(NSString *)reuseIdentifier userId:(NSString*)userId;

/**
 * @locale zh
 * @type api
 * @region 关闭视频
 * @brief 关闭视频流
 * @param reuseIdentifier video 的唯一标识符
 */
- (void)closeVideoWith:(NSString *)reuseIdentifier;

/**
 * @locale zh
 * @type api
 * @region 获取视频的宽高
 * @brief 获取视频原始宽高
 * @param reuseIdentifier video 的唯一标识符
 * @return 视频的原始宽高
 */
- (CGSize)getVieoSizeWith:(NSString *)reuseIdentifier;

/**
 * @locale zh
 * @type api
 * @region 切换视频的清晰度
 * @brief 实时视频<br>
 *        目前只有实时视频可切换，0 代表高清， 1 代表标清
 * @param reuseIdentifier video 的唯一标识符
 */
- (void)switchVideoResolutionWith:(NSString *)reuseIdentifier;

/**
 * @locale zh
 * @type api
 * @region 获取视频的清晰度
 * @brief 实时视频<br>
 *        目前只有实时视频可切换，0 代表高清， 1 代表标清
 * @param reuseIdentifier video 的唯一标识符
 * @return 视频的当前清晰度
 */
- (int)getVideoResolutionWith:(NSString *)reuseIdentifier;


@end

NS_ASSUME_NONNULL_END
