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
 * @return
 *        返回一个唯一的 编码用于识别后续回调, 根据唯一标识判断信号
 */
- (NSString *)openVideoCanvas:(MVDRabbitmqModel * _Nonnull)config
             withCanvas:( MVDPlayerVideoCanvas* _Nullable)canvas NS_SWIFT_NAME(openVideoCanvas(_:withCanvas:));
@end

NS_ASSUME_NONNULL_END
