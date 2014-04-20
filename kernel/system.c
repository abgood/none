#include    "kernel.h"

extern int at_main();
extern int fs_main();
extern int cons_main();
extern int clock_main();
extern int rs_main();

int (*tasks[])() = {
    clock_main,
    at_main,
    fs_main,
    cons_main,
    rs_main,
};

String taskName[] = {
    "Clock",
    "AT Hardware",
    "FS",
    "Conslo",
    "Serial"
};


static void shell(void){
    ObjectDesc o = run(FS_PID,OPEN,0,0,"shell");
    run(o,RUN,0,0,0);
}

int system_main(void){
    int i = 0;
    id_t id = 0;
hel:
    id = fork();
    if(ERROR == id){
        printk("Fork Failt\n");
    }else if(0 == id){
        memcpy(self()->name,taskName[i],strlen(taskName[i]) + 1);
        tasks[i]();
    }else{
        i++;
        /* printk("ID = %d %s\n",id,self()->name); */
        if(i < sizeof(tasks) / sizeof(void*)) goto hel;
        else shell();
    }
    dorun();
    while(1);
    return OK;
}
