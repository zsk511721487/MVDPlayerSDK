//
//  MVDDrawerShape.h
//  MVDPlayer
//
//  Created by 张少康 on 2025/1/10.
//

#import <Foundation/Foundation.h>
#import "mvdscribbler.h"

NS_ASSUME_NONNULL_BEGIN

@interface MVDDrawerShape : NSObject
@property (nonatomic, assign) int32_t clientId;
@property (nonatomic, assign) int32_t deviceId;
@property (nonatomic, assign) int channel;
@property (nonatomic, assign) int streamType;
@property (nonatomic, assign) int32_t cmd;
@property (nonatomic, assign) int32_t width;
@property (nonatomic, assign) uint32_t color;
@property (nonatomic, strong) NSArray<NSValue *> *positions; // 包装 MVDPOS

@property (nonatomic, assign) BOOL isCreator; // 是否是本人创建的

- (MVDSHAPE *)toCStruct;
@end

NS_ASSUME_NONNULL_END
