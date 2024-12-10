#include"shell.hpp"
int main()
{
    ish sh;
    Prompt pr;
    void show();
    show();
    while(true)
    {
        pr.PrintPrompt();
        sh.GetCommand();

    }




    return -1;
}