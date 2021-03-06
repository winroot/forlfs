/*
 * display.h
 *
 *  Created on: Jan 5, 2016
 *      Author: haoquan
 */

#ifndef SRC_UTIL_DISPLAY_H_
#define SRC_UTIL_DISPLAY_H_
#include <GL/gl.h>
#include <GL/glut.h>
#include "model/model.h"
#include "io/ringbuffer.h"

namespace dg {
class Displayer {
public:
    Displayer(RingBuffer *buffer, const string winName, int width, int height,
              int snapWidth, int snapHeight, const int fps);

    void Update(Frame *frame);
    void Run();
    void displayFrame();
    void timeFunc(int n);
    void render(Frame *frame);

private:
    static Displayer *self_;
    static void glutDisplayIt();
    static void glutTimerFuncIt(int n);
    static void glutIdleIt();


private:
    string win_name_;
    int width_;
    int height_;
    int snap_width_;
    int snap_height_;
    int fps_;
    int frame_iterval_;
    int display_pointer_;
    RingBuffer *ring_buffer_;

};
}
#endif /* SRC_UTIL_DISPLAY_H_ */
