#include "gtest/gtest.h"
#include "frame_batch_helper.h"
#include "vehicle_processor_head.h"
#include "processor/vehicle_marker_classifier_processor.h"
#include "file_reader.h"

using namespace std;
using namespace dg;

static FrameBatchHelper *fbhelper;
static VehicleProcessorHead *head;
static VehicleMarkerClassifierProcessor *vmcprocessor;
static FileReader *resultReader;

static void initConfig() {
    WindowCaffeDetector::WindowCaffeConfig wConfig;
    MarkerCaffeClassifier::MarkerConfig mConfig;
    string baseModelPath;
#ifdef UNENCRYPTMODEL
    wConfig.is_model_encrypt = false;
    mConfig.is_model_encrypt = false;
    baseModelPath = "data/0/";
#else
    wConfig.is_model_encrypt = true;
    mConfig.is_model_encrypt = true;
    baseModelPath = "data/1/";
#endif

    wConfig.deploy_file = baseModelPath + "701.txt";
    wConfig.model_file = baseModelPath + "701.dat";

    mConfig.deploy_file = baseModelPath + "601.txt";
    mConfig.model_file = baseModelPath + "601.dat";
    wConfig.target_max_size=160;
    wConfig.target_min_size=80;
    vmcprocessor = new VehicleMarkerClassifierProcessor(wConfig, mConfig);
}

static Operation getOperation() {
    Operation op;
    op.Set( OPERATION_VEHICLE |
            OPERATION_VEHICLE_MARKER |
            OPERATION_VEHICLE_DETECT );
    return op;
}

static void init() {
    initConfig();
    resultReader = NULL;
    head = new VehicleProcessorHead();
    fbhelper = new FrameBatchHelper(1);
    head->setNextProcessor(vmcprocessor);
}

static void destory() {
    if (head) {
        delete head;
        head = NULL;
    }
    if (resultReader) {
        delete resultReader;
        resultReader = NULL;
    }
    if (fbhelper) {
        delete fbhelper;
        fbhelper = NULL;
    }
}

TEST(VehicleMarkerClassifierTest, markerClassifierTest) {
    init();

    fbhelper->setBasePath("data/testimg/markerClassifier/");
    fbhelper->readImage(getOperation());
    head->process(fbhelper->getFrameBatch());
    FrameBatch *fb = fbhelper->getFrameBatch();
    resultReader = new FileReader("data/testimg/markerClassifier/multiCarMarkers/result.txt");
    EXPECT_TRUE(resultReader->is_open());
    resultReader->read(",");

    for (int i = 0; i < fb->batch_size(); ++i) {
        Vehicle *obj = (Vehicle *)fb->frames()[i]->objects()[0];
        stringstream s;
        s << i;
        EXPECT_EQ(resultReader->getIntValue(s.str(),0), obj->children().size()) << "i = " << i << endl;
    }

    for (int i = 0; i < fb->batch_size(); ++i) {

        vector<Object *>v = fb->frames()[i]->objects()[0]->children();
        stringstream s;
        s << i;
        for (int j = 0; j < v.size(); ++j) {
            Vehicle *vehicle = (Vehicle*)v[j];
            EXPECT_LE(resultReader->getIntValue(s.str(), 1), vehicle->detection().box.x);
            EXPECT_LE(resultReader->getIntValue(s.str(), 2), vehicle->detection().box.y);
            EXPECT_GE(resultReader->getIntValue(s.str(), 3), vehicle->detection().box.width);
            EXPECT_GE(resultReader->getIntValue(s.str(), 4), vehicle->detection().box.height);
        }
    }

    for (int i = 0; i < fb->batch_size(); ++i) {
        vector<Object *>v = fb->frames()[i]->objects()[0]->children();
        stringstream s;
        s << i;

        ASSERT_EQ(resultReader->getValue(s.str()).size(), 5 + v.size()) << "i = " << i << endl;
        for (int j = 0; j < v.size(); ++j) {
            Marker *marker = (Marker *)v[j];
            EXPECT_EQ(resultReader->getIntValue(s.str(), 5 + j), marker->class_id());
        }
    }

    destory();
}
