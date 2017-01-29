// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: position_message.proto

#ifndef PROTOBUF_position_5fmessage_2eproto__INCLUDED
#define PROTOBUF_position_5fmessage_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_position_5fmessage_2eproto();
void protobuf_AssignDesc_position_5fmessage_2eproto();
void protobuf_ShutdownFile_position_5fmessage_2eproto();

class position_message;

// ===================================================================

class position_message : public ::google::protobuf::Message {
 public:
  position_message();
  virtual ~position_message();

  position_message(const position_message& from);

  inline position_message& operator=(const position_message& from) {
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
  static const position_message& default_instance();

  void Swap(position_message* other);

  // implements Message ----------------------------------------------

  position_message* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const position_message& from);
  void MergeFrom(const position_message& from);
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

  // required float x = 1;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 1;
  inline float x() const;
  inline void set_x(float value);

  // required float y = 2;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 2;
  inline float y() const;
  inline void set_y(float value);

  // required float dir = 3;
  inline bool has_dir() const;
  inline void clear_dir();
  static const int kDirFieldNumber = 3;
  inline float dir() const;
  inline void set_dir(float value);

  // @@protoc_insertion_point(class_scope:position_message)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_dir();
  inline void clear_has_dir();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  float x_;
  float y_;
  float dir_;
  friend void  protobuf_AddDesc_position_5fmessage_2eproto();
  friend void protobuf_AssignDesc_position_5fmessage_2eproto();
  friend void protobuf_ShutdownFile_position_5fmessage_2eproto();

  void InitAsDefaultInstance();
  static position_message* default_instance_;
};
// ===================================================================


// ===================================================================

// position_message

// required float x = 1;
inline bool position_message::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void position_message::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void position_message::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void position_message::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float position_message::x() const {
  // @@protoc_insertion_point(field_get:position_message.x)
  return x_;
}
inline void position_message::set_x(float value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:position_message.x)
}

// required float y = 2;
inline bool position_message::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void position_message::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void position_message::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void position_message::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float position_message::y() const {
  // @@protoc_insertion_point(field_get:position_message.y)
  return y_;
}
inline void position_message::set_y(float value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:position_message.y)
}

// required float dir = 3;
inline bool position_message::has_dir() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void position_message::set_has_dir() {
  _has_bits_[0] |= 0x00000004u;
}
inline void position_message::clear_has_dir() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void position_message::clear_dir() {
  dir_ = 0;
  clear_has_dir();
}
inline float position_message::dir() const {
  // @@protoc_insertion_point(field_get:position_message.dir)
  return dir_;
}
inline void position_message::set_dir(float value) {
  set_has_dir();
  dir_ = value;
  // @@protoc_insertion_point(field_set:position_message.dir)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_position_5fmessage_2eproto__INCLUDED
