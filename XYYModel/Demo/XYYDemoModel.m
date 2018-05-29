//
//  XYYDemoModel.m
//  XYYModel
//
//  Created by 陈荣航 on 2018/5/4.
//  Copyright © 2018年 leslie. All rights reserved.
//

#import "XYYDemoModel.h"
#import <objc/runtime.h>

@implementation NSString(XYYDemoStruct1)


- (XYYDemoStruct1)XYYDemoStruct1Value
{
    XYYDemoStruct1 result = {0};
    NSArray<NSString *> * components = [self componentsSeparatedByString:@","];
    if (components.count == 2) {
        result.value1 = [components[0] intValue];
        result.value2 = [components[1] floatValue];
    }
    
    return result;
}

+ (NSString *)stringWithXYYDemoStruct1:(XYYDemoStruct1)struct1 {
    return [NSString stringWithFormat:@"%i,%f",struct1.value1,struct1.value2];
}

@end

@implementation XYYDemoModel

- (BOOL)xyy_alwaysAccessIvarDirectlyIfCanForDicToModel:(BOOL)dicToModel {
    return !dicToModel;
}

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

- (NSString *)convertDemoStructToJsonValue {
    return [NSString stringWithFormat:@"%i,%f",self.demoStruct.value1,self.demoStruct.value2];
}

- (Class)xyy_arrayContentClassForProperty:(NSString *)propertyName {
    
    if ([propertyName isEqualToString:@"subModels"]) {
        return [XYYSubDemoModel class];
    }
    
    return nil;
}

- (NSString *)onlyGetter {
    return @"onlyGetter";
}

@end

@implementation XYYSubDemoModel


@end
