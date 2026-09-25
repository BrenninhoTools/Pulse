#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PulseBridge : NSObject

- (instancetype)init;
- (float)trainXorWithEpochs:(NSInteger)epochs;
- (NSArray<NSNumber *> *)predictWithInput:(NSArray<NSNumber *> *)input;

@end

NS_ASSUME_NONNULL_END
