# riscv_learn
最便宜RiscV单片机开发板学RISCV汇编指令


![BearPi-HM_Nano.webp][1]
# BearPi-HM_Nano开发搭建环境  
## 小熊派开源社区 / BearPi-HM_Nano https://gitee.com/bearpi/bearpi-hm_nano
```
## 从小熊派开源社区下载源码，然后使用下行命令编译
python3 build.py BearPi-HM_Nano

## 如果提示错误，需要把 python 链接到 python3
cd /usr/bin/ && ln -s python3 python
```

## 安装Python环境pip3包管理工具 和 wget tmux vim 等常用软件
```
apt update -y \
  && apt install --no-install-recommends --no-install-suggests -y python3 python3-distutils \
  && apt install --no-install-recommends --no-install-suggests -y wget tmux vim \
  && wget https://bootstrap.pypa.io/get-pip.py  --no-check-certificate  \
  && python3 get-pip.py
```

## Python pip3 使用国内镜像源来提高下载速度
默认情况下 pip 使用的是国外的镜像，在下载的时候速度非常慢，我们可以通过使用国内镜像源来提高下载速度，例如使用国内清华大学的源，地址如下：

	-i https://pypi.tuna.tsinghua.edu.cn/simple

可以在 pip 命令中使用-i参数来指定镜像地址

	pip3 install kconfiglib  -i https://pypi.tuna.tsinghua.edu.cn/simple
	pip3 install setuptools
	pip3 install pycryptodome
	pip3 install six --upgrade --ignore-installed six
	pip3 install ecdsa

## 安装Scons

	apt install scons -y

## 安装和设置 samba
```
apt install samba

mkdir -p /home/BearPi
chown -R nobody:nogroup /home/BearPi/

vim /etc/samba/smb.conf
systemctl restart smbd.service
```

### 设置`smb.conf`

```
[global]
   workgroup = WORKGROUP
   max log size = 1000
   logging = file
   panic action = /usr/share/samba/panic-action %d
   server role = standalone server
   obey pam restrictions = yes
   unix password sync = yes

   passwd program = /usr/bin/passwd %u
   passwd chat = *Enter\snew\s*\spassword:* %n\n *Retype\snew\s*\spassword:* %n\n *password\supdated\ssuccessfully* .

   pam password change = yes
   map to guest = bad user
   usershare allow guests = yes

[homes]
   comment = Home Directories
   browseable = no
   read only = yes
   create mask = 0700
   directory mask = 0700
   valid users = %S

[BearPi]
   comment = Network Logon Service
   path = /home/BearPi/
   guest ok = yes
   read only = no
```

## 安装编译工具环境 [下载](https://pan.baidu.com/s/1bp2ypAfH2HaNPTY2KwEhEA) 提取码：1234
- 网络共享路径打开 `\\192.168.1.111\BearPi` 把下载的 `BearPi-HM_Nano` 开发板资料中编译器三个文件复制到共享路径
```
gcc_riscv32-linux-7.3.0.tar.gz
gn.1523.tar
ninja.1.9.0.tar
```
### 安装gn 安装ninja 和 安装gcc_riscv32（WLAN模组类编译工具链）
```
cd /home/BearPi/
tar -xvf gn.1523.tar -C ~/
tar -xvf ninja.1.9.0.tar -C ~/
tar -xvf gcc_riscv32-linux-7.3.0.tar.gz -C ~/
```

### 设置环境变量：`vim ~/.bashrc`   生效环境变量：`source ~/.bashrc`
```
export PATH=~/gn:$PATH
export PATH=~/ninja:$PATH
export PATH=~/gcc_riscv32/bin:$PATH
alias rvcc=riscv32-unknown-elf-gcc
```

## 编译工具不想百度网盘下载，也可以下载华为官方的
### https://repo.huaweicloud.com/harmonyos/compiler/

```
https://repo.huaweicloud.com/harmonyos/compiler/gcc_riscv32/7.3.0/linux/gcc_riscv32-linux-7.3.0.tar.gz
https://repo.huaweicloud.com/harmonyos/compiler/gn/2024/linux/gn-linux-x86-20221108.tar.gz
https://repo.huaweicloud.com/harmonyos/compiler/ninja/1.11.0/linux/ninja-linux-x86-1.11.0.tar.gz
```

## `rvcc -S swap.c`
### [使用 riscv-gcc 把简单的C代码，转换成汇编指令，方便学习](https://github.com/hongwenjun/riscv_learn/tree/main/CLang)


## 源码目录简介

### 小熊派的源码目录延续OpenHarmony官方目录结构，以下是源码目录的说明：

| 目录名  | 描述  |
| ------- | ------- |
|applications|BearPi-HM_Nano应用程序样例 |
| base|基础软件服务子系统集&硬件服务子系统集 |
| build|组件化编译、构建和配置脚本 |
| domains|增强软件服务子系统集 |
| drivers|驱动子系统 |
| foundation|系统基础能力子系统集 |
| kernel|内核子系统 |
| prebuilts|编译器及工具链子系统 |
| test|测试子系统 |
| third_party|开源第三方组件 |
| utils|常用的工具集 |
| vendor|厂商提供的软件 |
| build.py|编译脚本文件 |

  [1]: https://262235.xyz/usr/uploads/2023/03/4102201498.webp