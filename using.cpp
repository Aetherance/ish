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

vector<string> split(string s)
{
    vector<string>result;
    int pos = 0;
    while (pos< s.size())
    {
        int n = 0;
        while (s[pos+n]!=' '&&pos+n<s.size())
        {
            n++;
        }
        result.push_back(s.substr(pos,n));
        pos += n;
        while (s[pos] ==' '&&pos<s.size())
        {
            pos++;
        }
    }
    return result;
}

vector<char *> fromStoC(vector<string>s)
{
    vector<char *>c;
    for(int i = 0;i<s.size();i++)
    {
        char * buf = new char[s[i].size()];
        strcpy(buf,s[i].c_str());
        c.push_back(buf);
    }
    return c;
}

void nosignal()
{
    signal(SIGINT,SIG_IGN);
}

void Prompt::PrintPrompt()
{
    isError ? (cout<< failed + output) : cout << output << " ";
    isError = false;
    PromptLen = output.size() - colors.size();
}

void ish::GetCommand()
{
    getline(cin,line);  // get a line of command
}

string ish::line;
vector<string> ish::argv;

void ish::LineClear()
{
    line.clear();
}

void Command::isClear()
{
    if(line == "clear"||line == "cls")
        system("clear");
}

void Command::isExit()
{
    if(line == "exit")
        exit(EXIT_SUCCESS);
}

void Command::ExeCommand()
{
    argv = split(line);
    vector<char *>ar = fromStoC(argv);
    pid_t pid = fork();
    if(pid == 0)
    {
        if(strcmp(ar[0],"ls")==0)
        {
            ar.push_back((char *)"--color=auto");
        }

        execvp(ar[0],ar.data());
    }
    wait(&pid);
}
