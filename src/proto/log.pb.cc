// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: log.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "log.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* logRecord_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  logRecord_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_log_2eproto() {
  protobuf_AddDesc_log_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "log.proto");
  GOOGLE_CHECK(file != NULL);
  logRecord_descriptor_ = file->message_type(0);
  static const int logRecord_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(logRecord, ai_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(logRecord, vision_),
  };
  logRecord_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      logRecord_descriptor_,
      logRecord::default_instance_,
      logRecord_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(logRecord, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(logRecord, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(logRecord));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_log_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    logRecord_descriptor_, &logRecord::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_log_2eproto() {
  delete logRecord::default_instance_;
  delete logRecord_reflection_;
}

void protobuf_AddDesc_log_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_AddDesc_vision_5flog_2eproto();
  ::protobuf_AddDesc_ssl_5flog_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\tlog.proto\032\020vision_log.proto\032\rssl_log.p"
    "roto\">\n\tlogRecord\022\024\n\002ai\030\001 \001(\0132\010.SSL_log\022"
    "\033\n\006vision\030\002 \001(\0132\013.Vision_log", 108);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "log.proto", &protobuf_RegisterTypes);
  logRecord::default_instance_ = new logRecord();
  logRecord::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_log_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_log_2eproto {
  StaticDescriptorInitializer_log_2eproto() {
    protobuf_AddDesc_log_2eproto();
  }
} static_descriptor_initializer_log_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int logRecord::kAiFieldNumber;
const int logRecord::kVisionFieldNumber;
#endif  // !_MSC_VER

logRecord::logRecord()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void logRecord::InitAsDefaultInstance() {
  ai_ = const_cast< ::SSL_log*>(&::SSL_log::default_instance());
  vision_ = const_cast< ::Vision_log*>(&::Vision_log::default_instance());
}

logRecord::logRecord(const logRecord& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void logRecord::SharedCtor() {
  _cached_size_ = 0;
  ai_ = NULL;
  vision_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

logRecord::~logRecord() {
  SharedDtor();
}

void logRecord::SharedDtor() {
  if (this != default_instance_) {
    delete ai_;
    delete vision_;
  }
}

void logRecord::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* logRecord::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return logRecord_descriptor_;
}

const logRecord& logRecord::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_log_2eproto();
  return *default_instance_;
}

logRecord* logRecord::default_instance_ = NULL;

logRecord* logRecord::New() const {
  return new logRecord;
}

void logRecord::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_ai()) {
      if (ai_ != NULL) ai_->::SSL_log::Clear();
    }
    if (has_vision()) {
      if (vision_ != NULL) vision_->::Vision_log::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool logRecord::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .SSL_log ai = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_ai()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_vision;
        break;
      }

      // optional .Vision_log vision = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_vision:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_vision()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void logRecord::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .SSL_log ai = 1;
  if (has_ai()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->ai(), output);
  }

  // optional .Vision_log vision = 2;
  if (has_vision()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->vision(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* logRecord::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .SSL_log ai = 1;
  if (has_ai()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->ai(), target);
  }

  // optional .Vision_log vision = 2;
  if (has_vision()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->vision(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int logRecord::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .SSL_log ai = 1;
    if (has_ai()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->ai());
    }

    // optional .Vision_log vision = 2;
    if (has_vision()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->vision());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void logRecord::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const logRecord* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const logRecord*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void logRecord::MergeFrom(const logRecord& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ai()) {
      mutable_ai()->::SSL_log::MergeFrom(from.ai());
    }
    if (from.has_vision()) {
      mutable_vision()->::Vision_log::MergeFrom(from.vision());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void logRecord::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void logRecord::CopyFrom(const logRecord& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool logRecord::IsInitialized() const {

  if (has_ai()) {
    if (!this->ai().IsInitialized()) return false;
  }
  if (has_vision()) {
    if (!this->vision().IsInitialized()) return false;
  }
  return true;
}

void logRecord::Swap(logRecord* other) {
  if (other != this) {
    std::swap(ai_, other->ai_);
    std::swap(vision_, other->vision_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata logRecord::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = logRecord_descriptor_;
  metadata.reflection = logRecord_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
