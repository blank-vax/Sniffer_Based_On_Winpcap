# Sniffer-Based-On-Winpcap
## 0x00 项目概述

本产品使用C++语言编写，用于嗅探本机所处网络环境中通过特定网络适配器的流量包。

该产品使用Winpcap库提供的相关API进行核心逻辑编写，结合微软基础类库MFC进行整体框架设计与UI设计，实现对流量包的捕捉、解析与数量统计功能。

## 0x01 使用说明

根目录下的`Sniffer.sln`是可以在Visual Studio中打开的解决方案Solution，使用者可以在VS中打开并进行相关编辑。

Release文件夹中的`Sniffer.exe`为可执行文件，使用者可以用其进行本地网络环境流量包嗅探。

