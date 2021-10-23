# mb85rs16 软件包

中文页 | [English](README.md)

## 介绍

`mb85rs16` 软件包是 针对 SPI 铁电存储器MBR85RS16 推出的一个软件包。使用这个软件包，可以在 RT-Thread 上非常方便的使用该器。

本文主要介绍该软件包的使用方式、API，以及 `MSH` 测试命令。

### 目录结构

```
mb85rs16
│   README.md                       // 软件包说明
│   src\mb85rs16.c                       // 源文件
│   inc\mb85rs16.h                       // 头文件
│   mb85rs16_sample.c                // 软件包使用示例代码
│   SConscript                      // RT-Thread 默认的构建脚本
│   LICENSE                         // 许可证文件
```

### 许可证

mb85rs16 遵循 Apache-2.0 许可，详见 `LICENSE` 文件。

### 依赖

- RT_Thread 3.0+
- i2c 设备驱动

## 获取方式

使用 `mb85rs16 package` 需要在 RT-Thread 的包管理中选中它，具体路径如下：

```
RT-Thread online packages
    peripheral libraries and drivers  --->
        mb85rs16: 16K(2K x 8)Bit SPI FRAM Driver --->
```

进入 mb85rs16 软件包的配置菜单按自己的需求进行具体的配置

```
    --- mb85rs16: 16K(2K x 8)Bit SPI FRAM Driver
        [*]   Enable mcp23008 sample
           Version (latest)  --->
```

**Enable mb85rs16 sample** ：开启 mcp23008  使用示例

配置完成后让 RT-Thread 的包管理器自动更新，或者使用 pkgs --update 命令更新包到 BSP 中。

## 使用方法

mb85rs16 软件包的使用流程一般如下：

1. 初始化 mb85rs16 设备 `mb85rs16_spi_device_init`
2. 进行 读写的操作
   - 写使用 API `mb85rs16_write_byte` 
   - 读使用 API `mb85rs_read_bytes` 

详细的使用方法可以参考[mb85rs16 示例程序](https://github.com/XiaojieFan/mb85rs16/blob/main/examples/mb85rs16_sample.c)。

## MSH 测试命令

如果开启了'mb85rs16' 软件包的示例程序，就会导出 `fram_cmd` 命令到控制台。。运行结果如下：

```
msh >fram_cmd id
04 7f 01 01
```

## 注意事项

暂无。

## 联系方式

- 维护：[XiaojieFan](https://github.com/XiaojieFan)
- 主页：<https://github.com/XiaojieFan/mb85rs16>
