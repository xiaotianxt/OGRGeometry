作业9 - OGRGeometry
==========================

程序特点：
----------
1. 通过使用虚函数，统一了`OGRGeometryCollection`类对元素的调用，降低了代码量和维护代价。
2. 通过正则表达式对数据进行导入。

对代码中部分接口介绍：
----------

由于没有提供统一的函数接口，教学网上的描述和文档中的有些差异，这里描述一下自己对部分函数的接口设定。

1. `Clone`函数
   1. `void Clone(SampleType & Sample);`
      - 以`Sample`作为“模板”，将`Sample`的数据复制给自己。
   2. `SampleType &Clone();`
      - 以自己作为“模板”，复制一份并以引用传出。
   - 因为教学网的案例有参数，所以主要采用了第一种方式。

2. `GetMBR`函数
   1. `std::pair<OGRPoint, OGRPoint> GetMBR()`
      - 返回一个`std::pair`, 第一个为最小值点，第二个为最大值点
   2. `void GetMBR(double &XMin, double &XMax, double &YMin, double &YMax)`
      - 将外包矩形信息传递到四个参数中。
    - 因为教学网的案例没有参数，所以主要维护了第一种方式。

`util_variable.cpp / util_variable.h`文件说明
----------
主要包含官方头文件的引用，以及两个自定义函数（用于double比较和ID生成，个人认为并不破坏面向对象编程的实质）

`main.cpp`文件说明
----------
因为教学网上的测试仅仅测试了`Import`和`Export`的可行性，因此我临时询问了往届学长，并拿到了学长当时提供的`main.cpp`测试文件（然而发现和本学期的要求有较大出入），所以main.cpp是我经过一定的魔改之后，并未包含所有要求功能的测试代码。。。

代码运行环境说明
----------
代码使用`MacOS`下`CLion`编写，未尝试宇宙最强IDE的编译结果。（例如我发现`assert.h`在不`include`的情况下依然可以在`CLion`中使用）

