// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: witness.proto
#ifndef GRPC_witness_2eproto__INCLUDED
#define GRPC_witness_2eproto__INCLUDED

#include "witness.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/proto_utils.h>
#include <grpc++/impl/codegen/rpc_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/status.h>
#include <grpc++/impl/codegen/stub_options.h>
#include <grpc++/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class RpcService;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace dg {
namespace model {

class WitnessService GRPC_FINAL {
public:
    class StubInterface {
    public:
        virtual ~StubInterface() {}
        virtual ::grpc::Status Recognize(::grpc::ClientContext* context, const ::dg::model::WitnessRequest& request, ::dg::model::WitnessResponse* response) = 0;
        std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::WitnessResponse>> AsyncRecognize(::grpc::ClientContext* context, const ::dg::model::WitnessRequest& request, ::grpc::CompletionQueue* cq) {
            return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::WitnessResponse>>(AsyncRecognizeRaw(context, request, cq));
        }
        virtual ::grpc::Status BatchRecognize(::grpc::ClientContext* context, const ::dg::model::WitnessBatchRequest& request, ::dg::model::WitnessBatchResponse* response) = 0;
        std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::WitnessBatchResponse>> AsyncBatchRecognize(::grpc::ClientContext* context, const ::dg::model::WitnessBatchRequest& request, ::grpc::CompletionQueue* cq) {
            return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::WitnessBatchResponse>>(AsyncBatchRecognizeRaw(context, request, cq));
        }
    private:
        virtual ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::WitnessResponse>* AsyncRecognizeRaw(::grpc::ClientContext* context, const ::dg::model::WitnessRequest& request, ::grpc::CompletionQueue* cq) = 0;
        virtual ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::WitnessBatchResponse>* AsyncBatchRecognizeRaw(::grpc::ClientContext* context, const ::dg::model::WitnessBatchRequest& request, ::grpc::CompletionQueue* cq) = 0;
    };
    class Stub GRPC_FINAL : public StubInterface {
    public:
        Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
        ::grpc::Status Recognize(::grpc::ClientContext* context, const ::dg::model::WitnessRequest& request, ::dg::model::WitnessResponse* response) GRPC_OVERRIDE;
        std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::WitnessResponse>> AsyncRecognize(::grpc::ClientContext* context, const ::dg::model::WitnessRequest& request, ::grpc::CompletionQueue* cq) {
            return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::WitnessResponse>>(AsyncRecognizeRaw(context, request, cq));
        }
        ::grpc::Status BatchRecognize(::grpc::ClientContext* context, const ::dg::model::WitnessBatchRequest& request, ::dg::model::WitnessBatchResponse* response) GRPC_OVERRIDE;
        std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::WitnessBatchResponse>> AsyncBatchRecognize(::grpc::ClientContext* context, const ::dg::model::WitnessBatchRequest& request, ::grpc::CompletionQueue* cq) {
            return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::WitnessBatchResponse>>(AsyncBatchRecognizeRaw(context, request, cq));
        }

    private:
        std::shared_ptr< ::grpc::ChannelInterface> channel_;
        ::grpc::ClientAsyncResponseReader< ::dg::model::WitnessResponse>* AsyncRecognizeRaw(::grpc::ClientContext* context, const ::dg::model::WitnessRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
        ::grpc::ClientAsyncResponseReader< ::dg::model::WitnessBatchResponse>* AsyncBatchRecognizeRaw(::grpc::ClientContext* context, const ::dg::model::WitnessBatchRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
        const ::grpc::RpcMethod rpcmethod_Recognize_;
        const ::grpc::RpcMethod rpcmethod_BatchRecognize_;
    };
    static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

    class Service : public ::grpc::Service {
    public:
        Service();
        virtual ~Service();
        virtual ::grpc::Status Recognize(::grpc::ServerContext* context, const ::dg::model::WitnessRequest* request, ::dg::model::WitnessResponse* response);
        virtual ::grpc::Status BatchRecognize(::grpc::ServerContext* context, const ::dg::model::WitnessBatchRequest* request, ::dg::model::WitnessBatchResponse* response);
    };
    template <class BaseClass>
    class WithAsyncMethod_Recognize : public BaseClass {
    private:
        void BaseClassMustBeDerivedFromService(Service *service) {}
    public:
        WithAsyncMethod_Recognize() {
            ::grpc::Service::MarkMethodAsync(0);
        }
        ~WithAsyncMethod_Recognize() GRPC_OVERRIDE {
            BaseClassMustBeDerivedFromService(this);
        }
        // disable synchronous version of this method
        ::grpc::Status Recognize(::grpc::ServerContext* context, const ::dg::model::WitnessRequest* request, ::dg::model::WitnessResponse* response) GRPC_FINAL GRPC_OVERRIDE {
            abort();
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }
        void RequestRecognize(::grpc::ServerContext* context, ::dg::model::WitnessRequest* request, ::grpc::ServerAsyncResponseWriter< ::dg::model::WitnessResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
            ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
        }
    };
    template <class BaseClass>
    class WithAsyncMethod_BatchRecognize : public BaseClass {
    private:
        void BaseClassMustBeDerivedFromService(Service *service) {}
    public:
        WithAsyncMethod_BatchRecognize() {
            ::grpc::Service::MarkMethodAsync(1);
        }
        ~WithAsyncMethod_BatchRecognize() GRPC_OVERRIDE {
            BaseClassMustBeDerivedFromService(this);
        }
        // disable synchronous version of this method
        ::grpc::Status BatchRecognize(::grpc::ServerContext* context, const ::dg::model::WitnessBatchRequest* request, ::dg::model::WitnessBatchResponse* response) GRPC_FINAL GRPC_OVERRIDE {
            abort();
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }
        void RequestBatchRecognize(::grpc::ServerContext* context, ::dg::model::WitnessBatchRequest* request, ::grpc::ServerAsyncResponseWriter< ::dg::model::WitnessBatchResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
            ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
        }
    };
    typedef WithAsyncMethod_Recognize<WithAsyncMethod_BatchRecognize<Service > > AsyncService;
    template <class BaseClass>
    class WithGenericMethod_Recognize : public BaseClass {
    private:
        void BaseClassMustBeDerivedFromService(Service *service) {}
    public:
        WithGenericMethod_Recognize() {
            ::grpc::Service::MarkMethodGeneric(0);
        }
        ~WithGenericMethod_Recognize() GRPC_OVERRIDE {
            BaseClassMustBeDerivedFromService(this);
        }
        // disable synchronous version of this method
        ::grpc::Status Recognize(::grpc::ServerContext* context, const ::dg::model::WitnessRequest* request, ::dg::model::WitnessResponse* response) GRPC_FINAL GRPC_OVERRIDE {
            abort();
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }
    };
    template <class BaseClass>
    class WithGenericMethod_BatchRecognize : public BaseClass {
    private:
        void BaseClassMustBeDerivedFromService(Service *service) {}
    public:
        WithGenericMethod_BatchRecognize() {
            ::grpc::Service::MarkMethodGeneric(1);
        }
        ~WithGenericMethod_BatchRecognize() GRPC_OVERRIDE {
            BaseClassMustBeDerivedFromService(this);
        }
        // disable synchronous version of this method
        ::grpc::Status BatchRecognize(::grpc::ServerContext* context, const ::dg::model::WitnessBatchRequest* request, ::dg::model::WitnessBatchResponse* response) GRPC_FINAL GRPC_OVERRIDE {
            abort();
            return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
        }
    };
};

}
  // namespace model
} // namespace dg

#endif  // GRPC_witness_2eproto__INCLUDED