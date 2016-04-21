/*============================================================================
 * File Name   : ranker_service.h
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/15/2016
 * Description : 
 * ==========================================================================*/

#ifndef MATRIX_RANKER_RANKER_SERVICE_H_
#define MATRIX_RANKER_RANKER_SERVICE_H_

#include <vector>
#include <opencv2/core/core.hpp>

#include "model/rank_feature.h"

using namespace cv;
using namespace std;

namespace dg 
{

template <typename F>
class RankService
{
static_assert(std::is_base_of<RankFeature, F>::value, "F must derive from RankFeature");

public:
    F Deserialize(string featureStr) const
    {
        F feature;
        feature.Deserialize(featureStr);
        return feature;
    }

    string Serialize(F& feature) const
    {
        return feature.Serialize();
    }

    virtual vector<Score> Rank(const Mat& image, const Rect& hotspot, const vector<F>& candidates);
};

class CarRankService final : RankService<CarFeature>
{
private:
    CarRankEngine engine_;

    virtual vector<Score> Rank(const Mat& image, const Rect& hotspot, const vector<CarFeature>& candidates) override
    {
        return engine_.Rank(image, hotspot, candidates);
    }
};

class FaceRankService final : RankService<FaceFeature>
{
private:
    FaceRankEngine engine_;

    virtual vector<Score> Rank(const Mat& image, const Rect& hotspot, const vector<FaceFeature>& candidates) override
    {
        return engine_.Rank(image, hotspot, candidates);
    }
};


}

#endif //MATRIX_RANKER_RANKER_SERVICE_H_