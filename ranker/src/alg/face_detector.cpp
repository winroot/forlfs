/*============================================================================
 * File Name   : face_detector.cpp
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/19/2016
 * Description : 
 * ==========================================================================*/

#include "face_detector.h"
using namespace dg;

FaceDetector::FaceDetector(string align_model, string avg_face)
        : _detector(dlib::get_frontal_face_detector()) 
{
    dlib::deserialize(align_model) >> _sp;

    Mat avg_face_img = imread(avg_face);
    dlib::cv_image<dlib::bgr_pixel> avg_face_image(avg_face_img);

    vector<dlib::rectangle> avg_face_bbox = _detector(avg_face_image);
    assert(avg_face_bbox.size() == 1);

    predict(avg_face_image, avg_face_bbox[0], _avg_face_points);
}

FaceDetector::~FaceDetector() 
{

}

bool FaceDetector::predict(dlib::cv_image<dlib::bgr_pixel>& image, dlib::rectangle& bbox, vector<dlib::point>& points)
{
    dlib::full_object_detection shape = _sp(image, bbox);
    if (shape.num_parts() != _avg_face_points.size())
    {
        return false;
    }

    for (unsigned long i = 0; i < shape.num_parts(); i++)
    {
        points.push_back(shape.part(i));
    }
    return true;
}


Mat FaceDetector::transform(dlib::cv_image<dlib::bgr_pixel>& image, vector<dlib::point>& points)
{
    dlib::array2d<dlib::bgr_pixel> out(128, 128);    
    dlib::point_transform_affine trans = find_affine_transform(_avg_face_points, points);
    transform_image(image, out, dlib::interpolate_bilinear(), trans);
    return toMat(out).clone();
}

void FaceDetector::Detect(vector<cv::Mat>& images, vector<vector<Mat>>& vvResults, vector<vector<BoundingBox>>& vvBoxes)
{
    for(Mat& image : images)
    {
        dlib::cv_image<dlib::bgr_pixel> dlibImg(image);
        vector<dlib::rectangle> faceBoxes = _detector(dlibImg);

        vector<Mat> results;
        vector<BoundingBox> vboxes;
        for(dlib::rectangle& bbox : faceBoxes)
        {
            vector<dlib::point> points;
            if (predict(dlibImg, bbox, points))
            {
                results.push_back(transform(dlibImg, points));

                struct BoundingBox box;
                box.rect.x = bbox.left();
                box.rect.y = bbox.right();
                box.rect.width = bbox.width();
                box.rect.height = bbox.height();
                vboxes.push_back(box);
            }
        }

        vvBoxes.push_back(vboxes);
        vvResults.push_back(results);
    }
}

void FaceDetector::Detect(Mat& image, vector<BoundingBox> boxes, vector<Mat>& results)
{
    dlib::cv_image<dlib::bgr_pixel> dlibImg(image);

    for(BoundingBox& box : boxes)
    {
        dlib::rectangle bbox(box.rect.x, box.rect.y, 
            box.rect.x + box.rect.width, box.rect.y + box.rect.height);

        vector<dlib::point> points;
        if (predict(dlibImg, bbox, points))
        {
            results.push_back(transform(dlibImg, points));
        }
    }
}

void FaceDetector::Align(vector<Mat>& images, vector<Mat>& results)
{
    for(Mat& image : images)
    {
        dlib::cv_image<dlib::bgr_pixel> dlibImg(image);
        dlib::rectangle bbox(0, 0, image.cols, image.rows);

        vector<dlib::point> points;
        if (predict(dlibImg, bbox, points))
        {
            results.push_back(transform(dlibImg, points));
        }
    }
}