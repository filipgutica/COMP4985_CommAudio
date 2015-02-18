/*****************************************
* functions demonstrates how you can scan and read an entire directory for files.
* We can use this with a directory of .wav as our "database" of audio files. 
* Our server can scan a directory for .wav files and display them in a list in the UI
* and send the list to the client. 
* This uses the <dirent.h> library and the readdir() and opendir() functions. 
*
* got the function from: http://www.cplusplus.com/forum/beginner/9173/ 
*****************************************/
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>

void listFile();

int main(){
    listFile();
    return 0;
}

void listFile(){
        DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir("./data/item") ){
                while(entry = readdir(pDIR)){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                        cout << entry->d_name << "\n";
                }
                closedir(pDIR);
        }
}