# webCpp
用C++开发web服务器框架
### 整体设计
* 参考了spring AOP的编程思路
* 效仿node的express框架
* 不使用xml配置文件，所有配置依靠编程实现
* 采用异步IO，封装多线程及多路复用
* 尽量使用单继承和接口化，增强可扩展性


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
