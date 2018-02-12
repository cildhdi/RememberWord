# RememberWord
- 界面：
![ui](http://img02.sogoucdn.com/app/a/100520146/4d2164ff379d7aae08a9fd9ccac1dda0)
每次查询先在words.xml中查找，未找到则在线查找并保存在words.xml,支持删除
- 界面部分使用我的另外一个repo：[KrUI](https://github.com/cildhdi/KrUI)，请自行下载
- 使用[金山词霸查词开放平台](http://open.iciba.com/?c=api)
- 使用libcurl发送请求
- 使用[TinyXML2](https://github.com/leethomason/tinyxml2)解析返回的XML
- 项目请使用Unicode字符集
- 生成后请将libcurl.dll和exe文件放在同一目录
- 请右键属性在兼容性中禁止高DPI自动缩放
