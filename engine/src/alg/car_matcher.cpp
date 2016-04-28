/*
 * car_matcher.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: haoquan
 */

#include <glog/logging.h>
#include "car_matcher.h"

namespace dg {
#define FEATURE_NUM_CUDA 256

#if not USE_CUDA
CarMatcher::CarMatcher() {
    feature_num_ = FEATURE_NUM_CUDA;
//    orb_ = ORB(feature_num_);
    max_resize_size_ = 300;
    max_mis_match_ = 50;
    min_remarkableness_ = 0.8;
    max_mapping_offset_ = 50;
    selected_area_weight_ = 50;
    profile_time_ = false;
}

CarMatcher::~CarMatcher() {
}
#endif

<<<<<<< HEAD
void CarMatcher::ExtractDescriptor(const Mat &img, CarRankFeature &des) {
    if (profile_time_)
        t_profiler_feature_.Reset();
    des.height_ = img.rows;
    des.width_ = img.cols;
    Mat resize_img;
    Size new_size;
    calcNewSize(des.height_, des.width_, new_size);
    if (img.channels() != 3)
        LOG(WARNING)<<"Color image is required.";
    if ((img.rows < 10) || (img.cols < 10))
        LOG(WARNING)<<"Image needs to be larger than 10*10 to extract enough feature.";
    resize(img, resize_img, new_size);
    orb_(resize_img, Mat(), key_point_, descriptor_);
    if (key_point_.size() < 50)
        LOG(WARNING)<<"Not enough feature extracted.";
    descriptor_.copyTo(des.descriptor_);
    des.position_ = Mat::zeros(key_point_.size(), 2, CV_16UC1);
    for (int i = 0; i < key_point_.size(); i++) {
        des.position_.at<ushort>(i, 0) = ((ushort) key_point_[i].pt.x);
        des.position_.at<ushort>(i, 1) = ((ushort) key_point_[i].pt.y);
    }
    if (profile_time_) {
        t_profiler_str_ = "Descriptor";
        t_profiler_feature_.Update(t_profiler_str_);
    }
}

int CarMatcher::ComputeMatchScore(const CarRankFeature &des1, const CarRankFeature &des2, const Rect &box) {
=======
//void CarMatcher::ExtractDescriptor(const Mat &img, CarRankFeature &des) {
//    if (profile_time_)
//        t_profiler_feature_.Reset();
//
//    des.height_ = img.rows;
//    des.width_ = img.cols;
//    Mat resize_img;
//    Size new_size;
//    calcNewSize(des.height_, des.width_, new_size);
//
//    if (img.channels() != 3)
//        LOG(WARNING)<<"Color image is required.";
//    if ((img.rows < 10) || (img.cols < 10))
//        LOG(WARNING)<<"Image needs to be larger than 10*10 to extract enough feature.";
//    resize(img, resize_img, new_size);
//
//    orb_(resize_img, Mat(), key_point_, descriptor_);
//    if (key_point_.size() < 50)
//        LOG(WARNING)<<"Not enough feature extracted.";
//
//    descriptor_.copyTo(des.descriptor_);
//    des.position_ = Mat::zeros(key_point_.size(), 2, CV_16UC1);
//
//    for (int i = 0; i < key_point_.size(); i++) {
//        des.position_.at<ushort>(i, 0) = ((ushort) key_point_[i].pt.x);
//        des.position_.at<ushort>(i, 1) = ((ushort) key_point_[i].pt.y);
//    }
//
//    if (profile_time_) {
//        t_profiler_str_ = "Descriptor";
//        t_profiler_feature_.Update(t_profiler_str_);
//    }
//}

int CarMatcher::ComputeMatchScore(const CarRankFeature &des1,
                                  const CarRankFeature &des2, const Rect &box) {
>>>>>>> origin
    if (profile_time_)
        t_profiler_matching_.Reset();
    Rect box1, box2;
    calcNewBox(des1, des2, box, box1, box2);
    int score = 0;
    for (int i = 0; i < des1.descriptor_.rows; i++) {
        uint min_dist = 9999;
        uint sec_dist = 9999;
        int min_idx = -1, sec_idx = -1;
        const uchar* query_feat = des1.descriptor_.ptr<uchar>(i);
        for (int j = 0; j < des2.descriptor_.rows; j++)
            if (calcDis2(des1.position_.at<ushort>(i, 0),
                         des1.position_.at<ushort>(i, 1),
                         des2.position_.at<ushort>(j, 0),
                         des2.position_.at<ushort>(j, 1))
                    < max_mapping_offset_ * max_mapping_offset_) {
                const uchar* train_feat = des2.descriptor_.ptr(j);
                uint dist = calcHammingDistance(query_feat, train_feat);
                if (dist < min_dist) {
                    sec_dist = min_dist;
                    sec_idx = min_idx;
                    min_dist = dist;
                    min_idx = j;
                } else if (dist < sec_dist) {
                    sec_dist = dist;
                    sec_idx = j;
                }
            }
        if ((min_dist <= (unsigned int) (min_remarkableness_ * sec_dist))
                && (min_dist <= (unsigned int) max_mis_match_)) {
            if ((inBox(des1.position_.at<ushort>(i, 0),
                       des1.position_.at<ushort>(i, 1), box1))
                    && (inBox(des2.position_.at<ushort>(min_idx, 0),
                              des2.position_.at<ushort>(min_idx, 1), box2))) {
                score = score + selected_area_weight_;
            } else
                score++;
        }
    }
    if (profile_time_) {
        t_profiler_str_ = "Matching";
        t_profiler_matching_.Update(t_profiler_str_);
    }
    return score;
}

<<<<<<< HEAD
void CarMatcher::calcNewBox(
    const CarRankFeature &des1,
    const CarRankFeature &des2, 
    const Rect &box, Rect &box1, Rect &box2) {
=======
void CarMatcher::calcNewBox(const CarRankFeature &des1,
                            const CarRankFeature &des2, const Rect &box,
                            Rect &box1, Rect &box2) {
>>>>>>> origin
    if (box.x > 0) {
        float resize_rto1 = max(des1.height_, des1.width_);
        resize_rto1 = ((float) max_resize_size_) / resize_rto1;
        box1.x = box.x * resize_rto1;
        box1.y = box.y * resize_rto1;
        box1.width = box.width * resize_rto1;
        box1.height = box.height * resize_rto1;
        float resize_rto2 = max(des2.height_, des2.width_);
        resize_rto2 = ((float) max_resize_size_) / resize_rto2;
        box2.x = box.x * resize_rto2 - max_mapping_offset_;
        box2.y = box.y * resize_rto2 - max_mapping_offset_;
        box2.width = box.width * resize_rto2 + max_mapping_offset_ * 2;
        box2.height = box.height * resize_rto2 + max_mapping_offset_ * 2;
    } else {
        box1.x = 0;
        box1.y = 0;
        box1.width = max_resize_size_;
        box1.height = max_resize_size_;
        box2.x = 0;
        box2.y = 0;
        box2.width = max_resize_size_;
        box2.height = max_resize_size_;
    }
}

<<<<<<< HEAD
vector<int> CarMatcher::computeMatchScoreCpu(const CarRankFeature &des, const Rect &in_box, const vector<CarRankFeature> &all_des)
{
=======
vector<int> CarMatcher::computeMatchScoreCpu(
        const CarRankFeature &des, const Rect &in_box,
        const vector<CarRankFeature> &all_des) {
>>>>>>> origin
    vector<int> score;
    for (int i = 0; i < all_des.size(); i++) {
        score.push_back(ComputeMatchScore(des, all_des[i], in_box));
    }
    return score;
}

<<<<<<< HEAD
vector<int> CarMatcher::ComputeMatchScore(const CarRankFeature &des, const Rect &in_box, const vector<CarRankFeature> &all_des)
{
=======
vector<int> CarMatcher::ComputeMatchScore(
        const CarRankFeature &des, const Rect &in_box,
        const vector<CarRankFeature> &all_des) {
>>>>>>> origin
#if USE_CUDA
    return computeMatchScoreGpu(des, in_box, all_des);
#else
    return computeMatchScoreCpu(des, in_box, all_des);
#endif
}

<<<<<<< HEAD
=======
}

>>>>>>> origin
