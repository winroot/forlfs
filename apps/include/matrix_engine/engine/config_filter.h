/*
 * config_filter.h
 *
 *  Created on: May 5, 2016
 *      Author: jiajaichen
 */

#ifndef SRC_ENGINE_CONFIG_FILTER_H_
#define SRC_ENGINE_CONFIG_FILTER_H_

#include "processor/processor.h"
#include "engine_config_value.h"
#include "processor/vehicle_multi_type_detector_processor.h"
#include "processor/vehicle_classifier_processor.h"
#include "processor/vehicle_color_processor.h"
#include "processor/vehicle_marker_classifier_processor.h"
#include "processor/vehicle_plate_recognizer_processor.h"
#include "processor/car_feature_extract_processor.h"
#include "processor/face_detect_processor.h"
#include "processor/face_feature_extract_processor.h"
#include "config.h"
#include "fs_util.h"

namespace dg {
class ConfigFilter {

 public:

    static ConfigFilter* GetInstance() {
        if (!instance_)
            instance_ = new ConfigFilter;
        return instance_;
    }

    void createFaceDetectorConfig(const Config &cconfig,
                                  FaceDetector::FaceDetectorConfig & config);
    void createFaceExtractorConfig(
            const Config &cconfig,
            FaceFeatureExtractor::FaceFeatureExtractorConfig & config);
    void createVehicleConfig(
            const Config &cconfig,
            vector<VehicleCaffeClassifier::VehicleCaffeConfig> & configs);
    void createVehicleColorConfig(
            const Config &cconfig,
            vector<VehicleCaffeClassifier::VehicleCaffeConfig> &configs);
    void createVehiclePlateConfig(const Config &cconfig,
                                  PlateRecognizer::PlateConfig & pConfig);
    void createVehicleMutiTypeDetectorConfig(
            const Config &cconfig,
            VehicleMultiTypeDetector::VehicleMultiTypeConfig & config);
    void createMarkersConfig(const Config &cconfig,
                             MarkerCaffeClassifier::MarkerConfig &mConfig);
    void createWindowConfig(const Config &cconfig,
                            WindowCaffeDetector::WindowCaffeConfig &wConfig);
    int initDataConfig(const Config &config);

 private:
    ConfigFilter();
    static ConfigFilter* instance_;

    Config data_config_;
};

}

#endif /* SRC_ENGINE_CONFIG_FILTER_H_ */