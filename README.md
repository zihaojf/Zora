# Zora

### 武汉大学2024级高级语言程序设计期末大作业


技术栈:qt图形框架 c++ 内置sqlite数据库

团队协作使用github

需求:桌面助手

**核心功能(删除线部分是未实现的功能)**

- 桌面状态左键点击有不同的状态，有stand,jump,tumble,lie

- 桌面状态右键可以呼出菜单
- 音乐播放，选择本地音乐文件，列表展示，播放、暂停、下一首、上一首、播放模式~~、歌词、显示音乐图片~~

- 功能包括记账，记录收入支出，记录时间，按照时间排序，~~支持月总览，年总览，图表（扇形图）~~

- 课程备忘录，分为课程和作业两方面，课程部分实现课程表创建，添加，删除，显示~~，并能够提醒即将上课~~

​	~~作业部分:支持添加作业名称,ddl，并且在ddl时间提醒~~

- 工作记录器，实现番茄时钟，用于记录自己的学习时间等，自定义时间；

- 密码记录器，记录自己常用的账号及密码信息等，查询的时候注意隐私保护和处理；

- 笔记、待办：支持添加笔记、编辑笔记、删除笔记、记录笔记时间，添加待办、勾选代办、删除代办

各个功能之间**比较独立**，每个存储模块使用**sqlite**存储，并且保存到文件当中，实现永久保存

## 小组分工

- 首页、课程表、笔记待办 hzh
- 记账、密码管理器 tyh
- 音乐播放、番茄时钟 yym

# 进度管理

## 2024年11月21日

实现stand,jump,tumble和lie四种动作的切换，实现动作动图的播放

待解决问题：四种动作的图片像素大小不同，导致不同动作图片主体显示的位置不同     byhzh

## 2024年11月22日
### 首页按钮
- closebtn
- musicbtn
- accountbtn
- classbtn
- workbtn
- passwordbtn
- lifebtn
- minbtn 最小化按钮

## 2024年12月4日
### 记账模块
#### 存储数据属性
- 交易ID（ID）：为每笔交易分配一个唯一标识符，以便于跟踪和管理。
- 金额（Amount）：交易的金额，收入为正数，支出为负数。
- 支付方式（Payment Method）：记录支付方式，如现金、信用卡、借记卡、支票、在线支付等。
- 描述（Description）：对交易的简短描述，帮助用户记住交易的具体内容。
- 支付时间（Payment Time）：记录交易被添加到系统的时间。

## 2024年12月7日

### 音乐模块

- 播放、暂停

- 选择音乐文件夹

- 显示当前正在播放的歌曲

- 顺序、乱序播放模式设定

## 2024年12月9日

### 密码记录器模块

- 登录验证用户密码
- 密码显示
- 密码查询

## 2024年12月15日

笔记待办模块

## 202412月19日

完成课程表模块

