#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>

using namespace std;

void nosignal();
vector<string> split(string,char);
vector<char*>fromStoC(vector<string>);

class ish
{
friend vector<string>split(string,char);
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
    }

protected:
    string hostName = "TheINK";
    string userName = "user";
    static string wdPath;
    string gitHEAD = "master";
    static string line;
    static vector<string>argv;
    static vector<int *>fds;
    static int ExeCount;

    int PromptLen;
    static bool isError;
};

class Prompt: public ish
{
public:
    void PrintPrompt();
    void PrintPrompt(int FAILED);
    Prompt()
    {
        colors = (string)"\e[100m" + "\e[90m" + "\e[104m" + "\e[43m" + "\e[34m" + "\e[33m" + "\e[39m" + "\e[33m" + "\e[49m" + "\e[39m";
        output;
        failed = "\e[100m\e[31m ✘\e[39m";
        isError = false;
    }

private:
    string colors;
    string output;
    string failed;
};

class Command: public ish
{
public:
    bool isClear();
    void isExit();
    void ExeCommand();
    void Process();


private:
    
};