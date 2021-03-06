/*============================================================================
 * File Name   : feature_serializer.h
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/15/2016
 * Description : 
 * ==========================================================================*/
#ifndef MATRIX_RANKER_FEATURE_SERIALIZER_H_
#define MATRIX_RANKER_FEATURE_SERIALIZER_H_

#include <string>
#include <vector>
#include <set>
#include <glog/logging.h>
#include <opencv2/core/core.hpp>

using namespace std;

namespace dg {

const int CAR_FEATURE_ORB_ROWS_MAX = 256;
const int CAR_FEATURE_ORB_COLS_MAX = 32;
const int CAR_FEATURE_DES_MAX_SIZE = CAR_FEATURE_ORB_ROWS_MAX * CAR_FEATURE_ORB_COLS_MAX;

class Score {
 public:
    int index_;
    float score_;

    Score() {
    }

    Score(int index, float score)
        : index_(index),
          score_(score) {
    }

    Score(const Score &s)
        : index_(s.index_),
          score_(s.score_) {
    }

    virtual ~Score() {
    }

    //sortable: score[desc] >> index[asc]
    bool operator<(const Score &right) const {
        return score_ != right.score_ ?
               (score_ > right.score_) : (index_ < right.index_);
    }
};

class RankFeature {
 public:
    virtual string Serialize() const {
    };
    virtual bool Deserialize(string featureStr) {
    };

 protected:
    template<typename T>
    static void ConvertToByte(T value, vector<uchar> &data) {
        uchar *ptr = (uchar *) (&value);
        copy(ptr, ptr + sizeof(T), back_inserter(data));
    }

    template<typename T>
    static void ConvertToValue(T *value, vector<uchar> data) {
        uchar *ptr = (uchar *) value;
        for (int i = 0; i < sizeof(T); i++) {
            ptr[i] = data[i];
        }
    }
};

class CarRankFeature final: public RankFeature {
 public:
    ushort width_;
    ushort height_;
    cv::Mat descriptor_;
    cv::Mat position_;

    virtual string Serialize() const override;
    virtual bool Deserialize(string featureStr) override;
};

class FaceRankFeature final: public RankFeature {
 public:
    string id_;
    std::vector<float> feature_;
    std::string name_;
    std::map<string, std::set<string>> attributes_;
    std::string image_uri_;
    cv::Mat image_;

    virtual string Serialize() const override;
    virtual bool Deserialize(string featureStr) override;

    friend ostream &operator<<(std::ostream &os, const FaceRankFeature &f) {
        os << "ID: " << f.id_ << ", feature:" << f.feature_.size() << ", image uri: " << f.image_uri_
            << ", attributes: {";
        for (auto itr = f.attributes_.begin(); itr != f.attributes_.end(); ++itr) {
            os << "\"" << itr->first << "\"" << ":" << "[";
            for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2) {
                os << *itr2 << ",";
            }
            os << "]";

        }
        os << "}" << endl;
        return os;

    }
};

}

#endif //MATRIX_RANKER_FEATURE_SERIALIZER_H_
