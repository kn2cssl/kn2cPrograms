// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Ball_message.proto

#ifndef PROTOBUF_Ball_5fmessage_2eproto__INCLUDED
#define PROTOBUF_Ball_5fmessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

<<<<<<< HEAD
#if GOOGLE_PROTOBUF_VERSION < 3001000
=======
#if GOOGLE_PROTOBUF_VERSION < 2006000
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
<<<<<<< HEAD
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
=======
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "position_message.pb.h"
// @@protoc_insertion_point(includes)
class Ball_message;
class Ball_messageDefaultTypeInternal;
extern Ball_messageDefaultTypeInternal _Ball_message_default_instance_;
class position_message;
class position_messageDefaultTypeInternal;
extern position_messageDefaultTypeInternal _position_message_default_instance_;

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_Ball_5fmessage_2eproto();
void protobuf_InitDefaults_Ball_5fmessage_2eproto();

// ===================================================================

class Ball_message : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Ball_message) */ {
 public:
  Ball_message();
  virtual ~Ball_message();

  Ball_message(const Ball_message& from);

  inline Ball_message& operator=(const Ball_message& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Ball_message& default_instance();

  static inline const Ball_message* internal_default_instance() {
    return reinterpret_cast<const Ball_message*>(
               &_Ball_message_default_instance_);
  }

  void Swap(Ball_message* other);

  // implements Message ----------------------------------------------

  inline Ball_message* New() const PROTOBUF_FINAL { return New(NULL); }

  Ball_message* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Ball_message& from);
  void MergeFrom(const Ball_message& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Ball_message* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:
<<<<<<< HEAD

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;
=======
  ::google::protobuf::Metadata GetMetadata() const;
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required bool isValid = 1;
  bool has_isvalid() const;
  void clear_isvalid();
  static const int kIsValidFieldNumber = 1;
  bool isvalid() const;
  void set_isvalid(bool value);

  // required .position_message position = 2;
  bool has_position() const;
  void clear_position();
  static const int kPositionFieldNumber = 2;
  const ::position_message& position() const;
  ::position_message* mutable_position();
  ::position_message* release_position();
  void set_allocated_position(::position_message* position);

  // required .position_message velocity = 3;
  bool has_velocity() const;
  void clear_velocity();
  static const int kVelocityFieldNumber = 3;
  const ::position_message& velocity() const;
  ::position_message* mutable_velocity();
  ::position_message* release_velocity();
  void set_allocated_velocity(::position_message* velocity);

  // @@protoc_insertion_point(class_scope:Ball_message)
 private:
<<<<<<< HEAD
  void set_has_isvalid();
  void clear_has_isvalid();
  void set_has_position();
  void clear_has_position();
  void set_has_velocity();
  void clear_has_velocity();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
=======
  inline void set_has_isvalid();
  inline void clear_has_isvalid();
  inline void set_has_position();
  inline void clear_has_position();
  inline void set_has_velocity();
  inline void clear_has_velocity();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  mutable int _cached_size_;
  ::position_message* position_;
  ::position_message* velocity_;
  bool isvalid_;
<<<<<<< HEAD
  friend void  protobuf_InitDefaults_Ball_5fmessage_2eproto_impl();
  friend void  protobuf_AddDesc_Ball_5fmessage_2eproto_impl();
  friend const ::google::protobuf::uint32* protobuf_Offsets_Ball_5fmessage_2eproto();
=======
  friend void  protobuf_AddDesc_Ball_5fmessage_2eproto();
  friend void protobuf_AssignDesc_Ball_5fmessage_2eproto();
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  friend void protobuf_ShutdownFile_Ball_5fmessage_2eproto();

};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Ball_message

// required bool isValid = 1;
inline bool Ball_message::has_isvalid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Ball_message::set_has_isvalid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Ball_message::clear_has_isvalid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Ball_message::clear_isvalid() {
  isvalid_ = false;
  clear_has_isvalid();
}
inline bool Ball_message::isvalid() const {
  // @@protoc_insertion_point(field_get:Ball_message.isValid)
  return isvalid_;
}
inline void Ball_message::set_isvalid(bool value) {
  set_has_isvalid();
  isvalid_ = value;
  // @@protoc_insertion_point(field_set:Ball_message.isValid)
}

// required .position_message position = 2;
inline bool Ball_message::has_position() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Ball_message::set_has_position() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Ball_message::clear_has_position() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Ball_message::clear_position() {
  if (position_ != NULL) position_->::position_message::Clear();
  clear_has_position();
}
inline const ::position_message& Ball_message::position() const {
  // @@protoc_insertion_point(field_get:Ball_message.position)
<<<<<<< HEAD
  return position_ != NULL ? *position_
                         : *::position_message::internal_default_instance();
}
inline ::position_message* Ball_message::mutable_position() {
  set_has_position();
  if (position_ == NULL) {
    position_ = new ::position_message;
  }
=======
  return position_ != NULL ? *position_ : *default_instance_->position_;
}
inline ::position_message* Ball_message::mutable_position() {
  set_has_position();
  if (position_ == NULL) position_ = new ::position_message;
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  // @@protoc_insertion_point(field_mutable:Ball_message.position)
  return position_;
}
inline ::position_message* Ball_message::release_position() {
  // @@protoc_insertion_point(field_release:Ball_message.position)
  clear_has_position();
  ::position_message* temp = position_;
  position_ = NULL;
  return temp;
}
inline void Ball_message::set_allocated_position(::position_message* position) {
  delete position_;
  position_ = position;
  if (position) {
    set_has_position();
  } else {
    clear_has_position();
  }
  // @@protoc_insertion_point(field_set_allocated:Ball_message.position)
}

// required .position_message velocity = 3;
inline bool Ball_message::has_velocity() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Ball_message::set_has_velocity() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Ball_message::clear_has_velocity() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Ball_message::clear_velocity() {
  if (velocity_ != NULL) velocity_->::position_message::Clear();
  clear_has_velocity();
}
inline const ::position_message& Ball_message::velocity() const {
  // @@protoc_insertion_point(field_get:Ball_message.velocity)
<<<<<<< HEAD
  return velocity_ != NULL ? *velocity_
                         : *::position_message::internal_default_instance();
}
inline ::position_message* Ball_message::mutable_velocity() {
  set_has_velocity();
  if (velocity_ == NULL) {
    velocity_ = new ::position_message;
  }
=======
  return velocity_ != NULL ? *velocity_ : *default_instance_->velocity_;
}
inline ::position_message* Ball_message::mutable_velocity() {
  set_has_velocity();
  if (velocity_ == NULL) velocity_ = new ::position_message;
>>>>>>> d766c95da96dc8ee70e0992aefe4e0a62d783e28
  // @@protoc_insertion_point(field_mutable:Ball_message.velocity)
  return velocity_;
}
inline ::position_message* Ball_message::release_velocity() {
  // @@protoc_insertion_point(field_release:Ball_message.velocity)
  clear_has_velocity();
  ::position_message* temp = velocity_;
  velocity_ = NULL;
  return temp;
}
inline void Ball_message::set_allocated_velocity(::position_message* velocity) {
  delete velocity_;
  velocity_ = velocity;
  if (velocity) {
    set_has_velocity();
  } else {
    clear_has_velocity();
  }
  // @@protoc_insertion_point(field_set_allocated:Ball_message.velocity)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Ball_5fmessage_2eproto__INCLUDED
