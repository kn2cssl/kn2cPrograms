// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: vision_log.proto

#ifndef PROTOBUF_vision_5flog_2eproto__INCLUDED
#define PROTOBUF_vision_5flog_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "messages_robocup_ssl_wrapper.pb.h"
#include "messages_robocup_ssl_wrapper_legacy.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_vision_5flog_2eproto();
void protobuf_AssignDesc_vision_5flog_2eproto();
void protobuf_ShutdownFile_vision_5flog_2eproto();

class Vision_chunk;
class Vision_log;

// ===================================================================

class Vision_chunk : public ::google::protobuf::Message {
 public:
  Vision_chunk();
  virtual ~Vision_chunk();

  Vision_chunk(const Vision_chunk& from);

  inline Vision_chunk& operator=(const Vision_chunk& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Vision_chunk& default_instance();

  void Swap(Vision_chunk* other);

  // implements Message ----------------------------------------------

  Vision_chunk* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Vision_chunk& from);
  void MergeFrom(const Vision_chunk& from);
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
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int64 time_elapsed = 1;
  inline bool has_time_elapsed() const;
  inline void clear_time_elapsed();
  static const int kTimeElapsedFieldNumber = 1;
  inline ::google::protobuf::int64 time_elapsed() const;
  inline void set_time_elapsed(::google::protobuf::int64 value);

  // optional int64 id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline ::google::protobuf::int64 id() const;
  inline void set_id(::google::protobuf::int64 value);

  // required .SSL_WrapperPacket packet = 3;
  inline bool has_packet() const;
  inline void clear_packet();
  static const int kPacketFieldNumber = 3;
  inline const ::SSL_WrapperPacket& packet() const;
  inline ::SSL_WrapperPacket* mutable_packet();
  inline ::SSL_WrapperPacket* release_packet();
  inline void set_allocated_packet(::SSL_WrapperPacket* packet);

  // @@protoc_insertion_point(class_scope:Vision_chunk)
 private:
  inline void set_has_time_elapsed();
  inline void clear_has_time_elapsed();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_packet();
  inline void clear_has_packet();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 time_elapsed_;
  ::google::protobuf::int64 id_;
  ::SSL_WrapperPacket* packet_;
  friend void  protobuf_AddDesc_vision_5flog_2eproto();
  friend void protobuf_AssignDesc_vision_5flog_2eproto();
  friend void protobuf_ShutdownFile_vision_5flog_2eproto();

  void InitAsDefaultInstance();
  static Vision_chunk* default_instance_;
};
// -------------------------------------------------------------------

class Vision_log : public ::google::protobuf::Message {
 public:
  Vision_log();
  virtual ~Vision_log();

  Vision_log(const Vision_log& from);

  inline Vision_log& operator=(const Vision_log& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Vision_log& default_instance();

  void Swap(Vision_log* other);

  // implements Message ----------------------------------------------

  Vision_log* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Vision_log& from);
  void MergeFrom(const Vision_log& from);
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
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int64 number = 1;
  inline bool has_number() const;
  inline void clear_number();
  static const int kNumberFieldNumber = 1;
  inline ::google::protobuf::int64 number() const;
  inline void set_number(::google::protobuf::int64 value);

  // repeated .Vision_chunk chunks = 2;
  inline int chunks_size() const;
  inline void clear_chunks();
  static const int kChunksFieldNumber = 2;
  inline const ::Vision_chunk& chunks(int index) const;
  inline ::Vision_chunk* mutable_chunks(int index);
  inline ::Vision_chunk* add_chunks();
  inline const ::google::protobuf::RepeatedPtrField< ::Vision_chunk >&
      chunks() const;
  inline ::google::protobuf::RepeatedPtrField< ::Vision_chunk >*
      mutable_chunks();

  // @@protoc_insertion_point(class_scope:Vision_log)
 private:
  inline void set_has_number();
  inline void clear_has_number();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 number_;
  ::google::protobuf::RepeatedPtrField< ::Vision_chunk > chunks_;
  friend void  protobuf_AddDesc_vision_5flog_2eproto();
  friend void protobuf_AssignDesc_vision_5flog_2eproto();
  friend void protobuf_ShutdownFile_vision_5flog_2eproto();

  void InitAsDefaultInstance();
  static Vision_log* default_instance_;
};
// ===================================================================


// ===================================================================

// Vision_chunk

// required int64 time_elapsed = 1;
inline bool Vision_chunk::has_time_elapsed() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Vision_chunk::set_has_time_elapsed() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Vision_chunk::clear_has_time_elapsed() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Vision_chunk::clear_time_elapsed() {
  time_elapsed_ = GOOGLE_LONGLONG(0);
  clear_has_time_elapsed();
}
inline ::google::protobuf::int64 Vision_chunk::time_elapsed() const {
  // @@protoc_insertion_point(field_get:Vision_chunk.time_elapsed)
  return time_elapsed_;
}
inline void Vision_chunk::set_time_elapsed(::google::protobuf::int64 value) {
  set_has_time_elapsed();
  time_elapsed_ = value;
  // @@protoc_insertion_point(field_set:Vision_chunk.time_elapsed)
}

// optional int64 id = 2;
inline bool Vision_chunk::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Vision_chunk::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Vision_chunk::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Vision_chunk::clear_id() {
  id_ = GOOGLE_LONGLONG(0);
  clear_has_id();
}
inline ::google::protobuf::int64 Vision_chunk::id() const {
  // @@protoc_insertion_point(field_get:Vision_chunk.id)
  return id_;
}
inline void Vision_chunk::set_id(::google::protobuf::int64 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:Vision_chunk.id)
}

// required .SSL_WrapperPacket packet = 3;
inline bool Vision_chunk::has_packet() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Vision_chunk::set_has_packet() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Vision_chunk::clear_has_packet() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Vision_chunk::clear_packet() {
  if (packet_ != NULL) packet_->::SSL_WrapperPacket::Clear();
  clear_has_packet();
}
inline const ::SSL_WrapperPacket& Vision_chunk::packet() const {
  // @@protoc_insertion_point(field_get:Vision_chunk.packet)
  return packet_ != NULL ? *packet_ : *default_instance_->packet_;
}
inline ::SSL_WrapperPacket* Vision_chunk::mutable_packet() {
  set_has_packet();
  if (packet_ == NULL) packet_ = new ::SSL_WrapperPacket;
  // @@protoc_insertion_point(field_mutable:Vision_chunk.packet)
  return packet_;
}
inline ::SSL_WrapperPacket* Vision_chunk::release_packet() {
  clear_has_packet();
  ::SSL_WrapperPacket* temp = packet_;
  packet_ = NULL;
  return temp;
}
inline void Vision_chunk::set_allocated_packet(::SSL_WrapperPacket* packet) {
  delete packet_;
  packet_ = packet;
  if (packet) {
    set_has_packet();
  } else {
    clear_has_packet();
  }
  // @@protoc_insertion_point(field_set_allocated:Vision_chunk.packet)
}

// -------------------------------------------------------------------

// Vision_log

// optional int64 number = 1;
inline bool Vision_log::has_number() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Vision_log::set_has_number() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Vision_log::clear_has_number() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Vision_log::clear_number() {
  number_ = GOOGLE_LONGLONG(0);
  clear_has_number();
}
inline ::google::protobuf::int64 Vision_log::number() const {
  // @@protoc_insertion_point(field_get:Vision_log.number)
  return number_;
}
inline void Vision_log::set_number(::google::protobuf::int64 value) {
  set_has_number();
  number_ = value;
  // @@protoc_insertion_point(field_set:Vision_log.number)
}

// repeated .Vision_chunk chunks = 2;
inline int Vision_log::chunks_size() const {
  return chunks_.size();
}
inline void Vision_log::clear_chunks() {
  chunks_.Clear();
}
inline const ::Vision_chunk& Vision_log::chunks(int index) const {
  // @@protoc_insertion_point(field_get:Vision_log.chunks)
  return chunks_.Get(index);
}
inline ::Vision_chunk* Vision_log::mutable_chunks(int index) {
  // @@protoc_insertion_point(field_mutable:Vision_log.chunks)
  return chunks_.Mutable(index);
}
inline ::Vision_chunk* Vision_log::add_chunks() {
  // @@protoc_insertion_point(field_add:Vision_log.chunks)
  return chunks_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Vision_chunk >&
Vision_log::chunks() const {
  // @@protoc_insertion_point(field_list:Vision_log.chunks)
  return chunks_;
}
inline ::google::protobuf::RepeatedPtrField< ::Vision_chunk >*
Vision_log::mutable_chunks() {
  // @@protoc_insertion_point(field_mutable_list:Vision_log.chunks)
  return &chunks_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_vision_5flog_2eproto__INCLUDED
