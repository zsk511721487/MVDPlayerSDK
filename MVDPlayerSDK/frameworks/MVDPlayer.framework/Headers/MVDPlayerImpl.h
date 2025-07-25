//
//  NSObject+MVDRealPlay_h.h
//  MVDPlayer
//
//  Created by 曹江浩 on 2024/1/11.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MVDPlayer/MVDDef.h>
#import <MVDPlayer/MVDRabbitmqModel.h>

typedef NS_ENUM(int, EPTZControlType){
    EOCPTZStop       = 0,   //stop PTZ moving
    EOCPTZReset      = 1,   //reset PTZ to predefined position

    EOCPTZUp         = 21,   //œÚ…œ
    EOCPTZLeftUp     = 25,   //◊Û…œ
    EOCPTZDown       = 22,   //œÚœ¬
    EOCPTZLeftDown   = 27,   //◊Ûœ¬
    EOCPTZLeft       = 23,   //œÚ◊Û
    EOCPTZRightUp    = 26,   //”“…œ
    EOCPTZRight      = 24,   //œÚ”“
    EOCPTZRightDown  = 28,   //”“œ¬
    EOCPTZZoomOut    = 12,   //‘∂
    EOCPTZZoomIn     = 11,   //Ω¸
};

typedef NS_ENUM(int, EPixelType){
    EOCPixelFmtYUV420P   = 0,    //AV_PIX_FMT_YUV420P
    EOCPixelFmtYUYV422   = 1,    //AV_PIX_FMT_YUYV422
    EOCPixelFmtRGB24     = 2,    //AV_PIX_FMT_RGB24
    EOCPixelFmtBGR24     = 3,    //AV_PIX_FMT_BGR24

    EOCPixelFmtARGB      = 25,   //AV_PIX_FMT_ARGB
    EOCPixelFmtRGBA      = 26,   //AV_PIX_FMT_RGBA
    EOCPixelFmtABGR      = 27,   //AV_PIX_FMT_ABGR
    EOCPixelFmtBGRA      = 28,   //AV_PIX_FMT_BGRA
};

@class  MVDPlayer;

@protocol MVDPlayerDelegate <NSObject>
@optional

/**
 @brief 播放器事件回调
 @param player 播放器player指针
 @param eventType 播放器事件类型
 */
-(void)onPlayerEvent:(MVDPlayer*)player eventType:(MVDEventType)eventType;

/**
 @brief 链接失败
 @param player 播放器player指针
 */
- (void)onPlayerConnectFailed:(MVDPlayer*)player;

/**
 @brief 回放视频更新时间成功
 @param player 播放器player指针
 */
- (void)onPlayerPlayBackUpdateDateSuccess:(MVDPlayer*)player;

/**
 @brief 回放视频更新播放进度
 @param player 播放器player指针
 @param speed 当前选择播放倍速
 */
- (void)onPlayerSetPlaybackSpeedSuccess:(MVDPlayer*)player speed:(int)speed;

/**
 @brief 暂停播放
 @param player 播放器player指针
 */
- (void)onPause:(MVDPlayer*)player;

/**
 @brief 恢复播放
 @param player 播放器player指针
 */
- (void)onResume:(MVDPlayer*)player;

/**
 @brief 对讲 VOLC 功能开启
 @param player 播放器player指针
 */
- (void)onPlayerTalkingOpened:(MVDPlayer* )player appId:(NSString *)appId roomId:(NSString*)roomId token:(NSString*)token;

/**
 @brief 对讲功能开启
 @param player 播放器player指针
 */
- (void)onPlayerTalkingOpened:(MVDPlayer*)player;

/**
 @brief 对讲功能关闭
 @param player 播放器player指针
 */
- (void)onPlayerTalkingStop:(MVDPlayer*)player;

/**
 @brief 音频开始传输
 @param player 播放器player指针
 */
- (void)onPlayerTalkingStart:(MVDPlayer*)player;

/**
 @brief 音频暂停传输
 @param player 播放器player指针
 */
- (void)onPlayerTalkingPause:(MVDPlayer*)player;

/**
 @brief 获取当前视频帧图片
 @param player 播放器player指针
 @param imagePath 图片地址
 */
- (void)onPlayerSnpshotCurrentFrame:(MVDPlayer*)player imagePath:(NSString*)imagePath;

/**
 @brief 开始录制视频
 @param player 播放器player指针
 */
- (void)onPlayerRecordVideoStart:(MVDPlayer*)player;

/**
 @brief 获取当前录制的视频地址
 @param player 播放器player指针
 @param videoPath 视频地址
 */
- (void)onPlayerRecordVideo:(MVDPlayer*)player videoPath:(NSString*)videoPath;

/**
 @brief 当前录制视频的时长
 @param player 播放器player指针
 @param duration 视频时长
 */
- (void)onPlayerRecordVideo:(MVDPlayer*)player duration:(int)duration;

/**
 @brief 录制视频时间过短
 @param player 播放器player指针
 */
- (void)onPlayerRecordVideoDurationTooShort:(MVDPlayer*)player;

/**
 @brief 错误代理回调
 @param player 播放器player指针
 */
- (void)onError:(MVDPlayer*)player errorType:(MVDPlayerError)errorType;

/**
 @brief 视频大小变化回调
 @param player 播放器player指针
 @param width 视频宽度
 @param height 视频高度
 */
- (void)onVideoSizeChanged:(MVDPlayer*)player width:(int)width height:(int)height;

/**
 @brief 视频清晰度变化回调
 @param player 播放器player指针
 @param quality 清晰度 0： 高清， 1：标清
 */
- (void)onVideoQualityChanged:(MVDPlayer*)player quality:(int)quality;

@end

@class MVDPlayerVideoCanvas;
@interface MVDPlayer : NSObject

/**
 @brief 设置预览视图
 */
@property (nonatomic, strong) UIView *preView;

/**
 @brief 设置代理，参考MVDPlayerDelegate
 @see MVDPlayerDelegate
 */
@property (nonatomic, weak) id<MVDPlayerDelegate> delegate;

- (instancetype)initWithStream:(int)streamtype;

/**
 @brief 实时信号连接
 @param deviceId 设备id
 @param channel 通道数
 @param channelType 摄像头类型
 @param rabbitmq 服务器配置
 */
- (void)connectWithDeviceId:(int)deviceId channel: (int)channel channelType:(int)channelType rabbitmq:(MVDRabbitmqModel *)rabbitmq;

/**
 @brief 切换码流
 @param type 0 为主码流 1 为副码流
 */
- (void)switchStreamType:(int)type;

/**
 @brief 回放信号连接
 @param deviceId 设备id
 @param channel 通道数
 @param starttime 开始时间
 @param channelType 摄像头类型
 @param rabbitmq 服务器配置
 */
- (void)connectPlayBackWithDeviceId:(int)deviceId channel: (int)channel starttime:(uint32_t)starttime channelType:(int)channelType rabbitmq:(MVDRabbitmqModel *)rabbitmq;

/**
 @brief 关闭信号连接
 */
- (void)stop;

/**
 @brief 销毁信号
 */
- (void)destroy;

/**
 @brief 开始接受回放屏信号
 */
- (void)startPlayBack;

/**
 @brief 暂停接受回放屏信号
 */
- (void)pausePlayBack;

/**
 @brief 恢复接受回放屏信号
 */
- (void)resumePlayBack;

/**
 @brief 更新回放信号的 开始和结束时间段
 @param starttime 开始时间
 成功与否会收到回调

 */
- (void)updatePlayBackwithStarttime:(uint32_t)starttime;

/**
 @brief 设置播放速度以播放回放视频流
 
 @param speedIndex  要设置的播放速度的索引。该速度索引可以从 -3 到 3，以将播放速度设置为正常播放速度的 (2 << speed_index) 倍。
 换句话说：
 -speed_index 为 -3，播放速度将是正常播放速度的 1/8。
 -speed_index 为 -2，播放速度将是正常播放速度的 1/4。
 -speed_index 为 -1，播放速度将是正常播放速度的 1/2。
 -speed_index 为 0，播放速度将是正常播放速度，即一倍速。
 -speed_index 为 1，播放速度将是正常播放速度的 2 倍。
 -speed_index 为 2，播放速度将是正常播放速度的 4 倍。
 -speed_index 为 3，播放速度将是正常播放速度的 8 倍。
 */
- (void)setPlayBackSpeed:(int)speedIndex;

/**
 @brief 开启 Volc 对讲功能
 
 成功或失败会收到 MVDPlayerDelegate 的回调
 */
- (void)openVolcTalkingWith:(NSString*)userId;

/**
 @brief 关闭对讲功能
 
 成功或失败会收到 相关回调
 */
- (void)closeTalking;

/**
 @brief 云台操作
 @param cmd 云台操作指令
 @param reserved 当前写死为0

 进行云台的操作
 */
- (void)controlPTZ:(EPTZControlType)cmd reserved:(int)reserved;

/**
 @brief 截取当前视频
 @see 图片会在回调方法 <onPlayerSnpshotCurrentFrame: image:>
  */
- (void)cuptureImage;

/**
 @brief 录制视频
 @see 图片会在回调方法 <onPlayerSnpshotCurrentFrame: videoPath:>
  */
- (void)startRecordVideo;

/**
 @brief 录制视频
 @see 图片会在回调方法 <onPlayerSnpshotCurrentFrame: videoPath:>
 如果时间小于3秒回收到 onPlayerRecordVideoDurationTooShort 回调，并不会停止录制。
  */
- (void)stopRecordVideo;

/**
 @brief 获取回放屏当前播放的日期
  */
- (uint32_t)getPlaybackStreamOsdtime;
/**
 @brief 获取回放屏当前播放的时长
  */
- (int)getPlaybackStreamPlayingtime;

/**
 @brief 获取当前视频的 size
  */
- (CGSize)getCurrentVideoSize;

/**
 @brief 设置涂鸦展示状态
 @param isEnableDraw false： 只能展示 true： 既展示又可以绘制
  */
- (void)setIsEnableDraw:(BOOL)isEnableDraw;

/**
 @brief 设置线宽
 @param width width of the pen in pixel
  */
- (void)setPenWidth:(int32_t)width;

/**
 @brief 设置画笔颜色
 @param color RGB color of the pen.  the color scheme:  0x00bbggrr
  */
- (void)setPenColor:(uint32_t)color;

/**
 @brief 设置绘画形状
 @param cmd  0:nothing 1:draw a line segment  2:draw a polyline  3:draw a circle/ellipse  4:draw an arrow  5: draw a rectangle
  */
- (void)setDrawCmd:(int)cmd;

/**
 @brief 撤销上一步涂鸦
  */
- (void)undoGraffiti;

/**
 @brief 清空涂鸦
  */
- (void)clearGradditi;

/**
* Get the resolution of a video source with the specific channel type.
*
* @param video_channel_type  type of the video channel
* @param width               buffer to retrieve the width in pixel of the resoution of the video source
* @param height              buffer to retrieve the height in pixel of the resoution of the video source
*
* @return:
*    true : the got width & height of the resolution in success
*    false : no resolution definition for the specific video channel type. In this case, please
*            treat the video source resolution same as the video stream resolution for this video channel type.
*
*/
-(bool) mvdGetSourceResolution:(int)video_channel_type width:(int*)width height:(int*)height;

//////////////////////////////////////////////////////////////////////////////
//                       API for log control of SDK                         //
//////////////////////////////////////////////////////////////////////////////
/**
 open log output when error occurred within let library.
*
* @param fName pointer to the log file name.
*              If NULL or empty file name provided to call this function for the first time,
*              the default file name "mvdplayer.log" is used. For later call this function,
*              the fname parameter is ignored
*
* @remarks:
*    Default log output is disabled
*/
- (void)mvdOpenLog:(NSString*)fName;
/**
* close log output.
* Can call mvd_open_log() to re-open log output after this function.
*/
- (void)mvdCloseLog;

//////////////////////////////////////////////////////////////////////////////
//                         API for E-Touch                                  //
//////////////////////////////////////////////////////////////////////////////


/**
* request to start the remote control of medicine device via E-Touch device
* installed on the MVD device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param channel    reserved in this version, must be 0.
* @param width, height in pixel. The real screen resolution of the remote computer to control
*                      can be -1 means keep the resolution set before.
*
* @return
*    >  0 :  started in succes and can call mvd_send_etouch_keyboard_event()/
*            mvd_send_etouch_mouse_event() to control the remote medicine device.
*    =  0 :  E-Touch function disabled on the MVD device,
*            no E-Touch device installed on the MVD device,
*            or E-Touch device controlled by other user now.
*    <  0 :  failed to started on system error
*/
-(int)  mvdStartEtouchControlWidth:(int)width height:(int)height;

/**
* send a keyboard event to the E-Touch which is installde the MVD device.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param events     Keyboard events. It can be one of the following:
*                       0x01 :  means the key pressed for a while,
*                                               and later need to send a seperate
*                                                ETOUCH_EVENT_KEYUP event.
*                       0x02 :    means a key up event
*                       0x01|0x02 : means the key hitted once.
* @param keyvalue   The key value defined at below:
*                         0x05~0x0C :  Left CTRL, SHIFT, ALT, GUI;
*                                      Right CTRL, SHIFT, ALT, GUI
*                         0x0D~0x11 :  ENTER, ESC, BACKSPACE, TAB, SPACE
*                         0x12      :  CAPS LOCK
*                         0x13~0x14 :  PAGE DOWN, PAGE UP
*                         0x15~0x18 :  LEFT, RIGHT, DOWN, UP
*                         0x19~0x1A :  HOME, END
*                         0x1B~0x1D :  DELETE, INSERT, Print Screen
*                         0x20~0x39 :  A ~ Z
*                         0x40~0x49 :  1 ~ 0
*                         0x50~0x5A :  -_, +=£¨ {[, }], |\, ~`, :;, "', ,<, >., ?/
*                         0x60~0x6B :  F1 ~F12
*
* @return
*    >  0 :  send the event sucessfully.
*    =  0 :  The events or the key is not supported, or
*            the E-Touch control is not opened for this user.
*    <  0 :  failed to send on system error
*
* Remarks:
*   Only after mvd_start_etouch_control() called in success, and then
*   mvd_send_etouch_keyboard_event() can be called.
*/
-(int)  mvdSendEtouchKeyboardEvent:(int)events keyvalue:(int)keyvalue;


/**
* send a mouse event to the E-Touch which is installde the MVD device.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
*
* @param event      Mouse event defined as below:
*                        0 : mouse move event
*
*                        1 : mouse left key down only
*                        2 : mouse left key down & up
*                        3 : mouse left key up ony
*
*                        4 : mouse right key down only
*                        5 : mouse right key down & up
*                        6 : mouse right key up only
*
*                        7 : mouse middle key down only
*                        8 : mouse middle key down & up
*                        9 : mouse middle key up only
*
*                        10 : mouse wheel forward
*                        11 : mouse wheel backward
*
* @param dx,dy    Mouse movement offset in pixel, only valid when event is mouse move event.
*                  for other events, them will be ignored.
*                  When event is mouse move event:
*                      dx < 0 :  move left; dx > 0: move right
*                      dy < 0 :  move up;   dy > 0: move down
*
* @return
*    >  0 :  send the event sucessfully.
*    =  0 :  The events or the key is not supported, or
*            the E-Touch control is not opened for this user.
*    <  0 :  failed to send on system error
*
* Remarks:
*   Only after mvd_start_etouch_control() called in success, and then
*   mvd_send_etouch_mouse_event() can be called.
*/
-(int)  mvdSendEtouchMouseEvent:(int)event dx:(int)dx dy:(int)dy;

/**
* send a mouse absolute position to the E-Touch which is installde the MVD device.
*
* @param hDevice         Handle to a connected MVD device which was returned by
*                        mvd_create_device().
* @param width, height   Absolution position in pixel
* @param keys            The states mouse keys defined as below:
*                             bit0 : mouse left key pressed or not. 1 for pressed
*                              bit1 : mouse right key pressed or not. 1 for pressed
*                          bit2 : mouse middle key pressed or not. 1 for pressed
*                          bit3~7: reserved, must be 0
*
* @return
*    >  0 :  send the position sucessfully.
*    =  0 :  The position is not supported, or
*            the E-Touch control is not opened for this user.
*    <  0 :  failed to send on system error
*
* Remarks:
*   Only after mvd_start_etouch_control() called in success, and then
*   mvd_send_etouch_mouse_position() can be called.
*/
-(int)  mvdSendEtouchMousePositionX:(uint16_t)x y:(uint16_t)y keys:(uint8_t)keys;

/**
* request to stop E-Touch remote control.
*/
-(void)  mvdCloseEtouchControl;

/**
* Helper API to speed up the release of some global resources, such as threads, memory,... to
* let the application exit as quick as possible.
*
* This function is only for some application or some scenario which need to quick exit and it can be called
* just before the whole program to exist. It is optional to call this API before the program exit.
*/
-(void) mvdCloseAllToExit;

/**
* Show/hide the waterprint for a spearate realplay or playback vide stream
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param id         the video stream id of realtime video stream/playback video stream.
* @param show       flag indicate to show or hide. true : show;  false : hide
*
*
* @remarks
*    1) video will show waterprint by default when the mvd device created with a valid waterprint file provide.
*    2) call this mvd_show_stream_waterprint() to show/hide the waterprint
*    3) if no valid waterprint file provided to create the mvd device, the waterprint will not be displayed even if
*       call this function with true flag.
*
*/
-(void) mvdShowStreamWaterprint:(void*)hDevice tid:(uint64_t)tid show:(bool)show;


/**
* record a video stream with a specified duration
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         the video stream id of realtime/playback video stream.
* @param filename      pointer to the name of a file to save the vidoe stream
* @param duration   duration in second to record.
*                   The beginning of the duration is from the function returned in success.
*                   This duration is video time but not the system clock time.
* @param width,height require width and height in pixel for target video picture.
*                     either -1 means to record in the stream original width and height
*
* @return
*    > 0 : started in success
*    = 0 : there is already an on-going recording.
*          in this case, mvd_close_stream_record() can be called to close/reset the recording state.
*    < 0 : failed to start
*
* @remarks
*    1) the id must be a realtime/playback video stream
*    2£©the duration is in video time*
*/
-(int) mvdStartStreamRecord:(void*)hDevice tid:(uint64_t)tid filename:(NSString*)filename duration:(int)duration width:(int)width heigth:(int)height;

/**
* get/query the recorded duration of the stream after mvd_start_stream_record() called in success.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param id         the video stream id of realtime/playback video stream.
*
* @return
*    >= 0 : recorded duration in second
*    < 0 :  failed
*/
-(int) mvdGetStreamRecordedDuration:(void*)hDevice tid:(uint64_t)tid;

/**
* close a video stream recording.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
 * @param tid         the video stream id on which called start_stream_record() successfully
* @param cancel     flag indicate to cancel the on-going recording if the recording is still not completed
*
* return
*    > 0 : the recording is completed in success
*    = 0 : if cancel is true, the recording is cancelled and maybe the length is less than required duratoin;
*          if cancel is false, the recording is not completed and is on-going
*    < 0 : failed to close on error
*/
-(int) mvdCloseStreamRecord:(void*)hDevice tid:(uint64_t)tid cancel:(bool)cancel;


@end
