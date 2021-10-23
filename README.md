

# mb85rs16 package

[中文页](https://github.com/XiaojieFan/mb85rs16/blob/main/README_ZH.md) | English

## Introduction

The `mb85rs16` software package is a software package developed by XiaojieFan for the SPI FRAM MB85RS16. Using this software package, you can use the device on RT-Thread very conveniently .

This article mainly introduces the use of the package, API, and `MSH` test commands.

### Directory Structure

```
mcp23008
│ README.md // package description
│ src\mb85rs16.c // source file
│ inc\mcp23008.h // header file
│ sample\mb85rs16_sample.c // Sample code for software package
│ SConscript // RT-Thread default build script
│ LICENSE // License file
```

### License

mb85rs16 complies with the Apache-2.0 license, see the `LICENSE` file for details.

### Dependence

- RT_Thread 3.0+
- i2c device driver

## method of obtaining

To use `mb85rs16 package`, you need to select it in the package management of RT-Thread. The specific path is as follows:

```
RT-Thread online packages
    peripheral libraries and drivers --->
        mb85rs16: 16K(2K x 8)Bit SPI FRAM Driver --->
```

Enter the configuration menu of the mcp23008 software package for specific configuration according to your needs

```
    --- mb85rs16: 16K(2K x 8)Bit SPI FRAM Driver
        [*] Enable mb85rs16 sample
           Version (latest) --->
```

**Enable mb85rs16 sample**: Enable mb85rs16 sample

After the configuration is complete, let the RT-Thread package manager automatically update, or use the pkgs --update command to update the package to the BSP.

## Instructions

The use process of mb85rs16 software package is generally as follows:

1. Initialize mb85rs16 device `mb85rs16_spi_device_init`
2. Perform RW operations
   - Wriet Use API `mb85rs16_write_byte` ` 
   - Read Use API `mb85rs16_read_byte` 

For detailed usage, please refer to [mb85rs16 sample program](https://github.com/XiaojieFan/mb85rs16/blob/main/examples/mb85rs16_sample.c).

## MSH Test Command

If the sample program of the mb85rs16 software package is enabled, the command `fram_cmd` will be exported to the console. 

```
msh >fram_cmd id
04 7f 01 01
```

## Precautions

Nothing.

## Contact information

- Maintenance: [XiaojieFan](https://github.com/XiaojieFan)
- Homepage: <https://github.com/XiaojieFan/mb85rs16>