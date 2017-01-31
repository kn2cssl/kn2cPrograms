// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: vision_log.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "vision_log.pb.h"

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
class Vision_chunkDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<Vision_chunk> {};
Vision_chunkDefaultTypeInternal _Vision_chunk_default_instance_;
class Vision_logDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<Vision_log> {};
Vision_logDefaultTypeInternal _Vision_log_default_instance_;

namespace {

::google::protobuf::Metadata file_level_metadata[2];

}  // namespace


const ::google::protobuf::uint32* protobuf_Offsets_vision_5flog_2eproto() GOOGLE_ATTRIBUTE_COLD;
const ::google::protobuf::uint32* protobuf_Offsets_vision_5flog_2eproto() {
  static const ::google::protobuf::uint32 offsets[] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_chunk, _has_bits_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_chunk, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_chunk, time_elapsed_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_chunk, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_chunk, packet_),
    1,
    2,
    0,
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_log, _has_bits_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_log, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_log, number_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Vision_log, chunks_),
    0,
    1,
  };
  return offsets;
}

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 7, sizeof(Vision_chunk)},
  { 10, 16, sizeof(Vision_log)},
};

static const ::google::protobuf::internal::DefaultInstanceData file_default_instances[] = {
  {reinterpret_cast<const ::google::protobuf::Message*>(&_Vision_chunk_default_instance_), NULL},
  {reinterpret_cast<const ::google::protobuf::Message*>(&_Vision_log_default_instance_), NULL},
};

namespace {

void protobuf_AssignDescriptors() {
  protobuf_AddDesc_vision_5flog_2eproto();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "vision_log.proto", schemas, file_default_instances, protobuf_Offsets_vision_5flog_2eproto(), factory,
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

void protobuf_ShutdownFile_vision_5flog_2eproto() {
  _Vision_chunk_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
  _Vision_log_default_instance_.Shutdown();
  delete file_level_metadata[1].reflection;
}

void protobuf_InitDefaults_vision_5flog_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_InitDefaults_messages_5frobocup_5fssl_5fwrapper_2eproto();
  ::RoboCup2014Legacy::Wrapper::protobuf_InitDefaults_messages_5frobocup_5fssl_5fwrapper_5flegacy_2eproto();
  ::google::protobuf::internal::InitProtobufDefaults();
  _Vision_chunk_default_instance_.DefaultConstruct();
  _Vision_log_default_instance_.DefaultConstruct();
  _Vision_chunk_default_instance_.get_mutable()->packet_ = const_cast< ::SSL_WrapperPacket*>(
      ::SSL_WrapperPacket::internal_default_instance());
}

void protobuf_InitDefaults_vision_5flog_2eproto() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_InitDefaults_vision_5flog_2eproto_impl);
}
void protobuf_AddDesc_vision_5flog_2eproto_impl() {
  protobuf_InitDefaults_vision_5flog_2eproto();
  static const char descriptor[] = {
      "\n\020vision_log.proto\032\"messages_robocup_ssl"
      "_wrapper.proto\032)messages_robocup_ssl_wra"
      "pper_legacy.proto\"T\n\014Vision_chunk\022\024\n\014tim"
      "e_elapsed\030\001 \002(\003\022\n\n\002id\030\002 \001(\003\022\"\n\006packet\030\003 "
      "\002(\0132\022.SSL_WrapperPacket\";\n\nVision_log\022\016\n"
      "\006number\030\001 \001(\003\022\035\n\006chunks\030\002 \003(\0132\r.Vision_c"
      "hunk"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 244);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "vision_log.proto", &protobuf_RegisterTypes);
  ::protobuf_AddDesc_messages_5frobocup_5fssl_5fwrapper_2eproto();
  ::RoboCup2014Legacy::Wrapper::protobuf_AddDesc_messages_5frobocup_5fssl_5fwrapper_5flegacy_2eproto();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_vision_5flog_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_vision_5flog_2eproto_once_);
void protobuf_AddDesc_vision_5flog_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_vision_5flog_2eproto_once_,
                 &protobuf_AddDesc_vision_5flog_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_vision_5flog_2eproto {
  StaticDescriptorInitializer_vision_5flog_2eproto() {
    protobuf_AddDesc_vision_5flog_2eproto();
  }
} static_descriptor_initializer_vision_5flog_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Vision_chunk::kTimeElapsedFieldNumber;
const int Vision_chunk::kIdFieldNumber;
const int Vision_chunk::kPacketFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Vision_chunk::Vision_chunk()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_InitDefaults_vision_5flog_2eproto();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:Vision_chunk)
}
Vision_chunk::Vision_chunk(const Vision_chunk& from)
<<<<<<< HEAD
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_packet()) {
    packet_ = new ::SSL_WrapperPacket(*from.packet_);
  } else {
    packet_ = NULL;
  }
  ::memcpy(&time_elapsed_, &from.time_elapsed_,
    reinterpret_cast<char*>(&id_) -
    reinterpret_cast<char*>(&time_elapsed_) + sizeof(id_));
=======
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  // @@protoc_insertion_point(copy_constructor:Vision_chunk)
}

void Vision_chunk::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&packet_, 0, reinterpret_cast<char*>(&id_) -
    reinterpret_cast<char*>(&packet_) + sizeof(id_));
}

Vision_chunk::~Vision_chunk() {
  // @@protoc_insertion_point(destructor:Vision_chunk)
  SharedDtor();
}

void Vision_chunk::SharedDtor() {
  if (this != internal_default_instance()) {
    delete packet_;
  }
}

void Vision_chunk::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Vision_chunk::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0].descriptor;
}

const Vision_chunk& Vision_chunk::default_instance() {
  protobuf_InitDefaults_vision_5flog_2eproto();
  return *internal_default_instance();
}

Vision_chunk* Vision_chunk::New(::google::protobuf::Arena* arena) const {
  Vision_chunk* n = new Vision_chunk;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Vision_chunk::Clear() {
<<<<<<< HEAD
// @@protoc_insertion_point(message_clear_start:Vision_chunk)
  if (has_packet()) {
    GOOGLE_DCHECK(packet_ != NULL);
    packet_->::SSL_WrapperPacket::Clear();
  }
  if (_has_bits_[0 / 32] & 6u) {
    ::memset(&time_elapsed_, 0, reinterpret_cast<char*>(&id_) -
      reinterpret_cast<char*>(&time_elapsed_) + sizeof(id_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
=======
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Vision_chunk*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(time_elapsed_, id_);
    if (has_packet()) {
      if (packet_ != NULL) packet_->::SSL_WrapperPacket::Clear();
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
}

bool Vision_chunk::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
<<<<<<< HEAD
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Vision_chunk)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
=======
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Vision_chunk)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 time_elapsed = 1;
      case 1: {
<<<<<<< HEAD
        if (tag == 8u) {
          set_has_time_elapsed();
=======
        if (tag == 8) {
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &time_elapsed_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int64 id = 2;
      case 2: {
<<<<<<< HEAD
        if (tag == 16u) {
          set_has_id();
=======
        if (tag == 16) {
         parse_id:
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .SSL_WrapperPacket packet = 3;
      case 3: {
<<<<<<< HEAD
        if (tag == 26u) {
=======
        if (tag == 26) {
         parse_packet:
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_packet()));
        } else {
          goto handle_unusual;
        }
<<<<<<< HEAD
=======
        if (input->ExpectAtEnd()) goto success;
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
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
  // @@protoc_insertion_point(parse_success:Vision_chunk)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Vision_chunk)
  return false;
#undef DO_
}

void Vision_chunk::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Vision_chunk)
  // required int64 time_elapsed = 1;
  if (has_time_elapsed()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->time_elapsed(), output);
  }

  // optional int64 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->id(), output);
  }

  // required .SSL_WrapperPacket packet = 3;
  if (has_packet()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, *this->packet_, output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Vision_chunk)
}

<<<<<<< HEAD
::google::protobuf::uint8* Vision_chunk::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
=======
::google::protobuf::uint8* Vision_chunk::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  // @@protoc_insertion_point(serialize_to_array_start:Vision_chunk)
  // required int64 time_elapsed = 1;
  if (has_time_elapsed()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->time_elapsed(), target);
  }

  // optional int64 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->id(), target);
  }

  // required .SSL_WrapperPacket packet = 3;
  if (has_packet()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        3, *this->packet_, false, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Vision_chunk)
  return target;
}

size_t Vision_chunk::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:Vision_chunk)
  size_t total_size = 0;

  if (has_packet()) {
    // required .SSL_WrapperPacket packet = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->packet_);
  }

  if (has_time_elapsed()) {
    // required int64 time_elapsed = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->time_elapsed());
  }

  return total_size;
}
size_t Vision_chunk::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Vision_chunk)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .SSL_WrapperPacket packet = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->packet_);

    // required int64 time_elapsed = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->time_elapsed());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  // optional int64 id = 2;
  if (has_id()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->id());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Vision_chunk::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Vision_chunk)
  GOOGLE_DCHECK_NE(&from, this);
  const Vision_chunk* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Vision_chunk>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Vision_chunk)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Vision_chunk)
    MergeFrom(*source);
  }
}

void Vision_chunk::MergeFrom(const Vision_chunk& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Vision_chunk)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._has_bits_[0 / 32] & 7u) {
    if (from.has_packet()) {
      mutable_packet()->::SSL_WrapperPacket::MergeFrom(from.packet());
    }
    if (from.has_time_elapsed()) {
      set_time_elapsed(from.time_elapsed());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
  }
}

void Vision_chunk::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Vision_chunk)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Vision_chunk::CopyFrom(const Vision_chunk& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Vision_chunk)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Vision_chunk::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  if (has_packet()) {
    if (!this->packet_->IsInitialized()) return false;
  }
  return true;
}

void Vision_chunk::Swap(Vision_chunk* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Vision_chunk::InternalSwap(Vision_chunk* other) {
  std::swap(packet_, other->packet_);
  std::swap(time_elapsed_, other->time_elapsed_);
  std::swap(id_, other->id_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Vision_chunk::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Vision_chunk

// required int64 time_elapsed = 1;
bool Vision_chunk::has_time_elapsed() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void Vision_chunk::set_has_time_elapsed() {
  _has_bits_[0] |= 0x00000002u;
}
void Vision_chunk::clear_has_time_elapsed() {
  _has_bits_[0] &= ~0x00000002u;
}
void Vision_chunk::clear_time_elapsed() {
  time_elapsed_ = GOOGLE_LONGLONG(0);
  clear_has_time_elapsed();
}
::google::protobuf::int64 Vision_chunk::time_elapsed() const {
  // @@protoc_insertion_point(field_get:Vision_chunk.time_elapsed)
  return time_elapsed_;
}
void Vision_chunk::set_time_elapsed(::google::protobuf::int64 value) {
  set_has_time_elapsed();
  time_elapsed_ = value;
  // @@protoc_insertion_point(field_set:Vision_chunk.time_elapsed)
}

// optional int64 id = 2;
bool Vision_chunk::has_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void Vision_chunk::set_has_id() {
  _has_bits_[0] |= 0x00000004u;
}
void Vision_chunk::clear_has_id() {
  _has_bits_[0] &= ~0x00000004u;
}
void Vision_chunk::clear_id() {
  id_ = GOOGLE_LONGLONG(0);
  clear_has_id();
}
::google::protobuf::int64 Vision_chunk::id() const {
  // @@protoc_insertion_point(field_get:Vision_chunk.id)
  return id_;
}
void Vision_chunk::set_id(::google::protobuf::int64 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:Vision_chunk.id)
}

// required .SSL_WrapperPacket packet = 3;
bool Vision_chunk::has_packet() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void Vision_chunk::set_has_packet() {
  _has_bits_[0] |= 0x00000001u;
}
void Vision_chunk::clear_has_packet() {
  _has_bits_[0] &= ~0x00000001u;
}
void Vision_chunk::clear_packet() {
  if (packet_ != NULL) packet_->::SSL_WrapperPacket::Clear();
  clear_has_packet();
}
const ::SSL_WrapperPacket& Vision_chunk::packet() const {
  // @@protoc_insertion_point(field_get:Vision_chunk.packet)
  return packet_ != NULL ? *packet_
                         : *::SSL_WrapperPacket::internal_default_instance();
}
::SSL_WrapperPacket* Vision_chunk::mutable_packet() {
  set_has_packet();
  if (packet_ == NULL) {
    packet_ = new ::SSL_WrapperPacket;
  }
  // @@protoc_insertion_point(field_mutable:Vision_chunk.packet)
  return packet_;
}
::SSL_WrapperPacket* Vision_chunk::release_packet() {
  // @@protoc_insertion_point(field_release:Vision_chunk.packet)
  clear_has_packet();
  ::SSL_WrapperPacket* temp = packet_;
  packet_ = NULL;
  return temp;
}
void Vision_chunk::set_allocated_packet(::SSL_WrapperPacket* packet) {
  delete packet_;
  packet_ = packet;
  if (packet) {
    set_has_packet();
  } else {
    clear_has_packet();
  }
  // @@protoc_insertion_point(field_set_allocated:Vision_chunk.packet)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Vision_log::kNumberFieldNumber;
const int Vision_log::kChunksFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Vision_log::Vision_log()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_InitDefaults_vision_5flog_2eproto();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:Vision_log)
}
Vision_log::Vision_log(const Vision_log& from)
<<<<<<< HEAD
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      chunks_(from.chunks_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  number_ = from.number_;
=======
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  // @@protoc_insertion_point(copy_constructor:Vision_log)
}

void Vision_log::SharedCtor() {
  _cached_size_ = 0;
  number_ = GOOGLE_LONGLONG(0);
}

Vision_log::~Vision_log() {
  // @@protoc_insertion_point(destructor:Vision_log)
  SharedDtor();
}

void Vision_log::SharedDtor() {
}

void Vision_log::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Vision_log::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[1].descriptor;
}

const Vision_log& Vision_log::default_instance() {
  protobuf_InitDefaults_vision_5flog_2eproto();
  return *internal_default_instance();
}

Vision_log* Vision_log::New(::google::protobuf::Arena* arena) const {
  Vision_log* n = new Vision_log;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Vision_log::Clear() {
<<<<<<< HEAD
// @@protoc_insertion_point(message_clear_start:Vision_log)
=======
  number_ = GOOGLE_LONGLONG(0);
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  chunks_.Clear();
  number_ = GOOGLE_LONGLONG(0);
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool Vision_log::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
<<<<<<< HEAD
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Vision_log)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
=======
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Vision_log)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 number = 1;
      case 1: {
<<<<<<< HEAD
        if (tag == 8u) {
          set_has_number();
=======
        if (tag == 8) {
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &number_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .Vision_chunk chunks = 2;
      case 2: {
<<<<<<< HEAD
        if (tag == 18u) {
          DO_(input->IncrementRecursionDepth());
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
=======
        if (tag == 18) {
         parse_chunks:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
                input, add_chunks()));
        } else {
          goto handle_unusual;
        }
<<<<<<< HEAD
        input->UnsafeDecrementRecursionDepth();
=======
        if (input->ExpectTag(18)) goto parse_chunks;
        if (input->ExpectAtEnd()) goto success;
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
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
  // @@protoc_insertion_point(parse_success:Vision_log)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Vision_log)
  return false;
#undef DO_
}

void Vision_log::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Vision_log)
  // optional int64 number = 1;
  if (has_number()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->number(), output);
  }

  // repeated .Vision_chunk chunks = 2;
  for (unsigned int i = 0, n = this->chunks_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->chunks(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Vision_log)
}

<<<<<<< HEAD
::google::protobuf::uint8* Vision_log::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
=======
::google::protobuf::uint8* Vision_log::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  // @@protoc_insertion_point(serialize_to_array_start:Vision_log)
  // optional int64 number = 1;
  if (has_number()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->number(), target);
  }

  // repeated .Vision_chunk chunks = 2;
  for (unsigned int i = 0, n = this->chunks_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        2, this->chunks(i), false, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Vision_log)
  return target;
}

size_t Vision_log::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Vision_log)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  // repeated .Vision_chunk chunks = 2;
  {
    unsigned int count = this->chunks_size();
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->chunks(i));
    }
  }

  // optional int64 number = 1;
  if (has_number()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->number());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Vision_log::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Vision_log)
  GOOGLE_DCHECK_NE(&from, this);
  const Vision_log* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Vision_log>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Vision_log)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Vision_log)
    MergeFrom(*source);
  }
}

void Vision_log::MergeFrom(const Vision_log& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Vision_log)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  chunks_.MergeFrom(from.chunks_);
  if (from.has_number()) {
    set_number(from.number());
  }
}

void Vision_log::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Vision_log)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Vision_log::CopyFrom(const Vision_log& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Vision_log)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Vision_log::IsInitialized() const {
<<<<<<< HEAD
=======

>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  if (!::google::protobuf::internal::AllAreInitialized(this->chunks())) return false;
  return true;
}

void Vision_log::Swap(Vision_log* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Vision_log::InternalSwap(Vision_log* other) {
  chunks_.UnsafeArenaSwap(&other->chunks_);
  std::swap(number_, other->number_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Vision_log::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[1];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Vision_log

// optional int64 number = 1;
bool Vision_log::has_number() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void Vision_log::set_has_number() {
  _has_bits_[0] |= 0x00000001u;
}
void Vision_log::clear_has_number() {
  _has_bits_[0] &= ~0x00000001u;
}
void Vision_log::clear_number() {
  number_ = GOOGLE_LONGLONG(0);
  clear_has_number();
}
::google::protobuf::int64 Vision_log::number() const {
  // @@protoc_insertion_point(field_get:Vision_log.number)
  return number_;
}
void Vision_log::set_number(::google::protobuf::int64 value) {
  set_has_number();
  number_ = value;
  // @@protoc_insertion_point(field_set:Vision_log.number)
}

// repeated .Vision_chunk chunks = 2;
int Vision_log::chunks_size() const {
  return chunks_.size();
}
void Vision_log::clear_chunks() {
  chunks_.Clear();
}
const ::Vision_chunk& Vision_log::chunks(int index) const {
  // @@protoc_insertion_point(field_get:Vision_log.chunks)
  return chunks_.Get(index);
}
::Vision_chunk* Vision_log::mutable_chunks(int index) {
  // @@protoc_insertion_point(field_mutable:Vision_log.chunks)
  return chunks_.Mutable(index);
}
::Vision_chunk* Vision_log::add_chunks() {
  // @@protoc_insertion_point(field_add:Vision_log.chunks)
  return chunks_.Add();
}
::google::protobuf::RepeatedPtrField< ::Vision_chunk >*
Vision_log::mutable_chunks() {
  // @@protoc_insertion_point(field_mutable_list:Vision_log.chunks)
  return &chunks_;
}
const ::google::protobuf::RepeatedPtrField< ::Vision_chunk >&
Vision_log::chunks() const {
  // @@protoc_insertion_point(field_list:Vision_log.chunks)
  return chunks_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
