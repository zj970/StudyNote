
## 问题描述

```

ninja: no work todo.

No need to regenerate ninja file

No need to regenerate ninja file

[0%1/4440]//system/tools/aidl:libaidl-common lex aidl_language_l.ll [linux_glibc]

FAILED: out/soong/.intermediates/system/tools/aidl/libaidl-common/linux_glibc_x86_64_static/gen/lex/system/tools/aidl/aidl_language_l.cpp

prebuilts/misc/linux-x86/flex/flex-2.5.39 -oout/soong/.intermediates/system/tools/aidl/libaidl-common/linux_glibc_x86_64_static/gen/lex/system/tools/aidl/aidl_language_l.cpp system/tools/aidl/aidl_language_l.ll

flex-2.5.39: loadlocale.c:130:_nl_intern_locale_data: ??'cnt < (sizeof (_nl_value_type_LC_TIME) / sizeof (_nl_value_type_LC_TIME[0]))' ???

Aborted (core dumped)

[0%8/4440]//external/libcxxabi:libc++abi clang++ src/stdlib_new_delete.cpp [linux_glibc]

ninja: build stopped: subcommand failed.

18:04:05 ninja failed with: exit status 1


```

## 解决方案 

```
在.bashrc中添加 LC_ALL=C
$ source ~/.bashrc
```

在AOSP中的flex可执行文件在Ubuntu22上运行不兼容

```

you:AOSP/prebuilts/misc/linux-x86/flex$ ll  //你可能会看到：flex-2.5.39（可执行文件）、flex-2.5.39.tar.gz（flex压缩包）
you:AOSP/prebuilts/misc/linux-x86/flex$ mkdir flex-2.5.39.source
you:AOSP/prebuilts/misc/linux-x86/flex$ tar -zxvf flex-2.5.39.tar.gz -C flex-2.5.39.source/
you:AOSP/prebuilts/misc/linux-x86/flex$ cd flex-2.5.39.source
you:AOSP/prebuilts/misc/linux-x86/flex-2.5.39.source$ mkdir install

you:AOSP/prebuilts/misc/linux-x86/flex-2.5.39.source$ cd flex-2.5.39

安装到刚才创建的install目录，绝对地址:
you:AOSP/prebuilts/misc/linux-x86/flex-2.5.39.source/flex-2.5.39$ ./configure --prefix=/home/you/xxxxxxxxxxxxxxxxxx/AOSP/prebuilts/misc/linux-x86/flex/flex-2.5.39.source/install/

you:AOSP/prebuilts/misc/linux-x86/flex-2.5.39.source/flex-2.5.39$ make
you:AOSP/prebuilts/misc/linux-x86/flex-2.5.39.source/flex-2.5.39$ make install
you:AOSP/prebuilts/misc/linux-x86/flex-2.5.39.source/flex-2.5.39$ cd ../install
you:AOSP/prebuilts/misc/linux-x86/flex-2.5.39.source/flex-2.5.39/install$ ls

将bin下flex 可执行文件替换掉AOSP/prebuilts/misc/linux-x86/flex下的flex-2.5.39可执行文件重新编译即可。

```

## 编译framework报错

```
Attempting to fall back to imageless running. Error was: Failed to mmap at expected address, mapped at 0x7f75efc00000 instead of 0x704a5000
```

报错指出，mmap系统调用返回的内存起始地址与传下去的建议地址值不一致。
实际上，这个建议值在Linux kernel 5.18（Host端，即PC或工作站端）及其以后，基本是被无视掉了，导致每次创建的内存地址值，跟建议值都不一样，从而报错，而在Linux kernel 5.17及其以前的版本，建议值通常都会被接受，并按照该地址申请内存；

解决方式：
mmap系统调用时，flag添加MAP_FIXED_NOREPLACE标志位；

https://blog.csdn.net/u014175785/article/details/131326625