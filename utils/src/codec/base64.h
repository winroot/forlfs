/*============================================================================
 * File Name   : base64.h
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/15/2016
 * Description : 
 * ==========================================================================*/
#ifndef MATRIX_UTIL_CODEC_BASE64_H_
#define MATRIX_UTIL_CODEC_BASE64_H_

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
const int CHARS_PER_LINE = 72;
typedef enum
{
    step_A, step_B, step_C
} base64_encodestep;

typedef struct
{
    base64_encodestep step;
    char result;
    int stepcount;
} base64_encodestate;
typedef enum
{
    step_a, step_b, step_c, step_d
} base64_decodestep;

typedef struct
{
    base64_decodestep step;
    char plainchar;
} base64_decodestate;

static int base64_decode_value(char value_in)
{
    static const char decoding[] =
    { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,
            -2, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1,
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
            43, 44, 45, 46, 47, 48, 49, 50, 51 };
    static const char decoding_size = sizeof(decoding);
    value_in -= 43;
    if (value_in < 0 || value_in >= decoding_size)
        return -1;
    return decoding[(int) value_in];
}

static void base64_init_decodestate(base64_decodestate* state_in)
{
    state_in->step = step_a;
    state_in->plainchar = 0;
}

static int base64_decode_block(const char* code_in, const int length_in,
        char* plaintext_out, base64_decodestate* state_in)
{
    const char* codechar = code_in;
    char* plainchar = plaintext_out;
    char fragment;

    *plainchar = state_in->plainchar;

    switch (state_in->step)
    {
        while (1)
        {
            case step_a:
            do
            {
                if (codechar == code_in + length_in)
                {
                    state_in->step = step_a;
                    state_in->plainchar = *plainchar;
                    return plainchar - plaintext_out;
                }
                fragment = (char) base64_decode_value(*codechar++);
            } while (fragment < 0);
            *plainchar = (fragment & 0x03f) << 2;
            case step_b:
            do
            {
                if (codechar == code_in + length_in)
                {
                    state_in->step = step_b;
                    state_in->plainchar = *plainchar;
                    return plainchar - plaintext_out;
                }
                fragment = (char) base64_decode_value(*codechar++);
            } while (fragment < 0);
            *plainchar++ |= (fragment & 0x030) >> 4;
            *plainchar = (fragment & 0x00f) << 4;
            case step_c:
            do
            {
                if (codechar == code_in + length_in)
                {
                    state_in->step = step_c;
                    state_in->plainchar = *plainchar;
                    return plainchar - plaintext_out;
                }
                fragment = (char) base64_decode_value(*codechar++);
            } while (fragment < 0);
            *plainchar++ |= (fragment & 0x03c) >> 2;
            *plainchar = (fragment & 0x003) << 6;
            case step_d:
            do
            {
                if (codechar == code_in + length_in)
                {
                    state_in->step = step_d;
                    state_in->plainchar = *plainchar;
                    return plainchar - plaintext_out;
                }
                fragment = (char) base64_decode_value(*codechar++);
            } while (fragment < 0);
            *plainchar++ |= (fragment & 0x03f);
        }
    }
    /* control should not reach here */
    return plainchar - plaintext_out;
}


static void base64_init_encodestate(base64_encodestate* state_in)
{
    state_in->step = step_A;
    state_in->result = 0;
    state_in->stepcount = 0;
}

static char base64_encode_value(char value_in)
{
    static const char* encoding =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (value_in > 63)
        return '=';
    return encoding[(int) value_in];
}

static int base64_encode_block(const char* plaintext_in, int length_in, char* code_out,
        base64_encodestate* state_in)
{
    const char* plainchar = plaintext_in;
    const char* const plaintextend = plaintext_in + length_in;
    char* codechar = code_out;
    char result;
    char fragment;

    result = state_in->result;

    switch (state_in->step)
    {
        while (1)
        {
            case step_A:
            if (plainchar == plaintextend)
            {
                state_in->result = result;
                state_in->step = step_A;
                return codechar - code_out;
            }
            fragment = *plainchar++;
            result = (fragment & 0x0fc) >> 2;
            *codechar++ = base64_encode_value(result);
            result = (fragment & 0x003) << 4;
            case step_B:
            if (plainchar == plaintextend)
            {
                state_in->result = result;
                state_in->step = step_B;
                return codechar - code_out;
            }
            fragment = *plainchar++;
            result |= (fragment & 0x0f0) >> 4;
            *codechar++ = base64_encode_value(result);
            result = (fragment & 0x00f) << 2;
            case step_C:
            if (plainchar == plaintextend)
            {
                state_in->result = result;
                state_in->step = step_C;
                return codechar - code_out;
            }
            fragment = *plainchar++;
            result |= (fragment & 0x0c0) >> 6;
            *codechar++ = base64_encode_value(result);
            result = (fragment & 0x03f) >> 0;
            *codechar++ = base64_encode_value(result);

            ++(state_in->stepcount);
            if (state_in->stepcount == CHARS_PER_LINE / 4)
            {
                *codechar++ = '\n';
                state_in->stepcount = 0;
            }
        }
    }
    /* control should not reach here */
    return codechar - code_out;
}

static int base64_encode_blockend(char* code_out, base64_encodestate* state_in)
{
    char* codechar = code_out;

    switch (state_in->step)
    {
        case step_B:
            *codechar++ = base64_encode_value(state_in->result);
            *codechar++ = '=';
            *codechar++ = '=';
            break;
        case step_C:
            *codechar++ = base64_encode_value(state_in->result);
            *codechar++ = '=';
            break;
        case step_A:
            break;
    }
    *codechar++ = '\n';

    return codechar - code_out;
}

namespace dg {
class Base64 {
public:
    static int Encode(char value) {
        return base64_encode_value(value);
    }

    static int Encode(const char *buffer_in, int buffer_in_len, char *buffer_out) {
        int buffer_out_len;

        base64_encodestate state;
        base64_init_encodestate(&state);

        buffer_out_len = base64_encode_block(buffer_in, buffer_in_len, buffer_out, &state);
        buffer_out_len += encodeEnd(buffer_out + buffer_out_len, &state);
        return buffer_out_len;
    }

    static void Encode(istream &input, ostream &output) {
        char buffer_out[2 * BUFSIZ], buffer_in[BUFSIZ];
        int buffer_out_len, buffer_in_len;

        base64_encodestate state;
        base64_init_encodestate(&state);

        while (input.good()) {
            input.read(buffer_in, BUFSIZ);
            buffer_in_len = input.gcount();
            buffer_out_len = base64_encode_block(buffer_in, buffer_in_len, buffer_out, &state);
            output.write((const char *) buffer_out, buffer_out_len);
        }

        buffer_out_len = encodeEnd(buffer_out, &state);
        output.write(buffer_out, buffer_out_len);

        output.flush();
    }

    template<typename T>
    static string Encode(const vector<T> input_data) {
        stringstream ss_in, ss_out;
        for (int i = 0; i < input_data.size(); i++) {
            ss_in.write((char *) &input_data[i], sizeof(T));
        }
        Encode(ss_in, ss_out);
        return ss_out.str();
    }

    static int Decode(char value) {
        return base64_decode_value(value);
    }

    static int Decode(const char *buffer_in, int buffer_in_len, char *buffer_out) {
        base64_decodestate state;
        base64_init_decodestate(&state);

        return base64_decode_block(buffer_in, buffer_in_len, buffer_out, &state);
    }

    static void Decode(istream &input, ostream &output) {
        char buffer_out[BUFSIZ], buffer_in[BUFSIZ];
        int buffer_out_len, buffer_in_len;

        base64_decodestate state;
        base64_init_decodestate(&state);

        while (input.good()) {
            input.read(buffer_in, BUFSIZ);
            buffer_in_len = input.gcount();
            buffer_out_len = base64_decode_block(buffer_in, buffer_in_len, buffer_out, &state);
            output.write((const char *) buffer_out, buffer_out_len);
        }
    }

    template<typename T>
    static void Decode(const string &base64_string, vector<T> &result_array) {
        stringstream ss_in, ss_out;
        ss_in << base64_string;
        Decode(ss_in, ss_out);

        T temp;
        while (ss_out.good()) {
            ss_out.read((char *) (&temp), sizeof(T));
            result_array.push_back(temp);
        }
    }

private:
    static int encodeEnd(char *buffer_in, base64_encodestate *state) {
        return base64_encode_blockend(buffer_in, state);
    }
}; //end of class Base64
} //end of namespace dg

#endif // MATRIX_UTIL_CODEC_BASE64_H_
