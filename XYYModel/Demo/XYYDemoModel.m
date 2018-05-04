//
//  XYYDemoModel.m
//  XYYModel
//
//  Created by 陈荣航 on 2018/5/4.
//  Copyright © 2018年 leslie. All rights reserved.
//

#import "XYYDemoModel.h"
#import <objc/runtime.h>

@implementation XYYDemoModel

- (XYYDemoStruct)convertDemoStructValue:(id)value
{
    XYYDemoStruct result = {0};
    if ([value isKindOfClass:[NSString class]]) {
        NSArray<NSString *> * components = [value componentsSeparatedByString:@","];
        if (components.count == 2) {
            result.value1 = [components[0] intValue];
            result.value2 = [components[1] floatValue];
        }
    }
    
    return result;
}

- (Class)arrayContentClassForProperty:(NSString *)propertyName {
    
    if ([propertyName isEqualToString:@"subModels"]) {
        return [XYYSubDemoModel class];
    }
    
    return nil;
}

- (NSString *)description
{
    NSMutableString * description = [NSMutableString string];
    
    unsigned int outCount;
    Ivar * ivars = class_copyIvarList([self class], &outCount);
    for (int i = 0; i < outCount; i ++) {
        Ivar ivar = ivars[i];
        
        NSString * key = [NSString stringWithUTF8String:ivar_getName(ivar)];
        [description appendFormat:@"%@=%@;",key,[self valueForKey:key]];
//        [aCoder encodeObject:[self valueForKey:key] forKey:key];
    }
    
    //释放内存
    if (ivars != NULL) {
        free(ivars);
    }
    
    return description;
}


@end

@implementation XYYSubDemoModel

- (NSString *)description
{
    NSMutableString * description = [NSMutableString string];
    
    unsigned int outCount;
    Ivar * ivars = class_copyIvarList([self class], &outCount);
    for (int i = 0; i < outCount; i ++) {
        Ivar ivar = ivars[i];
        
        NSString * key = [NSString stringWithUTF8String:ivar_getName(ivar)];
        [description appendFormat:@"%@=%@;",key,[self valueForKey:key]];
        //        [aCoder encodeObject:[self valueForKey:key] forKey:key];
    }
    
    //释放内存
    if (ivars != NULL) {
        free(ivars);
    }
    
    return description;
}

@end
