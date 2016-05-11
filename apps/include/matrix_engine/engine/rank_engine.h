/*============================================================================
 * File Name   : rank_engine.h
 * Author      : yanlongtan@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 04/15/2016
 * Description : 
 * ==========================================================================*/

#ifndef MATRIX_ENGINE_RANK_ENGINE_H_
#define MATRIX_ENGINE_RANK_ENGINE_H_

#include <glog/logging.h>
#include "processor/processor.h"
#include "model/model.h"
#include "model/rank_feature.h"
#include "config.h"

namespace dg {

class RankEngine {

};

class CarRankEngine : public RankEngine {
 public:
    CarRankEngine();
    virtual ~CarRankEngine();

    vector<Score> Rank(const Mat& image, const Rect& hotspot,
                       const vector<CarRankFeature>& candidates);

 private:
    Identification id_;
    Processor *processor_;
};

class FaceRankEngine : public RankEngine {

 public:
    FaceRankEngine(const Config &config);
    virtual ~FaceRankEngine();
    vector<Score> Rank(const Mat& image, const Rect& hotspot,
                       const vector<FaceRankFeature>& candidates);

 private:
    void init(const Config &config);
    Identification id_;
    Processor *detector_;
    Processor *extractor_;
    Processor *ranker_;
};

}

#endif //MATRIX_ENGINE_RANK_ENGINE_H_