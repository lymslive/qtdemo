# 开发笔记

## 参考示例

* serialport/terminal : 主窗口 app ，接收串口数据，在 plainText 控件中显示
* charts/zoomlinechart : 可缩放平移的单线图表显示，自定义 chart 与 chartView

网络博客示例：

* https://my.oschina.net/u/3919756/blog/2051008 逐步添加数轴与数列
* https://blog.csdn.net/yishuicanhong/article/details/80738361 利用定时器
  QTimer 模块实时生成数据，实时绘图

初始框架参考以上示例综合功能。

## to do

- 将 demo 静态与实时曲线分离出单独类，不要杂合在 mainwindows.cpp 中。
- 增加对话框设置图表范围、样式等控制
* 优化 chartView 的鼠标键盘事件。
- 状态栏优化，需要全局处理，可用单例模式
- 抽出 serialPort 处理真实串口数据
* 应该再分离 chartModel 处理 demo 与 port 串口数据，不宜放在 chartView
- 另外单独写个 app 模拟写入串口
- 利用 QPointer 指针代替对象裸指针成员，利用对象树尽可能省略手写析构负担。

深化学习 chart 及其底层的 Graphics View Framework

