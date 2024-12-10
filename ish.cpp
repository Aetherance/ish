#include"shell.hpp"
#define DB 0
int main()
{
    ish sh;
    Prompt pr;
    Command cmd;
    void show();
    show();
    if(DB)nosignal();
    system("clear");
    cout<<"In ish!"<<endl;
    while(true)
    {
        pr.PrintPrompt();
        sh.GetCommand();
        cmd.isClear();
        cmd.isExit();
    }

    return -1;
}