# webCpp
用C++开发web服务器框架
### 主要结构 ###
* 整体思路类似node的express框架
* 不使用xml配置文件
* 使用aio线程模式，实现异步和高并发
### 类结构 ###
* Object: 所有类的最终父类
* TCPServer: 负债accept
* StreamIO: 封装aio，并提供读写方法
* IOEvents: IO事件接口
