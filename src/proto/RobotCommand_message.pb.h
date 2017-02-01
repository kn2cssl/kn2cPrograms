// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RobotCommand_message.proto

#ifndef PROTOBUF_RobotCommand_5fmessage_2eproto__INCLUDED
#define PROTOBUF_RobotCommand_5fmessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
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
class RobotCommand_message;
class RobotCommand_messageDefaultTypeInternal;
extern RobotCommand_messageDefaultTypeInternal _RobotCommand_message_default_instance_;
class position_message;
class position_messageDefaultTypeInternal;
extern position_messageDefaultTypeInternal _position_message_default_instance_;

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_RobotCommand_5fmessage_2eproto();
void protobuf_InitDefaults_RobotCommand_5fmessage_2eproto();

// ===================================================================

class RobotCommand_message : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:RobotCommand_message) */ {
 public:
  RobotCommand_message();
  virtual ~RobotCommand_message();

  RobotCommand_message(const RobotCommand_message& from);

  inline RobotCommand_message& operator=(const RobotCommand_message& from) {
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
  static const RobotCommand_message& default_instance();

  static inline const RobotCommand_message* internal_default_instance() {
    return reinterpret_cast<const RobotCommand_message*>(
               &_RobotCommand_message_default_instance_);
  }

  void Swap(RobotCommand_message* other);

  // implements Message ----------------------------------------------

  inline RobotCommand_message* New() const PROTOBUF_FINAL { return New(NULL); }

  RobotCommand_message* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const RobotCommand_message& from);
  void MergeFrom(const RobotCommand_message& from);
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
  void InternalSwap(RobotCommand_message* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .position_message fin_pos = 1;
  bool has_fin_pos() const;
  void clear_fin_pos();
  static const int kFinPosFieldNumber = 1;
  const ::position_message& fin_pos() const;
  ::position_message* mutable_fin_pos();
  ::position_message* release_fin_pos();
  void set_allocated_fin_pos(::position_message* fin_pos);

  // required .position_message fin_vel = 2;
  bool has_fin_vel() const;
  void clear_fin_vel();
  static const int kFinVelFieldNumber = 2;
  const ::position_message& fin_vel() const;
  ::position_message* mutable_fin_vel();
  ::position_message* release_fin_vel();
  void set_allocated_fin_vel(::position_message* fin_vel);

  // required float maxSpeed = 3;
  bool has_maxspeed() const;
  void clear_maxspeed();
  static const int kMaxSpeedFieldNumber = 3;
  float maxspeed() const;
  void set_maxspeed(float value);

  // required float kickspeedx = 4;
  bool has_kickspeedx() const;
  void clear_kickspeedx();
  static const int kKickspeedxFieldNumber = 4;
  float kickspeedx() const;
  void set_kickspeedx(float value);

  // required float kickspeedz = 5;
  bool has_kickspeedz() const;
  void clear_kickspeedz();
  static const int kKickspeedzFieldNumber = 5;
  float kickspeedz() const;
  void set_kickspeedz(float value);

  // required bool useNav = 6;
  bool has_usenav() const;
  void clear_usenav();
  static const int kUseNavFieldNumber = 6;
  bool usenav() const;
  void set_usenav(bool value);

  // required bool isBallObs = 7;
  bool has_isballobs() const;
  void clear_isballobs();
  static const int kIsBallObsFieldNumber = 7;
  bool isballobs() const;
  void set_isballobs(bool value);

  // required bool isKickObs = 8;
  bool has_iskickobs() const;
  void clear_iskickobs();
  static const int kIsKickObsFieldNumber = 8;
  bool iskickobs() const;
  void set_iskickobs(bool value);

  // @@protoc_insertion_point(class_scope:RobotCommand_message)
 private:
  void set_has_fin_pos();
  void clear_has_fin_pos();
  void set_has_fin_vel();
  void clear_has_fin_vel();
  void set_has_maxspeed();
  void clear_has_maxspeed();
  void set_has_kickspeedx();
  void clear_has_kickspeedx();
  void set_has_kickspeedz();
  void clear_has_kickspeedz();
  void set_has_usenav();
  void clear_has_usenav();
  void set_has_isballobs();
  void clear_has_isballobs();
  void set_has_iskickobs();
  void clear_has_iskickobs();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::position_message* fin_pos_;
  ::position_message* fin_vel_;
  float maxspeed_;
  float kickspeedx_;
  float kickspeedz_;
  bool usenav_;
  bool isballobs_;
  bool iskickobs_;
  friend void  protobuf_InitDefaults_RobotCommand_5fmessage_2eproto_impl();
  friend void  protobuf_AddDesc_RobotCommand_5fmessage_2eproto_impl();
  friend const ::google::protobuf::uint32* protobuf_Offsets_RobotCommand_5fmessage_2eproto();
  friend void protobuf_ShutdownFile_RobotCommand_5fmessage_2eproto();

};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// RobotCommand_message

// required .position_message fin_pos = 1;
inline bool RobotCommand_message::has_fin_pos() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RobotCommand_message::set_has_fin_pos() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RobotCommand_message::clear_has_fin_pos() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RobotCommand_message::clear_fin_pos() {
  if (fin_pos_ != NULL) fin_pos_->::position_message::Clear();
  clear_has_fin_pos();
}
inline const ::position_message& RobotCommand_message::fin_pos() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.fin_pos)
  return fin_pos_ != NULL ? *fin_pos_
                         : *::position_message::internal_default_instance();
}
inline ::position_message* RobotCommand_message::mutable_fin_pos() {
  set_has_fin_pos();
  if (fin_pos_ == NULL) {
    fin_pos_ = new ::position_message;
  }
  // @@protoc_insertion_point(field_mutable:RobotCommand_message.fin_pos)
  return fin_pos_;
}
inline ::position_message* RobotCommand_message::release_fin_pos() {
  // @@protoc_insertion_point(field_release:RobotCommand_message.fin_pos)
  clear_has_fin_pos();
  ::position_message* temp = fin_pos_;
  fin_pos_ = NULL;
  return temp;
}
inline void RobotCommand_message::set_allocated_fin_pos(::position_message* fin_pos) {
  delete fin_pos_;
  fin_pos_ = fin_pos;
  if (fin_pos) {
    set_has_fin_pos();
  } else {
    clear_has_fin_pos();
  }
  // @@protoc_insertion_point(field_set_allocated:RobotCommand_message.fin_pos)
}

// required .position_message fin_vel = 2;
inline bool RobotCommand_message::has_fin_vel() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RobotCommand_message::set_has_fin_vel() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RobotCommand_message::clear_has_fin_vel() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RobotCommand_message::clear_fin_vel() {
  if (fin_vel_ != NULL) fin_vel_->::position_message::Clear();
  clear_has_fin_vel();
}
inline const ::position_message& RobotCommand_message::fin_vel() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.fin_vel)
  return fin_vel_ != NULL ? *fin_vel_
                         : *::position_message::internal_default_instance();
}
inline ::position_message* RobotCommand_message::mutable_fin_vel() {
  set_has_fin_vel();
  if (fin_vel_ == NULL) {
    fin_vel_ = new ::position_message;
  }
  // @@protoc_insertion_point(field_mutable:RobotCommand_message.fin_vel)
  return fin_vel_;
}
inline ::position_message* RobotCommand_message::release_fin_vel() {
  // @@protoc_insertion_point(field_release:RobotCommand_message.fin_vel)
  clear_has_fin_vel();
  ::position_message* temp = fin_vel_;
  fin_vel_ = NULL;
  return temp;
}
inline void RobotCommand_message::set_allocated_fin_vel(::position_message* fin_vel) {
  delete fin_vel_;
  fin_vel_ = fin_vel;
  if (fin_vel) {
    set_has_fin_vel();
  } else {
    clear_has_fin_vel();
  }
  // @@protoc_insertion_point(field_set_allocated:RobotCommand_message.fin_vel)
}

// required float maxSpeed = 3;
inline bool RobotCommand_message::has_maxspeed() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RobotCommand_message::set_has_maxspeed() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RobotCommand_message::clear_has_maxspeed() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RobotCommand_message::clear_maxspeed() {
  maxspeed_ = 0;
  clear_has_maxspeed();
}
inline float RobotCommand_message::maxspeed() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.maxSpeed)
  return maxspeed_;
}
inline void RobotCommand_message::set_maxspeed(float value) {
  set_has_maxspeed();
  maxspeed_ = value;
  // @@protoc_insertion_point(field_set:RobotCommand_message.maxSpeed)
}

// required float kickspeedx = 4;
inline bool RobotCommand_message::has_kickspeedx() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void RobotCommand_message::set_has_kickspeedx() {
  _has_bits_[0] |= 0x00000008u;
}
inline void RobotCommand_message::clear_has_kickspeedx() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void RobotCommand_message::clear_kickspeedx() {
  kickspeedx_ = 0;
  clear_has_kickspeedx();
}
inline float RobotCommand_message::kickspeedx() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.kickspeedx)
  return kickspeedx_;
}
inline void RobotCommand_message::set_kickspeedx(float value) {
  set_has_kickspeedx();
  kickspeedx_ = value;
  // @@protoc_insertion_point(field_set:RobotCommand_message.kickspeedx)
}

// required float kickspeedz = 5;
inline bool RobotCommand_message::has_kickspeedz() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void RobotCommand_message::set_has_kickspeedz() {
  _has_bits_[0] |= 0x00000010u;
}
inline void RobotCommand_message::clear_has_kickspeedz() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void RobotCommand_message::clear_kickspeedz() {
  kickspeedz_ = 0;
  clear_has_kickspeedz();
}
inline float RobotCommand_message::kickspeedz() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.kickspeedz)
  return kickspeedz_;
}
inline void RobotCommand_message::set_kickspeedz(float value) {
  set_has_kickspeedz();
  kickspeedz_ = value;
  // @@protoc_insertion_point(field_set:RobotCommand_message.kickspeedz)
}

// required bool useNav = 6;
inline bool RobotCommand_message::has_usenav() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void RobotCommand_message::set_has_usenav() {
  _has_bits_[0] |= 0x00000020u;
}
inline void RobotCommand_message::clear_has_usenav() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void RobotCommand_message::clear_usenav() {
  usenav_ = false;
  clear_has_usenav();
}
inline bool RobotCommand_message::usenav() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.useNav)
  return usenav_;
}
inline void RobotCommand_message::set_usenav(bool value) {
  set_has_usenav();
  usenav_ = value;
  // @@protoc_insertion_point(field_set:RobotCommand_message.useNav)
}

// required bool isBallObs = 7;
inline bool RobotCommand_message::has_isballobs() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void RobotCommand_message::set_has_isballobs() {
  _has_bits_[0] |= 0x00000040u;
}
inline void RobotCommand_message::clear_has_isballobs() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void RobotCommand_message::clear_isballobs() {
  isballobs_ = false;
  clear_has_isballobs();
}
inline bool RobotCommand_message::isballobs() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.isBallObs)
  return isballobs_;
}
inline void RobotCommand_message::set_isballobs(bool value) {
  set_has_isballobs();
  isballobs_ = value;
  // @@protoc_insertion_point(field_set:RobotCommand_message.isBallObs)
}

// required bool isKickObs = 8;
inline bool RobotCommand_message::has_iskickobs() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void RobotCommand_message::set_has_iskickobs() {
  _has_bits_[0] |= 0x00000080u;
}
inline void RobotCommand_message::clear_has_iskickobs() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void RobotCommand_message::clear_iskickobs() {
  iskickobs_ = false;
  clear_has_iskickobs();
}
inline bool RobotCommand_message::iskickobs() const {
  // @@protoc_insertion_point(field_get:RobotCommand_message.isKickObs)
  return iskickobs_;
}
inline void RobotCommand_message::set_iskickobs(bool value) {
  set_has_iskickobs();
  iskickobs_ = value;
  // @@protoc_insertion_point(field_set:RobotCommand_message.isKickObs)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_RobotCommand_5fmessage_2eproto__INCLUDED
