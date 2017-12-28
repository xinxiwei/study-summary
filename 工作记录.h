administrator
yl


192.168.20.45
255.255.255.0
192.168.20.1

218.30.19.40

codeblocks下载：
https://sourceforge.net/projects/codeblocks/files/Binaries/16.01/Windows/codeblocks-16.01mingw-setup.exe/download


tar -xzvf  -czvf


1.编译android
cd /work/forlinx/android_kk4.4.2_1.0.0
source  env.sh
source build/envsetup.sh
lunch  sabresd_6dq-eng
make -j8  2>&1 | tee build.log

四核： boot.img  recovery.img  system.img  u-boot-6q.bin
双核： boot.img  recovery.img  system.img  u-boot-6dl.bin


2.编译 kernel
./mk.sh   kernel menuconfig
./mk.sh   kernel  boot.img
./mk.sh   kernel  distclean

3.编译 uboot
四核：
./mk.sh  uboot  android
./mk.sh  uboot  distclean

双核：
./build_6dl_android.sh
编译出u-boot.imx  u-boot.imx 重命名为 u-boot-imx6dl.imx



win7  64位机  安装ADB时提示计算机丢失adbwinapi.dll 什么办?
将 adb.exe  AdbWinApi.dll  AdbWinUsbApi.dll  fastboot.exe 4个文件放在 c:/windows/system32   和 sysWOW64两个目录下面


win7系统怎么把两个盘合并成一个盘（图文） http://www.xitongcheng.com/jiaocheng/win7_article_26383.html

1.首先下载vmware虚拟机
2.下载ubuntu12.04 镜像



adb shell
ll /sys/bus/i2c/drivers
usb节点：sys/class/android_usb/android0    


TP调试 ：https://app.yinxiang.com/Home.action#n=510215db-5129-4c40-b832-d9fac2e23797&ses=4&sh=2&sds=5&
INPUT驱动查看
查看设备结点
ls -l /dev/input
查看设备信息
ls -l /proc/bus/input/
cat /proc/bus/input/devices
查看input class信息
ls /sys/class/input
 
 
 调试触摸tp有无反应

使用adb shell getevent 指令，如果手指触摸tp，会有相应的event打印出来，如下面的格式：


查看ubuntu版本信息：
lsb_release -a 



====================
apt-get update:
update
update 是同步 /etc/apt/sources.list 和 /etc/apt/sources.list.d 中列出的源的索引，这样才能获取到最新的软件包。

upgrade
upgrade 是升级已安装的所有软件包，升级之后的版本就是本地索引里的，因此，在执行 upgrade 之前一定要执行 update ,  这样才能是最新的。
===============
//i.MAX6 Quad 四核
//i.MAX6 DuaLite  双核


项目 device/fsl/sabresd_6dq


//panel:
480x640
mxc_lcdif.c
board-mx6q_sabresd.c
imx6_android_defconfig
     {
	/* 480x640 @ 60 Hz  ,  pixel clk @ 24.5MHz */
	"AT070-WVGA" ,  60 ,  480 ,  640 ,  40816 ,  50 ,  50 ,  3 ,  3 ,  50 ,  3 , 
	FB_SYNC_CLK_LAT_FALL , 
	FB_VMODE_NONINTERLACED , 
	0 , } , 
struct fb_videomode {
	const char *name;	/* optional */
	u32 refresh;		/* optional */
	u32 xres;
	u32 yres;
	u32 pixclock;
	u32 left_margin;
	u32 right_margin;
	u32 upper_margin;
	u32 lower_margin;
	u32 hsync_len;
	u32 vsync_len;
	u32 sync;
	u32 vmode;
	u32 flag;
};	
	SABRESD_DISP_RST_B
	SABRESD_DISP_PWR_EN
	
	
	

CONFIG_FB_MXC_TRULY_WVGA_SYNC_PANEL=y

//TP:
CONFIG_TOUCHSCREEN_FT5X06=y
CONFIG_TOUCHSCREEN_MAX11801=y



struct input_event {
struct timeval time; //按键时间
__u16 type; //类型，在下面有定义
__u16 code; //要模拟成什么按键
__s32 value;//是按下还是释放
};

禁用VMware的vmem文件:
新建一个虚拟机，VMWare会默认为其创建一个虚拟内存文件*.VMEM ,  这个文件会影响系统的磁盘性能，所以最好关闭它。
该当是找到*.vmx文件，在文件最后加入一行 mainMem.useNamedFile=FALSE ,  重新启动虚拟机，虚拟内存文件就没有了。


该文件实现了gpio的各种应用功能和向内核注册gpio的中断例程等功能。  
用户的驱动程序可调用gpio_request和gpio_free使用或释放该gpio，  
可以调用gpio_direction_input和gpio_direction_output函数设置gpio输入输出方向，  
调用gpio_get_value和gpio_set_value获取设置值。 

通过dir寄存器相应该gpio的位来设置gpio输入输出方向，为0，则设置成输出，为1，则设置出输入。  
该函数是设置成输出，故设置dir寄存器为0.  
value参数用于选择gpio设置成输出后该gpio输出的值。 


        gpio_request( IMX_GPIO_NR( 2 ,  3 ) ,  "close beeper" );
        gpio_direction_output( IMX_GPIO_NR( 2 ,  3 ) ,  0 );
        gpio_set_value( IMX_GPIO_NR( 2 ,  3 ) ,  0 ); 

		
		==================
GPIO及中断API函数( 2012-06-19 17:39:51 )转载▼
标签： 宋体 中断处理程序 调用 函数 硬件中断 	分类： Linux的学习
#include <linux/gpio.h> // 标准 GPIO_API
   int gpio_request( unsigned gpio ,  const char *label );
    获得并占有 GPIO port 的使用权，由参数 gpio 指定具体 port，非空的lables指针有助于诊断。主要是告诉内核这地址被占用了。当其它地方调用同一地址的gpio_request就会报告错误，该地址已被申请。在/proc/mem应该会有地址占用表描述。
这种用法的保护作用前提是大家都遵守先申请再访问，有一个地方没遵守这个规则，这功能就失效了。好比进程互斥，必需大家在访问临界资源的时候都得先获取锁一样，其中一个没遵守约定，代码就废了。
例1：void gpio_free( unsigned gpio )；//释放 GPIO port 的使用权，由gpio 指定具体 port。
例2：gpio_free( RK29_PIN0_PA0 );//释放GPIO0_A0
int gpio_direction_input( unsigned gpio );//返回0
例3：gpio_direction_input( RK29_PIN0_PA0 );//把GPIO0_A0设置为输入
int gpio_direction_output( unsigned gpio ,  int value )；//返回0
        例4：gpio_direction_output( RK29_PIN0_PA0 , GPIO_LOW );//把GPIO0_A0设置为输出口，且其电平拉低。    int gpio_get_value( unsigned gpio );//返回value
        例5：ret = gpio_get_value( RK29_PIN0_PA0 );// 读取GPIO0_A0的电平 , 并赋值给变量ret。
void gpio_set_value( unsigned gpio ,  int value );
例6：gpio_set_value( RK29_PIN0_PA0 ,  GPIO_HIGH );// 设置RK29_PIN0_PA0电平为高。
        int gpio_pull_updown( unsigned gpio , unsigned value );
        value = 0 ,  normal
        value = 1 ,  pull up
        value = 2 ,  pull down
        例7：gpio_pull_updown（RK29_PIN0_PA0，1）上拉
       int gpio_cansleep( unsigned gpio );
支持这种gpio的平台为了通过在这个函数中返回非零来区分其它类型的gpio（需要一个已经被  gpio_request申请的gpio号）为了访问这些端口，定义了另一组函数接口：
       int gpio_get_value_cansleep( unsigned gpio );
       void gpio_set_value_cansleep( unsigned gpio ,  int value );
        只能在允许睡眠的上下文中访问这些端口，比如线程化的中断中，
       static inline int gpio_is_valid( int number )//判断GPIO是否有效 , 有效返回0
       int gpio_export( unsigned gpio ,  bool direction_may_change );//返回0成功
       void gpio_unexport( );  //返回0成功
       int gpio_export_link( struct device *dev ,  const char *name ,  unsigned gpio ) 
//创建到导出GPIO的 sysfs link  ，第一个参数是在哪个dev下创建，第二个是参数名字，第三个是gpio编号 
 
中断部分的API:
  static inline int gpio_to_irq( unsigned gpio )
    例8：gpioToIrq = gpio_to_irq( RK29_PIN0_PA0 );// 把GPIO0_A0的PIN值转换为相应的IRQ值，并赋值给变量gpioToIrq。
   gpio_to_irq( )返回的中断编号可以传给request_irq( )和free_irq( )。
   irq_to_gpio( )返回的gpio编号通常用来调用gpio_get_value( )，比如在沿触发的中断中获取引脚的状态。有些平台不支持这种映射，应该避免调用映射函数
   static inline int __must_check request_irq( unsigned int irq ,  irq_handler_t handler ,  unsigned long flags ,  const char *name ,  void *dev )；
范例：irq是要申请的硬件中断号； handler是向系统登记的中断处理函数，是一个回调函数，中断发生时，系统调用这个函数，dev参数将被传递； flags是中断处理的属性，若设置SA_INTERRUPT，标明中断处理程序是快速处理程序，快速处理程序被调用时屏蔽所有中断，慢速处理程序不屏蔽；若设置SA_SHIRQ，则多个设备共享中断，*dev在中断共享时会用到，一般设置为这个设备的device结构本身或者NULL。 当flags发生时，触发中断。
       例9：static irqreturn_t PA0IntHandler( int irq ,  void *dev_id )
{
        printk( KERN_INFO "PA0IntHandler:irq=%d " , irq );
    return IRQ_HANDLED;
}
void main( void )
{
// 把GPIO0_A0的PIN值转换为相应的IRQ值，并赋值给变量gpioToIrq。
unsigned long req_flags = IRQF_TRIGGER_RISING;
int gpioToIrq = gpio_to_irq( RK29_PIN0_PA0 );
If( gpioToIrq != -1 ){
//注册PA0IntHandler中断处理函数，中断号是RK29_PIN0_PA0，设置为上升沿触发
    request_irq( gpioToIrq ,  PA0IntHandler , req_flags ,  "PA0_test" ,  NULL );
    }
}
      void free_irq( unsigned int irq ,  void *dev_id )//释放中断
irq: 释放的中断号   dev_id: 释放的dev_id
例10： free_irq( gpio_to_irq( RK29_PIN0_PA0 ) , NULL );// 释放GPIO0_A0中断。
     int set_irq_type( unsigned int irq ,  unsigned int type )
irq: 指定的中断号type   : 设置的中断类型
例11：set_irq_type( gpio_to_irq( RK2818_PIN_PA0 ) , IRQF_TRIGGER_LOW );//设置GPIO0_A0中断为低电平触发
      void disable_irq_nosync( unsigned int irq )
强行关闭指定中断，不会等待当前中断处理程序执行完毕。，立即返回
例12：disable_irq_nosync( gpio_to_irq( RK29_PIN0_PA0 ) );//关闭GPIO0_A0中断。
      void disable_irq( unsigned int irq )
将关闭硬件中断并等待（可能有的）中断处理完成才返回。
例13：disable_irq( gpio_to_irq( RK29_PIN0_PA0 ) );//关闭GPIO0_A0中断。
      void enable_irq( unsigned int irq )
使能一个指定的中断
例14： enable_irq( gpio_to_irq( RK29_PIN0_PA0 ) );//使能GPIO0_A0中断。
注意：使能IRQ和不使能IRQ应该配对使用。
    若调用enable_irq之前，并未关闭指定中断（如调用disable_irq_nosync 关闭指定中断），
    则调用enable_irq会报警告（WARNING: at kernel/irq/manage.c:274 enable_irq+0x48/0x68( )；Unbalanced enable for IRQ 58），此为正常现象。
     int enable_irq_wake( unsigned int irq )//返回0成功
     int disable_irq_wake( unsigned int irq )//返回0成功
   要enable和disable的次数相同
例15：static inline int enable_irq_wake( unsigned int irq )
{return set_irq_wake( irq ,  1 );
}
static inline int disable_irq_wake( unsigned int irq )
{
return set_irq_wake( irq ,  0 );
}
  void rk29_
  
  
  
  wifi:  
  http://www.android100.org/html/201403/17/5949.html
  
  
  http://www.embedu.org/Column/Column416.htm
  
  
  2：安装：

sudo -s ./jdk-6u20-linux-i586.bin
3：配置环境变量

sudo vim /etc/profile
最后添加

export JAVA_HOME=/home/bestupon/jdk1.6.0_20  
export JRE_HOME=/home/bestupon/jdk1.6.0_20/jre  
export CLASSPATH=.:$JAVA_HOME/lib:$JRE_HOME/lib:$CLASSPATH  
export PATH=$JAVA_HOME/bin:$JRE_HOME/bin:$PATH  
4：使环境变量生效

source  /etc/profile
5：检验是否安装

java  -version




float *copy1( float array[  ] , float c1[  ] , int n )
{
int i;
for( i=0;i<n;i++ )
c1[ i ]=array[ i ];
return c1;
}

int  main( int argc ,  char *argv[  ] )
{
int size=4;
float source[ 4 ]={1 , 2.3 , 4.5 , 6.7};
float first_copy[ 4 ];

float *fp;
fp = copy1( source , first_copy , size );
printf( "The first copy: %f , %f , %f , %f\n" , fp[ 0 ] , fp[ 1 ] , fp[ 2 ] , fp[ 3 ] );
return 0;
}


int a[  ]={1 , 6 , 18 , 19 , 13 , 5 , 2 , 20 , 3 , 4 , 12 , 14 , 15 , 16 , 17 , 7 , 8 , 9 , 10 , 11};
   long i , imax , len;
   len = sizeof( a )/sizeof( float );

    for( i=0;i<len;i++ ){
        if( a[ imax ]<a[ i ] )
            imax=i;
    }
    printf( "The maximum is the subscript of %d elements. value is =%d\n" , imax  , a[ imax-1 ] );
	
	
	
	
	
	    @Override
    public void PowerOn( ) throws InterruptedException {
        BDdriver.GpioSet( ConstClass.FPGA_1V2_CTR , ConstClass.GPIO_SET_ON );
        BDdriver.GpioSet( ConstClass.FPGA_2V5_CTR , ConstClass.GPIO_SET_ON );
        BDdriver.GpioSet( ConstClass.FPGA_3V3_CTR , ConstClass.GPIO_SET_ON );
    }//缁檉pga鏂數
    @Override
    public void PowerOff( ) throws InterruptedException {
        BDdriver.GpioSet( ConstClass.FPGA_3V3_CTR , ConstClass.GPIO_SET_OFF );
        BDdriver.GpioSet( ConstClass.FPGA_2V5_CTR , ConstClass.GPIO_SET_OFF );
        BDdriver.GpioSet( ConstClass.FPGA_1V2_CTR , ConstClass.GPIO_SET_OFF );
        Log.d( "FpgaBoardHal" , "3.3 , 2.5 , 1.2 POWER OFF" );
    }//缁檉pga涓婄數
	
	int retError = _GpioSet( device , value );
	 if( GpioSet( local_device ,  local_value ) < 0 )
    {
        LOGD( "In jni_GpioSet  GpioSet( device , value ) error." );
        return GpioSet_ecode;
    }
	
	
	
1.底层数据已采集上来，但数据有无丢失待验证
2.数据处理算法，傅立叶算法( 待验证 )，其它小算法( 已完成70% )

float *byte_to_float2(  unsigned char c[  ] , float b[  ] , int len )
{

 int i=0;
 int j=0;
 int k=0;

 for( i=0;i<len;i +=4 )
 {
    b[ j ] =(  c[ i ] << 24  ) +(  c[ i+1 ] << 16  ) +(  c[ i+2 ] << 8  ) + c[ i+3 ] ;
    j++;
 }
 for( k=0;k<j;k++ )
   printf( "111%e ,  \n" , b[ k ] );//25.607
 return b;
}

float *p2;
p2 = byte_to_float2( c1 , b , byte_num );
printf( "b2 value  : %e ,  %f\n" , b[ 0 ] , b[ 1 ] );


ret_value[ 0 ]=( av_max/n )*1000/20;
	ret_value[ 1 ]=( av_min/n )*1000/20;
	ret_value[ 2 ]= num_period;
	for( j=0;j<num_period;j++;i++ )
	{
		//for( i=0;i< num_period;i++ )
			ret_value[ i+3 ]= FinalData[ j+min_index ];
	}

	
	
	
数组名可以当指针用
float  a3[  ]={0.0};
float  *p;
p = a3;


提交人：辛希伟
日期：2017.
修改内容：


-1 :主设备打开异常
-2; 表示主设备配置参数异常
-3: 从设备打开异常
-4: 从设备未正常关闭
-5: 打开设备失败


http://blog.csdn.net/lin37985/article/details/38582027

//callback_backup.create_thread_cb( "SPI NATIVE" , press_thread_dial , NULL );
	pthread_create( &id ,  NULL ,  press_thread_dial ,  NULL );
	
	
#if 1
  float tempdata =0.0;
  memcpy( &tempdata , g_wave_length_buf3 , 4 );
  LOGD( "tempdata =%f " , tempdata );
#endif
			  
			  
真峰值：WALG_TDA_TruePeakValue
真峰峰值：WALG_TDA_TruePeakToPeakValue			  
真有效值：WALG_TDA_RMSValue  
最大值：WALG_TDA_Max
最小值：WALG_TDA_Min
均值：WALG_TDA_DCValue
      信号的直流分量，即数据的平均值
	  
偏度：WALG_TDA_Skew
方差：WALG_TDA_Variance

峰值因子：WALG_TDA_CrestFactor    波形是否有冲击，是波峰高度的指标
峭度指标：WALG_TDA_Kurtosis        波形的尖峭程度，有无冲击
波形因数：WALG_TDA_ShapeFactor    波形与正弦波相比，指偏移和畸变的程度
脉冲因子：WALG_TDA_ImpulseFactor   表示波的冲击性质的指标
裕度因子：WALG_TDA_ClearanceFactor   表示波的丰满程度的指标

平均幅值：
方根幅值：


 
  http://www.docin.com/p-448549682.html
set_adc_clk


vibrate_callback_backup.single_ch_callback( time_CH1_buf , g_waveLength );
vibrate_callback_backup.double_ch_callback( ret_CH1_Tbuf , ret_CH2_Tbuf , g_waveLength/2 );



yinlian@yinlian:/srv/work$ mkdir xinxiwei
yinlian@yinlian:/srv/work$ cd xinxiwei/
//yinlian@yinlian:/srv/work/xinxiwei$ git init
Initialized empty Git repository in /srv/work/xinxiwei/.git/
yinlian@yinlian:/srv/work/xinxiwei$ 
yinlian@yinlian:/srv/work/xinxiwei$ 
//yinlian@yinlian:/srv/work/xinxiwei$ git config user.name xinxiwei
//yinlian@yinlian:/srv/work/xinxiwei$ git config user.email lanyingx@126.com
//yinlian@yinlian:/srv/work/xinxiwei$ cat .git/config
[ core ]
	repositoryformatversion = 0
	filemode = true
	bare = false
	logallrefupdates = true
[ user ]
	name = xinxiwei
	email = lanyingx@126.com
yinlian@yinlian:/srv/work/xinxiwei$ cd .git
yinlian@yinlian:/srv/work/xinxiwei/.git$ ll
total 40
drwxrwxr-x 7 yinlian yinlian 4096 Jul 19 17:31 ./
drwxrwxr-x 3 yinlian yinlian 4096 Jul 19 17:30 ../
drwxrwxr-x 2 yinlian yinlian 4096 Jul 19 17:30 branches/
-rw-rw-r-- 1 yinlian yinlian  142 Jul 19 17:31 config
-rw-rw-r-- 1 yinlian yinlian   73 Jul 19 17:30 description
-rw-rw-r-- 1 yinlian yinlian   23 Jul 19 17:30 HEAD
drwxrwxr-x 2 yinlian yinlian 4096 Jul 19 17:30 hooks/
drwxrwxr-x 2 yinlian yinlian 4096 Jul 19 17:30 info/
drwxrwxr-x 4 yinlian yinlian 4096 Jul 19 17:30 objects/
drwxrwxr-x 4 yinlian yinlian 4096 Jul 19 17:30 refs/


//yinlian@yinlian:/srv/work/xinxiwei$ ssh-keygen -t rsa -C  lanyingx@126.com
Generating public/private rsa key pair.
Enter file in which to save the key( /home/yinlian/.ssh/id_rsa ): 
Created directory '/home/yinlian/.ssh'.
Enter passphrase( empty for no passphrase ): 
Enter same passphrase again: 
Your identification has been saved in /home/yinlian/.ssh/id_rsa.
Your public key has been saved in /home/yinlian/.ssh/id_rsa.pub.
The key fingerprint is:
93:e0:81:a4:68:57:92:02:7e:df:27:4a:36:61:e9:db lanyingx@126.com
The key's randomart image is:
+--[  RSA 2048 ]----+
|o  .o.           |
|.o +o..          |
|.ooo.+o          |
|. o +.oo .       |
|     *.oS.       |
|    o = o.       |
|     o E         |
|                 |
|                 |
+-----------------+
yinlian@yinlian:~$ cd .ssh
yinlian@yinlian:~/.ssh$ ls
id_rsa  id_rsa.pub
//yinlian@yinlian:~/.ssh$ cat id_rsa.pub 
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDPfszXXQzOvDxuZ24gFIDBT7OtOWZNlpQ3pnJTM4/Dt5KuY5lss07+/tP6rSdChgkCDxGvALMaOiLsMmWUgUOVWb/KVgrMbul3BhQ9+9xalSGzyqsffMow/WLOe3/I20JvpYXmbaQIJHVIrvTeW+ts3hR7dUAyup6Surt1xGgsmz37bsbVHEBF4jslodijdKo4ejDV7MmO/gJG0NkgD1en/nho/PA47HOpH0Z4WTMcd0z1i1kZW8xBm5Png3CtIPUh3bMNGAMxk4jsVzrQmOECpwEnmE5YoprkvLcS32vW7/JgESVrbhEGMRs6+ZOiytOzqST5F+2I7muAjaa15XGt lanyingx@126.com
//yinlian@yinlian:~/.ssh$ ssh -T git@github.com
The authenticity of host 'github.com( 192.30.253.113 )' can't be established.
RSA key fingerprint is 16:27:ac:a5:76:28:2d:36:63:1b:56:4d:eb:df:a6:48.
Are you sure you want to continue connecting( yes/no )? yes
Warning: Permanently added 'github.com , 192.30.253.113'( RSA ) to the list of known hosts.
Enter passphrase for key '/home/yinlian/.ssh/id_rsa': 
Hi xinxiwei! You've successfully authenticated ,  but GitHub does not provide shell access.

==========================================================
1.建立项目工程
     /srv/working/xinxiwei/code-server   
2.创建git库   
     mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-server$ git init
     Initialized empty Git repository in /srv/working/xinxiwei/code-server/.git/
3.向工程添加文件： 将文件添加入版本库文件索引中 , 表示记入了版本历史中--只是刷新了跟踪信息，并没有提交其内容到git的内容跟踪范畴之内
     mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-server$ git add UpdateService
4.查看差异
     mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-server$ git diff
5.查看版本库的当前状态
     mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-server$ git status
6.提交文件
     直接调用git commit命令，会提交填写注释。每一次提交，git就会为全局代码建议一个唯一的commit标识代码，用户可以通过git-revert命令恢复到任意一次提交时的代码
     mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-server$ git commit -m "Android.mk modify"
7.链接到git server
   // git remote add origin  git@192.168.1.69:midgit/ .git
8.push 代码到远程仓库
  //  git push -u origin develop
首次必须用-u，用于指定一个默认主机，上面命令将本地的develop分支推送到origin主机，同时指定origin为默认主机，后面就可以不加任何参数使用git push了
9.查看历史
mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-server$ git log
commit 76bea0af39317a1bcf50f7e2955d23f9ae98e79d
Author: liangqg <liangqg@giec.com>
Date:   Sat May 30 13:53:43 2015 +0800

    logandroid.mk
10.还原文件状态
     还原这些文件的索引状态，但并不会还原文件中的内容
git reset .

11.还原提交
git reset HEAD^   命令还原我们这次提交
git reset HEAD^
git reset  --hard    之前的某个commit            （这样代码也都会回到之前的状态）


12.同步代码
xinxiwei@szmid-Ubuntu:~/working/code$ mkdir code-test
xinxiwei@szmid-Ubuntu:~/working/test-code$ git config --global user.name   "mid01"             
xinxiwei@szmid-Ubuntu:~/working/test-code$ git config --global user.email   "mid01@giec.cn"
上面两个必须要，否则有以下问题
GitLab: Failed to authorize your Git request: internal API unreachable
fatal: The remote end hung up unexpectedly

xinxiwei@szmid-Ubuntu:~/working/code/code-test$ git clone git@192.168.1.69:mid01/code-test.git   如果远程仓库已经建立，直接clone，而不用再git init
Cloning into 'code-test'...
remote: Counting objects: 3 ,  done.
remote: Total 3( delta 0 ) ,  reused 0( delta 0 )
Receiving objects: 100%( 3/3 ) ,  done.

mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-test$ git branch
* master
mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-test$ git branch -a
* master
  remotes/origin/master
mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-test$ git fetch -a   上面命令将某个远程主机的更新，全部取回本地。
remote: Counting objects: 5 ,  done.
remote: Total 3( delta 0 ) ,  reused 0( delta 0 )
Unpacking objects: 100%( 3/3 ) ,  done.
From 192.168.1.69:mid01/code-test
   589624a..8479744  master     -> origin/master
* [ new branch ]      dev        -> origin/dev
mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-test$ git checkout -b dev origin/dev   取远程分支并分化一个新分支
Branch dev set up to track remote branch dev from origin.
Switched to a new branch 'dev'
mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-test$ git branch
* dev
  master
mid_sz@szmid-Ubuntu:/srv/working/xinxiwei/code-test$ git branch -a
* dev
  master
  remotes/origin/dev
  remotes/origin/master
  
13.分支合并
合并分支使用git merge命令，例如：
$git checkout master
$git merge xinxiwei           将xinxiwei 分支上的改动合并到master分支
  
给远程仓库创建一个master分支
在本地   git    push   origin   master

更新本地代码
git   fetch -a
git   merge  develop  origin/develop     合并远程分支的改动到本地 develop 分支


上传本地改动到远程仓库
xinxiwei@szmid-Ubuntu:~/working/code/code-test/code-test$ git push -u origin develop  上传本地当前 develop  分支代码 到远程

14.分支总结：
创建分支
git branch            显示本地版本库中所有的本地分支名称，　当前检出分支的前面会有星号。
git branch newname　　在当前检出分支上新建分支，名叫newname。
git checkout newname　　检出分支，即切换到名叫newname的分支。
git checkout –b newname master　　这个命令将上面两个命令合并：在master分支上创建分支newname分支并检出到该分支

显示分支
1. git branch  –a    显示全部branch , 包括远程和本地
2. git branch  –r    只显示远程branch
3. git branch  -v    显示每个分支上的最后一个commit

删除分支
git branch -D xinxiwei  强制删除分支
git branch –d xinxiwei 删除分支 xinxiwei ,  注意不能删除当前所在分支，需要转到别的分支上。

分支重命名
git branch  –m oldname  newname　　-m不会覆盖已有分支名称，即如果名为newname的分支已经存在，则会提示已经存在了。
　　                               -M就可以覆盖已有分支名称了，即会强制覆盖名为newname的分支，这种操作要谨慎
1.先重命名本地分支
         git   branch   -m  old   new
2.删除远程old 分支
         git   push   origin    :old
3.将新命名分支new 推送到远程
         git   push   origin     new




15.下载和上传总结：
下载：git pull  远程主机名  远程分支名 : 本地分支名        git pull origin xinxiwei:xinxiwei  将远程origin xinxiwei分支内容更新到本地服务 xinxiwei分支上
          git pull = git fetch + git merge
上传：git push  远程主机名  本地分支名 : 远程分支名

git push origin master的意思就是上传本地当前master分支代码到远程master分支。
git push 是上传本地所有分支代码到远程对应的分支上


移动和更改名字
$ git mv file_from    file_to 
$ git mv README.txt    README  ----更改名字

检查在工作区和 暂存区的当前文件状态 
$ git status  .
On branch xin
# Changes to be committed:                    表示已经 git add 过的文件，已经在暂存区的文件
#  ( use "git reset HEAD <file>..." to unstage )
#
#       modified:   666.txt
#
# Changes not staged for commit:          表示没有 git  add的文件，文件还在工作区
#  ( use "git add/rm <file>..." to update what will be committed )
#  ( use "git checkout -- <file>..." to discard changes in working directory )
#
#       deleted:    111.txt
#
# Untracked files:       表示没有跟踪的文件
#  ( use "git add <file>..." to include in what will be committed )
#
#       333.txt
#       444.txt

cherry-pick就是从不同的分支中捡出一个单独的commit，并把它和你当前的分支合并

git     cherry-pick    <commit id>
git     push  -u  origin    远程分支


如果一个文件已经add到暂存区，还没有commit，此时如果不想要这个文件了，有两种方法：
1，用版本库内容清空暂存区，git reset HEAD
2，只把特定文件从暂存区删除，git rm --cache  xx.txt


git   log  --stat        仅显示简要的增改行数统计，显示提交的有哪些修改文件
git   log  --oneline         是 git log --pretty=oneline 简与，列出文件所有改动历史
git   log  --author=xinxiwei    显示 xinxiwei的所有提交 



create_alg_tree
create_acc_branch  加速度分支
create_vel_branch  速度分支
create_dsp_branch  位移分支




( SDS_I0Bessel(( Coeff *	SDS_Sqrt( SIGLIB_ONE - SDS_Pow(( SIGLIB_TWO * z /( WindowLength - 1 ) ) ,  SIGLIB_TWO ) ) ) ) /	SDS_I0Bessel( Coeff ) );

http://blog.csdn.net/huqinwei987/article/details/50551273


adb pull data/data/com.example.featuredemo/shared_prefs  d:\



颜色高亮
下面的命令使颜色突出显示在控制台的Git。
[ jerry@CentOS project ]$ git config --global color.ui true
[ jerry@CentOS project ]$ git config --global color.status auto
[ jerry@CentOS project ]$ git config --global color.branch auto

设置默认编辑器
默认情况下，Git的使用系统默认取自VISUAL或EDITOR环境变量的编辑器。我们可以设定一个不同的使用git 配置。
[ jerry@CentOS project ]$ git config --global core.editor vim

设置默认合并工具
Git不会提供一个默认的合并工具整合到工作树冲突的更改。我们可以设置默认的合并工具，通过启用以下设置。
[ jerry@CentOS project ]$ git config --global merge.tool vimdiff



//double *pfeature_value=NULL;	
	pfeature_value =( double* )malloc( feature_num*sizeof( double ) );
	memset( pfeature_value , 0 , feature_num*sizeof( double ) );	
	feature_value( pData , data_len , pfeature_value );
    #if 0	
	for( i=0;i<feature_num;i++ )
	{
		LOGD( "pfeature_value[ %d ] = %f" , i , pfeature_value[ i ] );
	}
	#endif 	
	return pfeature_value;


1.加速度
1.针对 1.28K  , 2.56K ,  6.4K ,  12.8K 四种采样率， 目前采集AD原始数据值就已经缩小1倍，硬件工程师正在分析AD采样模式异常
2.针对其它采样率，加速度验证OK
3.针对下限0.16hz , 目前还存在问题，正在分析中，没有测试

2.速度
1.因为采样率为2.56K ,  采集的AD原始数据值就已经缩小1倍，经过硬件积分后值也缩小1倍

3.位移
1.因为采样率为2.56K ,  采集的AD原始数据值就已经缩小1倍，经过硬件积分后值也缩小1倍

adb pull data/data/com.iline.ihip.pressuregather/shared_prefs  d:\log



auto lo
iface lo inet loopback
#The primary network interface

auto eth0
iface eth0 inet static
address 192.168.20.49
netmask 255.255.255.0
gateway 192.168.20.1


androidstudio 快捷键：
Alt+回车 导入包,自动修正

Ctrl+N   查找类

Ctrl+Shift+N 查找文件

Ctrl+Alt+L  格式化代码

Ctrl+Alt+O 优化导入的类和包

Alt+Insert 生成代码(如get,set方法,构造函数等)

Ctrl+E或者Alt+Shift+C  最近更改的代码

Ctrl+R 替换文本

//Ctrl+F 查找文本

Ctrl+Shift+Space 自动补全代码

Ctrl+空格 代码提示

Ctrl+Alt+Space 类名或接口名提示

Ctrl+P 方法参数提示

Ctrl+Shift+Alt+N 查找类中的方法或变量

Alt+Shift+C 对比最近修改的代码

Shift+F6  重构-重命名

Ctrl+Shift+先上键

//Ctrl+X 删除行

//Ctrl+D 复制行

//Ctrl+/ 或 Ctrl+Shift+/  注释（// 或者 ）

Ctrl+J  自动代码

//Ctrl+E 最近打开的文件

Ctrl+H 显示类结构图

Ctrl+Q 显示注释文档

Alt+F1 查找代码所在位置

Alt+1 快速打开或隐藏工程面板

Ctrl+Alt+ left/right 返回至上次浏览的位置

Alt+ left/right 切换代码视图

Alt+ Up/Down 在方法间快速移动定位

//Ctrl+Shift+Up/Down 代码向上/下移动。

F2 或Shift+F2 高亮错误或警告快速定位

代码标签输入完成后，按Tab，生成代码。

选中文本，按Ctrl+Shift+F7 ，高亮显示所有该文本，按Esc高亮消失。

Ctrl+W 选中代码，连续按会有其他效果

选中文本，按Alt+F3 ，逐个往下查找相同文本，并高亮显示。

Ctrl+Up/Down 光标跳转到第一行或最后一行下

Ctrl+B 快速打开光标处的类或方法 

 

最常用快捷键

1.Ctrl＋E，可以显示最近编辑的文件列表

2.Shift＋Click可以关闭文件

//3.Ctrl＋[或]可以跳到大括号的开头结尾

4.Ctrl＋Shift＋Backspace可以跳转到上次编辑的地方

5.Ctrl＋F12，可以显示当前文件的结构

6.Ctrl＋F7可以查询当前元素在当前文件中的引用，然后按F3可以选择

7.Ctrl＋N，可以快速打开类

8.Ctrl＋Shift＋N，可以快速打开文件

9.Alt＋Q可以看到当前方法的声明

10.Ctrl＋W可以选择单词继而语句继而行继而函数

11.Alt＋F1可以将正在编辑的元素在各个面板中定位

12.Ctrl＋P，可以显示参数信息

13.Ctrl＋Shift＋Insert可以选择剪贴板内容并插入

14.Alt＋Insert可以生成构造器/Getter/Setter等

15.Ctrl＋Alt＋V 可以引入变量。例如把括号内的SQL赋成一个变量

16.Ctrl＋Alt＋T可以把代码包在一块内，例如try/catch

17.Alt＋Up and Alt＋Down可在方法间快速移动

 

 

下面的不是很有用

18.在一些地方按Alt＋Enter可以得到一些Intention Action，例如将”==”改为”equals()”

19.Ctrl＋Shift＋Alt＋N可以快速打开符号

20.Ctrl＋Shift＋Space在很多时候都能够给出Smart提示

21.Alt＋F3可以快速寻找

22.Ctrl＋/和Ctrl＋Shift＋/可以注释代码

23.Ctrl＋Alt＋B可以跳转到抽象方法的实现

24.Ctrl＋O可以选择父类的方法进行重写

25.Ctrl＋Q可以看JavaDoc

26.Ctrl＋Alt＋Space是类名自动完成

27.快速打开类/文件/符号时，可以使用通配符，也可以使用缩写

28.Live Templates! Ctrl＋J

29.Ctrl＋Shift＋F7可以高亮当前元素在当前文件中的使用

30.Ctrl＋Alt＋Up /Ctrl＋Alt＋Down可以快速跳转搜索结果

31.Ctrl＋Shift＋J可以整合两行

32.Alt＋F8是计算变量值

 

IntelliJ IDEA使用技巧一览表 

在使用 InelliJ IDEA 的过程中，通过查找资料以及一些自己的摸索，发现这个众多 Java 程序员喜欢的 IDE 里有许多值得一提的小窍门，如果能熟练的将它们应用于实际开发过程中，相信它会大大节省你的开发时间，而且随之而来的还会有那么一点点成就感：） Try it ！ 

 

1 、写代码时用 Alt-Insert （ Code|Generate… ）可以创建类里面任何字段的 getter 与 setter 方法。 

2 、右键点击断点标记（在文本的左边栏里）激活速查菜单，你可以快速设置 enable/disable 断点或者条件它的属性。

3 、 CodeCompletion （代码完成）属性里的一个特殊的变量是，激活 Ctrl-Alt-Space 可以完成在或不在当前文件里的类名。如果类没有引入则 import 标志会自动创建。

4 、使用 Ctrl-Shift-V 快捷键可以将最近使用的剪贴板内容选择插入到文本。使用时系统会弹出一个含有剪贴内容的对话框，从中你可以选择你要粘贴的部分。 

5 、利用 CodeCompletion （代码完成）属性可以快速地在代码中完成各种不同地语句，方法是先键入一个类名地前几个字母然后再用 Ctrl-Space 完成全称。如果有多个选项，它们会列在速查列表里。 

6 、用 Ctrl-/ 与 Ctrl-Shift-/ 来注释 / 反注释代码行与代码块。 

-/ 用单行注释标记（“ //… ”）来注释 / 反注释当前行或者选择地代码块。而 Ctrl-Shift-/ 则可以用块注释标记（“ ”）把所选块包围起来。要反注释一个代码块就在块中任何一个地方按 Ctrl-Shift-/ 即可。

7 、按 Alt-Q （ View|Context Info ）可以不需要移动代码就能查看当前方法地声明。连续按两次会显示当前所编辑的类名。 

8 、使用 Refactor|Copy Class… 可以创建一个所选择的类的“副本”。这一点很有用，比如，在你想要创建一个大部分内容都和已存在类相同的类时。 

9 、在编辑器里 Ctrl-D 可以复制选择的块或者没有所选块是的当前行。

10 、 Ctrl-W （选择字）在编辑器里的功能是先选择脱字符处的单词，然后选择源代码的扩展区域。举例来说，先选择一个方法名，然后是调用这个方法的表达式，然后是整个语句，然后包容块，等等。

11 、如果你不想让指示事件细节的“亮球”图标在编辑器上显示，通过按 Alt-Enter 组合键打开所有事件列表然后用鼠标点击它就可以把这个事件文本附件的亮球置成非活动状态。 

这样以后就不会有指示特殊事件的亮球出现了，但是你仍然可以用 Alt-Enter 快捷键使用它。

12 、在使用 CodeCompletion 时，可以用逗点（ . ）字符，逗号（，）分号（；），空格和其它字符输入弹出列表里的当前高亮部分。选择的名字会随着输入的字符自动输入到编辑器里。 

13 、在任何工具窗口里使用 Escape 键都可以把焦点移到编辑器上。 

Shift-Escape 不仅可以把焦点移到编辑器上而且还可以隐藏当前（或最后活动的）工具窗口。 

F12 键把焦点从编辑器移到最近使用的工具窗口。 

14 、在调试程序时查看任何表达式值的一个容易的方法就是在编辑器中选择文本（可以按几次 Ctrl-W 组合键更有效地执行这个操作）然后按 Alt-F8 。 

15 、要打开编辑器脱字符处使用的类或者方法 Java 文档的浏览器，就按 Shift-F1 （右键菜单的 External JavaDoc ）。
要使用这个功能须要把加入浏览器的路径，在“ General ”选项中设置（ Options | IDE Settings ），另外还要把创建的 Java 文档加入到工程中（ File | Project Properties ）。 

16 、用 Ctrl-F12 （ View | File Structure Popup ）键你可以在当前编辑的文件中快速导航。 
这时它会显示当前类的成员列表。选中一个要导航的元素然后按 Enter 键或 F4 键。要轻松地定位到列表中的一个条目，只需键入它的名字即可。 

17 、在代码中把光标置于标记符或者它的检查点上再按 Alt-F7 （右键菜单中的 Find Usages… ）会很快地查找到在整个工程中使用地某一个类、方法或者变量的位置。

18 、按 Ctrl-N （ Go to | Class… ）再键入类的名字可以快速地在编辑器里打开任何一个类。从显示出来的下拉列表里选择类。 
同样的方法你可以通过使用 Ctrl-Shift-N （ Go to | File… ）打开工程中的非 Java 文件。

19 、要导航代码中一些地方使用到的类、方法或者变量的声明，把光标放在查看项上再按 Ctrl-B 即可。也可以通过按 Ctrl 键的同时在查看点上单击鼠标键调转到声明处。 

20 、把光标放到查看点上再按 Ctrl-Alt-B 可以导航到一个抽象方法的实现代码。

21 、要看一个所选择的类的继承层次，按 Ctrl-H （ Browse Type Hierarchy ）即可。也可以激活编辑器中的继承关系视图查看当前编辑类的继承关系。22 、使用 Ctrl-Shift-F7 （ Search | Highlight Usages in File ）可以快速高亮显示当前文件中某一变量的使用地方。按 Escape 清除高亮显示。 

23 、用 Alt-F3 （ Search | Incremental Search ）在编辑器中实现快速查查找功能。 

在“ Search for: ”提示工具里输入字符，使用箭头键朝前和朝后搜索。按 Escape 退出。

24 、按 Ctrl-J 组合键来执行一些你记不起来的 Live Template 缩写。比如，键“ it ”然后按 Ctrl-J 看看有什么发生。

25 、 Introduce Variable 整合帮助你简化代码中复杂的声明。举个例子，在下面的代码片断里，在代码中选择一个表达式：然后按 Ctrl-Alt-V 。

26 、 Ctrl-Shift-J 快捷键把两行合成一行并把不必要的空格去掉以匹配你的代码格式。

27 、 Ctrl-Shift-Backspace （ Go to | Last Edit Location ）让你调转到代码中所做改变的最后一个地方。 

多按几次 Ctrl-Shift-Backspace 查看更深的修改历史。 

28 、用 Tools | Reformat Code… 根据你的代码样式参考（查看 Options | IDE Setting | Code Style ）格式化代码。 

使用 Tools | Optimize Imports… 可以根据设置（查看 Options | IDE Setting | Code Style | Imports ）自动“优化” imports （清除无用的 imports 等）。

29 、使用 IDEA 的 Live Templates | Live Templates 让你在眨眼间创建许多典型代码。比如，在一个方法里键入 

再按 Tab 键看有什么事情发生了。 

用 Tab 键在不同的模板域内移动。查看 Options | Live Templates 获取更多的细节。

30 、要查看一个文件中修改的本地历史，激活右键菜单里的 Local VCS | Show History… 。也许你可以导航不同的文件版本，看看它们的不同之处再回滚到以前的任何一个版本吧。 

使用同样的右键菜单条目还可以看到一个目录里修改的历史。有了这个特性你就不会丢失任何代码了。

31 、如果要了解主菜单里每一个条目的用途，把鼠标指针移到菜单条目上再应用程序框架的底部的状态栏里就会显示它们的一些简短描述，也许会对你有帮助。 

32 、要在编辑器里显示方法间的分隔线，打开 Options | IDE Settings | Editor ，选中“ Show method separators ”检查盒（ checkbox ）。 

33 、用 Alt-Up 和 Alt-Down 键可以在编辑器里不同的方法之间快速移动。 

34 、用 F2/Shift-F2 键在高亮显示的语法错误间跳转。 

用 Ctrl-Alt-Down/Ctrl-Alt-Up 快捷键则可以在编译器错误信息或者查找操作结果间跳转。

35 、通过按 Ctrl-O （ Code | Override Methods… ）可以很容易地重载基本类地方法。 

要完成当前类 implements 的（或者抽象基本类的）接口的方法，就使用 Ctrl-I （ Code | Implement Methods… ）。 

36 、如果光标置于一个方法调用的括号间，按 Ctrl-P 会显示一个可用参数的列表。

37 、要快速查看编辑器脱字符处使用的类或方法的 Java 文档，按 Ctrl-Q （在弹出菜单的 Show Quick JavaDoc 里）即可。 

38 、像 Ctrl-Q （ Show Quick JavaDoc 显示简洁 Java 文档）， Ctrl-P （ Show Parameter Info 显示参数信息）， Ctrl-B （ Go to Declaration 跳转到声明）， Shift-F1 （ External JavaDoc 外部 Java 文档）以及其它一些快捷键不仅可以在编辑器里使用，也可以应用在代码完成右键列表里。 

39 、 Ctrl-E （ View | Recent Files ）弹出最近访问的文件右键列表。选中文件按 Enter 键打开。 

40 、在 IDEA 中可以很容易地对你的类，方法以及变量进行重命名并在所有使用到它们的地方自动更正。 

试一下，把编辑器脱字符置于任何一个变量名字上然后按 Shift-F6 （ Refactor | Rename… ）。在对话框里键入要显示地新名字再按 Enter 。你会浏览到使用这个变量地所有地方然后按“ Do Refactor ”按钮结束重命名操作。 

41 、要在任何视图（ Project View 工程视图， Structure View 结构视图或者其它视图）里快速 

选择当前编辑地部分（类，文件，方法或者字段），按 Alt-F1 （ View | Select in… ）。 

42 、在“ new ”字符后实例化一个已知类型对象时也许你会用到 SmartType 代码完成这个特性。比如，键入 

再按 Ctrl-Shift-Space ：

43 、通过使用 SmartType 代码完成，在 IDEA 中创建接口的整个匿名 implementation 也是非常容易的，比如，对于一些 listener （监听器），可以键入 

 
Component component;  
component.addMouseListener(  
  new 
); 


然后再按 Ctrl-Shift-Space 看看有什么发生了。 

44 、在你需要设置一个已知类型的表达式的值时用 SmartType 代码完成也很有帮助。比如，键入 

String s = (    
再按 Ctrl-Shift-Space 看看会有什么出现。 

45 、在所有视图里都提供了速查功能：在树里只需键入字符就可以快速定位到一个条目。 

46 、当你想用代码片断捕捉异常时，在编辑器里选中这个片断，按 Ctrl-Alt-T （ Code | Surround with… ）然后选择“ try/catch ”。它会自动产生代码片断中抛出的所有异常的捕捉块。在 Options | File Templates | Code tab 中你还可以自己定制产生捕捉块的模板。 

用列表中的其它项可以包围别的一些结构。 

47 、在使用代码完成时，用 Tab 键可以输入弹出列表里的高亮显示部分。

不像用 Enter 键接受输入，这个选中的名字会覆盖掉脱字符右边名字的其它部分。这一点在用一个方法或者变量名替换另一个时特别有用。 

48 、在声明一个变量时代码完成特性会给你显示一个建议名。比如，开始键入“ private FileOutputStream ”然后按 Ctrl-Space 

////////notepad设置
Global Styles
Indent guideline style  缩进参考线的颜色
Brace highlight style 鼠标指针在框架左右时框架的颜色（如css中{}   js中的（））
Bad brace color  错误的框架的颜色（如js中{}里面有错误，这个{}的颜色）
Current line background colour  鼠标指向的当前行的背景颜色
Selected text colour  选中文本的颜色
Caret colour  鼠标指针的颜色
Line number margin  行号数字的颜色
Fold  隐藏代码按钮颜色
Fold margin  隐藏代码按钮上下背景颜色
Smart HighLighting  双击选择文字的背景颜色
Tags match highlighting  鼠标指针在当前标签时该标签的背景颜色
Tags attribute  鼠标指针在当前标签时属性和属性值的背景颜色
Active tab focused  出现连个文档界面时选中的文档的背景颜色
Active tab unfocused  出现连个文档界面时没选中的文档的背景颜色（另一视图的第一个文档）
Active tab text  当前文档的名称的颜色
Inactive tabs  未选中的文档的标签背景颜色




////
http://www.chinadmd.com/file/esoworpxwxsxtxcwxsirspp6wiwtapo6tstpus6s_3.html
ALT+F4  退出程序
// ctrl + T  将当前行与上一行交换位置
// ctrl + D  复制当前行到下方，或复制选中区域至其后, 复制并粘贴当行
//ctrl +Q   添加/删除注释( 单行或多行)    //
//ALT  +Q   区块添加/删除注释            /*  */

//ctrl +  up  将当前行上移一行
//ctrl +  down 将当前行下移一行
//ctrl + L    删除当前行

ctrl + j    合并所选的多行
ctrl + G    跳转至某行


ctrl + B    跳转到配对的括号
ctrl + H    打开替换搜索对话框

F2  跳至下一个标签处
F11  打开全屏显示
// ALT + 0  收缩所有折叠
// CTRL+ 0  展开所有层次折叠

//ALT + SHIFT + F    收缩当次折叠
//CTRL + SHIFT + F   展开当次折叠
CTRL + ALT + S  另存为
shift +TAB 删除缩进

1222
32
12


http://tools.android.com/knownissues 

39.513023] jzw;pwm_backlight_update_status:s_bl_en=1




正常调用流程_Init
1.FirFilterTable_Init
2.IIRFilterTable_Init //初始化IIR滤波器表
3.InvalidNum_Init


main.c
1.SysRuntimeContext_Create//运行时上下文对象
    PipeManager_Create 
        _Start====pipe_creat()   //PipeManager.c     
            pipe_creat()
            1._Get_InvalidNum //根据FIR和IIR频率获得无效点个数
            2.ACCWavePipe_Create //创建加速度波形管道,原始数据->FIR滤波->IIR滤波->处理后的数据
                1.FIRFilterNode_Create //创建FIR低通滤波器节点
                    1._GetFilterByFC
                    2.AlgNode_Create
                        _FirFilterCalc//FIR滤波算法
                        
                2.IIRFilterNode_Create //创建IIR高通滤波器节点
                    IIRFilterNode_Create //IIR滤波器节点创建
                    1._GetSampRate  //通过上限获取采样率
                    2._GetFilterByFC //通过采样率，下限，获取IIR滤波器表
                    3.AlgNode_Create//AlgNode 对象创建函数
                        _IIRFilterCalc//IIR滤波计算
                            _IIRCascadeFilter //IIR级联滤波
                3.ResultNode_Create //创建存放结果的节点
    
    
特征值计算
_CharCalc
1.AlgFun_Create
2.fnCalc  ===_Calc //计算特征值 AlgFuns.c





频谱计算
_SpectrumCalc
1.SpectrumNode_Create
2.fnCalc  ===_Calc //计算频谱 Spectrum.c


波形数据压缩
_DataCompress



一次积分
O1IntegFilterNode_Create
    _O1IntegCalc//一次积分算法
        _OrderOneIntegration
        fnInStation//将计算完的数据放到下个节点的buffer
    
    
    
    
二次积分
O2IntegFilterNode_Create
    _O2IntegCalc
        _OrderTwoIntegration
    
    
EN_WAVE_INDEX_ACC = 0,      // 00 加速度
    EN_WAVE_INDEX_VEL,          // 01 速度
    EN_WAVE_INDEX_DIS,          // 02 位移
    EN_WAVE_INDEX_ENV,          // 03 包络
    EN_WAVE_INDEX_LQ,           // 04 LQ
    EN_WAVE_INDEX_CALIBRATE,    // 05 校准
    EN_WAVE_INDEX_RAW,          // 06 原始波形
    EN_WAVE_INDEX_STARTSTOP,    // 07 启停机
    
、、、、、、、
定时器是我们需要经常处理的一种资源。那linux下面的定时器又是怎么一回事呢？其实，在linux里面有一种进程中信息传递的方法，那就是信号。这里的定时器就相当于系统每隔一段时间给进程发一个定时信号，我们所要做的就是定义一个信号处理函数。

在这之前，先看linux中定义好的一个结构体：struct itimerval;

struct itimerval {//结构体中又包含结构体timeval

struct timeval it_interval;//表示时间间隔，包括秒和微妙

struct timeval it_value;   //表示第一次定的时间，也包括秒和微妙， 这个时间为0后，会把上一个时间赋给他，已达到循环的目的，如果

//不需循环，则it_intval的秒和微妙都设为0；

};

struct timeval {

long tv_sec;   //表示秒

long tv_usec;   //表示微妙

};

看完上面两个结构体后，还需知道一个linux的信号函数signal(信号种类，函数)； 本例中，定时器（因为设定为了ITIMER_REAL）时间到了会发出一个SIGALRM信号，接收到此信号，会引发函数动作

#include <stdio.h>  
#include <time.h>  
#include <sys/time.h> //
包含setitimer()函数
#include <stdlib.h>  
#include <signal.h> 
//包含signal()函数
static int count = 0;  
static struct itimerval oldtv;  
void set_timer()  
{  
  struct itimerval itv;  
  itv.it_interval.tv_sec = 1;  设置为1秒
  itv.it_interval.tv_usec = 0;  
  itv.it_value.tv_sec = 1;  
  itv.it_value.tv_usec = 0;  
  setitimer(ITIMER_REAL, &itv, &oldtv);  //此函数为linux的api,不是c的标准库函数
}  
void signal_handler(int m)  
{  
  count ++;  
  printf("%d\n", count);  
}  
int main()  
{  
  signal(SIGALRM, signal_handler);  //注册当接收到SIGALRM时会发生是么函数；
  set_timer();  //启动定时器，
  while(count < 10000);  
  exit(0);  
  return 1;  
}


sublime -text3 快捷键
//Ctrl+M 光标移动至括号内结束或开始的位置。

//Ctrl+Enter 在下一行插入新行。举个栗子：即使光标不在行尾，也能快速向下插入一行。
//Ctrl+Shift+Enter 在上一行插入新行。举个栗子：即使光标不在行首，也能快速向上插入一行。

//Ctrl+[ 选中代码，按下快捷键，折叠代码。
//Ctrl+] 选中代码，按下快捷键，展开代码。
    
//Ctrl+K+0 展开所有折叠代码。
//Ctrl+← 向左单位性地移动光标，快速移动光标。
//Ctrl+→ 向右单位性地移动光标，快速移动光标。
    
//Ctrl+↑ 将光标所在行和上一行代码互换（将光标所在行插入到上一行之前）。
//Ctrl+↓ 将光标所在行和下一行代码互换（将光标所在行插入到下一行之后）。
    
编辑类
//Ctrl+D 复制光标所在整行，插入到下一行。
//Ctrl+L 删除整行。
//alt+ q 注释单行。
//alt+ w 注释多行。

搜索类
//Ctrl+F 打开底部搜索框，查找关键字。
//Ctrl+shift+F 在文件夹内查找，与普通编辑器不同的地方是sublime允许添加多个文件夹进行查找，略高端，未研究。
//Ctrl+P 输入当前项目中的文件名，快速搜索文件
/* Ctrl+G 打开搜索框，自动带：，输入数字跳转到该行代码。
Ctrl+R 打开搜索框，自动带@，输入关键字，查找文件中的函数名。
Ctrl+Shift+P 打开命令框。场景栗子：打开命名框，输入关键字，调用sublime text或插件的功能，例如使用package安装插件
Esc 退出光标多行选择，退出搜索框，命令框等。 */
//F11 全屏模式
{ "keys": ["Alt+q"], "command": "toggle_comment", "args": { "block": false } },
{ "keys": ["Alt+w"], "command": "toggle_comment", "args": { "block": true } },
{ "keys": ["ctrl+d"], "command": "duplicate_line" },
{ "keys": ["ctrl+l"], "command": "run_macro_file", "args": {"file": "res://Packages/Default/Delete Line.sublime-macro"} },
{ "keys": ["ctrl+up"], "command": "swap_line_up" },
{ "keys": ["ctrl+down"], "command": "swap_line_down" },
{ "keys": ["ctrl+["], "command": "fold" },
{ "keys": ["ctrl+]"], "command": "unfold" },

Atom快捷键：
显示缩进竖线：Setting -> Editor Setting -> 勾选 Show Indent Guide
CTRL + G : 光标移动到指定位置
CTRL + p : 查找文件
CTRL + r : 当前文档内搜索变量或函数名
CTRL + F : buffer中查找
CTRL + SHIFT + R: 工程内搜索
CTRL + SHIFT + D: 复制当前行到下一行
CTRL + SHIFT + F: 在整个工程中查找
CTRL + SHIFT + K: 删除当前行
CTRL + SHIFT + U: 调出编码方式

CTRL + UP : 当前行向上
CTRL + ALT + [ : 折叠代码。
CTRL + ALT + ] : 展开代码。
CTRL + / : 注释行



插件：
autocomplete-python — 你懂得，更加细致

主题：
monokai-flat：  用过sublime flat主题的都知道


uC/OS-II是一种基于优先级的可抢占的硬实时内核
uC/OS-II 中最多可以支持64 个任务，分别对应优先级0～63，其中0 为最高优先级。63为最低级，系统保留了4个最高优先级的任务和4个最低优先级的任务，所有用户可以使用的任务数有56个。
uC/OS-II提供了任务管理的各种函数调用，包括创建任务，删除任务，改变任务的优先级，任务挂起和恢复等。
系统初始化时会自动产生两个任务：一个是空闲任务，它的优先级最低，该任务仅给一个整型变量做累加运算；另一个是系统任务，它的优先级为次低，该任务负责统计当前cpu的利用率。
时间管理
uC/OS-II的时间管理是通过定时中断来实现的，该定时中断一般为10毫秒或100毫秒发生一次，时间频率取决于用户对硬件系统的定时器编程来实现。中断发生的时间间隔是固定不变的，该中断也成为一个时钟节拍。
uC/OS-II要求用户在定时中断的服务程序中，调用系统提供的与时钟节拍相关的系统函数，例如中断级的任务切换函数，系统时间函数。
内存管理
在ANSI C中是使用malloc和free两个函数来动态分配和释放内存。但在嵌入式实时系统中，多次这样的操作会导致内存碎片，且由于内存管理算法的原因，malloc和free的执行时间也是不确定。
uC/OS-II中把连续的大块内存按分区管理。每个分区中包含整数个大小相同的内存块，但不同分区之间的内存块大小可以不同。用户需要动态分配内存时，系统选择一个适当的分区，按块来分配内存。释放内存时将该块放回它以前所属的分区，这样能有效解决碎片问题，同时执行时间也是固定的。

μC/OS-II是一个多任务的操作系统


、、、、、、、、、、、
消息队列
//1 OSQCreate()
该函数用于建立一个消息队列。任务或中断可以通过消息队列向一个或多个任务发送消息。消息的含义是和具体的 
应用密切相关的。

函数原型：OS_EVENT *OSQCreate (void **start, INT8U size);
参数说明：
start 是消息内存区的首地址，消息内存区是一个指针数组。
size 是消息内存区的大小。
返回值：
OSQCreate() 函数返回一个指向消息队列控制块的指针。如果没有空闲的控制块，OSQCreate() 函数返回空指针。

//2 OSQPend()
该函数用于任务等待消息。消息通过中断或任务发送给需要的任务。消息是一个指针变量，在不同的应用中消息的 
具体含义不同。如果调用 OSQPend() 函数时队列中已经存在消息，那么该消息被返回给 OSQPend() 函数的调用者，该 
消息同时从队列中清除。如果调用 OSQPend() 函数时队列中没有消息，OSQPend() 函数挂起调用任务直到得到消息或 
超出定义的超时时间。如果同时有多个任务等待同一个消息，μC/OS-Ⅱ默认最高优先级的任务取得消息。一个由 
OSTaskSuspend() 函数挂起的任务也可以接受消息，但这个任务将一直保持挂起状态直到通过调用 OSTaskResume() 函 
数恢复任务的运行。

函数原型：void *OSQPend (OS_EVENT *pevent, INT16U timeout, INT8U *err);
参数说明：
pevent 是指向消息队列的指针，该指针的值在建立该队列时可以得到。（参考 OSQCreate() 函数）。
timeout 允许一个任务以指定数目的时钟节拍等待消息。超时后如果还没有得到消息则恢复成就绪状态。如 
果该值设置成零则表示任务将持续地等待消息，最大的等待时间为65535个时钟节拍。这个时间长度并不是非常严格的 
，可能存在一个时钟节拍的误差。
err 是指向包含错误码的变量的指针。

OSQPend() 函数返回的错误码可能为下述几种：
* OS_NO_ERR ：消息被正确地接受。
* OS_TIMEOUT ：消息没有在指定的时钟周期数内接收到消息。
* OS_ERR_PEND_ISR ：从中断调用该函数。虽然规定了不允许从中断中调用该函数，但μC/OS-Ⅱ仍然包 
含了检测这种情况的功能。
* OS_ERR_EVENT_TYPE ：pevent 不是指向消息队列的指针。

返回值：
OSQPend() 函数返回取得的消息并将 *err 置为 OS_NO_ERR。如果没有在指定数目的时钟节拍内接受到消息，OSQPend 
() 函数返回空指针并将 *err 设置为 OS_TIMEOUT。

OSQPost()

该函数用于向消息队列发送消息。消息是一个指针长度的变量，在不同的应用中消息的含义也可能不同。如果队列 
中已经存满消息，则此调用返回错误码。如果有任何任务在等待队列中的消息，则最高优先级的任务将得到这个消息。 
如果等待消息的任务优先级比发送消息的任务优先级高，那么高优先级的任务将在得到消息后立即抢占当前任务执行， 
也就是说，将发生一次任务切换。消息是以先入先出（FIFO）方式进入队列的，即先进入队列的消息先被传递给任务。

函数原型：INT8U OSQPost(OS_EVENT *pevent, void *msg);

参数说明：
pevent 是指向即将接受消息的消息队列的指针。该指针的值在建立队列时可以得到。（参考 OSQCreate() 
函数）。
msg 是即将发送给队列的消息。不允许传递一个空指针。

返回值：

OSQPost() 函数的返回值为下述之一：

* OS_NO_ERR ：消息成功地放到消息队列中。

* OS_Q_FULL ：消息队列已满。

* OS_ERR_EVENT_TYPE ：pevent 不是指向消息队列的指针。

5 OSQFlush()

该函数用于清空消息队列。

函数原型：INT8U *OSQFlush（OS_EVENT *pevent）;

参数说明：pevent 是指向消息队列的指针。该指针的值在建立队列时可以得到。（参考 OSQCreate() 函数）。

返回值：

OSQFlush() 函数的返回值为下述之一：

* OS_NO_ERR ：消息队列被成功清空

* OS_ERR_EVENT_TYPE ：试图清除不是消息队列的对象

6 OSQQuery()

该函数用来取得消息队列的信息。用户程序必须建立一个 OS_Q_DATA 的数据结构，该结构用来保存从消息队列的 
控制块得到的数据。通过调用该函数可以知道是否有任务在等待消息、有多少个任务在等待消息、队列中有多少消息以 
及消息队列可以容纳的消息数。OSQQuery() 函数还可以得到即将被传递给任务的消息。

函数原型：INT8U OSQQuery(OS_EVENT *pevent, OS_Q_DATA *pdata);

参数说明：pevent 是指向消息队列的指针。该指针的值在建立消息队列时可以得到。（参考 OSQCreate() 函数）。

pdata 是指向 OS_Q_DATA 数据结构的指针，该数据结构包含下述成员：

void *OSMsg; /* 下一个可用的消息 */

INT16U OSNMsgs; /* 队列中的消息数目 */

INT16U OSQSize; /* 消息队列的大小 */

INT8U OSEventTbl[OS_EVENT_TBL_SIZE]; /* 消息队列的等待队列 */

INT8U OSEventGrp；

返回值：

OSQQuery() 函数的返回值为下述之一：

* OS_NO_ERR ：调用成功

* OS_ERR_EVENT_TYPE ：pevent 不是指向消息队列的指针。

7 OSQDel()

该函数用于删除指定的消息队列。

任务管理
//1 OSTaskCreate()
建立一个新任务。任务的建立可以在多任务环境启动之前，也可以在正在运行的任务中建立。中断处理程序中不能 
建立任务。一个任务可以为无限循环的结构。

函数原型：INT8U OSTaskCreate(void (*task)(void *pd), void *pdata, OS_STK *ptos, INT8U prio);

参数说明：
task 是指向任务代码首地址的指针。
pdata 指向一个数据结构，该结构用来在建立任务时向任务传递参数(通常为NULL)
ptos 指向任务堆栈栈顶的指针，通常写我们把创建的任务的堆栈数组的首地址
prio 任务的优先级

返回值：
OSTaskCreate() 的返回值为下述之一：
* OS_NO_ERR：函数调用成功。
* OS_PRIO_EXIST：具有该优先级的任务已经存在。
* OS_PRIO_INVALID：参数指定的优先级大于OS_LOWEST_PRIO。
* OS_NO_MORE_TCB：系统中没有OS_TCB可以分配给任务了。


//OSTaskSuspend()
无条件挂起一个任务。任务挂起后，系统会重新进行任务调度，运行下一个优先级最高的就绪任务。唤 
醒挂起任务需要调用函数OSTaskResume()。

函数原型：INT8U OSTaskSuspend(INT8U prio);

参数说明：
prio为指定要获取挂起的任务优先级，也可以指定参数 OS_PRIO_SELF，挂起任务本身。此时，下一个优先 
级最高的就绪任务将运行。

返回值：
OSTaskSuspend() 的返回值为下述之一：
* OS_NO_ERR：函数调用成功。
* OS_TASK_SUSPEND_IDLE：试图挂起μC/OS-II中的空闲任务（Idle task）。此为非法操作。
* OS_PRIO_INVALID：参数指定的优先级大于 OS_LOWEST_PRIO 或没有设定 OS_PRIO_SELF 的值。
* OS_TASK_SUSPEND_PRIO：要挂起的任务不存在。


//3 OSTaskResume()
唤醒一个用 OSTaskSuspend() 函数挂起的任务。OSTaskResume() 也是唯一能“解挂”挂起任务的函数。
函数原型：INT8U OSTaskResume(INT8U prio);
参数说明：
prio指定要唤醒任务的优先级。

返回值：
OSTaskResume() 的返回值为下述之一：
* OS_NO_ERR：函数调用成功。
* OS_TASK_RESUME_PRIO：要唤醒的任务不存在。
* OS_TASK_NOT_SUSPENDED：要唤醒的任务不在挂起状态。
* OS_PRIO_INVALID：参数指定的优先级大于或等于OS_LOWEST_PRIO。



//OSTaskDel
信号量

1 OSSemCreate()

该函数建立并初始化一个信号量，信号量的作用如下：

* 允许一个任务和其他任务或者中断同步

* 取得设备的使用权

* 标志事件的发生

函数原型：OS_EVENT *OSSemCreate(INT16U value);

参数说明：value 参数是所建立的信号量的初始值，可以取0到65535之间的任何值。

返回值：

OSSemCreate() 函数返回指向分配给所建立的信号量的控制块的指针。如果没有可用的控制块，OSSemCreate() 函数返 
回空指针。

2 OSSemPend()

该函数用于任务试图取得设备的使用权、任务需要和其他任务或中断同步、任务需要等待特定事件的发生的场合。 
如果任务调用OSSemPend() 函数时，信号量的值大于零，OSSemPend() 函数递减该值并返回该值。如果调用时信号量值 
等于零，OSSemPend() 函数将任务加入该信号量的等待队列。OSSemPend() 函数挂起当前任务直到其他的任务或中断设 
置信号量或超出等待的预期时间。如果在预期的时钟节拍内信号量被设置，μC/OS-Ⅱ默认让最高优先级的任务取得信 
号量并回到就绪状态。一个被OSTaskSuspend() 函数挂起的任务也可以接受信号量，但这个任务将一直保持挂起状态直 
到通过调用OSTaskResume() 函数恢复该任务的运行。

函数原型：void OSSemPend ( OS_EVNNT *pevent, INT16U timeout, int8u *err );

参数说明：pevent 是指向信号量的指针。该指针的值在建立该信号量时可以得到。（参考OSSemCreate() 函数）。

timeout 允许一个任务在经过了指定数目的时钟节拍后还没有得到需要的信号量时恢复就绪状态。如果该值 
为零表示任务将持续地等待信号量，最大的等待时间为65535个时钟节拍。这个时间长度并不是非常严格的，可能存在 
一个时钟节拍的误差。

err 是指向包含错误码的变量的指针，返回的错误码可能为下述几种：

* OS_NO_ERR ：信号量不为零。

* OS_TIMEOUT ：信号量没有在指定数目的时钟周期内被设置。

* OS_ERR_PEND_ISR ：从中断调用该函数。虽然规定了不允许从中断调用该函数，但μC/OS-Ⅱ仍然包含 
了检测这种情况的功能。

* OS_ERR_EVENT_TYPE ：pevent 不是指向信号量的指针。

返回值：无

3 OSSemPost()

该函数用于设置指定的信号量。如果指定的信号量是零或大于零，OSSemPost() 函数递增该信号量的值并返回。如 
果有任何任务在等待该信号量，则最高优先级的任务将得到信号量并进入就绪状态。任务调度函数将进行任务调度，决 
定当前运行的任务是否仍然为最高优先级的就绪任务。

函数原型：INT8U OSSemPost（OS_EVENT *pevent）;

参数说明：pevent 是指向信号量的指针。该指针的值在建立该信号量时可以得到。（参考OSSemCreate() 函数）。

返回值：

OSSemPost() 函数的返回值为下述之一：

* OS_NO_ERR ：信号量被成功地设置

* OS_SEM_OVF ：信号量的值溢出

* OS_ERR_EVENT_TYPE ：pevent 不是指向信号量的指针

时间

1 OSTimeDly()

该函数用于将一个任务延时若干个时钟节拍。如果延时时间大于0，系统将立即进行任务调度。延时时间的长度可 
从0到65535个时钟节拍。延时时间0表示不进行延时，函数将立即返回调用者。延时的具体时间依赖于系统每秒钟有多 
少个时钟节拍（由文件OS_CFG.H中的OS_TICKS_PER_SEC宏来设定）。

函数原型：void OSTimeDly (INT16U ticks);

参数说明：ticks 为要延时的时钟节拍数。

返回值：无

2 OSTimeDlyHMSM()

该函数用于将一个任务延时若干时间。延时的单位是小时、分、秒、毫秒。调用 OSTimeDlyHMSM() 后，如果延时 
时间不为0，系统将立即进行任务调度。

函数原型: INT8U OSTimeDlyHMSM (INT8U hours，INT8U minutes，INT8U seconds，INT16U milli);

参数说明：hours 为延时小时数，范围从0-255。

minutes 为延时分钟数，范围从0-59。

seconds 为延时秒数，范围从0-59

milli 为延时毫秒数，范围从0-999。

需要说明的是，操作系统在处理延时操作时都是以时钟节拍为单位的，实际的延时时间是时钟节拍的整数倍。如果 
系统时钟节拍的间隔是10ms，而设定延时为5ms的话，则不会产生延时操作；而如果设定延时为15ms，则实际的延时是 
两个时钟节拍，也就是20ms。

返回值：

OSTimeDlyHMSM() 的返回值为下述之一：

* OS_NO_ERR：函数调用成功。

* OS_TIME_INVALID_MINUTES：参数错误，分钟数大于59。

* OS_TIME_INVALID_SECONDS：参数错误，秒数大于59。

* OS_TIME_INVALID_MILLI：参数错误，毫秒数大于999。

* OS_TIME_ZERO_DLY：四个参数全为0。


WS1.5:  http://server02/svn/04_Development/29_iCMS/V1.5/v1.5.1/03_Design
Ihip: http://server02:8080/svn/04_Development/28_iHIP/01_中船重工

create_alg_tree //创建算法树
create_vel_branch //速度算法分支创建
create_alg_node //算法节点创建
run_alg_tree //运行算法树（当有采集的数据到来时）

result_node_create //创建结果节点
run_result_node //算法分支结果节点
query_alg_tree //查询算法树是否运算完成

calc_vel_spec_energy //计算频带能量
access_wave //存取波形数据
calc_band_energy //计算频带能量

daqer_init--->_daqer_main--->_daqer_on_message--->_daqer_start_daq--->vibration_init（初始化振动采集硬件）--->_vibration_spi_init( GPIO,DMA)
                                                                      create_alg_tree（创建算法树）
                                                                      vibration_start（直接启动采集）--->_vibration_on_data_arrive(数据单位转换)
                                                  _daqer_halt_daq（停止采集）--->_daqer_stop_peripheral(停止外围设备)
                                                  _daqer_on_data_arrive(振动数据到达)--->run_calibration(振动校准，计算出增益，偏移)
                                                  
                                                  
                                                                                         query_alg_tree(查询算法树是否计算完成)
                                                                                         alg_tree_run_non_real_time_algorithm（非常规特征值计算）--->calc_vel_spec_energy(计算频带能量)--->calc_band_energy
                                                  _daqer_start_calibrate(启动校准采集)

                                                                                         
create_alg_tree--->create_acc_branch(创建加速度算法分支)--->create_iir_node(创建IIR高通滤波器节点)--->create_alg_node(创建算法节点)--->run_iir_filter(运行IIR滤波器)--->cascade_iir_filter(IIR级联滤波)                                               
                                                            result_node_create（创建结果节点）--->create_alg_node(创建算法节点)--->run_result_node(运行结果节点，里面计算各种特征值)
                                                                                                  if_save_wave（判断是否需要保存波形）
                                                            
                                                            
                                                            
sync_daq_init(同步采集模块初始化)



init_commer-->commor（通信器线程处理函数）--->dn_serial_handle_rx_frame(处理收到的HDLC帧)
              dn_ipmt_init(ip层初始化函数)
runner_init-->_runner_main  
                                                            
worker_init--->_worker_main-->  _worker_on_start-->sm_init-->daq_state_init(采集态初始化函数)-->_daq_state_enter-->_daq_on_temp_daq
                                _worker_on_message--->sm_send_message                                                          
          

_daq_on_temp_daq(温度采集完成时间处理函数)-->cm_get_utc_seconds(获取网络时间)
                                             get_dev_temp（获取仪器自身温度）
                                             cm_get_battery_voltage（获取电池电压）
                                             con_noti_hr（温度采集完成后，发送健康报告）


temperature_start（启动温度采集）--->_temperature_timer_init
                                     _temperature_on_data_arrive--->temperature_stop
                                     
temperature_get_data-->_temperature_convert(温度单位转换)
                       

vbat_init--->_vbat_io_init
             _vbat_adc_init


             
             
             
             
 _init_state_enter-->_recover(唤醒后恢复数据)-->_recover_from_reset(重启唤醒或系统第一次上电)  
                                                _recover_from_exti (外部中断唤醒)
                                                _recover_from_alarm(闹钟定制唤醒)
             
             

//IIR高通滤波：
由所计算的波形的高端频率和低端频率确定，对应相应的滤波器系数
//作用为高通滤波，滤掉低频波形，为达到滤波器的稳定，要先预热一段时间，处理一定长度的数据，但这些数据不能使用，需要被扔掉，这些数据称为无效数据，无效数据个数由所求波形的上端截至频率和下端截止频率共同确定

//FIR低通滤波：
FIR滤波器由波形的高端截止频率确定，可能有1~3 个滤波器级联组成，//作用包括滤波和降采样
根据抽样点数抽样运算

//一次积分：
作用是把加速度波形转换为速度波形

//二次积分：
作用是把加速度波形转换为位移波形

//加速度包络算法：
在一定的波形数据间隔内，求取一个绝对值最大的波形数据点，把该绝对值作为包络波形的点
最后得到包络波形，波形数据间隔由包络带宽所确定


arm keil下载对应的标准外设库包MDK5 Software Packs ：http://www.keil.com/dd2/Pack/#/eula-container

MOTE命令：
get mode
help
info   

keil5编译优化时间：
Project -> Options for Target -> C/C++下面勾选“Optimize for Time”优化时间，即优化代码中费时的地方。
Project--Options--Output中取消Debug Information 和 Browse Infomation



FRAM SRAM EEPROM FLASH区别：
EEPROM 可以按“位”擦写，而FLASH 只能一大片一大片的擦。
EEPROM 一般容量都不大，如果大的话，EEPROM相对与FLASH 就没有价格上的优势了。市面上卖的stand alone 的EERPOM 一般都是在64KBIT 以下，而FLASH 一般都是8MEG BIT 以上（NOR 型）。
读的速度的话，应该不是两者的差别，只是EERPOM一般用于低端产品，读的速度不需要那么快，真要做的话，其实也是可以做的和FLASH差不多
EEPROM是低端产品，容量低，价格便宜，但是稳定性较FLASH要好一些。但对于EEPROM和FLASH的设计来说，FLASH则要难的多，不论是从工艺上的还是从外围电路设计上来说


Flash memory指的是“闪存”，所谓“闪存”，它也是一种非易失性的内存，属于EEPROM的改进产品。它的最大特点是必须按块(Block)擦除(每个区块的大小不定，不同厂家的产品有不同的规格)， 而EEPROM则可以一次只擦除一个字节(Byte)。目前“闪存”被广泛用在PC机的主板上，用来保存BIOS程序，便于进行程序的升级。其另外一大应用领域是用来作为硬盘的替代品，具有抗震、速度快、无噪声、耗电低的优点，但是将其用来取代RAM就显得不合适，因为RAM需要能够按字节改写，而Flash ROM做不到
用作存储Bootloader以及操作系统或者程序代码或者直接当硬盘使用(U盘)。
目前Flash主要有两种NOR Flash和NADN Flash。NOR Flash的读取和我们常见的SDRAM的读取是一样，用户可以直接运行装载在NOR FLASH里面的代码，这样可以减少SRAM的容量从而节约了成本。NAND Flash没有采取内存的随机读取技术，它的读取是以一次读取一快的形式来进行的，通常是一次读取512个字节，采用这种技术的Flash比较廉价。用户不能直接运行NAND Flash上的代码，因此好多使用NAND Flash的开发板除了使用NAND Flah以外，还作上了一块小的NOR Flash来运行启动代码。
一般小容量的用NOR Flash，因为其读取速度快，多用来存储操作系统等重要信息，而大容量的用NAND FLASH，最常见的NAND FLASH应用是嵌入式系统采用的DOC(Disk On Chip)和我们通常用的"闪盘"，可以在线擦除。目前市面上的FLASH 主要来自Intel，AMD，Fujitsu和Toshiba，而生产NAND Flash的主要厂家有Samsung和Toshiba。


ROM和RAM指的都是半导体存储器，
ROM是Read Only Memory的缩写，
RAM是Random Access Memory的缩写。
ROM在系统停止供电的时候仍然可以保持数据，而RAM通常都是在掉电之后就丢失数据，典型的RAM就是计算机的内存。

RAM有两大类，
一种称为静态RAM(Static RAM/SRAM)，SRAM速度非常快，是目前读写最快的存储设备了，但是它也非常昂贵，所以只在要求很苛刻的地方使用，譬如CPU的一级缓冲，二级缓冲。
另一种称为动态RAM(Dynamic RAM/DRAM)，DRAM保留数据的时间很短，速度也比SRAM慢，不过它还是比任何的ROM都要快，但从价格上来说DRAM相比SRAM要便宜很多，计算机内存就是DRAM的

DDR RAM(Date-Rate RAM)也称作DDR SDRAM，这种改进型的RAM和SDRAM是基本一样的，不同之处在于它可以在一个时钟读写两次数据，这样就使得数据传输速度加倍了。这是目前电脑中用得最多的内存，而且它有着成本优势，事实上击败了Intel的另外一种内存标准-Rambus DRAM。在很多高端的显卡上，也配备了高速DDR RAM来提高带宽，这可以大幅度提高3D加速卡的像素渲染能力。


ROM也有很多种，PROM是可编程的ROM，PROM和EPROM(可擦除可编程ROM)两者区别是，PROM是一次性的，也就是软件灌入后，就无法修改了，这种是早期的产品，现在已经不可能使用了，而EPROM是通过紫外光的照射擦出原先的程序，是一种通用的存储器。另外一种EEPROM是通过电子擦出，价格很高，写入时间很长，写入很慢。