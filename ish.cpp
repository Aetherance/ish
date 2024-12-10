#include"shell.hpp"
int main()
{
    ish sh;
    void show();
    show();
    while(true)
    {
        sh.PrintPrompt();
        sh.GetCommand();
    }




    return -1;
}