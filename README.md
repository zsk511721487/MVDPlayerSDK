# MVDPlayerSDK

[![CI Status](https://img.shields.io/travis/511721487@qq.com/MVDPlayerSDK.svg?style=flat)](https://travis-ci.org/511721487@qq.com/MVDPlayerSDK)
[![Version](https://img.shields.io/cocoapods/v/MVDPlayerSDK.svg?style=flat)](https://cocoapods.org/pods/MVDPlayerSDK)
[![License](https://img.shields.io/cocoapods/l/MVDPlayerSDK.svg?style=flat)](https://cocoapods.org/pods/MVDPlayerSDK)
[![Platform](https://img.shields.io/cocoapods/p/MVDPlayerSDK.svg?style=flat)](https://cocoapods.org/pods/MVDPlayerSDK)

MVDPlayerSDK is a comprehensive iOS SDK for medical video device streaming and playback. It provides real-time video streaming, historical playback, PTZ camera control, voice communication, and remote device control capabilities specifically designed for medical applications.

## Features

- **Real-time Video Streaming**: Live video streaming from medical devices with low latency
- **Historical Playback**: Time-based video playback with seek and speed control
- **Multi-channel Support**: Handle multiple devices and channels simultaneously
- **PTZ Camera Control**: Pan-tilt-zoom operations for camera positioning
- **Voice Communication**: Two-way audio communication with devices
- **Remote Control**: Keyboard and mouse control of connected medical devices
- **Video Recording**: Built-in screenshot and video recording capabilities
- **Drawing Overlay**: Annotation and markup tools on video streams
- **Volc Integration**: Online meeting capabilities for remote collaboration
- **Download Support**: Save video segments to local storage

## Requirements

- iOS 13.0+
- Xcode 12.0+
- Swift 5.0+ or Objective-C
- CocoaPods for dependency management

## Installation

MVDPlayerSDK is available through [CocoaPods](https://cocoapods.org). To install it, simply add the following line to your Podfile:

```ruby
pod 'MVDPlayerSDK'
```

For projects using private spec repositories, ensure you have the BrainMedSpec repository configured:

```ruby
source 'https://cdn.cocoapods.org/'
source 'https://github.com/zsk511721487/BrainMedSpec.git'
```

Then run:

```bash
pod install
```

## Quick Start

### Basic Setup

```objective-c
#import <MVDPlayerSDK/MVDPlayerSDK.h>

// Initialize player
MVDPlayer *player = [[MVDPlayer alloc] initWithStream:0];
player.preView = self.videoView;
player.delegate = self;

// Configure RabbitMQ connection
MVDRabbitmqModel *config = [[MVDRabbitmqModel alloc] init];
config.host = @"your-rabbitmq-host";
config.port = 5672;
config.vhost = @"/";
config.user = @"username";
config.password = @"password";

// Connect to device
[player connectWithDeviceId:12345 channel:1 channelType:0 rabbitmq:config];
```

### Real-time Streaming

```objective-c
// Start real-time streaming
[player prepare];

// PTZ control examples
[player controlPTZ:EOCPTZUp reserved:0];     // Move camera up
[player controlPTZ:EOCPTZZoomIn reserved:0]; // Zoom in
[player controlPTZ:EOCPTZStop reserved:0];   // Stop movement
```

### Playback Streaming

```objective-c
// Start playback from specific time
uint32_t startTime = [[NSDate date] timeIntervalSince1970] - 3600; // 1 hour ago
[player connectPlayBackWithDeviceId:12345 channel:1 starttime:startTime channelType:0 rabbitmq:config];

// Control playback speed
[player setPlayBackSpeed:1]; // 2x speed
[player setPlayBackSpeed:0]; // Normal speed
[player setPlayBackSpeed:-1]; // 0.5x speed
```

### Voice Communication

```objective-c
// Open voice communication
[player openTalking];

// Or use Volc integration for online meetings
[player openVolcTalkingWith:@"user-id"];
```

### Recording and Capture

```objective-c
// Take screenshot
[player cuptureImage];

// Start video recording
[player startRecordVideo];

// Stop recording
[player stopRecordVideo];
```

### Drawing and Annotation

```objective-c
// Enable drawing
[player setIsEnableDraw:YES];
[player setPenWidth:3];
[player setPenColor:0xFF0000]; // Red color
[player setDrawCmd:1]; // Line segment

// Drawing operations
[player undoGraffiti]; // Undo last action
[player clearGradditi]; // Clear all drawings
```

## API Reference

### Core Classes

#### MVDPlayer

Main player class for device connection and video streaming.

**Properties:**
- `preView` - UIView for video display
- `delegate` - Delegate for event callbacks

**Key Methods:**
- `connectWithDeviceId:channel:channelType:rabbitmq:` - Connect to device for real-time streaming
- `connectPlayBackWithDeviceId:channel:starttime:channelType:rabbitmq:` - Connect for playback streaming
- `switchStreamType:` - Switch between primary/secondary streams
- `controlPTZ:reserved:` - PTZ camera control
- `openTalking` / `closeTalking` - Voice communication
- `startRecordVideo` / `stopRecordVideo` - Video recording
- `cuptureImage` - Screenshot capture

#### MVDPlayerVideoCanvas

Video rendering canvas for advanced video display and interaction.

#### MVDHDeviceManager

Device management utilities for device discovery and configuration.

### Delegates

Implement `MVDPlayerDelegate` to receive callbacks:

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

### Advanced Features

#### Remote Device Control (E-Touch)

```objective-c
// Start remote control
[player mvdStartEtouchControlWidth:1920 height:1080];

// Send keyboard events
[player mvdSendEtouchKeyboardEvent:0x01 keyvalue:0x20]; // 'A' key press

// Send mouse events
[player mvdSendEtouchMouseEvent:0 dx:10 dy:10]; // Mouse move
[player mvdSendEtouchMouseEvent:2 dx:0 dy:0];   // Left click
```

#### Video Download

```objective-c
// Download video segment
uint64_t downloadId = [player mvdStartDwonloadStream:@"save_path.mp4" 
                                           channel:1 
                                       starttime:startTime 
                                         endtime:endTime 
                                         bitrate:2048 
                                            concat:YES];

// Check progress
int progress = [player mvdGetDownloadStreamProgress:downloadId];
```

#### Playback Groups

```objective-c
// Create playback group for synchronized multi-channel playback
void* groupHandle = [player mvdCreatePlaybackGroup];

// Add streams to group
[player mvdAddPlaybackGroupStream:groupHandle 
                          channel:1 
                            width:&width 
                           height:&height 
                              fps:&fps 
                        starttime:startTime 
                          endtime:endTime];

// Control entire group
[player mvdStartPlaybackGroup:groupHandle];
[player mvdPausePlaybackGroup:groupHandle];
[player mvdSetPlaybackGroupSpeed:groupHandle speedIndex:1]; // 2x speed
```

## Example

To run the example project:

1. Clone the repository
2. Navigate to the Example directory: `cd Example`
3. Install dependencies: `pod install`
4. Open the workspace: `open MVDPlayerSDK.xcworkspace`
5. Build and run the example app

## Development Commands

```bash
# Validate podspec locally
pod lib lint --skip-import-validation --allow-warnings

# Validate podspec remotely
pod spec lint --skip-import-validation --allow-warnings

# Publish to private spec repository
pod repo push BrainMedSpec MVDPlayerSDK.podspec --skip-import-validation --allow-warnings

# Update repository
上传更新仓库
```

## Configuration Examples

### RabbitMQ Configuration

```objective-c
MVDRabbitmqModel *config = [[MVDRabbitmqModel alloc] init];
config.host = @"your-rabbitmq-server.com";
config.port = 5672;
config.vhost = @"your-vhost";
config.user = @"username";
config.password = @"password";
```

### Volc Integration Setup

```objective-c
// Get Volc meeting credentials
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

## Troubleshooting

### Common Issues

1. **Connection Failed**: Check RabbitMQ configuration and network connectivity
2. **No Video Display**: Verify device ID, channel number, and permissions
3. **Audio Issues**: Ensure microphone permissions are granted
4. **Recording Failed**: Check storage permissions and available space

### Debug Logging

```objective-c
// Enable debug logging
[player mvdOpenLog:@"debug.log"];

// Disable logging
[player mvdCloseLog];
```

## Requirements

- iOS 13.0 or later
- Xcode 12.0 or later
- Physical device recommended for testing (simulator has limitations)
- Network connectivity for device communication

## License

MVDPlayerSDK is available under the MIT license. See the LICENSE file for more info.

## Author

511721487@qq.com, 511721487@qq.com

## Support

For technical support and questions, please contact the development team or refer to the example project implementation.
