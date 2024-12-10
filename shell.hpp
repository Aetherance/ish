#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/ioctl.h>


using namespace std;

class ish
{
public:

    void PrintPrompt();
    void GetCommand();


private:
    string hostName = "TheINK";
    string userName = "user";
    string wdPath = "~/CODE/ish";
    string gitHEAD = "master";
    string line;

    int PromptLen;
};