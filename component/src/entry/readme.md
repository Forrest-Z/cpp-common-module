# 动态加载

> 编译库时 ，函数加上 extern "C" ，以C符号导出；加上 -rdynamic  的 g++ 编译选项；
> 使用时 ， 加上 -ldl   的 g++ 编译选项 (使用 dlopen);