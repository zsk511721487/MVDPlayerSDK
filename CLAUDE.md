# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

MVDPlayerSDK is an iOS CocoaPod SDK for medical video device streaming and playback. It provides real-time video streaming, playback, PTZ control, voice communication, and remote device control capabilities for medical applications.

## Architecture

- **Framework Structure**: The SDK is distributed as a pre-compiled framework (`MVDPlayer.framework`) in the `MVDPlayerSDK/frameworks/` directory
- **iOS Platform**: Minimum deployment target iOS 13.0
- **Installation**: Distributed via CocoaPods from both CocoaPods trunk and a private spec repository
- **Example Project**: Located in `Example/` directory with CocoaPods integration

## Key Components

### Core Classes
- **MVDPlayer**: Main player class for device connection and video streaming
- **MVDPlayerVideoCanvas**: Video rendering canvas for displaying video streams
- **MVDHDeviceManager**: Device management utilities
- **MVDDrawerManager**: Drawing/annotation utilities for video overlay

### Streaming Capabilities
- **Real-time streaming**: Live video from medical devices
- **Playback streaming**: Historical video with seek, speed control
- **Multi-stream support**: Multiple channels/devices simultaneously
- **Download streams**: Save video data to local files

### Communication Features
- **RabbitMQ integration**: Device communication via message queuing
- **Voice communication**: Two-way audio with devices
- **Volc integration**: Online meeting capabilities for remote collaboration
- **E-Touch support**: Remote keyboard/mouse control of connected devices

### Video Processing
- **Multiple pixel formats**: YUV420P, RGB24, ARGB, RGBA, etc.
- **PTZ control**: Pan-tilt-zoom camera operations
- **Video quality switching**: HD/SD quality adjustment
- **Screen capture and recording**: Built-in screenshot and video recording
- **Drawing overlay**: Annotation capabilities on video streams

## Development Commands

### Setup
```bash
# Install dependencies for example project
cd Example && pod install

# Run lint checks on podspec
pod lib lint --skip-import-validation --allow-warnings
pod spec lint --skip-import-validation --allow-warnings

# Publish to private spec repository
pod repo push BrainMedSpec MVDPlayerSDK.podspec --skip-import-validation --allow-warnings
```

### Building
```bash
# Open example project
open Example/MVDPlayerSDK.xcworkspace

# Build example app
xcodebuild -workspace Example/MVDPlayerSDK.xcworkspace -scheme MVDPlayerSDK-Example -configuration Debug
```

### Testing
```bash
# Run tests from Example directory
xcodebuild test -workspace Example/MVDPlayerSDK.xcworkspace -scheme MVDPlayerSDK-Example -destination 'platform=iOS Simulator,name=iPhone 14'
```

## Key APIs

### Device Connection
- `mvdCreateDevice:deviceid:mqhost:mqport:mqvhost:mquser:mqpassword:waterprintfname:waterprintframe:` - Establish device connection
- `mvdDestroyDevice:` - Clean up device connection

### Video Streaming
- `mvdOpenRealPlayStream:width:height:fps:channel:streamtype:` - Start live streaming
- `mvdOpenPlaybackStream:channel:width:height:fps:starttime:endtime:` - Start playback streaming
- `mvdGetFrameDisplay:tid:frame:lineSize:width:height:fmt:align:` - Get video frames

### Voice Communication
- `mvdOpenTalking:audioChannels:audioSamplerate:audioSamplebits:inputAudioFormatName:inputAudioDeviceName:` - Start voice communication
- `mvdOpenVolcTalking:userId:audioChannels:audioSamplerate:audioSamplebits:volcAppid:volcRoomid:volcToken:` - Volc meeting integration

### Recording
- `mvdStartStreamRecord:tid:filename:duration:width:heigth:` - Record video streams
- `mvdStartDwonloadStream:filename:channel:starttime:endtime:bitrate:concat:` - Download video segments

## Configuration

- **RabbitMQ Configuration**: Required for device communication (host, port, vhost, user, password)
- **Volc Integration**: App ID, room ID, token for online meetings
- **Device Parameters**: Device ID, channel numbers, channel types
- **Video Settings**: Resolution, frame rate, pixel format selection

## Dependencies

- CocoaPods for package management
- FBSnapshotTestCase for testing (in Example project)
- Private spec repository: `https://github.com/zsk511721487/BrainMedSpec.git`