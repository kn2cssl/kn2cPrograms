// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ssl_log.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ssl_log.pb.h"

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
class log_chunkDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<log_chunk> {};
log_chunkDefaultTypeInternal _log_chunk_default_instance_;
class SSL_logDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<SSL_log> {};
SSL_logDefaultTypeInternal _SSL_log_default_instance_;

namespace {

::google::protobuf::Metadata file_level_metadata[2];

}  // namespace


const ::google::protobuf::uint32* protobuf_Offsets_ssl_5flog_2eproto() GOOGLE_ATTRIBUTE_COLD;
const ::google::protobuf::uint32* protobuf_Offsets_ssl_5flog_2eproto() {
  static const ::google::protobuf::uint32 offsets[] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(log_chunk, _has_bits_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(log_chunk, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(log_chunk, chunk_number_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(log_chunk, ball_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(log_chunk, ours_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(log_chunk, opps_),
    1,
    0,
    2,
    3,
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SSL_log, _has_bits_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SSL_log, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SSL_log, numberofchunks_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SSL_log, timerinterval_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SSL_log, chunks_),
    0,
    1,
    2,
  };
  return offsets;
}

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 8, sizeof(log_chunk)},
  { 12, 19, sizeof(SSL_log)},
};

static const ::google::protobuf::internal::DefaultInstanceData file_default_instances[] = {
  {reinterpret_cast<const ::google::protobuf::Message*>(&_log_chunk_default_instance_), NULL},
  {reinterpret_cast<const ::google::protobuf::Message*>(&_SSL_log_default_instance_), NULL},
};

namespace {

void protobuf_AssignDescriptors() {
  protobuf_AddDesc_ssl_5flog_2eproto();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "ssl_log.proto", schemas, file_default_instances, protobuf_Offsets_ssl_5flog_2eproto(), factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

}  // namespace

void protobuf_ShutdownFile_ssl_5flog_2eproto() {
  _log_chunk_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
  _SSL_log_default_instance_.Shutdown();
  delete file_level_metadata[1].reflection;
}

void protobuf_InitDefaults_ssl_5flog_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_InitDefaults_Robot_5fmessage_2eproto();
  ::protobuf_InitDefaults_Ball_5fmessage_2eproto();
  ::google::protobuf::internal::InitProtobufDefaults();
  _log_chunk_default_instance_.DefaultConstruct();
  _SSL_log_default_instance_.DefaultConstruct();
  _log_chunk_default_instance_.get_mutable()->ball_ = const_cast< ::Ball_message*>(
      ::Ball_message::internal_default_instance());
}

void protobuf_InitDefaults_ssl_5flog_2eproto() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_InitDefaults_ssl_5flog_2eproto_impl);
}
void protobuf_AddDesc_ssl_5flog_2eproto_impl() {
  protobuf_InitDefaults_ssl_5flog_2eproto();
  static const char descriptor[] = {
      "\n\rssl_log.proto\032\023Robot_message.proto\032\022Ba"
      "ll_message.proto\"z\n\tlog_chunk\022\024\n\014chunk_n"
      "umber\030\001 \002(\003\022\033\n\004ball\030\002 \002(\0132\r.Ball_message"
      "\022\034\n\004ours\030\003 \003(\0132\016.Robot_message\022\034\n\004opps\030\004"
      " \003(\0132\016.Robot_message\"T\n\007SSL_log\022\026\n\016numbe"
      "rOfChunks\030\001 \002(\003\022\025\n\rtimerInterval\030\002 \002(\003\022\032"
      "\n\006chunks\030\003 \003(\0132\n.log_chunk"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 266);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ssl_log.proto", &protobuf_RegisterTypes);
  ::protobuf_AddDesc_Robot_5fmessage_2eproto();
  ::protobuf_AddDesc_Ball_5fmessage_2eproto();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ssl_5flog_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_ssl_5flog_2eproto_once_);
void protobuf_AddDesc_ssl_5flog_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_ssl_5flog_2eproto_once_,
                 &protobuf_AddDesc_ssl_5flog_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ssl_5flog_2eproto {
  StaticDescriptorInitializer_ssl_5flog_2eproto() {
    protobuf_AddDesc_ssl_5flog_2eproto();
  }
} static_descriptor_initializer_ssl_5flog_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int log_chunk::kChunkNumberFieldNumber;
const int log_chunk::kBallFieldNumber;
const int log_chunk::kOursFieldNumber;
const int log_chunk::kOppsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

log_chunk::log_chunk()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_InitDefaults_ssl_5flog_2eproto();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:log_chunk)
}
log_chunk::log_chunk(const log_chunk& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      ours_(from.ours_),
      opps_(from.opps_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_ball()) {
    ball_ = new ::Ball_message(*from.ball_);
  } else {
    ball_ = NULL;
  }
  chunk_number_ = from.chunk_number_;
  // @@protoc_insertion_point(copy_constructor:log_chunk)
}

void log_chunk::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&ball_, 0, reinterpret_cast<char*>(&chunk_number_) -
    reinterpret_cast<char*>(&ball_) + sizeof(chunk_number_));
}

log_chunk::~log_chunk() {
  // @@protoc_insertion_point(destructor:log_chunk)
  SharedDtor();
}

void log_chunk::SharedDtor() {
  if (this != internal_default_instance()) {
    delete ball_;
  }
}

void log_chunk::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* log_chunk::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0].descriptor;
}

const log_chunk& log_chunk::default_instance() {
  protobuf_InitDefaults_ssl_5flog_2eproto();
  return *internal_default_instance();
}

log_chunk* log_chunk::New(::google::protobuf::Arena* arena) const {
  log_chunk* n = new log_chunk;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void log_chunk::Clear() {
// @@protoc_insertion_point(message_clear_start:log_chunk)
  ours_.Clear();
  opps_.Clear();
  if (has_ball()) {
    GOOGLE_DCHECK(ball_ != NULL);
    ball_->::Ball_message::Clear();
  }
  chunk_number_ = GOOGLE_LONGLONG(0);
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool log_chunk::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:log_chunk)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 chunk_number = 1;
      case 1: {
        if (tag == 8u) {
          set_has_chunk_number();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &chunk_number_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .Ball_message ball = 2;
      case 2: {
        if (tag == 18u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_ball()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .Robot_message ours = 3;
      case 3: {
        if (tag == 26u) {
          DO_(input->IncrementRecursionDepth());
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
                input, add_ours()));
        } else {
          goto handle_unusual;
        }
        input->UnsafeDecrementRecursionDepth();
        break;
      }

      // repeated .Robot_message opps = 4;
      case 4: {
        if (tag == 34u) {
          DO_(input->IncrementRecursionDepth());
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
                input, add_opps()));
        } else {
          goto handle_unusual;
        }
        input->UnsafeDecrementRecursionDepth();
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:log_chunk)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:log_chunk)
  return false;
#undef DO_
}

void log_chunk::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:log_chunk)
  // required int64 chunk_number = 1;
  if (has_chunk_number()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->chunk_number(), output);
  }

  // required .Ball_message ball = 2;
  if (has_ball()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *this->ball_, output);
  }

  // repeated .Robot_message ours = 3;
  for (unsigned int i = 0, n = this->ours_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->ours(i), output);
  }

  // repeated .Robot_message opps = 4;
  for (unsigned int i = 0, n = this->opps_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->opps(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:log_chunk)
}

::google::protobuf::uint8* log_chunk::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:log_chunk)
  // required int64 chunk_number = 1;
  if (has_chunk_number()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->chunk_number(), target);
  }

  // required .Ball_message ball = 2;
  if (has_ball()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        2, *this->ball_, false, target);
  }

  // repeated .Robot_message ours = 3;
  for (unsigned int i = 0, n = this->ours_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        3, this->ours(i), false, target);
  }

  // repeated .Robot_message opps = 4;
  for (unsigned int i = 0, n = this->opps_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        4, this->opps(i), false, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:log_chunk)
  return target;
}

size_t log_chunk::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:log_chunk)
  size_t total_size = 0;

  if (has_ball()) {
    // required .Ball_message ball = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->ball_);
  }

  if (has_chunk_number()) {
    // required int64 chunk_number = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->chunk_number());
  }

  return total_size;
}
size_t log_chunk::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:log_chunk)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .Ball_message ball = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->ball_);

    // required int64 chunk_number = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->chunk_number());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // repeated .Robot_message ours = 3;
  {
    unsigned int count = this->ours_size();
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->ours(i));
    }
  }

  // repeated .Robot_message opps = 4;
  {
    unsigned int count = this->opps_size();
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->opps(i));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void log_chunk::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:log_chunk)
  GOOGLE_DCHECK_NE(&from, this);
  const log_chunk* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const log_chunk>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:log_chunk)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:log_chunk)
    MergeFrom(*source);
  }
}

void log_chunk::MergeFrom(const log_chunk& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:log_chunk)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ours_.MergeFrom(from.ours_);
  opps_.MergeFrom(from.opps_);
  if (from._has_bits_[0 / 32] & 3u) {
    if (from.has_ball()) {
      mutable_ball()->::Ball_message::MergeFrom(from.ball());
    }
    if (from.has_chunk_number()) {
      set_chunk_number(from.chunk_number());
    }
  }
}

void log_chunk::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:log_chunk)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void log_chunk::CopyFrom(const log_chunk& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:log_chunk)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool log_chunk::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->ours())) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->opps())) return false;
  if (has_ball()) {
    if (!this->ball_->IsInitialized()) return false;
  }
  return true;
}

void log_chunk::Swap(log_chunk* other) {
  if (other == this) return;
  InternalSwap(other);
}
void log_chunk::InternalSwap(log_chunk* other) {
  ours_.UnsafeArenaSwap(&other->ours_);
  opps_.UnsafeArenaSwap(&other->opps_);
  std::swap(ball_, other->ball_);
  std::swap(chunk_number_, other->chunk_number_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata log_chunk::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// log_chunk

// required int64 chunk_number = 1;
bool log_chunk::has_chunk_number() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void log_chunk::set_has_chunk_number() {
  _has_bits_[0] |= 0x00000002u;
}
void log_chunk::clear_has_chunk_number() {
  _has_bits_[0] &= ~0x00000002u;
}
void log_chunk::clear_chunk_number() {
  chunk_number_ = GOOGLE_LONGLONG(0);
  clear_has_chunk_number();
}
::google::protobuf::int64 log_chunk::chunk_number() const {
  // @@protoc_insertion_point(field_get:log_chunk.chunk_number)
  return chunk_number_;
}
void log_chunk::set_chunk_number(::google::protobuf::int64 value) {
  set_has_chunk_number();
  chunk_number_ = value;
  // @@protoc_insertion_point(field_set:log_chunk.chunk_number)
}

// required .Ball_message ball = 2;
bool log_chunk::has_ball() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void log_chunk::set_has_ball() {
  _has_bits_[0] |= 0x00000001u;
}
void log_chunk::clear_has_ball() {
  _has_bits_[0] &= ~0x00000001u;
}
void log_chunk::clear_ball() {
  if (ball_ != NULL) ball_->::Ball_message::Clear();
  clear_has_ball();
}
const ::Ball_message& log_chunk::ball() const {
  // @@protoc_insertion_point(field_get:log_chunk.ball)
  return ball_ != NULL ? *ball_
                         : *::Ball_message::internal_default_instance();
}
::Ball_message* log_chunk::mutable_ball() {
  set_has_ball();
  if (ball_ == NULL) {
    ball_ = new ::Ball_message;
  }
  // @@protoc_insertion_point(field_mutable:log_chunk.ball)
  return ball_;
}
::Ball_message* log_chunk::release_ball() {
  // @@protoc_insertion_point(field_release:log_chunk.ball)
  clear_has_ball();
  ::Ball_message* temp = ball_;
  ball_ = NULL;
  return temp;
}
void log_chunk::set_allocated_ball(::Ball_message* ball) {
  delete ball_;
  ball_ = ball;
  if (ball) {
    set_has_ball();
  } else {
    clear_has_ball();
  }
  // @@protoc_insertion_point(field_set_allocated:log_chunk.ball)
}

// repeated .Robot_message ours = 3;
int log_chunk::ours_size() const {
  return ours_.size();
}
void log_chunk::clear_ours() {
  ours_.Clear();
}
const ::Robot_message& log_chunk::ours(int index) const {
  // @@protoc_insertion_point(field_get:log_chunk.ours)
  return ours_.Get(index);
}
::Robot_message* log_chunk::mutable_ours(int index) {
  // @@protoc_insertion_point(field_mutable:log_chunk.ours)
  return ours_.Mutable(index);
}
::Robot_message* log_chunk::add_ours() {
  // @@protoc_insertion_point(field_add:log_chunk.ours)
  return ours_.Add();
}
::google::protobuf::RepeatedPtrField< ::Robot_message >*
log_chunk::mutable_ours() {
  // @@protoc_insertion_point(field_mutable_list:log_chunk.ours)
  return &ours_;
}
const ::google::protobuf::RepeatedPtrField< ::Robot_message >&
log_chunk::ours() const {
  // @@protoc_insertion_point(field_list:log_chunk.ours)
  return ours_;
}

// repeated .Robot_message opps = 4;
int log_chunk::opps_size() const {
  return opps_.size();
}
void log_chunk::clear_opps() {
  opps_.Clear();
}
const ::Robot_message& log_chunk::opps(int index) const {
  // @@protoc_insertion_point(field_get:log_chunk.opps)
  return opps_.Get(index);
}
::Robot_message* log_chunk::mutable_opps(int index) {
  // @@protoc_insertion_point(field_mutable:log_chunk.opps)
  return opps_.Mutable(index);
}
::Robot_message* log_chunk::add_opps() {
  // @@protoc_insertion_point(field_add:log_chunk.opps)
  return opps_.Add();
}
::google::protobuf::RepeatedPtrField< ::Robot_message >*
log_chunk::mutable_opps() {
  // @@protoc_insertion_point(field_mutable_list:log_chunk.opps)
  return &opps_;
}
const ::google::protobuf::RepeatedPtrField< ::Robot_message >&
log_chunk::opps() const {
  // @@protoc_insertion_point(field_list:log_chunk.opps)
  return opps_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SSL_log::kNumberOfChunksFieldNumber;
const int SSL_log::kTimerIntervalFieldNumber;
const int SSL_log::kChunksFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SSL_log::SSL_log()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_InitDefaults_ssl_5flog_2eproto();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:SSL_log)
}
SSL_log::SSL_log(const SSL_log& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      chunks_(from.chunks_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&numberofchunks_, &from.numberofchunks_,
    reinterpret_cast<char*>(&timerinterval_) -
    reinterpret_cast<char*>(&numberofchunks_) + sizeof(timerinterval_));
  // @@protoc_insertion_point(copy_constructor:SSL_log)
}

void SSL_log::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&numberofchunks_, 0, reinterpret_cast<char*>(&timerinterval_) -
    reinterpret_cast<char*>(&numberofchunks_) + sizeof(timerinterval_));
}

SSL_log::~SSL_log() {
  // @@protoc_insertion_point(destructor:SSL_log)
  SharedDtor();
}

void SSL_log::SharedDtor() {
}

void SSL_log::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SSL_log::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[1].descriptor;
}

const SSL_log& SSL_log::default_instance() {
  protobuf_InitDefaults_ssl_5flog_2eproto();
  return *internal_default_instance();
}

SSL_log* SSL_log::New(::google::protobuf::Arena* arena) const {
  SSL_log* n = new SSL_log;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void SSL_log::Clear() {
// @@protoc_insertion_point(message_clear_start:SSL_log)
  chunks_.Clear();
  if (_has_bits_[0 / 32] & 3u) {
    ::memset(&numberofchunks_, 0, reinterpret_cast<char*>(&timerinterval_) -
      reinterpret_cast<char*>(&numberofchunks_) + sizeof(timerinterval_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool SSL_log::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:SSL_log)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 numberOfChunks = 1;
      case 1: {
        if (tag == 8u) {
          set_has_numberofchunks();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &numberofchunks_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int64 timerInterval = 2;
      case 2: {
        if (tag == 16u) {
          set_has_timerinterval();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &timerinterval_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .log_chunk chunks = 3;
      case 3: {
        if (tag == 26u) {
          DO_(input->IncrementRecursionDepth());
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
                input, add_chunks()));
        } else {
          goto handle_unusual;
        }
        input->UnsafeDecrementRecursionDepth();
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:SSL_log)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:SSL_log)
  return false;
#undef DO_
}

void SSL_log::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:SSL_log)
  // required int64 numberOfChunks = 1;
  if (has_numberofchunks()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->numberofchunks(), output);
  }

  // required int64 timerInterval = 2;
  if (has_timerinterval()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->timerinterval(), output);
  }

  // repeated .log_chunk chunks = 3;
  for (unsigned int i = 0, n = this->chunks_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->chunks(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:SSL_log)
}

::google::protobuf::uint8* SSL_log::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:SSL_log)
  // required int64 numberOfChunks = 1;
  if (has_numberofchunks()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->numberofchunks(), target);
  }

  // required int64 timerInterval = 2;
  if (has_timerinterval()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->timerinterval(), target);
  }

  // repeated .log_chunk chunks = 3;
  for (unsigned int i = 0, n = this->chunks_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        3, this->chunks(i), false, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:SSL_log)
  return target;
}

size_t SSL_log::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:SSL_log)
  size_t total_size = 0;

  if (has_numberofchunks()) {
    // required int64 numberOfChunks = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->numberofchunks());
  }

  if (has_timerinterval()) {
    // required int64 timerInterval = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->timerinterval());
  }

  return total_size;
}
size_t SSL_log::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:SSL_log)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required int64 numberOfChunks = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->numberofchunks());

    // required int64 timerInterval = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->timerinterval());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // repeated .log_chunk chunks = 3;
  {
    unsigned int count = this->chunks_size();
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->chunks(i));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SSL_log::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:SSL_log)
  GOOGLE_DCHECK_NE(&from, this);
  const SSL_log* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const SSL_log>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:SSL_log)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:SSL_log)
    MergeFrom(*source);
  }
}

void SSL_log::MergeFrom(const SSL_log& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:SSL_log)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  chunks_.MergeFrom(from.chunks_);
  if (from._has_bits_[0 / 32] & 3u) {
    if (from.has_numberofchunks()) {
      set_numberofchunks(from.numberofchunks());
    }
    if (from.has_timerinterval()) {
      set_timerinterval(from.timerinterval());
    }
  }
}

void SSL_log::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:SSL_log)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SSL_log::CopyFrom(const SSL_log& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:SSL_log)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SSL_log::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->chunks())) return false;
  return true;
}

void SSL_log::Swap(SSL_log* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SSL_log::InternalSwap(SSL_log* other) {
  chunks_.UnsafeArenaSwap(&other->chunks_);
  std::swap(numberofchunks_, other->numberofchunks_);
  std::swap(timerinterval_, other->timerinterval_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata SSL_log::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[1];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// SSL_log

// required int64 numberOfChunks = 1;
bool SSL_log::has_numberofchunks() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void SSL_log::set_has_numberofchunks() {
  _has_bits_[0] |= 0x00000001u;
}
void SSL_log::clear_has_numberofchunks() {
  _has_bits_[0] &= ~0x00000001u;
}
void SSL_log::clear_numberofchunks() {
  numberofchunks_ = GOOGLE_LONGLONG(0);
  clear_has_numberofchunks();
}
::google::protobuf::int64 SSL_log::numberofchunks() const {
  // @@protoc_insertion_point(field_get:SSL_log.numberOfChunks)
  return numberofchunks_;
}
void SSL_log::set_numberofchunks(::google::protobuf::int64 value) {
  set_has_numberofchunks();
  numberofchunks_ = value;
  // @@protoc_insertion_point(field_set:SSL_log.numberOfChunks)
}

// required int64 timerInterval = 2;
bool SSL_log::has_timerinterval() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void SSL_log::set_has_timerinterval() {
  _has_bits_[0] |= 0x00000002u;
}
void SSL_log::clear_has_timerinterval() {
  _has_bits_[0] &= ~0x00000002u;
}
void SSL_log::clear_timerinterval() {
  timerinterval_ = GOOGLE_LONGLONG(0);
  clear_has_timerinterval();
}
::google::protobuf::int64 SSL_log::timerinterval() const {
  // @@protoc_insertion_point(field_get:SSL_log.timerInterval)
  return timerinterval_;
}
void SSL_log::set_timerinterval(::google::protobuf::int64 value) {
  set_has_timerinterval();
  timerinterval_ = value;
  // @@protoc_insertion_point(field_set:SSL_log.timerInterval)
}

// repeated .log_chunk chunks = 3;
int SSL_log::chunks_size() const {
  return chunks_.size();
}
void SSL_log::clear_chunks() {
  chunks_.Clear();
}
const ::log_chunk& SSL_log::chunks(int index) const {
  // @@protoc_insertion_point(field_get:SSL_log.chunks)
  return chunks_.Get(index);
}
::log_chunk* SSL_log::mutable_chunks(int index) {
  // @@protoc_insertion_point(field_mutable:SSL_log.chunks)
  return chunks_.Mutable(index);
}
::log_chunk* SSL_log::add_chunks() {
  // @@protoc_insertion_point(field_add:SSL_log.chunks)
  return chunks_.Add();
}
::google::protobuf::RepeatedPtrField< ::log_chunk >*
SSL_log::mutable_chunks() {
  // @@protoc_insertion_point(field_mutable_list:SSL_log.chunks)
  return &chunks_;
}
const ::google::protobuf::RepeatedPtrField< ::log_chunk >&
SSL_log::chunks() const {
  // @@protoc_insertion_point(field_list:SSL_log.chunks)
  return chunks_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
