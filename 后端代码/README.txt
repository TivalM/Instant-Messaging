1、三层架构设计
（1）dao：数据访问层。
（2）service：服务层，处理系统逻辑。
（3）controller：控制器层，负责处理前端请求，并返回特定结果报文。

2、包说明（除了以上三个包）
entity：包含后端的所有实体类。包括前后端通信的响应报文实体，报文内容请参考“json约定”。
service.impl：service接口的所有实现类。
util：工具包，包括日志工具，系统常量，以及websocket工具。
websocket：包括WebSocket类、WebSocket的config类（配置类）。
Resource：存放系统配置文件，application.properties文件用于配置数据库和绑定端口等。

3、路由路径（URL）说明
http前缀：
http://{host_ip}:{host_port}
匹配项（具体参数、约束、返回格式参考接口文档）：
/login 登录，使用POST方法提交 
/register 注册，使用POST方法提交
/personalChat 私聊，使用POST方法提交
/historyMessage 获取历史消息，使用GET方法提交
/offlineMessage 获取离线消息，使用GET方法提交
...

4、开发环境说明
build：maven，一种构建项目的方法
JDK：1.8
集成开发环境：IntelliJ IDEA/eclipse（推荐使用IDEA，安装插件便捷）

5、第三方框架
SpringBoot
MyBatis：数据库框架

6、文件说明
源代码位置：im/src/main/java/..
配置文件位置：im/src/main/resources/..
im/pom.xml： <dependency>标签内是项目用到的jar包，编辑器会自动下载，无需手动传包。
其他文件：如.iml，.cmd等都是IDEA项目自动生成或测试文件，无需更改。




