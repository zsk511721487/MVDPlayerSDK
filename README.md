# MVDPlayerSDK

[![CI Status](https://img.shields.io/travis/511721487@qq.com/MVDPlayerSDK.svg?style=flat)](https://travis-ci.org/511721487@qq.com/MVDPlayerSDK)
[![Version](https://img.shields.io/cocoapods/v/MVDPlayerSDK.svg?style=flat)](https://cocoapods.org/pods/MVDPlayerSDK)
[![License](https://img.shields.io/cocoapods/l/MVDPlayerSDK.svg?style=flat)](https://cocoapods.org/pods/MVDPlayerSDK)
[![Platform](https://img.shields.io/cocoapods/p/MVDPlayerSDK.svg?style=flat)](https://cocoapods.org/pods/MVDPlayerSDK)

## 开发命令

```bash
# 本地验证podspec
pod lib lint --skip-import-validation --allow-warnings

# 远程验证podspec
pod spec lint --skip-import-validation --allow-warnings

# 发布到私有spec仓库
pod repo push BrainMedSpec MVDPlayerSDK.podspec --skip-import-validation --allow-warnings

# 更新仓库
上传更新仓库
```

MVDPlayerSDK 是一个专业的iOS医疗视频设备流媒体SDK。提供实时视频流、历史回放、PTZ摄像机控制、语音通信和远程设备控制功能，专为医疗应用设计。

## 功能特性

- **实时视频流**: 从医疗设备进行低延迟实时视频流传输
- **历史回放**: 基于时间的视频回放，支持拖拽和速度控制
- **多通道支持**: 同时处理多个设备和通道
- **PTZ摄像机控制**: 摄像机云台全方位控制（上下左右、变焦）
- **语音通信**: 与设备的双向音频通信
- **远程控制**: 通过键盘鼠标远程控制连接的医疗设备
- **视频录制**: 内置截图和视频录制功能
- **绘图标注**: 在视频流上添加注释和标记工具
- **Volc集成**: 在线会议功能，支持远程协作
- **下载支持**: 将视频片段保存到本地存储

## 环境要求

- iOS 13.0+
- Xcode 12.0+
- Swift 5.0+ 或 Objective-C
- CocoaPods 依赖管理

## 安装

MVDPlayerSDK 通过 [CocoaPods](https://cocoapods.org) 提供安装。在你的 Podfile 中添加以下行：

```ruby
pod 'MVDPlayerSDK'
```

对于使用私有spec仓库的项目，确保已配置 BrainMedSpec 仓库：

```ruby
source 'https://cdn.cocoapods.org/'
source 'https://github.com/zsk511721487/BrainMedSpec.git'
```

然后运行：

```bash
pod install
```

## 快速开始

### 基础设置

```objective-c
#import <MVDPlayerSDK/MVDPlayerSDK.h>

// 初始化播放器
MVDPlayer *player = [[MVDPlayer alloc] initWithStream:0];
player.preView = self.videoView;
player.delegate = self;

// 配置RabbitMQ连接
MVDRabbitmqModel *config = [[MVDRabbitmqModel alloc] init];
config.host = @"your-rabbitmq-host";
config.port = 5672;
config.vhost = @"/";
config.user = @"username";
config.password = @"password";

// 连接设备
[player connectWithDeviceId:12345 channel:1 channelType:0 rabbitmq:config];
```

### 实时流媒体

```objective-c
// 开始实时流媒体
[player prepare];

// PTZ控制示例
[player controlPTZ:EOCPTZUp reserved:0];     // 摄像机向上移动
[player controlPTZ:EOCPTZZoomIn reserved:0]; // 变焦放大
[player controlPTZ:EOCPTZStop reserved:0];   // 停止移动
```

### 回放流媒体

```objective-c
// 从指定时间开始回放
uint32_t startTime = [[NSDate date] timeIntervalSince1970] - 3600; // 1小时前
[player connectPlayBackWithDeviceId:12345 channel:1 starttime:startTime channelType:0 rabbitmq:config];

// 控制播放速度
[player setPlayBackSpeed:1];  // 2倍速
[player setPlayBackSpeed:0];  // 正常速度
[player setPlayBackSpeed:-1]; // 0.5倍速
```

### 语音通信

```objective-c
// 开启语音通信
[player openTalking];

// 或使用Volc集成进行在线会议
[player openVolcTalkingWith:@"user-id"];
```

### 录制和截图

```objective-c
// 截图
[player cuptureImage];

// 开始录制视频
[player startRecordVideo];

// 停止录制
[player stopRecordVideo];
```

### 绘图标注

```objective-c
// 启用绘图
[player setIsEnableDraw:YES];
[player setPenWidth:3];
[player setPenColor:0xFF0000]; // 红色
[player setDrawCmd:1]; // 线段

// 绘图操作
[player undoGraffiti];  // 撤销上一步
[player clearGradditi]; // 清除所有绘图

## API参考

### 核心类

#### MVDPlayer

主播放器类，用于设备连接和视频流媒体。

**属性:**
- `preView` - 用于视频显示的UIView
- `delegate` - 事件回调代理

**关键方法:**
- `connectWithDeviceId:channel:channelType:rabbitmq:` - 连接设备进行实时流媒体
- `connectPlayBackWithDeviceId:channel:starttime:channelType:rabbitmq:` - 连接设备进行回放流媒体
- `switchStreamType:` - 切换主码流/副码流
- `controlPTZ:reserved:` - PTZ摄像机控制
- `openTalking` / `closeTalking` - 语音通信控制
- `startRecordVideo` / `stopRecordVideo` - 视频录制
- `cuptureImage` - 截图功能

#### MVDPlayerVideoCanvas

高级视频渲染画布，用于视频显示和交互。

#### MVDHDeviceManager

设备管理工具，用于设备发现和配置。

### 代理协议

实现 `MVDPlayerDelegate` 接收回调：

```objective-c
@protocol MVDPlayerDelegate <NSObject>
@optional
- (void)onPlayerEvent:(MVDPlayer*)player eventType:(MVDEventType)eventType;
- (void)onPlayerConnectFailed:(MVDPlayer*)player;
- (void)onVideoSizeChanged:(MVDPlayer*)player width:(int)width height:(int)height;
- (void)onPlayerRecordVideo:(MVDPlayer*)player videoPath:(NSString*)videoPath;
- (void)onPlayerSnpshotCurrentFrame:(MVDPlayer*)player imagePath:(NSString*)imagePath;
@end
```

### 高级功能

#### 远程设备控制 (E-Touch)

```objective-c
// 启动远程控制
[player mvdStartEtouchControlWidth:1920 height:1080];

// 发送键盘事件
[player mvdSendEtouchKeyboardEvent:0x01 keyvalue:0x20]; // 按下'A'键

// 发送鼠标事件
[player mvdSendEtouchMouseEvent:0 dx:10 dy:10]; // 鼠标移动
[player mvdSendEtouchMouseEvent:2 dx:0 dy:0];   // 左键点击
```

#### 视频下载

```objective-c
// 下载视频片段
uint64_t downloadId = [player mvdStartDwonloadStream:@"save_path.mp4" 
                                           channel:1 
                                       starttime:startTime 
                                         endtime:endTime 
                                         bitrate:2048 
                                            concat:YES];

// 检查进度
int progress = [player mvdGetDownloadStreamProgress:downloadId];
```

#### 回放组管理

```objective-c
// 创建回放组用于同步多通道回放
void* groupHandle = [player mvdCreatePlaybackGroup];

// 添加流到组
[player mvdAddPlaybackGroupStream:groupHandle 
                          channel:1 
                            width:&width 
                           height:&height 
                              fps:&fps 
                        starttime:startTime 
                          endtime:endTime];

// 控制整个组
[player mvdStartPlaybackGroup:groupHandle];
[player mvdPausePlaybackGroup:groupHandle];
[player mvdSetPlaybackGroupSpeed:groupHandle speedIndex:1]; // 2倍速
```

## 示例项目

运行示例项目：

1. 克隆仓库
2. 进入Example目录: `cd Example`
3. 安装依赖: `pod install`
4. 打开工作空间: `open MVDPlayerSDK.xcworkspace`
5. 构建并运行示例应用

## 配置示例

### RabbitMQ配置

```objective-c
MVDRabbitmqModel *config = [[MVDRabbitmqModel alloc] init];
config.host = @"your-rabbitmq-server.com";
config.port = 5672;
config.vhost = @"your-vhost";
config.user = @"username";
config.password = @"password";
```

### Volc集成设置

```objective-c
// 获取Volc会议凭证
char appId[64], roomId[64], token[256];
int audioChannels, audioSamplerate, audioSamplebits;

int result = [player mvdOpenVolcTalking:userId 
                        audioChannels:&audioChannels 
                       audioSamplerate:&audioSamplerate 
                       audioSamplebits:&audioSamplebits 
                             volcAppid:appId 
                            volcRoomid:roomId 
                             volcToken:token];
```

## 故障排除

### 常见问题

1. **连接失败**: 检查RabbitMQ配置和网络连接
2. **无视频显示**: 验证设备ID、通道号和权限
3. **音频问题**: 确保麦克风权限已授予
4. **录制失败**: 检查存储权限和可用空间

### 调试日志

```objective-c
// 启用调试日志
[player mvdOpenLog:@"debug.log"];

// 禁用日志
[player mvdCloseLog];
```

## 环境要求

- iOS 13.0 或更高版本
- Xcode 12.0 或更高版本
- 建议使用真机测试（模拟器有限制）
- 网络连接用于设备通信

## 许可证

MVDPlayerSDK 基于MIT许可证提供。详情请参见LICENSE文件。

## 作者

511721487@qq.com, 511721487@qq.com

## 技术支持

如需技术支持和问题咨询，请联系开发团队或参考示例项目实现。
