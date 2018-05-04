//
//  MyModel.h
//  
//
//  Created by 陈荣航 on 2017/12/6.
//  Copyright © 2017年 LeslieChen. All rights reserved.
//

//----------------------------------------------------------

#import <UIKit/UIKit.h>

//----------------------------------------------------------

@interface XYYModel : NSObject <NSCoding>

#pragma mark - 初始化

//初始化
+ (NSMutableArray *)modelsWithDictionarys:(NSArray<NSDictionary *> *)dictionarys;
- (id)initWithDictionary:(NSDictionary *)dictionary;

#pragma mark - 更新属性值

//更新属性值，更新属性值策略为:
//(1)通过propertyNameForKey:方法获取key对应的属性名称
//
//(2)判断属性是否有效（可赋值属性）
//属性是否有效需满足四个条件:
//1.属性没有被needIgnoreProperty:方法忽视
//2.属性名对应属性存在
//3.属性类型是支持的数据类型,包括对象，C语言数字类型，结构体或联合体
//4.属性不是readonly（即有setter方法）或者属性有关联的成员变量
//
//(3)对属性值进行转换
//属性值转换顺序是：
//1.调用（如果存在）convert<PropertyName>Value:进行转换，调用方法前会进行方法参数和返回值判断
//2.进行默认转换
//属性值默认转换策略是：
//1.属性值为空（包括NSNull对象)返回默认空值
//2.属性类型为对象:首先判断值是否是同一种类对象，是直接返回，否则执行默认转换策略进行转换（能进行默认转换的类NSString、NSMutableString、NSMutableArray、NSMutableDictionary、NSNumber、NSDecimalNumber、NSDate以及MyModel子类），无法转换则返回nil
//3.属性类型为结构体或联合体:使用<struct/union>Value方法进行转换，无法转换则返回默认空值
//4.属性类型为C语言数字类型:使用数字类型相关方法进行转换,无法转换则返回默认空值
//默认空值为
//1.属性类型为对象:nil
//3.属性类型为结构体或联合体:返回填充为0的结构体或联合体
//4.属性类型为C语言数字类型:返回0
//
//(4)对属性进行赋值
//属性赋值策略为:
//1.存在setter方法，使用setter方法进行赋值
//2.直接对成员变量进行赋值
- (void)updateWithDictionary:(NSDictionary *)dictionary;

#pragma mark - 定制更新属性值

/**
 * key对应的属性名称（key到属性名的映射）
 * @param key key为key值
 * @return 默认返回key值
 * @note 覆盖该方法可定制key到属性名的映射
 */
- (NSString *)propertyNameForKey:(NSString *)key;

/**
 * 是否需要忽视属性
 * @param propertyName propertyName为属性名称
 * @return 默认返回NO
 * @note 覆盖该方法可自定义忽视的属性，忽视的属性即为无效属性将不参与赋值操作
 */
- (BOOL)needIgnoreProperty:(NSString *)propertyName;


/**
 * NSArray类型属性包含对象的类型信息，用于数组到模型数组的转换
 * @param propertyName propertyName为属性名称
 * @return 返回NSArray类型属性包含对象的类型信息，用于属性值的转换，默认返回nil，即不进行转换
 * @note 覆盖该方法可定制NSArray类型的属性值的转换，让数组内容转换成对应对象
 */
- (Class)arrayContentClassForProperty:(NSString *)propertyName;


/**
 * 开始更新某一个属性时会调用该方法
 * @param propertyName propertyName为属性名称
 * @param value value为属性值
 * @note 调用该方法时，属性没有进行有效判断，值也未进行转换，可覆盖定制化转换过程
 */
- (void)startUpdateProperty:(NSString *)propertyName withValue:(id)value;


#pragma mark - 帮助方法

/**
 * 属性是否为有效属性（可赋值属性）
 * @param propertyName propertyName为属性名称
 * @return 返回是否为有效属性
 * @note 该方法仅提供给调用，内部不会使用该方法返回值作为是否有效的依据即覆盖不会对赋值过程造成任何影响
 */
- (BOOL)isValidateProperty:(NSString *)propertyName;

/**
 * 转换属性值
 * @param value value为属性值
 * @param propertyName propertyName为属性名称
 * @return 返回转换后的属性值
 * @note 该方法仅提供给调用，内部不会使用该方法进行值转换覆盖不会对赋值过程造成任何影响
 */
- (id)convertValue:(id)value forProperty:(NSString *)propertyName;

/**
 * 更新属性值
 * @param propertyName propertyName为属性名称
 * @param value value为属性值
 * @note 该方法仅提供给调用，内部不会使用该方法更新属性值覆盖不会对赋值过程造成任何影响
 */
- (void)updateProperty:(NSString *)propertyName withValue:(id)value;


@end

//----------------------------------------------------------

@interface NSObject(ValueConvert)

/**
 * 对值进行装箱
 * @param value value为值的地址
 * @param typeEncoding typeEncoding为值的类型编码
 * @return 返回装箱后的值
 * 装箱策略为：
 * 1.值类型为viod返回NSNull对象
 * 2.值类型为对象直接返回
 * 3.值类型为C语言数字类型（基本数据类型）使用NSNumber装箱
 * 4.其他情况（结构体、联合体、非对象指针等等）使用NSValue装箱
 */
+ (id)boxValue:(void *)value typeEncoding:(const char *)typeEncoding;


/**
 * 转换对象成目标类型的对象或者装箱对象
 * @param returnTypes returnTypes为目标类型集合
 * @param aSelector aSelector为转换方法
 * @return 返回转换后的对象，无法转换则返回nil
 * @note 按照aSelector顺序执行转换方法，执行前会判断是否响应方法、方法参数是否合法以及返回值是否是目标类型集合中的一种，如果目标类型是C语言数字类型，会进行装箱操作，装箱策略见boxValue:typeEncoding:
 */
- (id)performConvertReturnTypes:(NSSet<NSString *> *)returnTypes selectors:(SEL)aSelector,...;
- (id)performConvertReturnTypes:(NSSet<NSString *> *)returnTypes selectorsArray:(NSPointerArray *)aSelectors;

/**
 * 获取C语言数字类型（基本数据类型）的类型编码集合
 * @return 返回C语言数字类型（基本数据类型）的类型编码集合
 */
+ (NSSet<NSString *> *)numberTypeEncodings;

/**
 * 转换对象成C语言数字类型装箱对象
 * @return 转换成功返回C语言数字类型装箱对象，否则返回nil
 */
- (NSNumber *)performDefaultConvertToNumber;


@end

//----------------------------------------------------------

@interface NSInvocation(BoxReturnValue)

/**
 * 获取装箱后的返回值
 * @return 返回装箱后的返回值
 * 装箱策略为：
 * 1.无返回值返回NSNull对象
 * 2.返回值为对象直接返回
 * 3.返回值为C语言数字类型（基本数据类型）使用NSNumber装箱
 * 4.其他情况（结构体、联合体、非对象指针等等）使用NSValue装箱
 */
- (id)getBoxReturnValue;

@end

//----------------------------------------------------------

@interface NSString(setter)

//返回首字母（如果存在）大写字符串
- (NSString *)firstUppercaseString;

//返回默认setter方法的字符串
- (NSString *)defaultSetterSelectorString;

@end

//----------------------------------------------------------

@interface NSString(NSStringSystemStructExtensions)

- (CGPoint)CGPointValue;
- (CGRect)CGRectValue;
- (CGSize)CGSizeValue;
- (CGVector)CGVectorValue;
- (CGAffineTransform)CGAffineTransformValue;
- (UIEdgeInsets)UIEdgeInsetsValue;
- (UIOffset)UIOffset;

@end






