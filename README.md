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
