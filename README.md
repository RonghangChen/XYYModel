# XYYModel
objc轻量JSON转模型库

# 支持的功能
1.自定义key到属性的映射

2.自定义value值转换

3.强大的默认value转换机制，容错处理完美

4.支持属性自定义setter方法赋值和对关联的成员变量直接赋值

5.支持自定义结构体/联合体

6.支持组合模型，即模型包含模型或模型数组

# 使用方法

## 1.简单实用
继承XYYModel类，调用modelsWithDictionarys:或者initWithDictionary:即可进行字典到模型的装换，或者也可以使用updateWithDictionary:进行更新模型


## 2.忽视特定属性
覆盖实现needIgnoreProperty:方法，示例如下

- (BOOL)needIgnoreProperty:(NSString *)propertyName

{

    if ([propertyName isEqualToString:@"xxx"]) {
    
        return YES;
        
    }
    
    //add other
    
    return [super needIgnoreProperty:propertyName];
    
}

## 2.自定义转换过程

### 1.自定义key到属性的映射
覆盖实现propertyNameForKey:方法，示例如下

- (NSString *)propertyNameForKey:(NSString *)key

{

    if ([key isEqualToString:@"xxx"]) {
    
        return @"xxx1";
        
    }
    
    //add other
    
    return [super propertyNameForKey:key];
    
}

### 2.自定义value值转换
实现convert<PropertyName>Value:方法，示例如下

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

### 3.实现组合模型转换
覆盖实现arrayContentClassForProperty:方法，示例如下

- (Class)arrayContentClassForProperty:(NSString *)propertyName 
{
    
    if ([propertyName isEqualToString:@"subModels"]) {
    
        return [XYYSubDemoModel class];
        
    }
    
    return nil;
    
}


# 转换策略及流程简介

## (1)通过propertyNameForKey:方法获取key对应的属性名称

## (2)判断属性是否有效（可赋值属性）
属性是否有效需满足四个条件:

1.属性没有被needIgnoreProperty:方法忽视

2.属性名对应属性存在

3.属性类型是支持的数据类型,包括对象，C语言数字类型，结构体或联合体

4.属性不是readonly（即有setter方法）或者属性有关联的成员变量

## (3)对属性值进行转换
属性值转换顺序是：

1.调用（如果存在）convert<PropertyName>Value:进行转换，调用方法前会进行方法参数和返回值判断
    
2.进行默认转换

属性值默认转换策略是：

1.属性值为空（包括NSNull对象)返回默认空值

2.属性类型为对象:首先判断值是否是同一种类对象，是直接返回，否则执行默认转换策略进行转换（能进行默认转换的类NSString、NSMutableString、NSMutableArray、NSMutableDictionary、NSNumber、NSDecimalNumber、NSDate以及MyModel子类），无法转换则返回nil

3.属性类型为结构体或联合体:使用<struct/union>Value方法进行转换，无法转换则返回默认空值

4.属性类型为C语言数字类型:使用数字类型相关方法进行转换,无法转换则返回默认空值


默认空值为

1.属性类型为对象:nil

3.属性类型为结构体或联合体:返回填充为0的结构体或联合体

4.属性类型为C语言数字类型:返回0

## (4)对属性进行赋值
属性赋值策略为:

1.存在setter方法，使用setter方法进行赋值

2.直接对成员变量进行赋值



# 联系方式

QQ：102731887

微信：Hldw_H

