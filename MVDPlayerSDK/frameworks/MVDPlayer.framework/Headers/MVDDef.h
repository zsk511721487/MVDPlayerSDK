//
//  MVDDef.h
//  MVDPlayerSDK
//
//  Created by 张少康 on 2024/2/2.
//

#ifndef MVDDef_h
#define MVDDef_h

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define MVDPlayerLog(format, ...) NSLog((@"[Line %d] " format), __LINE__, ##__VA_ARGS__)

/**@brief 播放器事件类型*/
typedef enum MVDEventType: NSUInteger {
    /**@brief 设备空闲中*/
    MVDEventFree,
    /**@brief 连接设备中*/
    MVDEventConnecting,
    /**@brief 连接设备成功*/
    MVDEventConnectDone,
    /**@brief 准备完成事件(流创建成功)*/
    MVDEventPrepareDone,
    /**@brief 首帧显示*/
    MVDEventFirstFrameDisplay,
    /**@brief 跳转完成事件*/
    MVDEventSeekEnd,
    /**@brief 播放完成事件(回放结束)*/
    MVDEventCompletion,
    /**@brief 断开连接*/
    MVDEventConnectStop,
    /**@brief 连接失败*/
    MVDEventConnectFailed,
} MVDEventType;


typedef enum MVDPlayerError : NSUInteger {
    // 连接相关错误
    /**@brief 设备连接失败*/
    MVDPlayerErrorDeviceConnect = 0,
    /**@brief 流连接失败*/
    MVDPlayerErrorStreamConnect,
    
    // 播放相关错误  
    /**@brief 回放操作失败*/
    MVDPlayerErrorPlaybackFailed,
    /**@brief 视频清晰度切换失败*/
    MVDPlayerErrorStreamSwitchFailed,
    /**@brief 暂停操作失败*/
    MVDPlayerErrorPause,
    /**@brief 恢复播放失败*/
    MVDPlayerErrorResume,
    
    // 功能相关错误
    /**@brief 对讲功能失败*/
    MVDPlayerErrorTalkingFailed,
    /**@brief 视频录制失败*/
    MVDPlayerErrorRecordingFailed,
    /**@brief 云台操作失败*/
    MVDPlayerErrorPTZFailed,
    /**@brief 图片截取失败*/
    MVDPlayerErrorFrameCapture,
    
    // 系统相关错误
    /**@brief 无效的状态转换*/
    MVDPlayerErrorInvalidState,
    /**@brief 资源操作失败*/
    MVDPlayerErrorResourceFailed,
    /**@brief 并发操作冲突*/
    MVDPlayerErrorConcurrentConflict,
    
    // UI相关错误
    /**@brief 未设置 preview视图*/
    MVDPlayerErrorNullPreview,
    
    // 废弃的错误类型(保持向后兼容)
    MVDPlayerErrorRealPlayConnect __deprecated_msg("使用 MVDPlayerErrorStreamConnect 替代"),
    MVDPlayerErrorRealPlayOpenTalking __deprecated_msg("使用 MVDPlayerErrorTalkingFailed 替代"),
    MVDPlayerErrorRealPlayLinkTalking __deprecated_msg("使用 MVDPlayerErrorTalkingFailed 替代"),
    MVDPlayerErrorPlayBackConnect __deprecated_msg("使用 MVDPlayerErrorStreamConnect 替代"),
    MVDPlayerErrorPlayBackSpeed __deprecated_msg("使用 MVDPlayerErrorPlaybackFailed 替代"),
    MVDPlayerErrorVideoRecoder __deprecated_msg("使用 MVDPlayerErrorRecordingFailed 替代"),
    MVDPlayerErrorPlayBackUpdateTime __deprecated_msg("使用 MVDPlayerErrorPlaybackFailed 替代"),
} MVDPlayerError;

#endif /* MVDDef_h */
