//
//  XYYDemoModel.h
//  XYYModel
//
//  Created by 陈荣航 on 2018/5/4.
//  Copyright © 2018年 leslie. All rights reserved.
//

#import "XYYModel.h"

typedef struct XYYDemoStruct {
    int value1;
    float value2;
} XYYDemoStruct;


typedef struct XYYDemoStruct1 {
    int value1;
    float value2;
} XYYDemoStruct1;


@interface NSString(XYYDemoStruct1)

- (XYYDemoStruct1)XYYDemoStruct1Value;
+ (NSString *)stringWithXYYDemoStruct1:(XYYDemoStruct1)struct1;

@end


@class XYYSubDemoModel;
@interface XYYDemoModel : XYYModel

//普通对象
@property(nonatomic,strong,readonly) NSString * string;

//数字
@property(nonatomic) NSInteger intValue;
//自定义setter
@property(nonatomic,setter=setFloatValue1:) CGFloat floatValue;

//转预定义对象
@property(nonatomic,strong,readonly) NSDate * date;

//结构体
@property(nonatomic,readonly) CGSize size;
//自定义结构体
@property(nonatomic,readonly) XYYDemoStruct demoStruct;
//自定义结构体
@property(nonatomic,readonly) XYYDemoStruct1 demoStruct1;

//自定义结构体
@property(nonatomic,readonly) NSString * onlyGetter;

//子对象
@property(nonatomic,strong,readonly) NSArray<XYYSubDemoModel *> * subModels;

@end


@interface XYYSubDemoModel : XYYModel

//字符
@property(nonatomic,strong,readonly) NSString * string;
//数字
@property(nonatomic,strong) NSDecimalNumber * number;


@end
