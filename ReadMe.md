[TOC]

# 矩阵操作类

## 第一版


这是矩阵操作的第一个版本，目前实现如下方法：

* 构造函数
* 拷贝构造函数
* 析构函数
* 重载`=`运算符
* 重载`()`运算符
* 重载`<<`运算符
* 获取行列数目和行列内容
* 设置某行和某列元素
* 获取子阵
* 矩阵转置

功能均已测试过，暂时没有问题。

说明：

* 这里根据老师的要求，采取了号称最快速的转置方法（其实就是意淫一下你已经转置类这个矩阵，实际上并没有转置），但是随之而来的是很多问题，有非常多的判定，变量`_t`就是为了这个带来的坑，`_t == 1`代表当前行列与数组相对应，`_t == 0`表示当前行列互换，然后在每一个涉及到行列操作的时候都需要判定并且开脑洞。
* 当然这里的有几个功能还能继续优化，暂时没有做，其实非常简单，因为实现方法是很灵活的，想怎么弄就怎么弄没关系的，不多赘述。

## 第二版

在原来基础上把整个矩阵类重新写成模版类，新文件`matrixTemplate.h`。

* 增加了加减乘除运算，支持几乎所有你能想到的运算

## 第三版

在原来基础上添加了`FFT`操作，没什么难的，自己看吧，跟老师的方法有些许出入，计算W那里直接用欧拉公式了，已经跟Matlab对比过了，基本没什么问题，太懒了，就不多说了。