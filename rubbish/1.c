#include"shell.hpp"
void show()
{
    if(fopen("./.has_been_visited","r") != NULL)    // 只需查看.has_been_visited文件的有无即可决定是否打印 oh my ish
        return;
    fopen("./.has_been_visited","w");

    string showName[9];
    showName[0] = "      __                                               __         ";
    showName[1] = "     /\\ \\                                  __         /\\ \\        ";
    showName[2] = "  ___\\ \\ \\___         ___ ___   __  __    /\\_\\    ____\\ \\ \\___    ";
    showName[3] = " / __`\\ \\  _ `\\     /' __` __`\\/\\ \\/\\ \\   \\/\\ \\  /',__\\ \\  _ `\\  ";
    showName[4] = "/\\ \\L\\ \\ \\ \\ \\ \\    /\\ \\/\\ \\/\\ \\ \\ \\_\\ \\   \\ \\ \\/\\__, `\\ \\ \\ \\ \\ ";
    showName[5] = "\\ \\____/\\ \\_\\ \\_\\   \\ \\_\\ \\_\\ \\_\\/`____ \\   \\ \\_\\/\\____/ \\ \\_\\ \\_\\";
    showName[6] = " \\/___/  \\/_/\\/_/    \\/_/\\/_/\\/_/`/___/> \\   \\/_/\\/___/   \\/_/\\/_/";
    showName[7] = "                                    /\\___/                        ";
    showName[8] = "                                    \\/__/                         ";

    for(int i = 0;i<9;i++)
    {
        printf("\e[9%dm",i);
        cout<<showName[i]<<endl;
        usleep(110000);
    }
}

void ish::PrintPrompt()
{
    string colors = (string)"\e[100m" + "\e[90m" + "\e[104m" + "\e[43m" + "\e[34m" + "\e[33m" + "\e[39m" + "\e[33m" + "\e[49m" + "\e[39m";
    string output = "\e[100m" + (string)" " + userName + "@" + hostName + " " + (string)"\e[90m" + (string)"\e[104m" + "" + " " + wdPath + " " + "\e[43m" + "\e[34m" + "" + "\e[33m" + "\e[39m" + "  " + gitHEAD + " ± " + "\e[33m" + "\e[49m" + "" + "\e[39m";
    cout << output << endl;
    PromptLen = output.size() - colors.size();
}

void ish::GetCommand()
{
    cout<<"\33[A";
    for(int i = 0;i<PromptLen;i++)cout<<"\33[C";
    getline(cin,line);  // get a line of command
}

// 写了这么多，只为让光标移到上一行的末尾

// 最后发现，只要cout的时候不换行就行了...