# 由于不正常宕机导致磁盘损坏无法开机

开机时出现BusyBox v1.22.1 built-in shell(ash) 解决方法

1. 输入exit会显示以下信息

```
/dev/sda2 contains a file system with errors, check forced.
Inodes that were part of a corruptde orphan linked list found.
 
/dev/sda2:UNEXPECTED INCONSISTENCY;RUN fsck MANUALLY.
         (i.e.,without -a or -p options)
fsck exited with status code 4
The root filesystem on /dev/sda2 requiers a manual fsck
```

2. sda2上出现了文件系统的错误，需要用fsck进行手动修复

```
fsck -y /dev/sda2
```

修复完成后会出现filesystem has been Modified类似的字样，此时输入exit重启