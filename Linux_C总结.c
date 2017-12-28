gcc用法：
-o ：output之意，用于指定生成一个可执行文件的文件名  
-c ：用于把源文件生成目标文件（.o)，并阻止编译器创建一个完整的程序  
-I ：增加编译时搜索头文件的路径  
-L ：增加编译时搜索静态连接库的路径  
-S ：把源文件生成汇编代码文件  
-lm：表示标准库的目录中名为libm.a的函数库  
-lpthread ：连接NPTL实现的线程库  
-std= ：用于指定把使用的C语言的版本  
  
# 例如：  
# 把源文件test.c按照c99标准编译成可执行程序test  
gcc -o test test.c -lm -std=c99  
#把源文件test.c转换为相应的汇编程序源文件test.s  
gcc -S test.c
    
    
    
分配一块内存用于存储变量的值
内存中每一个字节都有编号，编号就是内存地址
int i =100; //i占4个字节
变量i的内容被存放在以地址4500开始的4个字节的内存中，分配4个字节来存储该变量的值
char c ='a';
char *p = &c;//定义指针变量p, p用于存放一个char型变量的地址，把变量c的地址赋给变量p, &C用于取变量c的地址，变量p存放的是一个地址，指针p指向变量c
    
char c2 = *p+1;
*p含义是取得指针变量p所指向的变量的值，也就是c的值'a',加1后，c2的值为'b'
    
指针：专门用来存放内存地址的变量，每个指针都有一个数据类型
该类型决定了指针指向的变量的类型

&：取地址
*：取指针所指向的内存单元的值


/* 指针和数组
数组名相当于首地址 */
int a[] = {2,4,6};
int *p1 = a; //int* p1 = NULL;  p1 = a;    p1指向数组a的第一个元素，即a[0]
int *p2 = &a[0];
p1 = p1+3;//此时p1指向a[3]
int a[10],i,*p =NULL;
for(p=a;p<a+10;)
    printf("%d ",*p++);
*p++:先取当前p所指向的变量值再使p指向后一个变量
*p--:先取当前p所指向的变量值再使p指向前一个变量
*++p:先使p指向后一个变更再取得p所指向的变量的值    
*--p:先使p指向前一个变更再取得p所指向的变量的值    

/* 数组指针 */
int (*p)[5]:一个指针，它指向一个含有5个元素的数组
/* 指针数组 */
int* p[5]：一个数组，它的长度为5，数组中每一个元素指向一个整型变量


指针和函数
/* 指针作为函数的参数 */
将一个变量的地址传到函数中
函数的参数是局限于该函数的局部变量，函数调用时，系统为函数的局部变量分配内存，函数执行完，调用函数时分配的内存就被系统回收了
//函数中出现指针参数，一定要检查参数是否为NULL


/* 返回指针的函数 （指针函数）*/ 
函数返回一个指针，即地址
int*  func(int i,int j); //()优先级高于*，因此func与()结合，func是一个函数
char* week(int day)
{
    if(day<0 || day>7)
        ;
    else
        ;
}
char *p =NULL;
int day;
p = week(day);




/* 指向函数的指针（函数指针） */
指向函数的指针是一个指针变量，这个指针指向一个函数，一个函数的函数名是一个指针，它指向函数的代码
int (*func)(int i,int j);
函数的调用可以通过函数名来调用也可以通过指向函数的指针来调用
    
eg。
int get_min(int i,int j)
{
    return i>j?j:i;
}
int compare(int i,int j)
{
    int ret;
    int (*p)(int,int); //定义一个指向函数的指针p
    p = get_min;//把函数名赋予给p
    ret = p(i,j);//用p来调用相应的函数
    return ret;
}

/* 函数指针做形参 */
int fuc(int i,int j,int (*p)(int i,int j));
eg。
int get_big(int i,int j)
{
    return i>j?i:j;
}
int get_max(int i,int j,in tk,int (*p)(int i,int j))
{
    int ret;
    ret = p(i,j);
    ret = p(ret,k);
    return ret;
}
int main()
{
    int i=5,j=10,k=15,ret;
    ret = get_max(i,j,k,get_big);
    
    return 0;
}

/* 返回函数指针的函数 */
int (*get_func(int a))(int ,int);


指向字符串的指针
访问字符串的方法
.用字符数组存放一个字符串
    char string[] = "linux c";
    printf("%s\n",string);
.用字符串指针来指向字符串
    char* p= "linux c";
    printf("%s\n",p);
建议用法
    char string[] = "linx c";
    char *str = NULL;
    str = string; //数组名是指向数组第一个元素的首地址，str指向数组string的首地址
    printf("%s\n",str);

只有全局变量初始化时的默认值为0，而局部变量默认值是不确定的。所以，局部变量在使用之前一定要先赋值
register称为寄存器变量。它只能用于int,char,short ,unsigned和指针类型用寄存类，默认值为0
寄存器变量只适用于局部变量和函数的形式参数, 它属于auto型变量


puts()函数
int puts(char *string);
将一个以\0结尾的字符串输出到屏幕上，同printf("%s\n",str)相同
char a[] = "LINUX C";
puts(a);

gets()函数
char str[20];
gets(str);


char *fgets(char *buf, int bufsize, FILE *stream);
参数
*buf: 字符型指针，指向用来存储所得数据的地址。
bufsize: 整型数据，指明存储数据的大小。
*stream: 文件结构体指针，将要读取的文件流。


char string2[20] = {'\0'}; //字符数组初始化

strcpy和strncpy
char* strcpy(char* dst,char* src)//不安全
char* strncpy(char* dst,char* src,int n)//建议用法
复制是将字符串的"\0"一起被复制
char* s ="hello world";
char d1[20],d2[20];
strcpy(d1,s);
strncpy(d2,s,sizeof(s));


strcat和strncat 连接
char* strcat(char* dst,char* src)
char* strncat(char* dst,char* src,int n)

strcmp和strncmp 比较
char* strcmp(char* dst,char* src)
char* strncmp(char* dst,char* src,int n)
相等返回0


strlen 求字符串长度
char string[16]= "china";
strlen(string);


strlwr 和 strupr
strlwr: 将字符串字母转换为小写
strupr：将字符串字母转换为大写

strstr 和 strchr
char* strstr(char* s1,char* s2);//s1中寻找s2第一次出现的位置
char* strchr(char* s1,char c);//s1中寻找字符c第一次出现的位置































无参数宏
#define PI  3.1415
#undef PI  //提前终止宏作用范围
有参数宏：类似于有参数的函数
#define  MAX(x,y)  (x>y?x:y)

声明结构体
struct person{
    char name[20];
    int age;
};
声明结构体也是一个C语句，必须要; 结束
结构体相当于一个新的数据类型

定义结构体变量，才会分配内存
struct person p1,p2;
内存分配是4字节对齐，为了提高访问效率有一个规则   

声明结构体同时定义两个结构体变量
struct person{
    char name[20];
    int age;
}p3,p4;   
    
引用结构体变量中的成员方式
struct person p1;
strcpy(p1.name,"xin");
p1.age = 24;

"."是成员运算符
struct person p2={"xin",24};
struct person p[2] = {{"xin",24}
                      {"sky",25}}

结构体和指针
结构体中的各成员按顺序连续存放在内存中，一个结构体指针指向一个结构体变量，结构体指针所保存的值是它所指向的结构体变量所占内存的首地址

/* 指向结构体数组的指针 */
struct person
{
   char name [20];
   int age;
   char sex;
};

int main(void)
{
    struct person p1;
    struct person *p2;
    strcpy(p1.name,"xinxiwei");
    p1.age = 33;
    p1.sex = 'm';
    p2 = &p1;//取变量地址符
    printf("%s, %d, %c\n",p2->name,p2->age,p2->sex);
    
    struct person p3[3] ={{"sky",25,'m'},
                            {"blue",35,'s'},
                            {"xin",30,'m'}};
    struct person *p4;
    for(p4=p3;p4<p3+3;p4++)//指向结构体数组的首地址，数组名相当于首地址符
    {
        printf("%s, %d, %c\n",p4->name,p4->age,p4->sex);
    } 
    
    return 0;
}    

/* 结构体指针作函数参数 */
void func(struct person *p);
func(p4);
    
/* 共用体 */
把几种不同的数据类型的变量放在同一块内存里，变量共享同一块内存
union data
{
    int i;
    char c;
    double d;
};
union data a;
共用体变量中起作用的成员是最后一次存入的数据
共用体变量长度取决于其成员的最大长度
union data1
{
    double d;
    int i;
    char c;
    char c2[9];
};
sizeof(union data1) = 16   ?
因为此共用体最大基本类型为double，占8字节，所以此共用体以8对齐，字符数组c2占9个字节，那整个共用体应该占9字节，但按照对齐原则，实际分配的内存为16字节

struct data1
{
    double d;
    int i;
    char c;
    char c2[9];
};
sizeof(struct data1) = 24 ,先按存储大小 ，该结构体所占存储空间为 8+4+1+9 = 22字节，22不是8的倍数，这个结构体也是以8对齐，进行对齐，实际分配的是24字节
    
struct inner
{
    char c1;
    double d;
    char c2;
};
分配空间时，编译器知道是以8字节对齐，给C1分配时考虑对齐分配8字节，给d分配8字节，给c2分配时，也考虑对齐，分配8字节，共24字节
    
struct inner
{
    char c1;
    char c2;
    double d;
};   
分配空间时，编译器知道是以8字节对齐，给C1C2分配时只分配8字节就可以了，给d分配8字节，共16字节

/* typedef */
声明新类型名来替代已有的类型名
typedef int INT;
typedef struct
{
    int year;
    int month;
    int day;
}DATE;
DATE birthday; //使用新类型定义变量
    
    
第6章 文件操作
d是目录
_是普通文件
b块特殊文件
b字符特殊文件

//打开文件 
int open(const char *pathname,int flags)
int open(const char *pathname,int flags,mode_t mode)

O_RDONLY:只读方式打开文件 
O_WRONLY:只写方式
O_RDWR:可读可写

O_CREAT:或文件不存在则自动创建，此时需要参数mode
O_EXCL:若O_CREAT也设置，此指令会检查文件是否存在，不存在则创建，若文件存在则打开出错
O_TRUNC:若文件 存在，且以可写方式打开，此指令会将文件清0，原数据会丢失
O_APPEND:所写入的数据以追加的方式加入到文件后面
O_SYNC:以同步方式打开文件 

mode:
S_IRUSR 可读
S_IWUSR 可写
S_IXUSR 可执行
S_IRWXU 可读可写可执行

//创建文件 
int creat(const char *pathname,mode_t mode)//若文件不存在，则创建，若存在则覆盖
相当于
open(const char *pathname,(O_CREAT|O_WRONLY|O_TRUNC))

//关闭文件 
int close(int fd)
fd是open或creat的文件描述符，调用成功返回0

/* read函数:从打开的文件中读取数据，成功返回0*/
read(int fd,void *buf,size_t count)

/* 将数据写入已打开的文件 中，成功则返回写入的字节数 */
write(int fd,const void *buf,size_t count)

/* 文件读写指针的移动 ,用来移动文件读写指针的位置*/
lseek(int fd, off_t offset,int whence)
lseek(int fd, 0,SEEK_SET) :将文件读写指针移动到文件开头
lseek(int fd, 0,SEEK_END) :将文件读写指针移动到文件结尾
lseek(int fd, 0,SEEK_CUR) ：获取文件读写指针当前的位置
eg.
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* 定义错误处理函数 */
void my_err(const char *err_string, int line)
{
    fprintf(stderr,"line:%d",line);
    perror(err_string); //包含在stdio.h中
}

int main(void)
{
    int fd;
    char write_buf[32] = "hello world";
    /* 创建文件  */
    if((fd = open("my_rwl.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU) == -1)
    {
        my_err("open",__LINE__);
    }else{
        printf("create file success\n");
    }
    
    /* 写数据 */
    if(write(fd,write_buf,strlen(write_buf)) != strlen(write_buf))
    {
        my_err("write",__LINE__);
    }
    my_read(fd);
    
    if((ret = read(fd, read_buf, len)) < 0)
    {
        my_err("read",__LINE__);
    }
}
==================
/* fcntl函数： */
对已打开的文件描述符进行各种操作以改变文件的各种属性
fcntl( fd ,  F_SETOWN ,  getpid( ) );//将当前进程PID设置为fd文件所对应驱动程序将要发送SIGIO,SIGUSR信号进程PID      
oflags = fcntl( fd ,  F_GETFL );//获取fd的打开方式       
fcntl( fd ,  F_SETFL ,  oflags | FASYNC );//将fd的打开方式设置为FASYNC --- 即 支持异步通知

/* ioctl函数 */
用来控制设备文件的属性
int ioctl(int fd,int request, char *argp)
fd:必须是一个已经打开的文件描述符
request:决定参数是向ioctl传递数据还是从ioctl获取数据

strcpy:字符串copy
memcpy:内存copy


1.进程
进程是动态的实体，是程序的一次执行过程，是操作系统分配的最基本单位
进程和程序的区别在于进程是动态的，程序是静态的，进程是运行中的程序，程序是一些保存在硬盘上的可执行的代码

进程内部划分许多线程，线程是独立运行的基本单位，线程基本上不拥有系统资源，它与同属一个进程的其它线程共享进程拥有的全部资源，同一个进程中的线程可并行运行
getpid() 获取进程ID
getppid() 获取进程父进程ID
getuid()  获取进程的实际用户ID（标识运行该进程的用户）
geteuid() 获取进程的有效用户ID
getgid()  获取进程的实际组ID （实际用户所在组的组ID）
getegid() 获取进程的有效组ID

/* 进程结构：
代码段，数据段，堆栈段 */
代码段：存放程序的可执行代码
数据段：存放程序的全局变量，常量，静态变量
堆：存放动态分配的内存变量
栈：用于函数调用，存放函数参数，函数内部定义的局部变量，函数返回的地址

/* 进程状态： */
运行状态
可中断等待状态
不可中断等待状态
僵死状态：进程已终止，但进程描述符依然存在，直到父进程调用wait函数后释放
停止状态

/* 进程控制 */
fork: 创建一个新进程
exit: 终止进程
exec: 执行一个应用程序
wait：将父进程挂起，等待子进程终止
getpid： 获取进程ID
nice: 改变进程的优先级


/* 进程的内存映像 */
linux C程序的生成分4个阶段：预编译，编译，汇编，链接，gcc 经过前3步将源程序文件 转换为目标文件，gcc 还要将所需的库链接起来，//最后生成可执行程序

当程序执行时，os将可执行程序复制到内存中，程序转化为进程经过以下步骤：
.内核将程序读入内存。为程序分配内存空间
.内核为该进程分配进程标识符PID和其它所需要资源
.内核为该进程保存PID有相应的状态信息，把进程放到运行队列中等待执行，程序转化为进程后就可以被 os的调度程序调度执行了


进程的内存映像是指内核在内存中如何存放可执行程序文件 ，在将程序转化为进程的过程中，操作系统将可执行程序由硬盘复制到内存中

可执行程序和内存映像的区别：
.可执行程序位于磁盘中，而内存映像位于内存中
.可执行程序没有堆栈，因为程序被加载到内存中才会分配堆栈
.可执行程序是静态的不变的


/* 创建进程 */
创建一个子进程后，父进程和子进程争夺CPU。抢到CPU者执行，另一个挂起等待
想要父进程等待子进程执行完毕后再继续执行，可以在fork操作后调用wait或waitpid

fork函数:
分裂为两个进程，一个是原来的父进程，另一个是刚刚创建的子进程
两个返回值 ，一个是父进程调用fork后的返回值（即是刚创建的子进程的ID）,另一个是子进程中fork函数的返回值（返回值是0），创建成功返回两个值 ，创建失败只返回-1
#include <unistd.h>
pid_t pid;
pid = fork(void);
switch(pid){
    case 0:
        printf("child process is runnint ,curpid is %d,parentpid is %d",pid,getppid());
        break;
    case -1:
        printf("process create failed");
        break;
    default:
        printf("parent process is running,childpid is %d,parentpid is %d",pid,getpid());
        break;
}
exit(0);

fork进程失败原因通常是：
.父进程拥有的子进程个数超过了规定的限制 errno 为EAGAIN
.可供使用的内存不足，errno为 ENOMEM


/* 孤儿进程 */
父进程先于子进程结束，子进程就成为一个孤儿进程，它由init进程收养，成为init进程的子进程 


/* 守护进程 */
一个守护进程的父进程是init进程，因为它真正的父进程在fork出子进程后就先于子进程exit退出了，所以它是一个由init继承的孤儿进程

指在后台运行的，没有控制终端与之相连的进程，独立于控制终端，通常周期性的执行某种任务，是一种很有用的进程

守护进程的启动方式：
.从启动脚本/etc/rc.d中启动
.终端 shell执行

/* 进程退出 */
正常退出：
    main函数中执行return
    调用exit函数(exit(0),0代表进程正常终止)
    调用_exit函数 （执行后立即返回给内核，exit(0)要先执行一些清除操作，然后将控制权交给内核）
异常退出：
    调用abort函数
    进程收到某个信号，而该信号使程序终止
最终都 会执行内核中同一段代码（用来关闭进程所有已打开的文件描述符，释放它所占用的内存和其它资源）

/* 执行新程序 */
fork子进程后，子进程会调用exec函数来执行另一个程序,系统调exec用于执行一个可执行程序以代替当前进程的执行映像，一个进程一旦调用exec函数，它本身就“死亡”了，当前后面的代码就不会再执行了

正常情况下，这些函数是不会返回的
异常情况下，将返回-1
errno:
EACCES:指定的文件是不可执行的
E2BIG:新程序的命令行参数与环境变量之和超过ARG_MAX
ENOEXEC:没有正确的格式 ，指定的文件无法执行
ENOMEM:没有足够的内存空间
ETXTBUSY:指定的文件被一个或多个进程以可写的方式打开
EIO:从文件 系统读入文件时发生I/O错误
int execve(const char *path, char  *const argv[], char *const envp[]);

/* 僵尸进程 */
子进程先于父进程退出时，父进程没有调用wait和waitpid函数，子进程就会进入僵死状态

pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);

wait函数使父进程暂停执行，直到它的一个子进程结束为止，函数返回值是终止运行的子进程的PID，参数statloc所指向的变量存放子进程的退出码，即从子进程的main函数返回的值或子进程中exit函数的参数

waitpid用来等待子进程的结束，参数pid指明要等待的子进程的PID，option参数允许用户改变waitpid的行为，WNOHANG表示父进程不被挂起而立即返回并执行其后的代码
waitpid(child_pid, (int *)0,WNOHANG); 让父进程周期性检查某个特定的子进程是否已经退出
若子进程尚未退出，返回0，若子进程已经结束返回child_pid,调用失败时返回-1（原因包括没有该子进程，参数不合法等）


/* 获取进程ID */
getpid()
setuid()设置实际用户ID和有效用户ID
setgid()设置实际组ID和有效组ID

/* 改变进程的优先级 */
int nice(int increment);
int getpriority(int which, int who);
int setpriority(int which,int who,int prio);

getpriority:返回一组进程的优先级
which取值：
PRIO_PROCESS: 一个特定的进程，此时who取值为进程ID
PRIO_PGRP:一个进程组的所有进程，此时who取值为进程组ID
PRIO_USER:一个用户拥有的所有进程，此时who取值为实际用户ID
调用成功返回指定进程的优先级，出错返回-1.并设置errno的值
errno可能的取值：
ESRCH: which和who 的组合与现存的所有进程匹配
EINVAL:which是个无效的值

setpriority:函数返回指定进程的优先级
errno可能的取值：
EPERM:要设置优先级的进程与当前进程不属于同一个用户，且当前进程没有CAP_SYS_NICE特许
EACCES:该调用可能降低进程的优先级且进程没有CAP_SYS_NICE特许

int nice(int increment)
{
    int oldpro = getpriority(PRIO_PROCESS,getpid());
    return setpriority(PRIO_PROCESS,getpid(),oldpro + increment);
}

/* 第8章 线程 */
线程是计算机运行的最小单位，运行时占用很少的系统资源
多线程相对于多进程优点：
.多进程情况，每个进程都有自己独立的地址空间，而多线程情况，是同一个进程内的线程共享进程的地址空间，创建一个进程耗费的时间比创建一个线程花费的时间要多的多
.系统调度方面，由于进程地址空间独立，而线程共享地址空间，线程间的切换速度要远快于进程间的切换速度
.通信机制方面，进程间的数据空间相互独立，彼此通信必须经过操作系统，而同一进程内的多个线程共享数据空间，一个线程的数据可以直接提供给其它线程使用，而不必经过操作系统

线程节约资源，节约时间 
线程还有其它优点：
.提高应用程序的响应速度
.提高多处理器效率，让多个线程在不同的处理器上同时运行，大大提高执行速度
.改善程序的结构，可以让每个命令的处理设计成一个线程


linux支持POSIX多线程接口，称为pthread  ，需要pthread.h头文件 

/* 创建线程 */
int pthread_create(pthread_t *thread, pthread_attr_t *attr, void* (*start_routine)(void*), void *arg);
参数：
thread: 一个指针，当线程创建成功时，用来返回创建的线程ID
attr: 指定线程的属性，NULL表示使用默认属性
start_routine: 一个函数指针，指向线程创建后要调用 的函数(即叫线程函数)
arg: 指向传递给线程函数的参数

线程创建成功时，pthread_create函数返回0.若不为0则说明创建线程失败，常见错误码EAGIN EINVAL
EAGIN:表示系统限制创建新的线程，如线程数目过多
EINVAL:代表线程属性值非法
创建成功后，新创建的线程开始运行线程函数，原来的线程继续运行

pthread_t pthread_self(void): 获取本线程的线程ID
int pthread_equal(pthread_t thread1,pthread_t thread2):判断两个线程ID是否指向同一个线程
int pthread_once(pthread_once_t *once_control, void(*init_routine)(void)): 保证线程函数在进程中仅执行一次
eg：
pthread_once_t  once = PTHREAD_ONCE_INIT;
void run(void)
{
    printf("hello");
}
pthread_once(&once , run);



exit（0）：正常运行程序并退出程序；
exit（1）：非正常运行导致退出程序，这个1是返回给操作系统的。
return（）：返回函数，若在主函数中，则会退出函数并返回一值

/* 线程终止 */
方式：
.return
.void pthread_exit(void *retval);
唯一的参数是函数的返回代码，只要pthread_exit中的参数retval不是NULL，这个值将被传递给 thread_return
两种特殊情况：
.在主线程中，如果从main函数返回或是调用exit函数退出主线程，则整个进程将终止，此时进程中所有线程也将终止，因此主线程中不能过从main函数返回
.如果主线程调用pthread_exit函数，则仅表示主线程消亡，进程不会结束，进程内的其它线程也不会终止，直到所有线程结束，进程才会结束

pthread_cleanup_push
pthread_cleanup_pop
两个函数用于自动释放资源，且要成对出现，必须位于程序的同一代码中

/* 线程同步 */
终止的线程所占用的资源不会随着线程的终止而归还系统，而是仍在线程所在的进程持有，


//用来等待一个线程的结束，
int pthread_join(pthread_t th, void * thread_return);
第一个参数为被等待的线程标识符
第二个参数为一个用户定义的指针，它可以用来存储被等待线程的返回值(通常为NULL)
这个函数是一个线程阻塞的函数，调用它的线程将一直等待到被等待的线程结束为止，当函数返回时，被等待线程的资源被收回
    
//pthread_join()的调用者将被挂起并等待th线程终止，如果 thread_return 不为NULL.则*thread_return = retval，
一个线程仅允许一个pthread_join等待它的终止，并且被等待的线程应该牌可join状态，即非DETACHED 状态。
int pthread_detach(pthread_t th);
DETACHED状态是指对某个线程执行pthread_detach()后其所处的状态，处于DETACHED状态的线程无法由pthread_join()同步
    
一个可join的线程所占用的内存仅当有线程对其执行了pthread_join()后才会释放   
void assisthread(void *arg)
{
    printf("i am helping to do some jobs");
    sleep(3);
    pthread_exit(0);//退出码为0
}
int main(void)
{
    pthread_t assistthid;
    int  status;
    pthread_create(&assistthid, NULL,(void*)assisthread,NULL);
    pthread_join(assistthid, (void*)&status);
    printf("assisthread's exit is caused %d", status);
    return 0;
}
运行结果：
gcc  jointhread.c  -o jointhread  -lpthread ; ./jointhread
i am helping to do some jobs
assisthread's exit is caused 0
结果看出 pthread_join会阻塞主线程，等待线程assisthread结束，pthread_exit结束时的退出码是0，pthread_join得出status也为0，两者一致


//pthread_join用于等待一个线程的结束，也就是主线程中要是加了这段代码，就会在加代码的位置卡主，直到这个线程执行完毕才往下走。
//pthread_exit用于强制退出一个线程（非执行完毕退出），一般用于线程内部。

结合用法：
一般都是pthread_exit在线程内退出，然后返回一个值。这个时候就跳到主线程的pthread_join了（因为一直在等你结束），这个返回值会直接送到pthread_join，实现了主与分线程的通信。

注意事项：
这个线程退出的返回值的格式是void*，无论是什么格式都要强转成void*才能返回出来主线程
举个例子，如果是char* = “mimida”;传出来的tmp，必须（char*）tmp一下。
而如果是int* a = new(3888);这种类型返回的tmp，必须*(int*)tmp一下才能用。
最重要的一点，你定义的类型和最后出来的类型一定要一致，不然很容易出现问题。也就是你定义了int*，最后强转出来的一定是*（int*）。


/* 线程私有数据 */
操作线程私有数据函数：
int pthread_key_create(pthread_key_t *key, void (*destr_function) (void*));//创建一个键
int pthread_setspecific (pthread_key_t key, const void *pointer);//为一个键设置线程私有数据
void * pthread_getspecific(pthread_key_t key);//从一个键读取线程私有数据
int pthread_key_delete(pthread_key_t key);//删除一个键


/* 线程同步 */
线程最大的特点是资源共享性，然而资源共享中的同步问题是多线程编程的难点
处理同步方式有：
互斥锁
条件变量
异步信号

互斥锁通过锁机制来实现线程间的同步，同一个时刻它通常只允许一个线程执行一个关键部分的代码
pthread_mutex_init ：初始化一个互斥锁
pthread_mutex_destory: 注销一个互斥锁
pthread_mutex_lock： 加锁，如果不成功，阻塞等待
pthread_mutex_unlock: 解锁
pthread_mutex_trylock: 测试加锁，如果不成功则立即返回，错误码为EBUSY

int pthread_mutex_init(pthread_mutex_t  *mutex, const pthread_mutexattr_t *mutexattr)
eg.
pthread_mutex_t  mutex ;
pthread_mutex_init(&mutex,NULL); //NULL表示使用默认互斥锁属性
pthread_mutex_lock(&mutex);//如果mutex已经被锁住，当前尝试加锁的线程就会阻塞，直到互斥锁其它线程释放
pthread_mutex_unlock(&mutex);
pthread_mutex_destory(&mutex);//清除互斥锁


异步信号被进程用来进行相互通信，一个进程通知另一个进程


错误检查
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    FILE *stream;
    char *filename  ="test";
    errno = 0;
    stream = fopen(filename,"r");
    if(stream == NULL)
    {
       printf("open file %s failed,errno is %d",filename,errno); 
    }else
       printf("open file %s successfully",filename);
}


/* 第9章 信号及信号处理 */
SIGIO：此信号向进程指示发生了一个异步IO事件

//信号处理函数  
void my_signal_fun(int signum)  
{  
    unsigned char key_val;  
    read(fd, &key_val, 1);  
    printf("key_val: 0x%x\n", key_val);  
}
//在应用程序中捕捉SIGIO信号（由驱动程序发送）  
signal(SIGIO, my_signal_fun);  
  
fd = open("/dev/buttons", O_RDWR);  
if (fd < 0)  
{  
    printf("can't open!\n");  
}  

//将当前进程PID设置为fd文件所对应驱动程序将要发送SIGIO,SIGUSR信号进程PID  
fcntl(fd, F_SETOWN, getpid());  
  
//获取fd的打开方式  
Oflags = fcntl(fd, F_GETFL);   

//将fd的打开方式设置为FASYNC --- 即 支持异步通知  
//该行代码执行会触发 驱动程序中 file_operations->fasync 函数 ------fasync函数调用fasync_helper初始化一个fasync_struct结构体，该结构体描述了将要发送信号的进程PID (fasync_struct->fa_file->f_owner->pid)  
fcntl(fd, F_SETFL, Oflags | FASYNC);    

/* 信号的捕捉和处理： */
signal函数
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
eg.
signal(SIGIO,read_vibrate_data);
当指定的信号到达时就会跳转到handler指定的函数执行，handler是函数指针，它所指向的函数类型是sighandler_t, 它所指身后函数有一个int型参数，且返回值类型为void
    
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

#define ENV_UNSAVE 0
#define ENV_SAVED 1
int flag_saveenv = ENV_UNSAVE;
jmp_buf env;

void handler_sigrtmin15(int signo)
{
    if(flag_saveenv == ENV_UNSAVE)
    {
        printf("flag_saveenv == ENV_UNSAVE");
        return;
    }
    printf("recv SIGRTMIN+15\n");
    sleep(10);
    printf("in handler_sigrtmin15 ,after sleep\n");
    siglongjmp(env,1);    
}

int main()
{
    switch(sigsetjmp(env,1))
    {
        case 0:
            printf("return 0\n");
            flag_saveenv = ENV_SAVED;
            break;
        case 1:
            printf("return from SIGRTMIN+15\n");
            break;
        default:
            printf("return else\n");
            break;
    }
    signal(SIGRTMIN+15,handler_sigrtmin15);
    while(1)
        ;
    return 0;
}
===========
eg.
signal.c源代码如下：
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
/*自定义信号处理函数*/
void my_func(int sign_no)
{
    if(sign_no==SIGINT)
        printf("I have get SIGINT\n");
    else if(sign_no==SIGQUIT)
        printf("I have get SIGQUIT\n");
}
int main()
{
    printf("Waiting for signal SIGINT or SIGQUIT \n ");
    /*发出相应的信号，并跳转到信号处理函数处*/
    signal(SIGINT, my_func);
    signal(SIGQUIT, my_func);
    pause();
pause();
    exit(0);
}
编译 gcc signal.c –o signal。
执行 ./signal，执行结果如下：
Waiting for signal SIGINT or SIGQUIT
I have get SIGINT       /*按下Ctrl+C,操作系统就会向进程发送SIGINT信号*/
I have get SIGQUIT      /*按下Ctrl-\（退出）,操作系统就会向进程发送SIGQUIT信号*/
//sigaction()会依参数signum指定的信号编号来设置该信号的处理函数
int sigaction(int signum,const struct sigaction *act ,struct sigaction *oldact)
函数传入值
 
signum
可以指定SIGKILL和SIGSTOP以外的所有信号
act
参数结构sigaction定义如下
struct sigaction
{
    void (*sa_handler) (int);
    void  (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
}
①    sa_handler：此参数和signal()的参数handler相同，此参数主要用来对信号旧的安装函数signal()处理形式的支持
②    sa_sigaction：新的信号安装机制，处理函数被调用的时候，不但可以得到信号编号，而且可以获悉被调用的原因以及产生问题的上下文的相关信息。
③    sa_mask：用来设置在处理该信号时暂时将sa_mask指定的信号搁置
④    sa_restorer： 此参数没有使用
⑤    sa_flags：用来设置信号处理的其他相关操作，下列的数值可用。可用OR 运算（|）组合
   A_NOCLDSTOP:如果参数signum为SIGCHLD，则当子进程暂停时并不会通知父进程
   SA_ONESHOT/SA_RESETHAND:当调用新的信号处理函数前，将此信号处理方式改为系统预设的方式
   SA_RESTART:被信号中断的系统调用会自行重启
   SA_NOMASK/SA_NODEFER:在处理此信号未结束前不理会此信号的再次到来
   SA_SIGINFO：信号处理函数是带有三个参数的sa_sigaction
oldact 如果参数oldact不是NULL指针，则原来的信号处理方式会由此结构sigaction返回
eg.
sigaction.c源代码如下：
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <sys/types.h> 
#include <unistd.h> 
void new_op(int, siginfo_t *, void *); 
int main(int argc,char**argv) 
{ 
    struct sigaction act; 
    int sig; 
    sig=atoi(argv[1]); 
    sigemptyset(&act.sa_mask); 
    act.sa_flags=SA_SIGINFO; 
    act.sa_sigaction=new_op; 
    if(sigaction(sig,&act,NULL) < 0) 
    { 
        perror("install sigal error"); 
        return -1 ;
    } 
    while(1) 
    { 
        sleep(2); 
        printf("wait for the signal\n"); 
    } 
 
    return 0 ;
} 
void new_op(int signum,siginfo_t *info,void *myact) 
{ 
    printf("receive signal %d\n", signum); 
    sleep(5); 
} 
编译 gcc sigaction.c -o sigaction。
执行 ./sigaction 2，执行结果如下：
wait for the signal
receive signal 2       /*按下Ctrl+C */
退出                   /*按下Ctrl-\ */




=============
/* 信号的发送 */
kill : 发送信号给指定的进程
kill -s 信号名  进程号
kill -信号名    进程号

/* 第10章进程间通信 */
进程间通信的几种主要手段：
1.管道
2.有名管道
//3.信号量
//4.消息队列
//5.信号
//6.共享内存
7.套接字

/* 管道示例 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* 读管道 */
void read_from_pipe(int fd)
{
    char message[100];
    read(fd,message,100);
    printf("read from pipe: %s",message);
}

/* 写管道 */
void write_to_pipe(int fd)
{
    char *message = "hello,pipe!\n";
    write(fd,message,strlen(message)+1);
}


int main(void)
{
    int fd[2];
    pid_t pid;
    int stat_val;
    if(pipe(fd))
    {
        printf("creat pipe failed!\n");
        exit(1);   
    }
    
    pid = fork();//创建子进程
    switch(pid)
    {
        case -1:
            printf("fork error!\n");
            exit(1);
        case 0:
            /* 子进程关闭fd1 */
            close(fd[1]);//子进程关闭管道写端
            read_from_pipe(fd[0]);//子进程读数据
            exit(0);
        default:
            /* 父进程关闭fd0 */
            close(fd[0]);//父进程关闭管道的读端
            write_to_pipe(fd[1]);//父进程写数据
            wait(&stat_val);
            exit(0);            
    }
    return 0;
}
管道两端分别用描述符fd[0],fd[1]来描述，fd[0]为管道读端，fd[1]为管道写端
父进程向管道中写数据，子进程从管道中读数据
必须在系统调用fork()之前调用pipe(),否则进程将不会继续管道的文件描述符

生成静态库
gcc -o mylib.o -c mylib.c   最终生成libmylib.a
使用静态库
gcc -o test test.c -lmylib


生成动态库
gcc -fPIC -shared -o libttt.so mylib.c   最终生成libttt.so 
使用动态库
gcc -o test test.c  /usr/lib/libttt.so

另一种使用函数：
void *dlopen(const char *filename,int flag)//用于打开指定名字的动态链接库，并返回一个句柄
void *dlsym(void *handle,char *symbol)//根据动态链接库的句柄与函数名，返回函数名对应的函数的地址
int dlclose(void *handle)//关闭动态链接库，handle是dlopen时的句柄
const char *dlerror(void)//动态链接库中的函数执行失败时，dlerror返回出错信息，若执行成功，返回NULL

eg.
test.c
#include <stdio.h>

void welcome()
{
    printf("welcome to libmylib\n");
}
void outstring(const char *str)
{
    if(str != NULL)
        printf("%s",str);
}

int main(void)
{
    printf("create and use library\n");
    welcome();
    outstring("it's successfull\n");
}

gcc -fPIC -shared -o libttt.so test.c
编译生成动态库 libttt.so

testso.c
#include <stdio.h>
#include <dlfcn.h>
int main(void)
{
    void *handle;
    char *error;
    void (*welcome)();
    if((handle = dlopen("./libttt.so",RTLD_LAZY)) == NULL)//打开动态库
    {
        printf("dlopen error\n");
        exit(1);
    }
    
    welcome = dlsym(handle,"welcome");//根据句柄与函数名，返回函数名对应的函数地址
    if((error = dlerror()) != NULL)
    {
        printf("dlsym error\n");
        exit(1);
    }
    
    welcome();
    dlclose (handle);//关闭链接库
    exit(0);   
}
gcc -o testso testso.c -ldl    // -ldl  指明dlopen等函数所在的库
编译生成可执行文件 testso
./testso
welcome to libmylib


//指针函数：
int*  func(int a,int b); //func是函数名，返回值类型是一个int类型的指针
eg.
int *p1 = NULL;
p1 = func(1,2);
printf("*p1 = %d",*p1);
指针函数就是返回一个地址给调用者，用于需要地址的情况

//函数指针
//函数指针说的就是一个指针，但这个指针指向的是函数
int (*f)(int a, int b); // 声明函数指针   
函数指针与指针函数的最大区别是函数指针的函数名是一个指针，即函数名前面有一个指针类型的标志型号“*”
上面的函数指针定义为一个指向一个返回值为整型，有两个参数并且两个参数的类型都是整型的函数
eg.
int max(int a, int b) {  
    return a > b ? a : b;  
}
int (*func)(int, int); // 声明函数指针，指向返回值类型为int，有两个参数类型都是int的函数
func = max; // 函数指针f指向求最大值的函数max  
int c = (*func)(1, 2); 


























