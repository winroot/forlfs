// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: localcommon.proto

#ifndef PROTOBUF_localcommon_2eproto__INCLUDED
#define PROTOBUF_localcommon_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace dg {
namespace model {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_localcommon_2eproto();
void protobuf_AssignDesc_localcommon_2eproto();
void protobuf_ShutdownFile_localcommon_2eproto();

class MatrixError;
class Time;

enum RecognizeType {
  REC_TYPE_DEFAULT = 0,
  REC_TYPE_VEHICLE = 1,
  REC_TYPE_FACE = 2,
  REC_TYPE_ALL = 3,
  RecognizeType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  RecognizeType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool RecognizeType_IsValid(int value);
const RecognizeType RecognizeType_MIN = REC_TYPE_DEFAULT;
const RecognizeType RecognizeType_MAX = REC_TYPE_ALL;
const int RecognizeType_ARRAYSIZE = RecognizeType_MAX + 1;

const ::google::protobuf::EnumDescriptor* RecognizeType_descriptor();
inline const ::std::string& RecognizeType_Name(RecognizeType value) {
  return ::google::protobuf::internal::NameOfEnum(
    RecognizeType_descriptor(), value);
}
inline bool RecognizeType_Parse(
    const ::std::string& name, RecognizeType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RecognizeType>(
    RecognizeType_descriptor(), name, value);
}
enum RankType {
  RANK_TYPE_DEFAULT = 0,
  RANK_TYPE_VEHICLE = 1,
  RANK_TYPE_FACE = 2,
  RankType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  RankType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool RankType_IsValid(int value);
const RankType RankType_MIN = RANK_TYPE_DEFAULT;
const RankType RankType_MAX = RANK_TYPE_FACE;
const int RankType_ARRAYSIZE = RankType_MAX + 1;

const ::google::protobuf::EnumDescriptor* RankType_descriptor();
inline const ::std::string& RankType_Name(RankType value) {
  return ::google::protobuf::internal::NameOfEnum(
    RankType_descriptor(), value);
}
inline bool RankType_Parse(
    const ::std::string& name, RankType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RankType>(
    RankType_descriptor(), name, value);
}
enum RecognizeFunctions {
  RECFUNC_NONE = 0,
  RECFUNC_VEHICLE = 1,
  RECFUNC_VEHICLE_DETECT = 10,
  RECFUNC_VEHICLE_TRACK = 11,
  RECFUNC_VEHICLE_STYLE = 12,
  RECFUNC_VEHICLE_COLOR = 13,
  RECFUNC_VEHICLE_MARKER = 14,
  RECFUNC_VEHICLE_PLATE = 15,
  RECFUNC_VEHICLE_FEATURE_VECTOR = 16,
  RECFUNC_VEHICLE_DRIVER_NOBELT = 170,
  RECFUNC_VEHICLE_DRIVER_PHONE = 171,
  RECFUNC_VEHICLE_CODRIVER_NOBELT = 172,
  RECFUNC_FACE = 2,
  RECFUNC_FACE_DETECTOR = 20,
  RECFUNC_FACE_FEATURE_VECTOR = 21,
  RECFUNC_FACE_ALIGNMENT = 22,
  RECFUNC_FACE_QUALITY = 23,
  RECFUNC_PEDESTRIAN_ATTR = 3,
  RECFUNC_NON_VEHICLE_ATTR = 4,
  RecognizeFunctions_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  RecognizeFunctions_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool RecognizeFunctions_IsValid(int value);
const RecognizeFunctions RecognizeFunctions_MIN = RECFUNC_NONE;
const RecognizeFunctions RecognizeFunctions_MAX = RECFUNC_VEHICLE_CODRIVER_NOBELT;
const int RecognizeFunctions_ARRAYSIZE = RecognizeFunctions_MAX + 1;

const ::google::protobuf::EnumDescriptor* RecognizeFunctions_descriptor();
inline const ::std::string& RecognizeFunctions_Name(RecognizeFunctions value) {
  return ::google::protobuf::internal::NameOfEnum(
    RecognizeFunctions_descriptor(), value);
}
inline bool RecognizeFunctions_Parse(
    const ::std::string& name, RecognizeFunctions* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RecognizeFunctions>(
    RecognizeFunctions_descriptor(), name, value);
}
// ===================================================================

class Time : public ::google::protobuf::Message {
 public:
  Time();
  virtual ~Time();

  Time(const Time& from);

  inline Time& operator=(const Time& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Time& default_instance();

  void Swap(Time* other);

  // implements Message ----------------------------------------------

  inline Time* New() const { return New(NULL); }

  Time* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Time& from);
  void MergeFrom(const Time& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Time* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int64 Seconds = 1;
  void clear_seconds();
  static const int kSecondsFieldNumber = 1;
  ::google::protobuf::int64 seconds() const;
  void set_seconds(::google::protobuf::int64 value);

  // optional int64 NanoSecs = 2;
  void clear_nanosecs();
  static const int kNanoSecsFieldNumber = 2;
  ::google::protobuf::int64 nanosecs() const;
  void set_nanosecs(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:dg.model.Time)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::int64 seconds_;
  ::google::protobuf::int64 nanosecs_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_localcommon_2eproto();
  friend void protobuf_AssignDesc_localcommon_2eproto();
  friend void protobuf_ShutdownFile_localcommon_2eproto();

  void InitAsDefaultInstance();
  static Time* default_instance_;
};
// -------------------------------------------------------------------

class MatrixError : public ::google::protobuf::Message {
 public:
  MatrixError();
  virtual ~MatrixError();

  MatrixError(const MatrixError& from);

  inline MatrixError& operator=(const MatrixError& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MatrixError& default_instance();

  void Swap(MatrixError* other);

  // implements Message ----------------------------------------------

  inline MatrixError* New() const { return New(NULL); }

  MatrixError* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MatrixError& from);
  void MergeFrom(const MatrixError& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(MatrixError* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 Code = 1;
  void clear_code();
  static const int kCodeFieldNumber = 1;
  ::google::protobuf::int32 code() const;
  void set_code(::google::protobuf::int32 value);

  // optional string Message = 2;
  void clear_message();
  static const int kMessageFieldNumber = 2;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // @@protoc_insertion_point(class_scope:dg.model.MatrixError)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  ::google::protobuf::int32 code_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_localcommon_2eproto();
  friend void protobuf_AssignDesc_localcommon_2eproto();
  friend void protobuf_ShutdownFile_localcommon_2eproto();

  void InitAsDefaultInstance();
  static MatrixError* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Time

// optional int64 Seconds = 1;
inline void Time::clear_seconds() {
  seconds_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 Time::seconds() const {
  // @@protoc_insertion_point(field_get:dg.model.Time.Seconds)
  return seconds_;
}
inline void Time::set_seconds(::google::protobuf::int64 value) {
  
  seconds_ = value;
  // @@protoc_insertion_point(field_set:dg.model.Time.Seconds)
}

// optional int64 NanoSecs = 2;
inline void Time::clear_nanosecs() {
  nanosecs_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 Time::nanosecs() const {
  // @@protoc_insertion_point(field_get:dg.model.Time.NanoSecs)
  return nanosecs_;
}
inline void Time::set_nanosecs(::google::protobuf::int64 value) {
  
  nanosecs_ = value;
  // @@protoc_insertion_point(field_set:dg.model.Time.NanoSecs)
}

// -------------------------------------------------------------------

// MatrixError

// optional int32 Code = 1;
inline void MatrixError::clear_code() {
  code_ = 0;
}
inline ::google::protobuf::int32 MatrixError::code() const {
  // @@protoc_insertion_point(field_get:dg.model.MatrixError.Code)
  return code_;
}
inline void MatrixError::set_code(::google::protobuf::int32 value) {
  
  code_ = value;
  // @@protoc_insertion_point(field_set:dg.model.MatrixError.Code)
}

// optional string Message = 2;
inline void MatrixError::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MatrixError::message() const {
  // @@protoc_insertion_point(field_get:dg.model.MatrixError.Message)
  return message_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MatrixError::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:dg.model.MatrixError.Message)
}
inline void MatrixError::set_message(const char* value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:dg.model.MatrixError.Message)
}
inline void MatrixError::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:dg.model.MatrixError.Message)
}
inline ::std::string* MatrixError::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:dg.model.MatrixError.Message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MatrixError::release_message() {
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MatrixError::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:dg.model.MatrixError.Message)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace model
}  // namespace dg

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::dg::model::RecognizeType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::dg::model::RecognizeType>() {
  return ::dg::model::RecognizeType_descriptor();
}
template <> struct is_proto_enum< ::dg::model::RankType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::dg::model::RankType>() {
  return ::dg::model::RankType_descriptor();
}
template <> struct is_proto_enum< ::dg::model::RecognizeFunctions> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::dg::model::RecognizeFunctions>() {
  return ::dg::model::RecognizeFunctions_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_localcommon_2eproto__INCLUDED
