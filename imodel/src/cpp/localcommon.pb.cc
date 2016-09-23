// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: localcommon.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "localcommon.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace dg {
namespace model {

namespace {

const ::google::protobuf::Descriptor* Time_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Time_reflection_ = NULL;
const ::google::protobuf::Descriptor* MatrixError_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MatrixError_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* RecognizeType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* RankType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* RecognizeFunctions_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_localcommon_2eproto() {
  protobuf_AddDesc_localcommon_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "localcommon.proto");
  GOOGLE_CHECK(file != NULL);
  Time_descriptor_ = file->message_type(0);
  static const int Time_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Time, seconds_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Time, nanosecs_),
  };
  Time_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Time_descriptor_,
      Time::default_instance_,
      Time_offsets_,
      -1,
      -1,
      -1,
      sizeof(Time),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Time, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Time, _is_default_instance_));
  MatrixError_descriptor_ = file->message_type(1);
  static const int MatrixError_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatrixError, code_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatrixError, message_),
  };
  MatrixError_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      MatrixError_descriptor_,
      MatrixError::default_instance_,
      MatrixError_offsets_,
      -1,
      -1,
      -1,
      sizeof(MatrixError),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatrixError, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MatrixError, _is_default_instance_));
  RecognizeType_descriptor_ = file->enum_type(0);
  RankType_descriptor_ = file->enum_type(1);
  RecognizeFunctions_descriptor_ = file->enum_type(2);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_localcommon_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Time_descriptor_, &Time::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      MatrixError_descriptor_, &MatrixError::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_localcommon_2eproto() {
  delete Time::default_instance_;
  delete Time_reflection_;
  delete MatrixError::default_instance_;
  delete MatrixError_reflection_;
}

void protobuf_AddDesc_localcommon_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021localcommon.proto\022\010dg.model\")\n\004Time\022\017\n"
    "\007Seconds\030\001 \001(\003\022\020\n\010NanoSecs\030\002 \001(\003\",\n\013Matr"
    "ixError\022\014\n\004Code\030\001 \001(\005\022\017\n\007Message\030\002 \001(\t*`"
    "\n\rRecognizeType\022\024\n\020REC_TYPE_DEFAULT\020\000\022\024\n"
    "\020REC_TYPE_VEHICLE\020\001\022\021\n\rREC_TYPE_FACE\020\002\022\020"
    "\n\014REC_TYPE_ALL\020\003*L\n\010RankType\022\025\n\021RANK_TYP"
    "E_DEFAULT\020\000\022\025\n\021RANK_TYPE_VEHICLE\020\001\022\022\n\016RA"
    "NK_TYPE_FACE\020\002*\366\002\n\022RecognizeFunctions\022\020\n"
    "\014RECFUNC_NONE\020\000\022\023\n\017RECFUNC_VEHICLE\020\001\022\032\n\026"
    "RECFUNC_VEHICLE_DETECT\020\002\022\031\n\025RECFUNC_VEHI"
    "CLE_TRACK\020\003\022\031\n\025RECFUNC_VEHICLE_STYLE\020\004\022\031"
    "\n\025RECFUNC_VEHICLE_COLOR\020\005\022\032\n\026RECFUNC_VEH"
    "ICLE_MARKER\020\006\022\031\n\025RECFUNC_VEHICLE_PLATE\020\007"
    "\022\"\n\036RECFUNC_VEHICLE_FEATURE_VECTOR\020\010\022\020\n\014"
    "RECFUNC_FACE\020\t\022\031\n\025RECFUNC_FACE_DETECTOR\020"
    "\n\022\037\n\033RECFUNC_FACE_FEATURE_VECTOR\020\013\022#\n\037RE"
    "CFUNC_VEHICLE_PEDESTRIAN_ATTR\020\014b\006proto3", 679);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "localcommon.proto", &protobuf_RegisterTypes);
  Time::default_instance_ = new Time();
  MatrixError::default_instance_ = new MatrixError();
  Time::default_instance_->InitAsDefaultInstance();
  MatrixError::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_localcommon_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_localcommon_2eproto {
  StaticDescriptorInitializer_localcommon_2eproto() {
    protobuf_AddDesc_localcommon_2eproto();
  }
} static_descriptor_initializer_localcommon_2eproto_;
const ::google::protobuf::EnumDescriptor* RecognizeType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RecognizeType_descriptor_;
}
bool RecognizeType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* RankType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RankType_descriptor_;
}
bool RankType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* RecognizeFunctions_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RecognizeFunctions_descriptor_;
}
bool RecognizeFunctions_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      return true;
    default:
      return false;
  }
}


namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Time::kSecondsFieldNumber;
const int Time::kNanoSecsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Time::Time()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:dg.model.Time)
}

void Time::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

Time::Time(const Time& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:dg.model.Time)
}

void Time::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
  seconds_ = GOOGLE_LONGLONG(0);
  nanosecs_ = GOOGLE_LONGLONG(0);
}

Time::~Time() {
  // @@protoc_insertion_point(destructor:dg.model.Time)
  SharedDtor();
}

void Time::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Time::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Time::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Time_descriptor_;
}

const Time& Time::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_localcommon_2eproto();
  return *default_instance_;
}

Time* Time::default_instance_ = NULL;

Time* Time::New(::google::protobuf::Arena* arena) const {
  Time* n = new Time;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Time::Clear() {
// @@protoc_insertion_point(message_clear_start:dg.model.Time)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(Time, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<Time*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(seconds_, nanosecs_);

#undef ZR_HELPER_
#undef ZR_

}

bool Time::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:dg.model.Time)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 Seconds = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &seconds_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_NanoSecs;
        break;
      }

      // optional int64 NanoSecs = 2;
      case 2: {
        if (tag == 16) {
         parse_NanoSecs:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &nanosecs_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:dg.model.Time)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:dg.model.Time)
  return false;
#undef DO_
}

void Time::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:dg.model.Time)
  // optional int64 Seconds = 1;
  if (this->seconds() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->seconds(), output);
  }

  // optional int64 NanoSecs = 2;
  if (this->nanosecs() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->nanosecs(), output);
  }

  // @@protoc_insertion_point(serialize_end:dg.model.Time)
}

::google::protobuf::uint8* Time::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:dg.model.Time)
  // optional int64 Seconds = 1;
  if (this->seconds() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->seconds(), target);
  }

  // optional int64 NanoSecs = 2;
  if (this->nanosecs() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->nanosecs(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:dg.model.Time)
  return target;
}

int Time::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:dg.model.Time)
  int total_size = 0;

  // optional int64 Seconds = 1;
  if (this->seconds() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->seconds());
  }

  // optional int64 NanoSecs = 2;
  if (this->nanosecs() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->nanosecs());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Time::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:dg.model.Time)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Time* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const Time>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:dg.model.Time)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:dg.model.Time)
    MergeFrom(*source);
  }
}

void Time::MergeFrom(const Time& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:dg.model.Time)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from.seconds() != 0) {
    set_seconds(from.seconds());
  }
  if (from.nanosecs() != 0) {
    set_nanosecs(from.nanosecs());
  }
}

void Time::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:dg.model.Time)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Time::CopyFrom(const Time& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:dg.model.Time)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Time::IsInitialized() const {

  return true;
}

void Time::Swap(Time* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Time::InternalSwap(Time* other) {
  std::swap(seconds_, other->seconds_);
  std::swap(nanosecs_, other->nanosecs_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Time::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Time_descriptor_;
  metadata.reflection = Time_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Time

// optional int64 Seconds = 1;
void Time::clear_seconds() {
  seconds_ = GOOGLE_LONGLONG(0);
}
 ::google::protobuf::int64 Time::seconds() const {
  // @@protoc_insertion_point(field_get:dg.model.Time.Seconds)
  return seconds_;
}
 void Time::set_seconds(::google::protobuf::int64 value) {
  
  seconds_ = value;
  // @@protoc_insertion_point(field_set:dg.model.Time.Seconds)
}

// optional int64 NanoSecs = 2;
void Time::clear_nanosecs() {
  nanosecs_ = GOOGLE_LONGLONG(0);
}
 ::google::protobuf::int64 Time::nanosecs() const {
  // @@protoc_insertion_point(field_get:dg.model.Time.NanoSecs)
  return nanosecs_;
}
 void Time::set_nanosecs(::google::protobuf::int64 value) {
  
  nanosecs_ = value;
  // @@protoc_insertion_point(field_set:dg.model.Time.NanoSecs)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MatrixError::kCodeFieldNumber;
const int MatrixError::kMessageFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MatrixError::MatrixError()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:dg.model.MatrixError)
}

void MatrixError::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

MatrixError::MatrixError(const MatrixError& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:dg.model.MatrixError)
}

void MatrixError::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  code_ = 0;
  message_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

MatrixError::~MatrixError() {
  // @@protoc_insertion_point(destructor:dg.model.MatrixError)
  SharedDtor();
}

void MatrixError::SharedDtor() {
  message_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void MatrixError::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MatrixError::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MatrixError_descriptor_;
}

const MatrixError& MatrixError::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_localcommon_2eproto();
  return *default_instance_;
}

MatrixError* MatrixError::default_instance_ = NULL;

MatrixError* MatrixError::New(::google::protobuf::Arena* arena) const {
  MatrixError* n = new MatrixError;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MatrixError::Clear() {
// @@protoc_insertion_point(message_clear_start:dg.model.MatrixError)
  code_ = 0;
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool MatrixError::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:dg.model.MatrixError)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 Code = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &code_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_Message;
        break;
      }

      // optional string Message = 2;
      case 2: {
        if (tag == 18) {
         parse_Message:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_message()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->message().data(), this->message().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "dg.model.MatrixError.Message"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:dg.model.MatrixError)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:dg.model.MatrixError)
  return false;
#undef DO_
}

void MatrixError::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:dg.model.MatrixError)
  // optional int32 Code = 1;
  if (this->code() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->code(), output);
  }

  // optional string Message = 2;
  if (this->message().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "dg.model.MatrixError.Message");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->message(), output);
  }

  // @@protoc_insertion_point(serialize_end:dg.model.MatrixError)
}

::google::protobuf::uint8* MatrixError::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:dg.model.MatrixError)
  // optional int32 Code = 1;
  if (this->code() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->code(), target);
  }

  // optional string Message = 2;
  if (this->message().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "dg.model.MatrixError.Message");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->message(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:dg.model.MatrixError)
  return target;
}

int MatrixError::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:dg.model.MatrixError)
  int total_size = 0;

  // optional int32 Code = 1;
  if (this->code() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->code());
  }

  // optional string Message = 2;
  if (this->message().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->message());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MatrixError::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:dg.model.MatrixError)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const MatrixError* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const MatrixError>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:dg.model.MatrixError)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:dg.model.MatrixError)
    MergeFrom(*source);
  }
}

void MatrixError::MergeFrom(const MatrixError& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:dg.model.MatrixError)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from.code() != 0) {
    set_code(from.code());
  }
  if (from.message().size() > 0) {

    message_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.message_);
  }
}

void MatrixError::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:dg.model.MatrixError)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MatrixError::CopyFrom(const MatrixError& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:dg.model.MatrixError)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MatrixError::IsInitialized() const {

  return true;
}

void MatrixError::Swap(MatrixError* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MatrixError::InternalSwap(MatrixError* other) {
  std::swap(code_, other->code_);
  message_.Swap(&other->message_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata MatrixError::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MatrixError_descriptor_;
  metadata.reflection = MatrixError_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// MatrixError

// optional int32 Code = 1;
void MatrixError::clear_code() {
  code_ = 0;
}
 ::google::protobuf::int32 MatrixError::code() const {
  // @@protoc_insertion_point(field_get:dg.model.MatrixError.Code)
  return code_;
}
 void MatrixError::set_code(::google::protobuf::int32 value) {
  
  code_ = value;
  // @@protoc_insertion_point(field_set:dg.model.MatrixError.Code)
}

// optional string Message = 2;
void MatrixError::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& MatrixError::message() const {
  // @@protoc_insertion_point(field_get:dg.model.MatrixError.Message)
  return message_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void MatrixError::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:dg.model.MatrixError.Message)
}
 void MatrixError::set_message(const char* value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:dg.model.MatrixError.Message)
}
 void MatrixError::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:dg.model.MatrixError.Message)
}
 ::std::string* MatrixError::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:dg.model.MatrixError.Message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* MatrixError::release_message() {
  // @@protoc_insertion_point(field_release:dg.model.MatrixError.Message)
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void MatrixError::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:dg.model.MatrixError.Message)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace model
}  // namespace dg

// @@protoc_insertion_point(global_scope)
