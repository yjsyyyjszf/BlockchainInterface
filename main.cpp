#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <thread>

using namespace std;

void openNewTerminalWindow();
string getTerminalID();
string GetStdoutFromCommand(string cmd);
void startupSequence(string path);
void shutdownSequence(string path);
void print20();
void openConsoleThreaded();

void openConsoleThreaded() {
    system("gnome-terminal");
    system("echo terminal 1 > /dev/pts/0");
}

void print20() {
    for (int i = 0; i < 20; i++)
        cout << i << endl;
}

int main() {
    int i = 20;
    thread t(openConsoleThreaded);
    thread t2(openConsoleThreaded);
    system("echo I like big tiddies");
    string sawDefaultPath = "~/BlockchainStuff/Sawtooth/sawtooth-default.yaml";

    cout << getTerminalID() << endl;
    //openNewTerminalWindow();
    t.join();
    t2.join();
    cout << "Program done" << endl;
    //startupSequence(sawDefaultPath);
    //shutdownSequence(sawDefaultPath);

    return 0;
}

void openNewTerminalWindow() {
    system("gnome-terminal");
    //cout << getTerminalID() << endl;
}


string getTerminalID() {
    string cmd = "tty";
    return GetStdoutFromCommand(cmd);
}

string GetStdoutFromCommand(string cmd) {
    string data;
    FILE* stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        }
        pclose(stream);
    }

    return data;
}

void startupSequence(string path) {
    system(("docker-compose -f " + path + " up").c_str());
    system("echo Yay tiddies, it gracefully shutdown");
}

void shutdownSequence(string path) {
    system(("docker-compose -f " + path + " down").c_str());
    system("echo IT IS DONE, BRUH");
}