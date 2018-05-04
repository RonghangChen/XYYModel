//
//  ViewController.m
//  XYYModel
//
//  Created by 陈荣航 on 2018/5/4.
//  Copyright © 2018年 leslie. All rights reserved.
//

#import "ViewController.h"
#import "XYYDemoModel.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    NSArray * dics = [NSArray arrayWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Demo" ofType:@"plist"]];
    
    NSArray<XYYDemoModel *> * models = [XYYDemoModel modelsWithDictionarys:dics];
    
    NSLog(@"%@",models);
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
