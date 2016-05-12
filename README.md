# webCpp
用C++开发web服务器框架
### 整体设计
* 整体思路效仿node的express框架
* 不使用xml配置文件，所有配置依靠编程实现
* 使用aio线程模式，实现异步和高并发

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

[more...](https://www.watsonserve.com/webCpp)
