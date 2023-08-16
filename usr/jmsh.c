#include "jmsh.h"
#include "../hal/jmos-stm32-usart.h"

#define CMD_SIZE 200
char cmd[CMD_SIZE];

void getcmd(){
    
    int idx = 0;
    cmd[idx] = '\0';
    
    unsigned char c;
   
    while(c != '\r'){
        c = getchar();
        if(c == '\r'){
            break;
        }

        if(idx >= CMD_SIZE - 2){
            break;
        }
        if(c == 127){
            if(idx == 0){
                continue;
            }
            putchar('\b');
            putchar(' ');
            putchar('\b');

            cmd[idx] = '\0';
            idx--;

            continue;
        }
        cmd[idx] = c;
        cmd[idx+1] = '\0';
        putchar(c);

        idx++;
    }

    putchar('\n');
    putchar('\r');
}

int run(void){
    for(int i = 0; i < 100; i++){
        println("");
    }
    println("---------------------------------------------------------------------");
    println("--------------------------- JMOS UART Shell -------------------------");
    println("---------------------------------------------------------------------");
    println("");
   
    while(1){
        getcmd();
        println(cmd);
    }

    return 0;
}
