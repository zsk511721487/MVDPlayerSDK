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
 @brief 开启对讲功能
 
 成功或失败会收到 MVDPlayerDelegate 的回调
 */
- (void)openTalking;

/**
 @brief 关闭对讲功能
 
 成功或失败会收到 相关回调
 */
- (void)closeTalking;

/**
 @brief 开始接收音频数据
 
 成功或失败会收到 相关回调
 */
- (void)startTalking;

/**
 @brief 暂停接收音频数据
 
 成功或失败会收到 相关回调
 */
- (void)pauseTalking;

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
- (CGSize)getVideoSize;

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
//                       API for device management                          //
//////////////////////////////////////////////////////////////////////////////

/**
* Create a MVD device and build the connection with it.
* A handle to a MVD device is the basis of all other API
* to pull different streams.
*
* @param deviceid   id of the MVD device to connect.
* @param clientid   id of the user(client)
* @param mqhost     RabbitMQ server IP address or name
* @param mqport     RabbitMQ server TCP port
* @param mqvhost    RabbitMQ server virtual host name
* @param mquser     RabbitMQ server user name to login
* @param mqpassword RabbitMQ server password to login
*
* @return
*    NULL :    failed to connect with device
*    Non-NULL: The hanndle to the device
*
*/
- (void*)mvdCreateDevice: (uint32_t)clientid deviceid:(uint32_t)deviceid mqhost:(NSString *)mqhost mqport:(int)mqport mqvhost:(NSString *)mqvhost mquser:(NSString *)mquser mqpassword:(NSString *)mqpassword;
/**
* Destroy a MVD device if no longer need to use it.
* Please don't use the handle after it destroyed!
*
* @param hDevice   handle to the MVD device to destroy.
*                 this handle is returned by mvd_create_device().
*/
- (void)mvdDestroyDevice: (void*)hDevice;

//////////////////////////////////////////////////////////////////////////////
//                       API for realtime video stream                      //
//////////////////////////////////////////////////////////////////////////////

/**
* open a stream to pull the realtime video frames from a channel of the MVD device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param width      buffer to retrieve the width in pixel of the video stream if
*                   the function create the stream in success.
* @param height     buffer to retrieve the height in pixel of the video stream if
*                   the function create the stream in success.
* @param fps        buffer to retrieve the framerate of the video stream if
*                   the function create the stream in success.
* @param channel    the number of the channel from which to pull video stream
* @param streamtype stream type, must be 0 in this version.
*
* @return
*    The id of the stream if opened in success, otherwise return INVALID_STREAMID on error.
*
*/
- (uint64_t)mvdOpenRealPlayStream:(void*)hDevice width:(int*)width height:(int*)height fps:(float*)fps channel:(int)channel streamtype:(int)streamtype;

/**
* stop/close a realtime video stream of a device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id the a realtime video stream return by mvd_open_realplay_stream().

*
* @remarks
*    1) Don't use this id after it closed.
*    2) Be sure the stream belongs to this device, don't close a stream against
*       the handle to another device.
*    3) the id MUST BE returned by mvd_open_realplay_stream()! Please
*      don't call this API to close a stream with the id returned by other functions!
*
*/
- (void)mvdCloseRealPlayStream: (void*)hDevice tid:(uint64_t)tid;

/**
* stop/close all realtime video stream(s) of the specified device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
*
* @remarks
*    after called mvd_close_all_realplay_stream() to close all the realtime video stream,
*    mvd_open_realplay_stream() can be called again to open new stream(s) to play.
*
*/
- (void)mvdCloseAllRealPlayStream: (void*)hDevice;

/**
* Control the PTZ of the camera(channel) to move as required movement
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         the realtime video stream id returned by mvd_open_realplay_stream()
*                   of the specified MVD device.
* @param cmd        the required movement to control the PTZ.
*                   EPTZStop and EPTZReset are the two special command to stop/reset
*                   current moving
* @param reserved   must be 0 in this version
*
* @return
*    > 0 : control the PTZ to move in success
*    = 0 : the specified channel does't support PTZ
*    < 0 : Failed to control on some error
*
* @remarks
*    1) the id must be a realtime video stream returned by mvd_open_realplay_stream()!
*    2) the id must macthes its device
*    3) Except EPTZStop & EPTZReset, the PTZ will move continously after controlled in success.
*
*/
- (int)mvdControlPTZ: (void*)hDevice tid:(uint64_t)tid cmd:(EPTZControlType)cmd reserved:(int)reserved;

/**
* ask for a new frame of a realtime video stream or playback video stream to display.
* NULL frame will be returned if so far no frame recieved from the stream.
*
* The function will alway returned the last frame If the stream finished or stopped/paused
* to push video after a while and at least one frame received
*
* After got a frame by calling this function, must display this frame immediately.
* The returned value is the duration in second to keep the gotten frame displayed and then
* to call this function again to get new frame to refresh display.
*
* This function must be called repeatedly in a separate thread for each stream channel or
* at least in a thread to call this function for each stream channel
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         the realtime video stream id of realtime video stream/playback video stream.
* @param frame buffer to retrieve the pointer to the frame data in required format or NULL
*                   if no frame yet.
* @param lineSize  buffer to retrieve a positive or negative value, which is typically indicating
*                   the size in bytes of each picture line, but it can also be the negative byte size of
*                   lines for vertical flipping
* @param width      required width in pixel of the returned frame
* @param height     required height in pixel of the returned frame
* @param fmt        required pixel format of the returned frame
* @param align      required line align of the returned frame data, for example, if required RGB/RGBA for BMP
*                   pixel format, align must be 4 in windows platform to display
*
* @return
*    The duration in second for this frame to keep displayed
*
* @remarks
*    1) the id must be a realtime or playback video stream

*
*/
- (double)mvdGetFrameDisplay:(void*)hDevice tid:(uint64_t)tid frame:(const void**)frame  lineSize:(int *)lineSize width:(int)width height:(int)height fmt:(EPixelType)fmt align:(int)align;

//////////////////////////////////////////////////////////////////////////////
//                       API for talking                                    //
//////////////////////////////////////////////////////////////////////////////

/**
* Open the voice tunnel with the device to exchange PCM audio frames/data.
*
*
* @param hDevice           Handle to a connected MVD device which was returned by
*                          mvd_create_device().
* @param audioChannels    buffer to retrieve the PCM audio channels supported by the device
* @param audioSamplerate  buffer to retrieve the PCM audio sample rate, namely samples per second
* @param audioSamplebits  buffer to retrieve then PCM audio sampe bits, namely bits per sample.
* @param localInputDeviceName  The name of local microphone to capture audio data to send to the MVD device.
*                                 This name can be:
*                                    - "dshow" on windows platform;
*                                    - "fbdev" or "v4l2" on linux, and
*                                    - "avfoundation" on MAC.
*                                 It can be NULL or "" not to open the local microphone to capture audio,
*                                 in this case the application can call mvd_send_audio_frame() API to send
*                                 PCM audio data to the device on demand.
*
*
* @return
*    > 0 : opened in success.
*    = 0:  the device is alread in talking with other client or yourself
*    < 0:  Failed to open on system error
*
* @remarks:
*   1) If started successfully, call begin_talking()/pause_talking() to control
*      start(resume) and puase the talking
*   2) If started successfully, repeatedly call mvd_get_talking_data_play() to get
*      audio data from device to play
*/
- (int)mvdOpenTalking:(void*)hDevice audioChannels:(int*)audioChannels audioSamplerate:(int*)audioSamplerate audioSamplebits:(int*)audioSamplebits inputAudioFormatName:(NSString *)inputAudioFormatName inputAudioDeviceName:(NSString *)inputAudioDeviceName;

/**
* send PCM audio frames to the MVD device.
*
* @param hDevice   Handle to a connected MVD device which was returned by
*                  mvd_create_device().
* @param frame     PCM audio data. The format of the audio data must be consist with the
*                  channels, smaple rate and sample bits returned by mvd_open_talking(), otherwise
*                  the device can play the audio data properly.
* @param len       The length of the frame data in byte
*
* @return
*    true : send in success
*    false : failed to send
*
* @remarks:
*    This API is provided as an alternative when local audio capture device is not opened for some reason.
*
*/
- (bool)mvdSendAudioFrame:(void*)hDevice tid:(uint64_t)tid frame:(const void**)frame len:(int)len;

/**
* Get the state to indicate whether the voice tunnel is already opened with the device.
*
* @param hDevice   Handle to a connected MVD device which was returned by
*                  mvd_create_device().
*
* @return:
*    true : already opened
*    false : not open
*/
- (bool)mvdTalkingOpened:(void*)hDevice;

/**
* close the voice tunnel to stop talking with the MVD device.
*
* @param hDevice   Handle to a connected MVD device which was returned by
*                  mvd_create_device().
*/
- (void)mvdCloseTalking:(void*)hDevice;

/**
* Control to start/resume or pause sending audio data to device.
*/
- (void)mvdStartTalking:(void*)hDevice;
- (void)mvdPauseTalking:(void*)hDevice;

/**
* ask for talking audio data from device to play.
* return the length of data copied to the provided buf.
* The returned audio data is in the format returned by mvd_open_talking().
*
* @param hDevice   Handle to a connected MVD device which was returned by
*                  mvd_create_device().
* @param buf       buffer to retrieve PCM audio data
* @param len       the provided buffer size in byte
*
* @return:
*    The length of the audio data copied into the provided buffer.
*
* @remarks
*    This function need to be called immediately when previous audio
* data gotten by this API was completed playing.
*
*/
- (int)mvdGetTalkingDataPlay:(void*)hDevice buf:(void*)buf len:(int)len;

//////////////////////////////////////////////////////////////////////////////
//              API for individual playback video stream                    //
//////////////////////////////////////////////////////////////////////////////


/**
* open a stream to pull the playback video frames from a channel of the MVD device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param channel   the number of the channel from which to pull video stream
* @param width      buffer to retrieve the width in pixel of the video stream if
*                   the function create the stream in success.
* @param height     buffer to retrieve the height in pixel of the video stream if
*                   the function create the stream in success.
* @param fps        buffer to retrieve the framerate of the video stream if
*                   the function create the stream in success.
* @param starttime  the starttime from which to pull the playback video stream.
*                   It is the unix timestamp in second.
*                   It can be -1 to use the default start time, which is 1 hour back away from now.
* @param endtime    the endtime to which to stop pulling the playback video stream.
*                   It is the unix timestamp in second.
*                   It can be -1 to use the default end time, which is now.
*
* @return
*    The id of the stream if opened in success, otherwise return INVALID_STREAMID on error.
*
* @remarks
*    1) If open in success, can call mvd_get_frame_display() function to get video frame to display.
*       please refer to mvd_get_frame_display() for details.
*    2) after opend a playback stream, need to call  mvd_start_playback_stream() to begin to pull video stream.
*
*/
- (uint64_t)mvdOpenPlaybackStream:(void*)hDevice channel:(int)channel width:(int*)width height:(int*)height fps:(float*)fps starttime:(uint32_t)starttime endtime:(uint32_t)endtime;

/**
* stop/close a playback video stream of a device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
*
*
* @remarks
*    1) Don't use this id after it closed.
*    2) Be sure the stream belongs to this device, don't close a stream against
*       the handle to another device.
*    3) The stream id MUST BE returned by mvd_open_playback_stream()! Please
*       don't call this API to close a stream with the id returned by other functions!
*
*/
- (void)mvdClosePlaybackStream:(void*)hDevice tid:(uint64_t)tid;

/**
* stop/close all playback video stream(s) opened by mvd_open_playback_stream()
* with the specified device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
*
* @remarks
*    1) This API only close all the playback video streams opned by mvd_open_playback_stream()
*       for the specified device.
*    2) after called mvd_clase_all_playback_stream() to close all the video stream,
*        mvd_open_playback_stream() can be called again to open new stream(s) to play.
*
*/
- (void)mvdCloseAllPlaybackStream:(void*)hDevice;

/**
* set new starttime and endtime for a plackback stream.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
* @param starttime  the new start time from which to pull the playback video stream.
*                   It is the unix timestamp in second.
* @param endtime    the new end time to which to stop pulling the playback video stream.
*                   It is the unix timestamp in second.
*                   It can be -1 to use the default end time, which is now.
*
* @return
*    true for set in sucess, false on error
*
* @remarks
*    the id MUST BE returned by mvd_open_playback_stream() for this specified device
*
*/
- (bool)mvdSetPlaybackStreamNewtime:(void*)hDevice tid:(uint64_t)tid starttime:(uint32_t)starttime endtime:(uint32_t)endtime;

/**
* set playing speed to play the plackback video stream
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
* @param speedIndex  The index of the speed to playing. This speed index can be from -3 to 3 to
*                     set the playing speed as (2<<speed_index) times of normal playing speed.
*                     That is to say£∫
*                     -speed_index is -3, the speed of playing will be 1/8 of the normal playing speed.
*                     -speed_index is -2, the speed of playing will be 1/4 of the normal playing speed.
*                     -speed_index is -1, the speed of playing will be 1/2 of the normal playing speed.
*                     -speed_index is 0, the speed of playing will be the normal playing speed, namely one time speed.
*                     -speed_index is 1, the speed of playing will be 2 of the normal playing speed.
*                     -speed_index is 2, the speed of playing will be 4 of the normal playing speed.
*                     -speed_index is 3, the speed of playing will be 8 of the normal playing speed.
*
* @return
*    true for set in sucess, false on error
*
* @remarks
*    the id MUST BE returned by mvd_open_playback_stream() for this specified device
*
*/
- (bool)mvdSetPlaybackStreamSpeed:(void*)hDevice tid:(uint64_t)tid sppedIndex:(int)speedIndex;

/**
* start to pull video data from a playback video stream to play
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
*
* @return
*    true for sucess, false on error
*
* @remarks
*    the id MUST BE returned by mvd_open_playback_stream() for this specified device
*
*/
- (bool)mvdStartPlaybackStream:(void*)hDevice tid:(uint64_t)tid;

/**
* pause to pull video data from a playback video stream to play
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
*
* @return
*    true for sucess, false on error
*
* @remarks
*    the id MUST BE returned by mvd_open_playback_stream() for this specified device
*
*/
- (bool)mvdPausePlaybackStream:(void*)hDevice tid:(uint64_t)tid;

/**
* resume to pull video data from a playback video stream to play
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
*
* @return
*    true for sucess, false on error
*
* @remarks
*    the id MUST BE returned by mvd_open_playback_stream() for this specified device
*
*/
- (bool)mvdResumePlaybackStream:(void*)hDevice tid:(uint64_t)tid;

/**
* get the OSD(on-screen-displayed) time of the playback stream.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
* @param osdtime    buffer to retrieve the OSD time in unix timestamp in second.
*
* @return
*    true for sucess, false on error
*
* @remarks
*    1) the id MUST BE returned by mvd_open_playback_stream() for this specified device
*    2) Because this OSD time must be gotten from the real device by communication, please
*       don't call this function at high frequence. As an alternative, please call mvd_get_playback_stream_playingtime()
*       to calculate the OSD time for this stream
*
*/
- (bool)mvdGetPlaybackStreamOsdtime:(void*)hDevice tid:(uint64_t)tid osdtime:(uint32_t*)osdtime;

/**
* get the continous playing time in second after last new starttime set
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         id of a playback video stream return by mvd_open_playback_stream().
*
* @return
*    playtime in second or 0.0 if failed to get
*
* @remarks
*    1) the id MUST BE returned by mvd_open_playback_stream() for this specified device
*    2) call this function to help to calculate the OSD time with the most starttime
*       recently set to this stream.
*
*/
- (bool)mvdGetPlaybackStreamPlayingtime:(void*)hDevice tid:(uint64_t)tid;

//////////////////////////////////////////////////////////////////////////////
//                       API for downloading video data                     //
//////////////////////////////////////////////////////////////////////////////

/**
* start a video stream to download from a MVD device with the specified channel
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param filename   pointer to the name of the file to save the downloaded video in mp4 format.
* @param channel    the channel of the video to download
* @param starttime  the starttime from which to download.
*                   It is the unix timestamp in second.
* @param endtime    the endtime to which to stop  downloading.
*                   It is the unix timestamp in second.
* @param bitrate    expected downloading speed in kbps. It can be 0 to let download
*                   at max speed.  Please provide a suitable speed in the real situation.
* @param concat     flag indicate to support concatenate the subsequent downloading or not.
*
* @return
*    The id of the stream if started in success, otherwise return INVALID_STREAMID on error.
*
* @remarks
*    1) don't use the returned stream id to call mvd_get_frame_display()!
*       The returned stream is only for downloading
*    2) strongly recomment call this function with bitrate > 0 and bitrate <= 16384
*
*/
- (uint64_t)mvdStartDwonloadStream:(void*)hDevice filename:(NSString *)filename channel:(int)channel starttime:(uint32_t)starttime endtime:(uint32_t)endtime bitrate:(int)bitrate concat:(bool)concat;

/**
* Get the progress of the downloading stream
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         downloading stream id returned by mvd_start_download_stream()
*
* @return
*    [0, 100] : the progress the downloading
*        <  0 : downloading was broken on error
*
* @remarks
*    1) the stream id must be returned by mvd_start_download_stream()
*    2) If return 100, means complete the downloading sucessfully and need to call
*       the mvd_close_download_stream() immediately to close the stream.
*    3) If return < 0, means an error occurred for the real device and please call
*       the mvd_close_download_stream() immediately to close the stream.
*    4) Because this API will ask for real device to get the progress by comminication,
*       please don't call this API at high freqence, it is recommended for each 3~5 or more seconds to call
*       this API to get the progress
*/
- (int)mvdGetDownloadStreamProgress:(void*)hDevice tid:(uint64_t)tid;

/**
* close the download stream
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         downloading stream id returned by mvd_start_download_stream()
*
*
*/
- (void)mvdCloseDownloadStream:(void*)hDevice tid:(uint64_t)tid cancel:(bool)cancel;

/**
* close all the download stream of the device
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
*
*/
- (void)mvdCloseAllDownloadStream:(void*)hDevice;

//////////////////////////////////////////////////////////////////////////////
//                       Helper API for convenience                         //
//////////////////////////////////////////////////////////////////////////////

/**
* refresh the underlying playback group for individual playback stream.
*
* When the real MVD device re-started or the allpication lost network connection for a long time,
* please close all the playback stream returned by mvd_open_playback_stream() and then call
* this function to reuse mvd_open_playback_stream() to open individual playback stream, or
* call this function and the call mvd_refresh_display_stream() on all individual playback stream.
*/
- (bool)mvdRefreshPlayback:(void*)hDevice;

/**
* refresh a realtime or playback video stream to display.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param tid         stream id returned by mvd_open_realplay_stream(), mvd_open_playback_stream()
*                   or mvd_add_playback_group_stream().
*/
- (bool)mvdRefreshDisplayStream:(void*)hDevice tid:(uint64_t)tid;

/**
* close any type stream opened by mvd_open_realplay_stream(), mvd_open_playback_stream()
* mvd_add_playback_group_stream(), or mvd_start_download_stream()
*/
- (void)mvdCloseStream:(void*)hDevice tid:(uint64_t)tid;

/**
* Query about the recorded video time segment of the channel of a device
* between the specified time range.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param channel    channel to query about.
* @param fromtime   time range from which to query.  in unix second timestamp
* @param totime     time range to which to stop query.  in unix second timestamp
* @param starttime  buffer of an array to retrieve the start time of each segment.  in unix second timestamp
* @param endtime    buffer of an array to retrieve the end time of each segment.  in unix second timestamp
* @param hasMore   buffer to retrieve the flag to indicate has more time segment to retrieve for the specified range.
*
* @return
*    >= 0 :  number of retrieved time segment
*    <  0 :  failed on error
*/
- (int)mvdQueryRecordStreamTimeseg:(void*)hDevice channel:(int)channel fromtime:(uint32_t)fromtime totime:(uint32_t)totime starttime:(uint32_t[10])starttime endtime:(uint32_t[10])endtime hasMore:(bool*)hasMore;


//////////////////////////////////////////////////////////////////////////////
//                       API for playback group                             //
// Playback group is the group of playback video stream(s) of the same      //
// device to be controlled together convenniently                           //
//////////////////////////////////////////////////////////////////////////////


/**
* create a playback group for a MVD device.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
*
* @return
*    The handle to the new playbackgroup or NULL if failed to create.
*
*
*/

- (void*) mvdCreatePlaybackGroup:(void*)hDevice;

/**
* delete a playback group for a MVD device.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
*
* @remarks
*    1) The group must belongs to this device!
*    2) The group cannot be used after it was deleted
*
*
*/
- (void) mvdDeletePlaybackGroup:(void*)hDevice hGroup:(void*)hGroup;


/**
* open a stream and add to the specified group.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
* @param channel   the number of the channel from which to pull video stream
* @param width      buffer to retrieve the width in pixel of the video stream if
*                   the function create the stream in success.
* @param height     buffer to retrieve the height in pixel of the video stream if
*                   the function create the stream in success.
* @param fps        buffer to retrieve the framerate of the video stream if
*                   the function create the stream in success.
* @param starttime  the starttime from which to pull the playback video stream.
*                   It is the unix timestamp in second.
*                   It can be -1 to use the default start time, which is 1 hour back away from now.
* @param endtime    the endtime to which to stop pulling the playback video stream.
*                   It is the unix timestamp in second.
*                   It can be -1 to use the default end time, which is now.
*
* @return
*    The id of the stream if opened in success, otherwise return INVALID_STREAMID on error.
*
* @remarks
*    1) If open in success, can call mvd_get_frame_display() function to get video frame to display.
*       please refer to mvd_get_frame_display() for details.
*    2) after opend a playback stream, need to call  mvd_start_playback_group() to begin to pull video stream.
*
*/
- (uint64_t)mvdAddPlaybackGroupStream:(void*)hDevice hGroup:(void*)hGroup channel:(int)channel width:(int*)width height:(int*)height fps:(float*)fps starttime:(uint32_t)starttime endtime:(uint32_t)endtime;
/**
* close a playback video stream and remove it from the group.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
* @param id         id of a playback video stream return by mvd_add_playback_group_stream().
*
*
* @remarks
*    1) Don't use this id after it closed.
*    2) Be sure the stream belongs to this group, don't close a stream against
*       the handle to another group.
*    3) The stream id MUST BE returned by mvd_add_playback_group_stream()! Please
*       don't call this API to close a stream with the id returned by other functions!
*
*/
- (void) mvdRemovePlaybackGroupStream:(void*)hDevice hGroup:(void*)hGroup tid:(uint64_t)tid;

/**
* close all playback video streams and remove them from the group.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
*
*
* @remarks
*    1) This API only close all the playback video streams opened by mvd_add_playback_group_stream()
*       for the specified group.
*    2) after called mvd_remove_all_playback_group_stream() to close all the video stream,
*        mvd_add_playback_group_stream() can be called again to open new stream(s) to play.
*
*/
- (void) mvdRemoveAllPlaybackGroupStream:(void*)hDevice hGroup:(void*)hGroup;

/**
* set new starttime and endtime for all the playback streams of the plackback group.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
* @param starttime  the new start time from which to pull the playback video streams of this group.
*                   It is the unix timestamp in second.
* @param endtime    the new end time to which to stop pulling the playback video streams of this group.
*                   It is the unix timestamp in second.
*                   It can be -1 to use the default end time, which is now.
*
* @return
*    true for set in sucess, false on error
*
*
*/
- (bool) mvdSetPlaybackGroupNewtime:(void*)hDevice hGroup:(void*)hGroup starttime:(uint32_t)starttime endtime:(uint32_t)endtime;


/**
* set playing speed to play the all plackback video stream of the group
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
* @param speedIndex  The index of the speed to playing. This speed index can be from -3 to 3 to
*                     set the playing speed as (2<<speed_index) times of normal playing speed.
*                     That is to say£∫
*                     -speedIndex is -3, the speed of playing will be 1/8 of the normal playing speed.
*                     -speedIndex is -2, the speed of playing will be 1/4 of the normal playing speed.
*                     -speedIndex is -1, the speed of playing will be 1/2 of the normal playing speed.
*                     -speedIndex is 0, the speed of playing will be the normal playing speed, namely one time speed.
*                     -speedIndex is 1, the speed of playing will be 2 of the normal playing speed.
*                     -speedIndex is 2, the speed of playing will be 4 of the normal playing speed.
*                     -speedIndex is 3, the speed of playing will be 8 of the normal playing speed.
*
* @return
*    true for set in sucess, false on error
*/
- (bool) mvdSetPlaybackGroupSpeed:(void*)hDevice hGroup:(void*)hGroup speedIndex:(int)speedIndex;


/**
* start to pull video data from all playback video streams of the group
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
*
* @return
*    true for sucess, false on error
*
*
*/
-(bool) mvdStartPlaybackGroup:(void*)hDevice hGroup:(void*)hGroup;

/**
* pause to pull video data from all playback video streams of the group
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
*
* @return
*    true for sucess, false on error
*
*
*/
-(bool) mvdPausePlaybackGroup:(void*)hDevice hGroup:(void*)hGroup;

/**
* resume to pull video data from all playback video streams of the group
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
*
* @return
*    true for sucess, false on error
*
*
*/
-(bool) mvdResumePlaybackGroup:(void*)hDevice hGroup:(void*)hGroup;

/**
* get the OSD(on-screen-displayed) time of the playback group.
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
* @param osdtime    buffer to retrieve the OSD time in unix timestamp in second.
*
* @return
*    true for sucess, false on error
*
* @remarks
*    1) Because this OSD time must be gotten from the real device by communication, please
*       don't call this function at high frequence. As an alternative, please call mvd_get_playback_group_playingtime()
*       to calculate the OSD time for this group
*    2) If there are more than one playback stream in this group, the API only get the OSD time from any one stream.
*
*/
-(bool) mvdGetOsdtimePlaybackGroup:(void*)hDevice hGroup:(void*)hGroup osdtime:(uint32_t*)osdtime;

/**
* get the continous playing time in second after last new starttime set
*
* @param hDevice    Handle to a connected MVD device which was returned by
*                   mvd_create_device().
* @param hGroup     Handle to a playback group which was created by
*                   mvd_create_playback_group().
*
* @return
*    playtime in second or 0.0 if failed to get
*
* @remarks
*    1) call this function to help to calculate the OSD time with the starttime
*       most recently set to this stream.
*    3) If there are more than one playback stream in this group, the API only
*       get the playing time from any one stream.
*
*/
-(double) mvdGetPlaybackGroupPlayingtime:(void*)hDevice hGroup:(void*)hGroup;

/**
* refresh a playback group for group playback stream.
*
* When the real MVD device re-started or the allpication lost network connection for a long time,
* please close all the playback group stream returned by mvd_add_playback_group_stream() and then call
* this function to reuse mvd_add_playback_group_stream() to open group playback stream, or
* call this function and the call mvd_refresh_display_stream() on all group playback stream.
*/
-(bool) mvdRefreshPlaybackGroup:(void*)hDevice hGroup:(void*)hGroup;

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
