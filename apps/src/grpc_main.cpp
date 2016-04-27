#include <string>
#include <memory>
#include <iostream>
#include <glog/logging.h>
#include <grpc++/grpc++.h>
#include "config/config.h"
#include "grpc/witness_grpc.h"
#include "grpc/ranker_grpc.h"

using namespace std;
using namespace dg;
using namespace grpc;

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);

    Config *config = Config::GetInstance();
    config->Load("config.json");

    string instType = (string) config->Value("InstanceType");
    cout << "Instance type: " << instType << endl;
    
    grpc::Service *service = NULL;
    if (instType == "witness") {
        service = new GrpcWitnessServiceImpl(config);
        // bool asyn = config->Value("System/EnableAsyn");
        // if (asyn) {
        //     service = new WitnessServiceAsynImpl(config);
        // } else {
        //     service = new WitnessServiceImpl(config);
        // }
    } else if(instType == "ranker") {
        service = new GrpcRankerServiceImpl(config);
    } else {
        cout << "unknown instance type: " << instType << endl;
        return -1;
    }

    string address = (string) config->Value("System/Ip") + ":"
          + (string) config->Value("System/Port");

    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(service);
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << address << endl;
    server->Wait();

    return 0;
}

