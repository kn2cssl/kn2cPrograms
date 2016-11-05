// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ref_log.proto

#ifndef PROTOBUF_ref_5flog_2eproto__INCLUDED
#define PROTOBUF_ref_5flog_2eproto__INCLUDED

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
#include "referee.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ref_5flog_2eproto();
void protobuf_AssignDesc_ref_5flog_2eproto();
void protobuf_ShutdownFile_ref_5flog_2eproto();

class Ref_chunk;
class Ref_log;

// ===================================================================

class Ref_chunk : public ::google::protobuf::Message {
 public:
  Ref_chunk();
  virtual ~Ref_chunk();

  Ref_chunk(const Ref_chunk& from);

  inline Ref_chunk& operator=(const Ref_chunk& from) {
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
  static const Ref_chunk& default_instance();

  void Swap(Ref_chunk* other);

  // implements Message ----------------------------------------------

  Ref_chunk* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Ref_chunk& from);
  void MergeFrom(const Ref_chunk& from);
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

  // required .SSL_Referee packet = 3;
  inline bool has_packet() const;
  inline void clear_packet();
  static const int kPacketFieldNumber = 3;
  inline const ::SSL_Referee& packet() const;
  inline ::SSL_Referee* mutable_packet();
  inline ::SSL_Referee* release_packet();
  inline void set_allocated_packet(::SSL_Referee* packet);

  // @@protoc_insertion_point(class_scope:Ref_chunk)
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
  ::SSL_Referee* packet_;
  friend void  protobuf_AddDesc_ref_5flog_2eproto();
  friend void protobuf_AssignDesc_ref_5flog_2eproto();
  friend void protobuf_ShutdownFile_ref_5flog_2eproto();

  void InitAsDefaultInstance();
  static Ref_chunk* default_instance_;
};
// -------------------------------------------------------------------

class Ref_log : public ::google::protobuf::Message {
 public:
  Ref_log();
  virtual ~Ref_log();

  Ref_log(const Ref_log& from);

  inline Ref_log& operator=(const Ref_log& from) {
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
  static const Ref_log& default_instance();

  void Swap(Ref_log* other);

  // implements Message ----------------------------------------------

  Ref_log* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Ref_log& from);
  void MergeFrom(const Ref_log& from);
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

  // repeated .Ref_chunk chunks = 2;
  inline int chunks_size() const;
  inline void clear_chunks();
  static const int kChunksFieldNumber = 2;
  inline const ::Ref_chunk& chunks(int index) const;
  inline ::Ref_chunk* mutable_chunks(int index);
  inline ::Ref_chunk* add_chunks();
  inline const ::google::protobuf::RepeatedPtrField< ::Ref_chunk >&
      chunks() const;
  inline ::google::protobuf::RepeatedPtrField< ::Ref_chunk >*
      mutable_chunks();

  // @@protoc_insertion_point(class_scope:Ref_log)
 private:
  inline void set_has_number();
  inline void clear_has_number();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 number_;
  ::google::protobuf::RepeatedPtrField< ::Ref_chunk > chunks_;
  friend void  protobuf_AddDesc_ref_5flog_2eproto();
  friend void protobuf_AssignDesc_ref_5flog_2eproto();
  friend void protobuf_ShutdownFile_ref_5flog_2eproto();

  void InitAsDefaultInstance();
  static Ref_log* default_instance_;
};
// ===================================================================


// ===================================================================

// Ref_chunk

// required int64 time_elapsed = 1;
inline bool Ref_chunk::has_time_elapsed() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Ref_chunk::set_has_time_elapsed() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Ref_chunk::clear_has_time_elapsed() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Ref_chunk::clear_time_elapsed() {
  time_elapsed_ = GOOGLE_LONGLONG(0);
  clear_has_time_elapsed();
}
inline ::google::protobuf::int64 Ref_chunk::time_elapsed() const {
  // @@protoc_insertion_point(field_get:Ref_chunk.time_elapsed)
  return time_elapsed_;
}
inline void Ref_chunk::set_time_elapsed(::google::protobuf::int64 value) {
  set_has_time_elapsed();
  time_elapsed_ = value;
  // @@protoc_insertion_point(field_set:Ref_chunk.time_elapsed)
}

// optional int64 id = 2;
inline bool Ref_chunk::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Ref_chunk::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Ref_chunk::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Ref_chunk::clear_id() {
  id_ = GOOGLE_LONGLONG(0);
  clear_has_id();
}
inline ::google::protobuf::int64 Ref_chunk::id() const {
  // @@protoc_insertion_point(field_get:Ref_chunk.id)
  return id_;
}
inline void Ref_chunk::set_id(::google::protobuf::int64 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:Ref_chunk.id)
}

// required .SSL_Referee packet = 3;
inline bool Ref_chunk::has_packet() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Ref_chunk::set_has_packet() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Ref_chunk::clear_has_packet() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Ref_chunk::clear_packet() {
  if (packet_ != NULL) packet_->::SSL_Referee::Clear();
  clear_has_packet();
}
inline const ::SSL_Referee& Ref_chunk::packet() const {
  // @@protoc_insertion_point(field_get:Ref_chunk.packet)
  return packet_ != NULL ? *packet_ : *default_instance_->packet_;
}
inline ::SSL_Referee* Ref_chunk::mutable_packet() {
  set_has_packet();
  if (packet_ == NULL) packet_ = new ::SSL_Referee;
  // @@protoc_insertion_point(field_mutable:Ref_chunk.packet)
  return packet_;
}
inline ::SSL_Referee* Ref_chunk::release_packet() {
  clear_has_packet();
  ::SSL_Referee* temp = packet_;
  packet_ = NULL;
  return temp;
}
inline void Ref_chunk::set_allocated_packet(::SSL_Referee* packet) {
  delete packet_;
  packet_ = packet;
  if (packet) {
    set_has_packet();
  } else {
    clear_has_packet();
  }
  // @@protoc_insertion_point(field_set_allocated:Ref_chunk.packet)
}

// -------------------------------------------------------------------

// Ref_log

// optional int64 number = 1;
inline bool Ref_log::has_number() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Ref_log::set_has_number() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Ref_log::clear_has_number() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Ref_log::clear_number() {
  number_ = GOOGLE_LONGLONG(0);
  clear_has_number();
}
inline ::google::protobuf::int64 Ref_log::number() const {
  // @@protoc_insertion_point(field_get:Ref_log.number)
  return number_;
}
inline void Ref_log::set_number(::google::protobuf::int64 value) {
  set_has_number();
  number_ = value;
  // @@protoc_insertion_point(field_set:Ref_log.number)
}

// repeated .Ref_chunk chunks = 2;
inline int Ref_log::chunks_size() const {
  return chunks_.size();
}
inline void Ref_log::clear_chunks() {
  chunks_.Clear();
}
inline const ::Ref_chunk& Ref_log::chunks(int index) const {
  // @@protoc_insertion_point(field_get:Ref_log.chunks)
  return chunks_.Get(index);
}
inline ::Ref_chunk* Ref_log::mutable_chunks(int index) {
  // @@protoc_insertion_point(field_mutable:Ref_log.chunks)
  return chunks_.Mutable(index);
}
inline ::Ref_chunk* Ref_log::add_chunks() {
  // @@protoc_insertion_point(field_add:Ref_log.chunks)
  return chunks_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Ref_chunk >&
Ref_log::chunks() const {
  // @@protoc_insertion_point(field_list:Ref_log.chunks)
  return chunks_;
}
inline ::google::protobuf::RepeatedPtrField< ::Ref_chunk >*
Ref_log::mutable_chunks() {
  // @@protoc_insertion_point(field_mutable_list:Ref_log.chunks)
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

#endif  // PROTOBUF_ref_5flog_2eproto__INCLUDED
