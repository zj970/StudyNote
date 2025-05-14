# pacman 基本使用

sudo pacman -S package_name # 安装软件包
pacman -Ss # 在同步数据库中搜索包，包括包的名称和描述
sudo pacman -Syu # 升级系统。 -y:标记刷新、-yy：标记强制刷新、-u：标记升级动作（一般使用 -Syu 即可）
sudo pacman -Rns package_name # 删除软件包，及其所有没有被其他已安装软件包使用的依赖包
sudo pacman -R package_name # 删除软件包，保留其全部已经安装的依赖关系
pacman -Qi package_name # 检查已安装包的相关信息。-Q：查询本地软件包数据库
pacman -Qdt # 找出孤立包。-d：标记依赖包、-t：标记不需要的包、-dt：合并标记孤立包
sudo pacman -Rns $(pacman -Qtdq) # 删除孤立包
sudo pacman -Fy # 更新命令查询文件列表数据库
pacman -F some_command # 当不知道某个命令属于哪个包时，用来在远程软件包中查询某个命令属于哪个包（即使没有安装）
pactree package_name # 查看一个包的依赖树

# vim 使用教程

vimtutor  

# linux 服务操作

systemctl start dhcpcd # 启动服务
systemctl stop dhcpcd # 停止服务
systemctl restart dhcpcd # 重启服务
systemctl reload dhcpcd # 重新加载服务以及它的配置文件
systemctl status dhcpcd # 查看服务状态
systemctl enable dhcpcd # 设置开机启动服务
systemctl enable --now dhcpcd # 设置服务为开机启动并立即启动这个单元
systemctl disable dhcpcd # 取消开机自动启动
systemctl daemon-reload dhcpcd # 重新载入 systemd 配置。扫描新增或变更的服务单元、不会重新加载变更的配置

# 清理软件包缓存及孤立包 

sudo pacman -Rns $(pacman -Qtdq) # 如上文所述，删除孤立软件包（常用）
sudo pacman -Sc # 删除当前未安装的所有缓存包和未使用的同步数据库（可选）
sudo pacman -Scc # 从缓存中删除所有文件，这是最激进的方法，不会在缓存文件夹中留下任何内容（一般不使用）
paccache -r # 删除已安装和未安装包的所有缓存版本，但最近 3 个版本除外   

## 关机缓慢

journalctl -p5

按/(斜杠键)搜索Killing关键字，找到你关机的时间附近所在的匹配行，你可以在附近看到到底是哪一个进程导致了 timeout,然后再去排查这个进程有什么问题即可



软件包降级
在 archlinux 上偶尔会出现某一个包的最新版本有各种问题的情况，此时需要降级该包以正常使用，包可以是普通软件，也可以是内核。

yay -S downgrade


可能存在升级系统时异常关机或程序异常退出的情况，移除 pacman 的 db 锁即可
sudo rm /var/lib/pacman/db.lck

验证驱动载入情况，还需要安装 I2C Toolse

sudo pacman -S i2c-tools

sudo i2cdetect -l

## 一些操作

```shell
# 关闭暂停和休眠模式
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target

# 开启暂停和休眠模式
sudo systemctl unmask sleep.target suspend.target hibernate.target hybrid-sleep.target

# 查看状态

sudo systemctl unmask status.target suspend.target hibernate.target hybrid-sleep.target

```

## 学习资料

- Arch Linux 官方网站
网址：https://www.archlinux.org
这是 Arch Linux 的官方网站，提供了最新的新闻、发布公告和下载链接。

- Arch Wiki
网址：https://wiki.archlinux.org
Arch Wiki 是一个详尽的知识库，涵盖了从安装、配置到故障排除的各种信息。它是 Arch 用户的必备资源。

- Arch Linux Forums
网址：https://bbs.archlinux.org
Arch Linux 用户的交流社区。你可以在这里提问、分享经验和解决问题。

- Arch Linux reddit
网址：https://www.reddit.com/r/archlinux/
一个活跃的 Arch Linux 社区，用户在这里分享新闻、教程和经验。
    
- Arch Linux User Repository (AUR)
网址：https://aur.archlinux.org/
AUR 是由用户维护的存储库，包含了大量社区贡献的软件包。了解如何使用 AUR 是 Arch 用户的重要技能。 


## 日记

- 2025-05-14  Nvidia 显卡相关 

https://bbs.archlinux.org/viewtopic.php?id=295724