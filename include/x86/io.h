/*
 *  (c) LuoZH   2011
 *      这个文件的目录好像很深的样子,这个文件主要就是定义几个供内核操作IO使用
 *  的C语言宏,没有其他什么的.可以看出,我很多东西都抄linux的,这算不算抄?
 *      额,差点忘了,这段引至linux,版权不归我所有,好吧,上面版权那行无效.希望linus
 *  等人看到不会揍我,我是无辜的:-)
 */
#define outb(value,port)   \
    __asm__("out    %%al,%%dx"::"a"(value),"d"(port))
#define outw(value,port)   \
    __asm__("out    %%ax,%%dx"::"a"(value),"d"(port))
//下面这个其实我不是很理解,为何这样就能返回_v的值`
#define inb(port)           ({\
    unsigned    char    _v; \
    __asm__ volatile("in     %%dx,%%al":"=a"(_v):"d"(port));   \
    _v;\
    })
#define inw(port)           ({\
    unsigned    short    _v; \
    __asm__ volatile("in     %%dx,%%ax":"=a"(_v):"d"(port));   \
    _v;\
    })
//下面是带延时功能的
#define outb_p(value,port)  \
    __asm__("out    %%al,%%dx\n"\
        "jmp    1f\n"       \
        "1:jmp  1f\n"       \
        "1:"::"a"(value),"d"(port) \
       )
#define outw_p(value,port)  \
    __asm__("out    %%ax,%%dx\n"\
        "jmp    1f\n"       \
        "1:jmp  1f\n"       \
        "1:"::"a"(value),"d"(port) \
       )
#define inb_p(port)         ({\
    unsigned    char    _v; \
    __asm__ volatile("in    %%dx,%%al\n"    \
                 "jmp   1f\n"           \
                 "1:jmp 1f\n"           \
                 "1:":"=a"(_v):"d"(port));\
    _v;                                 \
    })
#define inw_p(port)         ({\
    unsigned    short    _v; \
    __asm__ volatile("in    %%dx,%%ax\n"    \
                 "jmp   1f\n"           \
                 "1:jmp 1f\n"           \
                 "1:":"=a"(_v):"d"(port));\
    _v;                                 \
    })

#define sti()   __asm__("sti")
#define cli()   __asm__("cli")
#define wait()  __asm__("wait")
#define hlt()   __asm__("hlt")
#define invalidate()   \
    __asm__("mov    %%cr3,%%eax\n\t"    \
        "mov    %%eax,%%cr3\n\t"    \
        :::"%eax")
