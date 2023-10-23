# 挂载磁盘的时候要根据磁盘的文件系统进行挂载


# 挂载远程文件

```shell

[root@CentOS7 /]# mount -t cifs -o username=test,password=123456,rw,file_mode=0777,dir_mode=0777,uid=0,gid=0,vers=2.0 //192.168.1.1/share  /mnt/share
```

将服务器上的文件传输到本地

ssh 【服务器用户名】@【服务器地址】
scp 【服务器用户名】@【服务器地址】：【服务器上存放文件的路径】【本地文件的路径】

# scp 命令详解

scp【本地或远程文件的路径】【服务器用户名】@【服务器地址】：【远程或本地文件的路径】
-1： 强制scp命令使用协议ssh1
-2： 强制scp命令使用协议ssh2
-4： 强制scp命令只使用IPv4寻址
-6： 强制scp命令只使用IPv6寻址
-B： 使用批处理模式（传输过程中不询问传输口令或短语）
-C： 允许压缩。（将-C标志传递给ssh，从而打开压缩功能）
-p：保留原文件的修改时间，访问时间和访问权限。
-q： 不显示传输进度条。
-r： 递归复制整个目录。
-v：详细方式显示输出。scp和ssh(1)会显示出整个过程的调试信息。这些信息用于调试连接，验证和配置问题。
-c cipher： 以cipher将数据传输进行加密，这个选项将直接传递给ssh。
-F ssh_config： 指定一个替代的ssh配置文件，此参数直接传递给ssh。
-i identity_file： 从指定文件中读取传输时使用的密钥文件，此参数直接传递给ssh。
-l limit： 限定用户所能使用的带宽，以Kbit/s为单位。
-o ssh_option： 如果习惯于使用ssh_config(5)中的参数传递方式，
-P port：注意是大写的P, port是指定数据传输用到的端口号
-S program： 指定加密传输时所使用的程序。此程序必须能够理解ssh(1)的选项。


nmcl 命令常用(需要下载netowrkmanager)



```shell
# 显示连接情况
nmcli connection show 
# 开启wifi
nmcli radio wifi on
# 识别wifi接入点

nmcli device wifi list

# 链接wifi

ncmli device wifi connection SSID password ""
# 显示链接
nmcli connection show
# 切换
nmcli connect connection down/up UUID
```

# 挂载网络文件

```shell
sudo mount.cifs -o username=admin,password="P@ssw0rd",uid=test,gid=test,dir_mode=0777 //172.20.10.20/test share
```
