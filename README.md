# riscv_learn
最便宜RiscV单片机开发板学RISCV汇编指令

## [Debian 11.6.0 For Oracle VM VirtualBox 磁盘镜像](https://pan.baidu.com/s/1qik1PwvvpS8kNKIJ_LJTGg?pwd=2pku)  提取码: 2pku
- 点击链接下载镜像文件 `Linux_Debian11.6.7z` 压缩包，解压得到 `Linux.vdi`，VM VirtualBox 新建一个虚拟机，挂载这个镜像，网络设置成桥接，使用分离模式启动
```
debian-11.6.0系统用户密码
用户名:  riscv
密码:    riscv
登陆后    sudo -i  命令切换到root用户
```
## [【Risc-V 汇编指令 Linux 学习环境搭建，学习HarmonyOS系统的环境搭建】](https://www.bilibili.com/video/BV1tj411c7Gd) [B站视频](https://www.bilibili.com/video/BV1tj411c7Gd)

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

## [学习 Risc-V 汇编, 使用 gcc -S 命令转换C语言源码成 RISC-V 汇编代码](https://262235.xyz/index.php/archives/1276/)

![](https://262235.xyz/usr/uploads/2023/03/625082788.webp)
当使用 `riscv32-unknown-elf-gcc -S` 命令时，会将 C 语言源代码转换成 RISC-V 汇编代码。
以下是一些常用的 RISC-V 汇编指令及其含义，以供参考：

- `add`: 将两个数相加。
- `addi`: 将一个数和一个立即数相加。
- `sub`: 从一个数中减去另一个数。
- `mul`: 将两个数相乘。
- `div`: 将一个数除以另一个数。
- `rem`: 取两个数的余数。
- `and`: 对两个数进行按位与操作。
- `or`: 对两个数进行按位或操作。
- `xor`: 对两个数进行按位异或操作。
- `sll`: 将一个数左移指定的位数。
- `srl`: 将一个数右移指定的位数。
- `sra`: 将一个有符号数右移指定的位数。
- `slt`: 如果第一个数小于第二个数，则将目标寄存器设置为 1，否则设置为 0。
- `slti`: 如果一个数小于一个立即数，则将目标寄存器设置为 1，否则设置为 0。
- `beq`: 如果两个寄存器相等，则跳转到指定的标签。
- `bne`: 如果两个寄存器不相等，则跳转到指定的标签。
- `blt`: 如果第一个寄存器小于第二个寄存器，则跳转到指定的标签。
- `bge`: 如果第一个寄存器大于等于第二个寄存器，则跳转到指定的标签。
- `j`: 无条件跳转到指定的标签。
- `jal`: 跳转到指定的标签，并将返回地址保存到目标寄存器中。
- `jr`: 跳转到目标寄存器所指向的地址。
- `jalr`: 跳转到目标寄存器所指向的地址，并将返回地址保存到指定的寄存器中。
- `lw`: 从内存中加载一个字（32 位）到目标寄存器中。
- `sw`: 将一个字（32 位）存储到内存中。
- `li`: 将一个立即数加载到目标寄存器中。
- `mv`: 将一个寄存器的值复制到另一个寄存器中。
- `la`: 将一个标签的地址加载到目标寄存器中。
- `auipc`: 将 PC 的高 20 位与一个立即数相加，并将结果存储到目标寄存器中。
- `lui`: 将一个立即数的高 20 位加载到目标寄存器中。

```
void mystrcpy(char *s, char *t)
{
	while (*s++ = *t++)
		;
}
```

这是一个简单的 C 语言函数，它的作用是将字符串 `t` 复制到字符串 `s` 中，包括字符串末尾的空字符。以下是该函数的汇编代码及其注释：

```assembly
mystrcpy:
    # 函数 prologue：保存寄存器并分配栈空间
    addi    sp, sp, -16      # 为 s 和 t 分配 8 字节的空间
    sw      ra, 12(sp)       # 保存返回地址
    sw      s0, 8(sp)        # 保存 s0
    sw      s1, 4(sp)        # 保存 s1

    # 函数体
    add     s0, x0, a0       # 将 s 的地址保存到 s0 中
    add     s1, x0, a1       # 将 t 的地址保存到 s1 中
loop:
    lbu     t0, 0(s1)        # 将 t 所指向的字节读入 t0 中
    addi    s1, s1, 1        # 将 t 指针加 1，指向下一个字节
    sb      t0, 0(s0)        # 将 t0写入 s 所指向的地址中，同时将 s 指针加 1，指向下一个字节
    bnez    t0, loop         # 如果 t0 不为 0（即还没有到字符串末尾），则跳转到 loop

    # 函数 epilogue：恢复寄存器并返回
    lw      ra, 12(sp)       # 恢复返回地址
    lw      s0, 8(sp)        # 恢复 s0
    lw      s1, 4(sp)        # 恢复 s1
    addi    sp, sp, 16       # 释放栈空间
    ret                     # 返回
```

下面是各条指令的注释：

- `addi sp, sp, -16`: 分配 16 字节的栈空间，用于存储返回地址、寄存器和参数。
- `sw ra, 12(sp)`: 保存返回地址。
- `sw s0, 8(sp)`: 保存寄存器 s0。
- `sw s1, 4(sp)`: 保存寄存器 s1。
- `add s0, x0, a0`: 将 s 的地址保存到寄存器 s0 中。
- `add s1, x0, a1`: 将 t 的地址保存到寄存器 s1 中。
- `loop`: 标签，用于循环。
- `lbu t0, 0(s1)`: 从 t 所指向的地址读取一个字节，保存到寄存器 t0 中。
- `addi s1, s1, 1`: 将寄存器 s1 中的地址加 1，指向下一个字节。
- `sb t0, 0(s0)`: 将寄存器 t0 中的字节写入 s 所指向的地址中，并将寄存器 s0 中的地址加 1，指向下一个字节。
- `bnez t0, loop`: 如果寄存器 t0 中的值不为 0，则跳转到 loop 标签，继续循环。
- `lw ra, 12(sp)`: 恢复返回地址。
- `lw s0, 8(sp)`: 恢复寄存器 s0。
- `lw s1, 4(sp)`: 恢复寄存器 s1。
- `addi sp, sp, 16`: 释放栈空间。
- `ret`: 返回。

## 实际 `rvcc -S strcpy.c` 翻译汇编代码
```
	.text
mystrcpy:
	add	sp,sp,-32   // sp栈，实际分配内存32字节
	sw	s0,28(sp)   // 还要保存sp指针和返回地址等值
	add	s0,sp,32

    // 实际 s 和 t 参数那个先分配由编译器决定
	sw	a0,-20(s0)  // char *s  函数参数的内存地址
	sw	a1,-24(s0)  // char *t  
	nop
.L2:
	lw	a4,-24(s0)  // lw 从内存加载 t 的地址
	add	a5,a4,1     // t++
	sw	a5,-24(s0)  // sw 保存 t 到内存中

	lw	a5,-20(s0)  // lw 从内存加载 s 的地址
	add	a3,a5,1     // s++
	sw	a3,-20(s0)  // sw 保存 s 到内存中

	lbu	a4,0(a4)    // 将 t 所指向的字节读入 t0 中
	sb	a4,0(a5)    // *t = *s  将值复制
	lbu	a5,0(a5)   
	bnez	a5,.L2   // 如果等于0，继续循环 .L2
	nop

	lw	s0,28(sp)   // sp栈，回收内存
	add	sp,sp,32
	jr	ra

```

## 常见的 `x86` 汇编指令及其含义
当使用 `gcc -S` 命令时，会将 C 语言源代码转换成汇编代码。
以下是一些常见的 `x86` 汇编指令及其含义，以供参考：

- `mov`: 将数据从一个位置移动到另一个位置。
- `add`: 将两个数相加。
- `sub`: 从一个数中减去另一个数。
- `mul`: 将两个数相乘。
- `div`: 将一个数除以另一个数。
- `push`: 将一个值压入栈中。
- `pop`: 将一个值从栈中弹出。
- `call`: 跳转到一个函数。
- `ret`: 返回函数调用的地方。
- `jmp`: 无条件跳转到另一个位置。
- `cmp`: 比较两个值的大小。
- `je`: 如果相等则跳转。
- `jne`: 如果不相等则跳转。
- `jg`: 如果大于则跳转。
- `jge`: 如果大于等于则跳转。
- `jl`: 如果小于则跳转。
- `jle`: 如果小于等于则跳转。
- `lea`: 计算一个地址，但不访问这个地址。
- `movzx`: 将一个字节或字的无符号整数零扩展为另一个寄存器。
- `movsx`: 将一个字节或字的有符号整数符号扩展为另一个寄存器。
- `and`: 对两个数进行按位与操作。
- `or`: 对两个数进行按位或操作。
- `xor`: 对两个数进行按位异或操作。
- `not`: 对一个数进行按位取反操作。
- `shl`: 将一个数左移指定的位数。
- `shr`: 将一个数右移指定的位数。
- `inc`: 将一个数加 1。
- `dec`: 将一个数减 1。

## Milk-V Duo Examples 工程提供了在Linux环境下使用C/C++开发应用的一些例子，可以在`Milk-V Duo`设备上运行

## 开发环境 安装编译依赖的工具:
```
apt install wget git make
```

## 获取 Examples
```
git clone https://github.com/milkv-duo/duo-examples.git
```

## 加载编译环境

```
cd duo-examples
source envsetup.sh
```
- 第一次加载会自动下载所需的SDK包，大小为180M左右，下载完会自动解压到`duo-examples`下，解压后的目录名为`duo-sdk`，下次加载时检测到已存在该目录，就不会再次下载了
- *注: 如果因为网络原因无法完成SDK包的下载，请通过其他途径获取到`duo-sdk.tar.gz`包，手动解压到`duo-examples`目录下，重新`source envsetup.sh`*


## 设置环境变量：vim ~/.bashrc 生效环境变量：source ~/.bashrc

```
export PATH=~/duo-examples/duo-sdk/riscv64-linux-musl-x86_64/bin:$PATH
alias gcc=riscv64-unknown-linux-musl-gcc
alias g++=riscv64-unknown-linux-musl-g++
alias objdump=riscv64-unknown-linux-musl-objdump
```

### [使用 riscv-gcc 把简单的C代码，转换成汇编指令，方便学习](https://github.com/hongwenjun/riscv_learn/tree/main/CLang)

  [1]: https://262235.xyz/usr/uploads/2023/03/4102201498.webp
