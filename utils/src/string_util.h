/*
 * string_util.h
 *
 *  Created on: Feb 24, 2016
 *      Author: chenzhen
 */

#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <b64/encode.h>
#include <boost/locale/encoding_utf.hpp>
#include "fs_util.h"

using namespace std;
using namespace cv;

namespace dg {

static wstring utf8_to_wstring(const string &str) {
    return boost::locale::conv::utf_to_utf<wchar_t>(str.c_str(),
                                                    str.c_str() + str.size());
}

static string findPrefix(const string s, const char sep) {
    int pos = s.find_first_of(sep);
    if (pos == string::npos) {
        return "";
    }
    return s.substr(0, pos);
}

static string findPostfix(const string s, const char sep) {
    int pos = s.find_last_of(sep);
    if (pos == string::npos) {
        return "";
    }
    return s.substr(pos + 1);
}

static base64::encoder base64Encoder;
static string encode2base64(char *data, int size) {
    stringstream ss;
    ss.write(data, sizeof(unsigned char) * size);
    stringstream encoded;
    base64Encoder.encode(ss, encoded);
    return encoded.str();
}
static string encode2base64(const char *filePath) {
    int length = FileSize(string(filePath));
    FILE *file = fopen(filePath, "rb");
    if (file == NULL) {
        return "";
    }
    char data[length];

    length = fread(data, sizeof(char), length, file);
    fclose(file);
    return encode2base64(data, length);
}

static void trimLR(string &s) {

    if (!s.empty() && (s[0] == ' ' || s[s.length() - 1] == ' ')) {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }

}

//static string encode2JPEGInBase64(cv::Mat &data) {
//    vector < uchar > buff;
//    cv::imencode(".jpg", data, buff);
//    return encode2base64((char*) buff.data(), buff.size());
//}
}
#endif /* STRING_UTIL_H_ */
