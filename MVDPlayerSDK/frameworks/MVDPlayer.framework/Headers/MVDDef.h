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

/**@brief 播放器事件类型*/
typedef enum MVDEventType: NSUInteger {
    /**@brief 链接设备中*/
    MVDEventConnecting,
    /**@brief 链接设备成功*/
    MVDEventConnectDone,
    /**@brief 准备完成事件*/
    MVDEventPrepareDone,
    /**@brief 播放完成事件*/
    MVDEventCompletion,
    /**@brief 首帧显示*/
    MVDEventFirstFrameDisplay,
    /**@brief 跳转完成事件*/
    MVDEventSeekEnd,
    /**@brief 断开连接*/
    MVDEventConnectStop,
    /**@brief 链接失败*/
    MVDEventConnectFailed,
} MVDEventType;


typedef enum MVDPlayerError : NSUInteger {
    /**@brief 设备链接失败*/
    MVDPlayerErrorDeviceConnect = 0,
    /**@brief 实时视频链接失败*/
    MVDPlayerErrorRealPlayConnect,
    /**@brief 实时视频开启对讲失败*/
    MVDPlayerErrorRealPlayOpenTalking,
    /**@brief 回放视频链接失败*/
    MVDPlayerErrorPlayBackConnect,
    /**@brief 回放视频设置倍速失败*/
    MVDPlayerErrorPlayBackSpeed,
    /**@brief 视频录制失败*/
    MVDPlayerErrorVideoRecoder,
    /**@brief 图片截取失败*/
    MVDPlayerErrorFrameCapture,
    /**@brief 未设置 privew*/
    MVDPlayerErrorNullPreview ,
    /**@brief 暂停失败*/
    MVDPlayerErrorPause,
    /**@brief 恢复播放失败*/
    MVDPlayerErrorResume,
    /**@brief 云台操作失败*/
    MVDPlayerErrorPTZ,
    /**@brief 回放屏更新时间失败*/
    MVDPlayerErrorPlayBackUpdateTime,
    
} MVDPlayerError;

#endif /* MVDDef_h */
