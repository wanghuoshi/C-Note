# C++核心编程
### 1 内存分区模型
##### 1.1 程序运行前
##### 1.2 程序运行后
##### 1.3 new操作符
### 2 引用
##### 2.1 引用的基本使用
##### 2.2 引用注意事项
##### 2.3 引用做函数参数
##### 2.4 引用做函数返回值
##### 2.5 引用的本质
##### 2.6 常量引用
### 3 函数提高
##### 3.1 函数默认参数
##### 3.2 函数占位参数
##### 3.3 函数重载
###### 3.3.1 函数重载概述
###### 3.3.2 函数重载注意事项
### 4 类和对象
charpter 10 对象和类
##### 4.1 封装
###### 4.1.1 封装的意义
###### 4.1.2 struct和class区别
###### 4.1.3 成员属性设置为私有
##### 4.2 对象的初始化和清理
charpter 10.3 
###### 4.2.1 构造函数
**目的:**初始化类
* 构造函数的分类及调用
* 默认构造函数
* 拷贝构造函数

* 使用初始化列表来初始化
```c++
class Person
{
    int m_Id;
    string m_Name;

public:
    Person(int a, int b): n_Id(a), m_Name(b)
    {
        cout<<"Person Id: "<<n_Id<<", Name: "<<m_Name<<endl;
    }
};
```
* 类对象作为类成员
```c++
class Phone
{
public:
    int Id;

    Phone(int a)
    {
        Id = a;
        cout << "This is Phone's constructor." << endl;
    }

    ~Phone()
    {
        cout << "This is Phone's destructor." << endl;
    }
};

class Person
{
    int m_Id;
    Phone m_Phone;

public:
    Person(int a, Phone b): m_Id(a), m_Phone(b)
    {
        cout << "This is Person's constructor." << endl;
    }

    void showInfo()
    {
        cout << "Person Id: " << m_Id << ", Phone: " << m_Phone.Id << endl;
    }

    ~Person()
    {
        cout << "This is Person's destructor." << endl;
    }

};

int main()
{
    Person p(5, 8);
    p.showInfo();
    return 0;
}
/*
This is Phone's constructor.
This is Person's constructor.
This is Phone's destructor.
Person Id: 5, Phone: 8
This is Person's destructor.
This is Phone's destructor.
*/
```
当类中成员是其他类对象时，我们称该成员为 对象成员
构造的顺序是 ：先调用对象成员的构造，再调用本类构造
析构顺序与构造相反
* 静态成员
###### 4.2.2 析构函数
##### 4.3 C++对象模型和this指针
###### 4.3.1 成员变量和成员函数分开存储
###### 4.3.2 this指针概念
###### 4.3.3 空指针访问成员函数
###### 4.3.4 const修饰成员函数
##### 4.4 友元
###### 4.4.1 友元函数
赋予该函数与类的成员函数相同的访问权限
```c++
class A
{
    friend void visit(A a);

    int num = 5;
};

void visit(A a)
{
    cout << a.num << endl;
}

int main()
{
    A a;
    visit(a);
    
    return 0;
}
```
###### 4.4.2 友元类
###### 4.4.3 友元成员函数
##### 4.5 运算符重载
###### 4.5.1 加号运算符重载
###### 4.5.2 左移运算符重载
###### 4.5.3 递增运算符重载
###### 4.5.4 赋值运算符重载
###### 4.5.5 关系运算符重载
###### 4.5.6 函数调用运算符重载
##### 4.6 继承
###### 4.6.1 继承的基本语法
###### 4.6.2 继承方式
###### 4.6.3 继承中的对象模型
###### 4.6.4 继承中构造和析构顺序
###### 4.6.5 继承同名成员处理方式
###### 4.6.6 继承同名静态成员处理方式
###### 4.6.7 多继承语法
###### 4.6.8 菱形继承
##### 4.7 多态
###### 4.7.1 多态的基本概念
###### 4.7.2 多态案例一-计算器类
###### 4.7.3 纯虚函数和抽象类
###### 4.7.4 多态案例二-制作饮品
###### 4.7.5 虚析构和纯虚析构
###### 4.7.6 多态案例三-电脑组装
### 5 文件操作
|模式标记|	适用对象|	作用|
|--------------|--------------|----------------|
|ios::in|	ifstream fstream|	打开文件用于读取数据。如果文件不存在，则打开出错。|
|ios::out|	ofstream fstream|	打开文件用于写入数据。如果文件不存在，则新建该文件；如果文件原来就存在，则打开时清除原来的内容。|
|ios::app|	ofstream fstream|	打开文件，用于在其尾部添加数据。如果文件不存在，则新建该文件。|
|ios::ate|	ifstream|	打开一个已有的文件，并将文件读指针指向文件末尾（读写指 的概念后面解释）。如果文件不存在，则打开出错。|
|ios:: trunc|	ofstream|	打开文件时会清空内部存储的所有数据，单独使用时与 ios::out 相同。|
|ios::binary|	ifstream ofstream fstream|	以二进制方式打开文件。若不指定此模式，则以文本模式打开。|
|ios::in\|ios::out|	fstream|	打开已存在的文件，既可读取其内容，也可向其写入数据。文件刚打开时，原有内容保持不变。如果文件不存在，则打开出错。|
|ios::in\|ios::out|	ofstream|	打开已存在的文件，可以向其写入数据。文件刚打开时，原有内容保持不变。如果文件不存在，则打开出错。|
|ios::in\|ios::out\|ios::trunc|	fstream|	打开文件，既可读取其内容，也可向其写入数据。如果文件本来就存在，则打开时清除原来的内容；如果文件不存在，则新建该文件。|
##### 5.1文本文件
###### 5.1.1写文件
###### 5.1.2读文件
析取器 >>
##### 5.2 二进制文件
###### 5.2.1 写文件
###### 5.2.2 读文件