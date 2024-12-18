#include"shell.hpp"
void show()
{
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
    cout<<"输入 '?' 以获取帮助"<<endl;
    cout<<"请按任意键继续";
    getchar();
}

string ish::wdPath;
string ish::line;
vector<string> ish::argv;
bool ish::isError = false;
int ish::ExeCount = 0;
vector<int *> ish::fds;

void help();
vector<string> split(string s,char ch)
{
    vector<string>result;
    int pos = 0;
    while (s[pos]==ch)
        pos++;
    
    while (pos< s.size())
    {
        int n = 0;
        while (s[pos+n]!=ch&&pos+n<s.size())
        {
            n++;
        }
        result.push_back(s.substr(pos,n));
        pos += n;
        while (s[pos] ==ch&&pos<s.size())
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

bool isRedirect(string str)
{
    if(str.find('<')==-1&&str.find('>')==-1)
        return 0;
    return 1;
}

void Prompt::PrintPrompt()
{
    output = "\e[100m" + (string)" " + userName + "@" + hostName + " " + (string)"\e[90m" + (string)"\e[104m" + "" + " " + wdPath + " " + "\e[43m" + "\e[34m" + "" + "\e[33m" + "  " + gitHEAD + " ± " + "\e[33m" + "\e[49m" + "" + "\e[39m\e[0m";
    isError ? (cout<< failed + output << " ") : cout << output << " ";
    isError = false;
    PromptLen = output.size() - colors.size();
}

void ish::GetCommand()
{
    FLAG:
    getline(cin,line);  // get a line of command
    int pos = 0;
    while (line[pos] == ' ')
    {
        pos ++;
    }
    line = line.substr(pos);
    argv = split(line,' ');
    if(line.empty())
    {
        Prompt news;
        news.PrintPrompt();
        goto FLAG;
    }
}

void ish::LineClear()
{
    line.clear();
}

bool Command::isClear()
{
    if(line == "clear"||line == "cls")
    {    
        system("clear");
        return true;
    }
    return false;
}

void Command::isExit()
{
    if(line == "exit")
        exit(EXIT_SUCCESS);
}

bool isH(string line)
{
    if(line=="?")
    {
        help();
        return true;
    }
    if(line=="!")
    {
        show();
        return true;
    }
    return false;
}

void Command::Process()
{
    if(isH(line))
        return;
    vector<int *>vpipes;
    vector<string>v = split(line,'|');
    if(v.size()==1)
    {
        argv = split(v[0],' ');
        ExeCommand();
    }
    else
    {
        for(int i = 0;i<v.size()-1;i++)
        {
            int * fd = new int[2];
            pipe(fd);
            fds.push_back(fd);
        }

        for(int i = 0;i<v.size();i++)
        {
            argv = split(v[i],' ');
            ExeCommand();

            if(ExeCount != 0)close(fds[ExeCount-1][0]);
            if(ExeCount != fds.size())close(fds[ExeCount][1]);    

            ExeCount ++;
        }
        ExeCount = 0;
        fds.clear();
    }
}

void Command::ExeCommand()
{
    vector<char *>ar = fromStoC(argv);

    if(isClear()||iscd())
        return;
    isExit();

    pid_t pid = fork();
    
    if(pid == 0)
    {   

        if(ExeCount != 0)dup2(fds[ExeCount-1][0],0);
        if(ExeCount != fds.size())dup2(fds[ExeCount][1],1);
        
        if(isRedirect(line))
        {
            for(int i = 0;i<argv.size();i++)
            {
                if(argv[i]=="<")
                {
                    int fd = open(argv[i+1].data(),O_RDONLY|O_CREAT);
                    dup2(fd,0);
                    ar.erase(ar.begin()+i);
                    close(fd);
                }
                if(argv[i]==">")
                {
                    int fd = open(argv[i+1].data(),O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
                    dup2(fd,1);
                    ar.erase(ar.begin()+i);
                    ar.erase(ar.begin()+i+1);
                    close(fd);
                }
                if(argv[i]==">>")
                {
                    int fd = open(argv[i+1].data(),O_RDWR|O_APPEND|O_CREAT,S_IRUSR|S_IWUSR);
                    dup2(fd,1);
                    ar.erase(ar.begin()+i);
                    ar.erase(ar.begin()+i+1);
                    close(fd);
                }
            }
        }

        ar.push_back(NULL);

        if(strcmp(ar[0],"ls")==0)
        {
            ar.pop_back();
            ar.push_back((char *)"--color=auto");
            ar.push_back(NULL);
        }

        if(execvp(ar[0],ar.data())==-1)
        {
            isError = true;
            cout<<"ish: command not found: "<<argv[0]<<endl;
        }
        
    }
    wait(&pid);
    if           (strcmp(ar[0],"cat")==0)
    {
        cout<<endl;
    }
}

bool ish::iscd()
{
    if(argv[0]!="cd")
        return 0;
    
    char * homepath = getenv("HOME");
    if(argv[0] == "cd"&&argv.size()==1)
        argv.push_back(homepath);

    
    if(argv[1]=="-")
    {
        char * lpath = getenv("OWD");
        cout<<lpath<<endl;
        if(chdir(lpath)==-1)
        {
            isError = true;
        }
        wdPath = lpath;
        return 1;
    }
    char rp[1000];
    realpath(argv[1].c_str(),rp);
    if(chdir(argv[1].c_str())==-1)
    {
        cout<<"cd: path not found"<<endl;
        isError = true;
        return 1;
    }
    
    setenv("OWD",wdPath.c_str(),1);
    wdPath = rp;

    return 1;
}

void help()
{
    cout<<"你知道吗？输入!可以观看炫酷的动画。"<<endl;
}