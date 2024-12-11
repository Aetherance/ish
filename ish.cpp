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
    cout<<"In ish!"<<endl;
    while(true)
    {
        pr.PrintPrompt();
        sh.GetCommand();
        cmd.isClear();
        cmd.isExit();
        
        cmd.ExeCommand();
        sh.LineClear();
    }

    return -1;
}