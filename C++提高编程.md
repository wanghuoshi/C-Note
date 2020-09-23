# C++提高编程
### 1.模板
##### 1.1 函数模板
```c++
template <typename T>
void Swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}
```
###### 1.1.1 模板重载

##### 1.2 类模板