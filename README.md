# TanCloud
## 简介
基于Rust异步运行时Tokio和Axum网络框架实现的轻量级网盘服务（1k并发压力测试内存占用35MB左右，日常9MB，2核2g服务器压力测试支持大概600-700并发），使用中间件统一处理鉴权、日志，实现用户的文件管理和分享。
基于Qt6.5和CMake构建的网盘客户端，使用Boost.Asio实现网络通信，使用SQLite实现相关数据存储。
移动端可能计划用flutter实现。
#### 为什么做这个项目
1.代替百度网盘 ~~（垃圾，开了会员还要看广告）~~ ，等第三方网盘。   
2.不想买成品NAS，群晖、威联通之类的成品NAS没啥性价比。   
3.不想用黑群晖，电脑需要单独装一个系统。   
4.开源的第三方网盘如NexCloud、seafile等大部分服务端程序都只能运行在linux平台，且部署还挺复杂。   
5.当然是学以致用，拿来练手🤣   
#### 使用场景
服务端也可以跨平台，windows、linux、mac。后续可能会用macmini或者香橙派来跑服务端，功耗低，还可以外接硬盘随意扩容。
在外面手机电脑就可以像用普通网盘一样管理和备份数据。
实现WebDav和简单的文件同步后，就可以搭配阅读软件，和Obsidian这样的笔记软件使用。一台设备上改了文件，自己就可以手动同步到其他设备上，就是手动同步可能需要自己管理文件稍微麻烦点。

#### 后续开发计划
先把桌面端完善，再实现移动端，保证多端都可以日常使用。然后实现WebDav功能，和一个简单的文件同步类似于没有版本的OneDrive。

## 目前效果
基本功能文件浏览、导航、列表和缩略图显示、创建文件夹、删除啥的都实现了。
数据库记录传输信息，文件流式上传下载啥的都实现了，就是做界面比较麻烦，还没有集成，这部分做完就可以日常实际使用看看效果了。
找到工作后再继续完善。
![主界面截图_列表显示文件内容](doc/image/主界面截图_列表显示文件内容.png)
![主界面截图_缩略图显示文件内容](doc/image/主界面截图_缩略图显示文件内容.png)