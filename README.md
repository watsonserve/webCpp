# webCpp
用C++开发web服务器框架

### 初衷
传统CGI或fastCGI等由于进程调度等原因导致性能较差
Java实现的tomcat、jetty等多采用同步模式，较重的实现方式导致面对一个小的变动总是需要重写依赖，而且运行时真的吃内存真的很有一套
python下除了多用类CGI模式，还有鸡肋的线程和作死的2.7 3.xAPI
nodejs的异步确实有益，但单线程对于运算密集型就显得乏力，而且对于系统调用等解释器本身没有提供API
Go倒是一个很棒的尝试，运行时消耗的内存能比Java低两位数
so
用C++构建一个支持异步IO的，能处理高并发的，运算速度快，且消耗内存少，支持各种方式外部调用的web服务器框架，
也许也是个不错的想法

### 整体设计
* 参考了spring AOP的编程思路
* 效仿node的express框架
* 不使用xml配置文件，所有配置依靠编程实现
* 采用异步IO，封装多线程及多路复用
* 尽量使用单继承和接口化，增强可扩展性
* 原则上尽量使用C++标准库，尽量使用POSIX标准库
* 尽量少的内存拷贝


### 不同平台下的实现
```
{
  "linux": " POSIX aio", // 以后会添加epoll + POSIX信号量模拟aio
  "BSD系": "kqueue + POSIX信号量模拟aio",
  "UNIX系": "poll + POSIX信号量模拟aio",
  "windows": "不支持"
}
```
目前对于模拟aio采用的是固定线程数线程池模式，后续会改成动态线程池，以满足单次处理时间长的场景

### 主要类结构
    Object: 所有类的最终父类
      │
      ├─Server
      |  |
      |  └─TCPServer: 负债accept
      │
      ├─StreamIO: 封装aio，并提供读写方法
      │
      ├─IOEvents: IO事件接口
      |  |
      |  └─HTTPDispatcher
      |
      ├─HTTPGram
      |  |
      |  ├─HTTPRequest
      |  |
      |  ├─HTTPResponse
      |  |
      |  └─HTTPSession
      |
      └─MiddleWare

### 使用方法
参看main.cpp

[wiki](https://github.com/watsonserve/webCpp/wiki)

[more...](http://wiki.watsonserve.com/web-cpp)
