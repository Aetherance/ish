#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<string.h>
#include<sys/wait.h>

using namespace std;

void nosignal();
vector<string> split(string);
vector<char*>fromStoC(vector<string>);

class ish
{
public:
    void GetCommand();
    void LineClear();

protected:
    string hostName = "TheINK";
    string userName = "user";
    string wdPath = "~/CODE/ish";
    string gitHEAD = "master";
    static string line;
    static vector<string>argv;

    int PromptLen;
};

class Prompt: public ish
{
public:
    bool isError;
    void PrintPrompt();
    void PrintPrompt(int FAILED);
    Prompt()
    {
        colors = (string)"\e[100m" + "\e[90m" + "\e[104m" + "\e[43m" + "\e[34m" + "\e[33m" + "\e[39m" + "\e[33m" + "\e[49m" + "\e[39m";
        output = "\e[100m" + (string)" " + userName + "@" + hostName + " " + (string)"\e[90m" + (string)"\e[104m" + "" + " " + wdPath + " " + "\e[43m" + "\e[34m" + "" + "\e[33m" + "  " + gitHEAD + " ± " + "\e[33m" + "\e[49m" + "" + "\e[39m\e[0m";
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
    void isClear();
    void isExit();
    void ExeCommand();

private:
    
};