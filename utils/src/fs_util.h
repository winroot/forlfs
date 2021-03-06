/*
 * fs_util.h
 *
 *  Created on: 22/03/2016
 *      Author: chenzhen
 */

#ifndef FS_UTIL_H_
#define FS_UTIL_H_

#include <stdio.h>
#include <string>
#include <string.h>
#include <cstdio>
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;
namespace dg {
static long FileSize(const string &file) {
    ifstream is;
    is.open(file.c_str(), ios::binary|ios::ate);

    // get length of file:
    is.seekg(0, std::ios::end);

    long length = is.tellg();
    is.seekg(0, std::ios::beg);
    is.close();
    return length;
}
static int WriteToFile(string filePath, char *data, unsigned int size) {
    FILE *file = fopen(filePath.c_str(), "wr");
    if (file == NULL) {
        return -1;
    }

    fwrite(data, sizeof(char), size, file);
    fflush(file);
    fclose(file);
    return 1;
}

static void ReadFromFile(string filePath, char *data, int &length, string mode) {
    length = FileSize(filePath);
    FILE *file = fopen(filePath.c_str(), mode.c_str());
    if (file == NULL) {
        return;
    }
    cout << "File len: " << length << endl;
    data = (char *)malloc(length);

    length = fread(data, sizeof(char), length, file);
    cout<<length<<endl;
    fclose(file);
    return;
}

static string ReadStringFromFile(string filePath, string mode) {
    long length = FileSize(filePath);
    FILE *file = fopen(filePath.c_str(), mode.c_str());
    if (file == NULL) {
        return "";
    }
    char *data = (char *)malloc(length);
    memset(data, 0, length);
    length = fread(data, sizeof(char), length, file);
    fclose(file);
    string result(data,length);
    free(data);
    return result;
}
// TODO
static bool CheckExists(string filepath) {
    return false;
}

}
#endif /* FS_UTIL_H_ */
