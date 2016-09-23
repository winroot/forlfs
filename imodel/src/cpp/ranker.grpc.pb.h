// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: ranker.proto
#ifndef GRPC_ranker_2eproto__INCLUDED
#define GRPC_ranker_2eproto__INCLUDED

#include "ranker.pb.h"

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
class Channel;
class RpcService;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace dg {
namespace model {

class SimilarityService GRPC_FINAL {
 public:
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status RankImage(::grpc::ClientContext* context, const ::dg::model::RankImageRequest& request, ::dg::model::RankImageResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::RankImageResponse>> AsyncRankImage(::grpc::ClientContext* context, const ::dg::model::RankImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::RankImageResponse>>(AsyncRankImageRaw(context, request, cq));
    }
    virtual ::grpc::Status RankFeature(::grpc::ClientContext* context, const ::dg::model::RankFeatureRequest& request, ::dg::model::RankFeatureResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::RankFeatureResponse>> AsyncRankFeature(::grpc::ClientContext* context, const ::dg::model::RankFeatureRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::RankFeatureResponse>>(AsyncRankFeatureRaw(context, request, cq));
    }
    // Deprecated
    virtual ::grpc::Status GetRankedVector(::grpc::ClientContext* context, const ::dg::model::FeatureRankingRequest& request, ::dg::model::FeatureRankingResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::FeatureRankingResponse>> AsyncGetRankedVector(::grpc::ClientContext* context, const ::dg::model::FeatureRankingRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::FeatureRankingResponse>>(AsyncGetRankedVectorRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::RankImageResponse>* AsyncRankImageRaw(::grpc::ClientContext* context, const ::dg::model::RankImageRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::RankFeatureResponse>* AsyncRankFeatureRaw(::grpc::ClientContext* context, const ::dg::model::RankFeatureRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::dg::model::FeatureRankingResponse>* AsyncGetRankedVectorRaw(::grpc::ClientContext* context, const ::dg::model::FeatureRankingRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub GRPC_FINAL : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status RankImage(::grpc::ClientContext* context, const ::dg::model::RankImageRequest& request, ::dg::model::RankImageResponse* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::RankImageResponse>> AsyncRankImage(::grpc::ClientContext* context, const ::dg::model::RankImageRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::RankImageResponse>>(AsyncRankImageRaw(context, request, cq));
    }
    ::grpc::Status RankFeature(::grpc::ClientContext* context, const ::dg::model::RankFeatureRequest& request, ::dg::model::RankFeatureResponse* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::RankFeatureResponse>> AsyncRankFeature(::grpc::ClientContext* context, const ::dg::model::RankFeatureRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::RankFeatureResponse>>(AsyncRankFeatureRaw(context, request, cq));
    }
    ::grpc::Status GetRankedVector(::grpc::ClientContext* context, const ::dg::model::FeatureRankingRequest& request, ::dg::model::FeatureRankingResponse* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::FeatureRankingResponse>> AsyncGetRankedVector(::grpc::ClientContext* context, const ::dg::model::FeatureRankingRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::dg::model::FeatureRankingResponse>>(AsyncGetRankedVectorRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::dg::model::RankImageResponse>* AsyncRankImageRaw(::grpc::ClientContext* context, const ::dg::model::RankImageRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::dg::model::RankFeatureResponse>* AsyncRankFeatureRaw(::grpc::ClientContext* context, const ::dg::model::RankFeatureRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::dg::model::FeatureRankingResponse>* AsyncGetRankedVectorRaw(::grpc::ClientContext* context, const ::dg::model::FeatureRankingRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    const ::grpc::RpcMethod rpcmethod_RankImage_;
    const ::grpc::RpcMethod rpcmethod_RankFeature_;
    const ::grpc::RpcMethod rpcmethod_GetRankedVector_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status RankImage(::grpc::ServerContext* context, const ::dg::model::RankImageRequest* request, ::dg::model::RankImageResponse* response);
    virtual ::grpc::Status RankFeature(::grpc::ServerContext* context, const ::dg::model::RankFeatureRequest* request, ::dg::model::RankFeatureResponse* response);
    // Deprecated
    virtual ::grpc::Status GetRankedVector(::grpc::ServerContext* context, const ::dg::model::FeatureRankingRequest* request, ::dg::model::FeatureRankingResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_RankImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_RankImage() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_RankImage() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RankImage(::grpc::ServerContext* context, const ::dg::model::RankImageRequest* request, ::dg::model::RankImageResponse* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestRankImage(::grpc::ServerContext* context, ::dg::model::RankImageRequest* request, ::grpc::ServerAsyncResponseWriter< ::dg::model::RankImageResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_RankFeature : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_RankFeature() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_RankFeature() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RankFeature(::grpc::ServerContext* context, const ::dg::model::RankFeatureRequest* request, ::dg::model::RankFeatureResponse* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestRankFeature(::grpc::ServerContext* context, ::dg::model::RankFeatureRequest* request, ::grpc::ServerAsyncResponseWriter< ::dg::model::RankFeatureResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetRankedVector : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_GetRankedVector() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_GetRankedVector() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetRankedVector(::grpc::ServerContext* context, const ::dg::model::FeatureRankingRequest* request, ::dg::model::FeatureRankingResponse* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetRankedVector(::grpc::ServerContext* context, ::dg::model::FeatureRankingRequest* request, ::grpc::ServerAsyncResponseWriter< ::dg::model::FeatureRankingResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_RankImage<WithAsyncMethod_RankFeature<WithAsyncMethod_GetRankedVector<Service > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_RankImage : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_RankImage() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_RankImage() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RankImage(::grpc::ServerContext* context, const ::dg::model::RankImageRequest* request, ::dg::model::RankImageResponse* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_RankFeature : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_RankFeature() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_RankFeature() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RankFeature(::grpc::ServerContext* context, const ::dg::model::RankFeatureRequest* request, ::dg::model::RankFeatureResponse* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetRankedVector : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_GetRankedVector() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_GetRankedVector() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetRankedVector(::grpc::ServerContext* context, const ::dg::model::FeatureRankingRequest* request, ::dg::model::FeatureRankingResponse* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
};

}  // namespace model
}  // namespace dg


#endif  // GRPC_ranker_2eproto__INCLUDED
