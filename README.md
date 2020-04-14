# Sniffer-Based-On-Winpcap
## 0x00 项目概述

本产品使用C++语言编写，用于嗅探本机所处网络环境中通过特定网络适配器的流量包。

该产品使用Winpcap库提供的相关API进行核心逻辑编写，结合微软基础类库MFC进行整体框架设计与UI设计，实现对流量包的捕捉、解析与数量统计功能。

## 0x01 使用说明

Release文件夹中的`Sniffer.exe`为可执行文件，使用者可以用其进行本地网络环境流量包嗅探。

## 0x02 嗅探器流程
结合Winpcap库开发嗅探器的简要流程如下:
![嗅探器流程.png-36.9kB][1]


  [1]: http://static.zybuluo.com/B1ank/6sd4gs7luxlugje6so6d1s3j/%E5%97%85%E6%8E%A2%E5%99%A8%E6%B5%81%E7%A8%8B.png