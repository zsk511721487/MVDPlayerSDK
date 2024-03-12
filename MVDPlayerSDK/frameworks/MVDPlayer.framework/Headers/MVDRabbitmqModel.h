//
//  MVDRabbitmqModel.h
//  MVDPlayer
//
//  Created by 张少康 on 2024/3/12.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MVDRabbitmqModel : NSObject

/// 服务器ip地址
@property (nonatomic, assign) int clientid;

/// 服务器ip地址
@property (nonatomic, copy) NSString *ip;

/// 端口号
@property (nonatomic, assign) int  port;

/// 服务器用户名
@property (nonatomic, copy) NSString *user;

/// 服务器密码
@property (nonatomic, copy) NSString *pwd;

/// 虚拟host名称
@property (nonatomic, copy) NSString *vhost;

- (NSString *)getRabbitmqKeyWith:(int)deviceId;

@end

NS_ASSUME_NONNULL_END
