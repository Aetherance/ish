#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<pwd.h>

using namespace std;

void nosignal();
vector<string> split(string,char);
vector<char*>fromStoC(vector<string>);
bool isRedirect(string);

class ish
{
friend vector<string>split(string,char);
friend bool isRedirect(string);

public:
    void GetCommand();
    void LineClear();
    bool iscd();

    ish()
    {
        char path[64];
        realpath(".",path);
        wdPath = path;
        setenv("OWD",".",1);
        char hostname[64];
        gethostname(hostname,64);
        hostName = hostname;
        int userid = getuid();
        struct passwd * pwd = getpwuid(userid);
        userName = pwd->pw_name;
    }

protected:
    string hostName;
    string userName;
    string gitHEAD = "master";
    static string wdPath;
    static string line;
    static vector<string>argv;
    static vector<int *>fds;
    static int ExeCount;
    static bool pipeError;
    int PromptLen;
    static bool isError;
};

class Prompt: public ish
{
public:
    void PrintPrompt();
    Prompt()
    {
        failed = "\e[100m\e[31m ✘\e[39m";
        isError = false;
    }

private:
    string colors;
    string output;
    string failed;
};

class Command: public Prompt
{
public:
    bool isClear();
    void isExit();
    void ExeCommand();
    void Process();
};