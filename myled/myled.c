#include <stdio.h>
#include <unistd.h>

#include "ohos_init.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"

void MyLed(void)
{
    //初始化GPIO
    GpioInit();

    //设置GPIO_2的复用功能为普通GPIO
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_2, WIFI_IOT_IO_FUNC_GPIO_2_GPIO);

    //设置GPIO_2为输出模式
    GpioSetDir(WIFI_IOT_GPIO_IDX_2, WIFI_IOT_GPIO_DIR_OUT);

    printf("闪烁LED灯18次。\n");
    for (int i =0; i != 18; i++)
    {
        //设置GPIO_2输出高电平点亮LED灯
        GpioSetOutputVal(WIFI_IOT_GPIO_IDX_2, 1);

        //延时1s
        usleep(1000000);

        //设置GPIO_2输出低电平熄灭LED灯
        GpioSetOutputVal(WIFI_IOT_GPIO_IDX_2, 0);

        //延时1s
        usleep(1000000);
    }

    printf("长亮LED灯!\n");

    //设置GPIO_2输出高电平点亮LED灯
    GpioSetOutputVal(WIFI_IOT_GPIO_IDX_2, 1);
}

APP_FEATURE_INIT(MyLed);

#if(0)
004a30e8 <MyLed>:
  4a30e8:	f5c572ef          	jal	t0,3fa844 <__riscv_save_0>
  4a30ec:	00002417          	auipc	s0,0x2
  4a30f0:	2d842403          	lw	s0,728(s0) # 4a53c4 <_GLOBAL_OFFSET_TABLE_+0xc4>
  4a30f4:	401c                	lw	a5,0(s0)
  4a30f6:	1141                	addi	sp,sp,-16
  4a30f8:	000f44b7          	lui	s1,0xf4
  4a30fc:	c63e                	sw	a5,12(sp)
  4a30fe:	ef3ff0ef          	jal	ra,4a2ff0 <GpioInit>
  4a3102:	4581                	li	a1,0
  4a3104:	4509                	li	a0,2
  4a3106:	f63ff0ef          	jal	ra,4a3068 <IoSetFunc>
  4a310a:	4585                	li	a1,1
  4a310c:	4509                	li	a0,2
  4a310e:	f0bff0ef          	jal	ra,4a3018 <GpioSetDir>
  4a3112:	0000c517          	auipc	a0,0xc
  4a3116:	ac250513          	addi	a0,a0,-1342 # 4aebd4 <g_logLevelInfo+0x58>
  4a311a:	b92570ef          	jal	ra,3fa4ac <printf>
  4a311e:	4949                	li	s2,18
  4a3120:	24048493          	addi	s1,s1,576 # f4240 <__HEAP_BEGIN__+0xfb40>
  4a3124:	4585                	li	a1,1
  4a3126:	4509                	li	a0,2
  4a3128:	f19ff0ef          	jal	ra,4a3040 <GpioSetOutputVal>
  4a312c:	8526                	mv	a0,s1
  4a312e:	ae27d0ef          	jal	ra,420410 <usleep>
  4a3132:	4581                	li	a1,0
  4a3134:	4509                	li	a0,2
  4a3136:	f0bff0ef          	jal	ra,4a3040 <GpioSetOutputVal>
  4a313a:	8526                	mv	a0,s1
  4a313c:	197d                	addi	s2,s2,-1
  4a313e:	ad27d0ef          	jal	ra,420410 <usleep>
  4a3142:	fe0911e3          	bnez	s2,4a3124 <MyLed+0x3c>
  4a3146:	0000c517          	auipc	a0,0xc
  4a314a:	aa650513          	addi	a0,a0,-1370 # 4aebec <g_logLevelInfo+0x70>
  4a314e:	b5e570ef          	jal	ra,3fa4ac <printf>
  4a3152:	4585                	li	a1,1
  4a3154:	4509                	li	a0,2
  4a3156:	eebff0ef          	jal	ra,4a3040 <GpioSetOutputVal>
  4a315a:	4732                	lw	a4,12(sp)
  4a315c:	401c                	lw	a5,0(s0)
  4a315e:	00f70463          	beq	a4,a5,4a3166 <MyLed+0x7e>
  4a3162:	856530ef          	jal	ra,3f61b8 <__stack_chk_fail>
  4a3166:	0141                	addi	sp,sp,16
  4a3168:	f005706f          	j	3fa868 <__riscv_restore_0>
#endif