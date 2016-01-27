// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: grSim_Commands.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "grSim_Commands.pb.h"

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

const ::google::protobuf::Descriptor* grSim_Robot_Command_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  grSim_Robot_Command_reflection_ = NULL;
const ::google::protobuf::Descriptor* grSim_Commands_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  grSim_Commands_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_grSim_5fCommands_2eproto() {
  protobuf_AddDesc_grSim_5fCommands_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "grSim_Commands.proto");
  GOOGLE_CHECK(file != NULL);
  grSim_Robot_Command_descriptor_ = file->message_type(0);
  static const int grSim_Robot_Command_offsets_[12] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, kickspeedx_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, kickspeedz_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, veltangent_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, velnormal_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, velangular_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, spinner_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, wheelsspeed_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, wheel1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, wheel2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, wheel3_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, wheel4_),
  };
  grSim_Robot_Command_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      grSim_Robot_Command_descriptor_,
      grSim_Robot_Command::default_instance_,
      grSim_Robot_Command_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Robot_Command, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(grSim_Robot_Command));
  grSim_Commands_descriptor_ = file->message_type(1);
  static const int grSim_Commands_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Commands, timestamp_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Commands, isteamyellow_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Commands, robot_commands_),
  };
  grSim_Commands_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      grSim_Commands_descriptor_,
      grSim_Commands::default_instance_,
      grSim_Commands_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Commands, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(grSim_Commands, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(grSim_Commands));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_grSim_5fCommands_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    grSim_Robot_Command_descriptor_, &grSim_Robot_Command::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    grSim_Commands_descriptor_, &grSim_Commands::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_grSim_5fCommands_2eproto() {
  delete grSim_Robot_Command::default_instance_;
  delete grSim_Robot_Command_reflection_;
  delete grSim_Commands::default_instance_;
  delete grSim_Commands_reflection_;
}

void protobuf_AddDesc_grSim_5fCommands_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024grSim_Commands.proto\"\352\001\n\023grSim_Robot_C"
    "ommand\022\n\n\002id\030\001 \002(\r\022\022\n\nkickspeedx\030\002 \002(\002\022\022"
    "\n\nkickspeedz\030\003 \002(\002\022\022\n\nveltangent\030\004 \002(\002\022\021"
    "\n\tvelnormal\030\005 \002(\002\022\022\n\nvelangular\030\006 \002(\002\022\017\n"
    "\007spinner\030\007 \002(\010\022\023\n\013wheelsspeed\030\010 \002(\010\022\016\n\006w"
    "heel1\030\t \001(\002\022\016\n\006wheel2\030\n \001(\002\022\016\n\006wheel3\030\013 "
    "\001(\002\022\016\n\006wheel4\030\014 \001(\002\"g\n\016grSim_Commands\022\021\n"
    "\ttimestamp\030\001 \002(\001\022\024\n\014isteamyellow\030\002 \002(\010\022,"
    "\n\016robot_commands\030\003 \003(\0132\024.grSim_Robot_Com"
    "mand", 364);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "grSim_Commands.proto", &protobuf_RegisterTypes);
  grSim_Robot_Command::default_instance_ = new grSim_Robot_Command();
  grSim_Commands::default_instance_ = new grSim_Commands();
  grSim_Robot_Command::default_instance_->InitAsDefaultInstance();
  grSim_Commands::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_grSim_5fCommands_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_grSim_5fCommands_2eproto {
  StaticDescriptorInitializer_grSim_5fCommands_2eproto() {
    protobuf_AddDesc_grSim_5fCommands_2eproto();
  }
} static_descriptor_initializer_grSim_5fCommands_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int grSim_Robot_Command::kIdFieldNumber;
const int grSim_Robot_Command::kKickspeedxFieldNumber;
const int grSim_Robot_Command::kKickspeedzFieldNumber;
const int grSim_Robot_Command::kVeltangentFieldNumber;
const int grSim_Robot_Command::kVelnormalFieldNumber;
const int grSim_Robot_Command::kVelangularFieldNumber;
const int grSim_Robot_Command::kSpinnerFieldNumber;
const int grSim_Robot_Command::kWheelsspeedFieldNumber;
const int grSim_Robot_Command::kWheel1FieldNumber;
const int grSim_Robot_Command::kWheel2FieldNumber;
const int grSim_Robot_Command::kWheel3FieldNumber;
const int grSim_Robot_Command::kWheel4FieldNumber;
#endif  // !_MSC_VER

grSim_Robot_Command::grSim_Robot_Command()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void grSim_Robot_Command::InitAsDefaultInstance() {
}

grSim_Robot_Command::grSim_Robot_Command(const grSim_Robot_Command& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void grSim_Robot_Command::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  kickspeedx_ = 0;
  kickspeedz_ = 0;
  veltangent_ = 0;
  velnormal_ = 0;
  velangular_ = 0;
  spinner_ = false;
  wheelsspeed_ = false;
  wheel1_ = 0;
  wheel2_ = 0;
  wheel3_ = 0;
  wheel4_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

grSim_Robot_Command::~grSim_Robot_Command() {
  SharedDtor();
}

void grSim_Robot_Command::SharedDtor() {
  if (this != default_instance_) {
  }
}

void grSim_Robot_Command::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* grSim_Robot_Command::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return grSim_Robot_Command_descriptor_;
}

const grSim_Robot_Command& grSim_Robot_Command::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_grSim_5fCommands_2eproto();
  return *default_instance_;
}

grSim_Robot_Command* grSim_Robot_Command::default_instance_ = NULL;

grSim_Robot_Command* grSim_Robot_Command::New() const {
  return new grSim_Robot_Command;
}

void grSim_Robot_Command::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    id_ = 0u;
    kickspeedx_ = 0;
    kickspeedz_ = 0;
    veltangent_ = 0;
    velnormal_ = 0;
    velangular_ = 0;
    spinner_ = false;
    wheelsspeed_ = false;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    wheel1_ = 0;
    wheel2_ = 0;
    wheel3_ = 0;
    wheel4_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool grSim_Robot_Command::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_kickspeedx;
        break;
      }

      // required float kickspeedx = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_kickspeedx:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &kickspeedx_)));
          set_has_kickspeedx();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(29)) goto parse_kickspeedz;
        break;
      }

      // required float kickspeedz = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_kickspeedz:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &kickspeedz_)));
          set_has_kickspeedz();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(37)) goto parse_veltangent;
        break;
      }

      // required float veltangent = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_veltangent:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &veltangent_)));
          set_has_veltangent();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(45)) goto parse_velnormal;
        break;
      }

      // required float velnormal = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_velnormal:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &velnormal_)));
          set_has_velnormal();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(53)) goto parse_velangular;
        break;
      }

      // required float velangular = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_velangular:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &velangular_)));
          set_has_velangular();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_spinner;
        break;
      }

      // required bool spinner = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_spinner:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &spinner_)));
          set_has_spinner();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_wheelsspeed;
        break;
      }

      // required bool wheelsspeed = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_wheelsspeed:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &wheelsspeed_)));
          set_has_wheelsspeed();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(77)) goto parse_wheel1;
        break;
      }

      // optional float wheel1 = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_wheel1:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &wheel1_)));
          set_has_wheel1();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(85)) goto parse_wheel2;
        break;
      }

      // optional float wheel2 = 10;
      case 10: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_wheel2:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &wheel2_)));
          set_has_wheel2();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(93)) goto parse_wheel3;
        break;
      }

      // optional float wheel3 = 11;
      case 11: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_wheel3:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &wheel3_)));
          set_has_wheel3();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(101)) goto parse_wheel4;
        break;
      }

      // optional float wheel4 = 12;
      case 12: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_wheel4:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &wheel4_)));
          set_has_wheel4();
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

void grSim_Robot_Command::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // required float kickspeedx = 2;
  if (has_kickspeedx()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->kickspeedx(), output);
  }

  // required float kickspeedz = 3;
  if (has_kickspeedz()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->kickspeedz(), output);
  }

  // required float veltangent = 4;
  if (has_veltangent()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->veltangent(), output);
  }

  // required float velnormal = 5;
  if (has_velnormal()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->velnormal(), output);
  }

  // required float velangular = 6;
  if (has_velangular()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(6, this->velangular(), output);
  }

  // required bool spinner = 7;
  if (has_spinner()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(7, this->spinner(), output);
  }

  // required bool wheelsspeed = 8;
  if (has_wheelsspeed()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->wheelsspeed(), output);
  }

  // optional float wheel1 = 9;
  if (has_wheel1()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(9, this->wheel1(), output);
  }

  // optional float wheel2 = 10;
  if (has_wheel2()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(10, this->wheel2(), output);
  }

  // optional float wheel3 = 11;
  if (has_wheel3()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(11, this->wheel3(), output);
  }

  // optional float wheel4 = 12;
  if (has_wheel4()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(12, this->wheel4(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* grSim_Robot_Command::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // required float kickspeedx = 2;
  if (has_kickspeedx()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->kickspeedx(), target);
  }

  // required float kickspeedz = 3;
  if (has_kickspeedz()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(3, this->kickspeedz(), target);
  }

  // required float veltangent = 4;
  if (has_veltangent()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(4, this->veltangent(), target);
  }

  // required float velnormal = 5;
  if (has_velnormal()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->velnormal(), target);
  }

  // required float velangular = 6;
  if (has_velangular()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(6, this->velangular(), target);
  }

  // required bool spinner = 7;
  if (has_spinner()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(7, this->spinner(), target);
  }

  // required bool wheelsspeed = 8;
  if (has_wheelsspeed()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->wheelsspeed(), target);
  }

  // optional float wheel1 = 9;
  if (has_wheel1()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(9, this->wheel1(), target);
  }

  // optional float wheel2 = 10;
  if (has_wheel2()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(10, this->wheel2(), target);
  }

  // optional float wheel3 = 11;
  if (has_wheel3()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(11, this->wheel3(), target);
  }

  // optional float wheel4 = 12;
  if (has_wheel4()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(12, this->wheel4(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int grSim_Robot_Command::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // required float kickspeedx = 2;
    if (has_kickspeedx()) {
      total_size += 1 + 4;
    }

    // required float kickspeedz = 3;
    if (has_kickspeedz()) {
      total_size += 1 + 4;
    }

    // required float veltangent = 4;
    if (has_veltangent()) {
      total_size += 1 + 4;
    }

    // required float velnormal = 5;
    if (has_velnormal()) {
      total_size += 1 + 4;
    }

    // required float velangular = 6;
    if (has_velangular()) {
      total_size += 1 + 4;
    }

    // required bool spinner = 7;
    if (has_spinner()) {
      total_size += 1 + 1;
    }

    // required bool wheelsspeed = 8;
    if (has_wheelsspeed()) {
      total_size += 1 + 1;
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional float wheel1 = 9;
    if (has_wheel1()) {
      total_size += 1 + 4;
    }

    // optional float wheel2 = 10;
    if (has_wheel2()) {
      total_size += 1 + 4;
    }

    // optional float wheel3 = 11;
    if (has_wheel3()) {
      total_size += 1 + 4;
    }

    // optional float wheel4 = 12;
    if (has_wheel4()) {
      total_size += 1 + 4;
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

void grSim_Robot_Command::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const grSim_Robot_Command* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const grSim_Robot_Command*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void grSim_Robot_Command::MergeFrom(const grSim_Robot_Command& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_kickspeedx()) {
      set_kickspeedx(from.kickspeedx());
    }
    if (from.has_kickspeedz()) {
      set_kickspeedz(from.kickspeedz());
    }
    if (from.has_veltangent()) {
      set_veltangent(from.veltangent());
    }
    if (from.has_velnormal()) {
      set_velnormal(from.velnormal());
    }
    if (from.has_velangular()) {
      set_velangular(from.velangular());
    }
    if (from.has_spinner()) {
      set_spinner(from.spinner());
    }
    if (from.has_wheelsspeed()) {
      set_wheelsspeed(from.wheelsspeed());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_wheel1()) {
      set_wheel1(from.wheel1());
    }
    if (from.has_wheel2()) {
      set_wheel2(from.wheel2());
    }
    if (from.has_wheel3()) {
      set_wheel3(from.wheel3());
    }
    if (from.has_wheel4()) {
      set_wheel4(from.wheel4());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void grSim_Robot_Command::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void grSim_Robot_Command::CopyFrom(const grSim_Robot_Command& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool grSim_Robot_Command::IsInitialized() const {
  if ((_has_bits_[0] & 0x000000ff) != 0x000000ff) return false;

  return true;
}

void grSim_Robot_Command::Swap(grSim_Robot_Command* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(kickspeedx_, other->kickspeedx_);
    std::swap(kickspeedz_, other->kickspeedz_);
    std::swap(veltangent_, other->veltangent_);
    std::swap(velnormal_, other->velnormal_);
    std::swap(velangular_, other->velangular_);
    std::swap(spinner_, other->spinner_);
    std::swap(wheelsspeed_, other->wheelsspeed_);
    std::swap(wheel1_, other->wheel1_);
    std::swap(wheel2_, other->wheel2_);
    std::swap(wheel3_, other->wheel3_);
    std::swap(wheel4_, other->wheel4_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata grSim_Robot_Command::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = grSim_Robot_Command_descriptor_;
  metadata.reflection = grSim_Robot_Command_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int grSim_Commands::kTimestampFieldNumber;
const int grSim_Commands::kIsteamyellowFieldNumber;
const int grSim_Commands::kRobotCommandsFieldNumber;
#endif  // !_MSC_VER

grSim_Commands::grSim_Commands()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void grSim_Commands::InitAsDefaultInstance() {
}

grSim_Commands::grSim_Commands(const grSim_Commands& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void grSim_Commands::SharedCtor() {
  _cached_size_ = 0;
  timestamp_ = 0;
  isteamyellow_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

grSim_Commands::~grSim_Commands() {
  SharedDtor();
}

void grSim_Commands::SharedDtor() {
  if (this != default_instance_) {
  }
}

void grSim_Commands::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* grSim_Commands::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return grSim_Commands_descriptor_;
}

const grSim_Commands& grSim_Commands::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_grSim_5fCommands_2eproto();
  return *default_instance_;
}

grSim_Commands* grSim_Commands::default_instance_ = NULL;

grSim_Commands* grSim_Commands::New() const {
  return new grSim_Commands;
}

void grSim_Commands::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    timestamp_ = 0;
    isteamyellow_ = false;
  }
  robot_commands_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool grSim_Commands::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required double timestamp = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &timestamp_)));
          set_has_timestamp();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_isteamyellow;
        break;
      }

      // required bool isteamyellow = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_isteamyellow:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isteamyellow_)));
          set_has_isteamyellow();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_robot_commands;
        break;
      }

      // repeated .grSim_Robot_Command robot_commands = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_robot_commands:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_robot_commands()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_robot_commands;
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

void grSim_Commands::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required double timestamp = 1;
  if (has_timestamp()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->timestamp(), output);
  }

  // required bool isteamyellow = 2;
  if (has_isteamyellow()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->isteamyellow(), output);
  }

  // repeated .grSim_Robot_Command robot_commands = 3;
  for (int i = 0; i < this->robot_commands_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->robot_commands(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* grSim_Commands::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required double timestamp = 1;
  if (has_timestamp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->timestamp(), target);
  }

  // required bool isteamyellow = 2;
  if (has_isteamyellow()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->isteamyellow(), target);
  }

  // repeated .grSim_Robot_Command robot_commands = 3;
  for (int i = 0; i < this->robot_commands_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->robot_commands(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int grSim_Commands::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required double timestamp = 1;
    if (has_timestamp()) {
      total_size += 1 + 8;
    }

    // required bool isteamyellow = 2;
    if (has_isteamyellow()) {
      total_size += 1 + 1;
    }

  }
  // repeated .grSim_Robot_Command robot_commands = 3;
  total_size += 1 * this->robot_commands_size();
  for (int i = 0; i < this->robot_commands_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->robot_commands(i));
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

void grSim_Commands::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const grSim_Commands* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const grSim_Commands*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void grSim_Commands::MergeFrom(const grSim_Commands& from) {
  GOOGLE_CHECK_NE(&from, this);
  robot_commands_.MergeFrom(from.robot_commands_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_timestamp()) {
      set_timestamp(from.timestamp());
    }
    if (from.has_isteamyellow()) {
      set_isteamyellow(from.isteamyellow());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void grSim_Commands::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void grSim_Commands::CopyFrom(const grSim_Commands& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool grSim_Commands::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  for (int i = 0; i < robot_commands_size(); i++) {
    if (!this->robot_commands(i).IsInitialized()) return false;
  }
  return true;
}

void grSim_Commands::Swap(grSim_Commands* other) {
  if (other != this) {
    std::swap(timestamp_, other->timestamp_);
    std::swap(isteamyellow_, other->isteamyellow_);
    robot_commands_.Swap(&other->robot_commands_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata grSim_Commands::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = grSim_Commands_descriptor_;
  metadata.reflection = grSim_Commands_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)