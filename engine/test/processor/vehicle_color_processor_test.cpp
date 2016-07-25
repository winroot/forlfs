#if true

#include "gtest/gtest.h"
#include "frame_batch_helper.h"
#include "vehicle_processor_head.h"
#include "processor/vehicle_color_processor.h"

using namespace std;
using namespace dg;

static FrameBatchHelper *fbhelper;
static VehicleProcessorHead *head;
static VehicleColorProcessor *vcprocessor;

static void initConfig() {
    CaffeVehicleColorClassifier::VehicleColorConfig config;
    config.is_model_encrypt = false;
    config.deploy_file = "data/models/200.txt";
    config.model_file = "data/models/200.dat";
    vector<CaffeVehicleColorClassifier::VehicleColorConfig> configs;
    configs.push_back(config);
    vcprocessor = new VehicleColorProcessor(configs);
}

static void init() {
    initConfig();
    head = new VehicleProcessorHead();
    fbhelper = new FrameBatchHelper(1);
    head->setNextProcessor(vcprocessor);
}

static void destory() {
    /**
    if (head) {
        delete head;
        head = NULL;
    }
     **/

    if (fbhelper) {
        delete fbhelper;
        fbhelper = NULL;
    }
}

static Operation getOperation() {
    Operation op;
    op.Set( OPERATION_VEHICLE |
            OPERATION_VEHICLE_COLOR |
            OPERATION_VEHICLE_DETECT );
    return op;
}

TEST(VehicleColorProcessorTest, vehicleColorTest) {
    init();
    fbhelper->setBasePath("data/testimg/vehicleColor/");
    fbhelper->readImage(getOperation());
    FrameBatch *fb = fbhelper->getFrameBatch();
    head->process(fb);

    int expectColor[] = {
            0, 11, 8, 4, 9, 10, 1, 3, -1, -1
    };

    for (int i = 0; i < fb->batch_size(); ++i) {
        Object *obj = fb->frames()[i]->objects()[0];
        Vehicle *v = (Vehicle *)obj;
        EXPECT_EQ(expectColor[i], v->color().class_id);
    }

    delete fbhelper;
    fbhelper = new FrameBatchHelper(2);

    fbhelper->setBasePath("data/testimg/vehicleColor/");
    fbhelper->readImage(getOperation());
    fb = fbhelper->getFrameBatch();

    for (int i = 0; i < fb->batch_size(); ++i) {
        Frame *f = fb->frames()[i];
        head->getProcessor()->Update(f);
        EXPECT_EQ(0, f->objects().size());
    }

    destory();
}

#endif
