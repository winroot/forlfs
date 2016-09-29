/*============================================================================
 * File Name   : face_rank_processor.cpp
 * Author      : tongliu@deepglint.com
 * Version     : 1.0.0.0
 * Copyright   : Copyright 2016 DeepGlint Inc.
 * Created on  : 2016年4月28日 下午4:09:47
 * Description :
 * ==========================================================================*/
#include "processor/face_rank_processor.h"
#include "processor_helper.h"
#include "io/rank_candidates_repo.h"
#include "alg/rank/database.h"

namespace dg {

FaceRankProcessor::FaceRankProcessor() {
//    ranker_ = new FaceRanker();
    RankCandidatesRepo &repo = RankCandidatesRepo::GetInstance();
    repo.Init("./repo");
}

FaceRankProcessor::~FaceRankProcessor() {
//    if (ranker_)
//        delete ranker_;
}

bool FaceRankProcessor::process(Frame *frame) {
    FaceRankFrame *fframe = (FaceRankFrame *) frame;


    const RankCandidatesRepo &repo = RankCandidatesRepo::GetInstance();
    CDatabase &ranker = RankCandidatesRepo::GetInstance().GetFaceRanker();

    vector<float> &feature = fframe->datum_.descriptor_;


    int candidatesNum = 10;
    vector<int64_t> results(candidatesNum);


    ranker.NearestN(feature.data(), candidatesNum, results.data());
    for (int64_t r: results) {
        Score score;
        score.index_ = r;
        fframe->result_.push_back(score);
    }

    performance_++;

    return true;

}
bool FaceRankProcessor::RecordFeaturePerformance() {

    return RecordPerformance(FEATURE_FACE_RANK, performance_);

}
bool FaceRankProcessor::beforeUpdate(FrameBatch *frameBatch) {
#if RELEASE
    if (performance_ > RECORD_UNIT) {
        if (!RecordFeaturePerformance()) {
            return false;
        }
    }
#endif

    return true;
}
} /* namespace dg */
