#include"shell.hpp"
#define DB 1    // DB为1时,进入debug模式 不屏蔽信号
int main()
{
    ish sh;
    Prompt pr;
    Command cmd;
    void show();
    show();
    if(!DB)nosignal();
    system("clear"); 
    while(true)
    {
        pr.PrintPrompt();
        sh.GetCommand();
        cmd.Process();
        sh.LineClear();
    }

    return -1;
}