// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CharacterData.proto
#pragma warning (disable : 4800)
#pragma warning (disable : 4125)
#pragma warning (disable : 4647)
#pragma warning (disable : 4668)
#pragma warning (disable : 4582)
#pragma warning (disable : 4583)
#pragma warning (disable : 4946)
#pragma warning (disable : 4577)

#ifdef _MSC_VER
#include "Windows/AllowWindowsPlatformTypes.h"
#endif
#include "CharacterData.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR CharacterData::CharacterData(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.playername_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.weaponsavedata_)*/nullptr
  , /*decltype(_impl_.level_)*/0
  , /*decltype(_impl_.exp_)*/0
  , /*decltype(_impl_.gold_)*/0
  , /*decltype(_impl_.rifleammo_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct CharacterDataDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CharacterDataDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~CharacterDataDefaultTypeInternal() {}
  union {
    CharacterData _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CharacterDataDefaultTypeInternal _CharacterData_default_instance_;
PROTOBUF_CONSTEXPR WeaponSaveData::WeaponSaveData(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.weaponlevel_)*/0
  , /*decltype(_impl_.weaponenhancementlevel_)*/0
  , /*decltype(_impl_.weapontype_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct WeaponSaveDataDefaultTypeInternal {
  PROTOBUF_CONSTEXPR WeaponSaveDataDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~WeaponSaveDataDefaultTypeInternal() {}
  union {
    WeaponSaveData _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 WeaponSaveDataDefaultTypeInternal _WeaponSaveData_default_instance_;
static ::_pb::Metadata file_level_metadata_CharacterData_2eproto[2];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_CharacterData_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_CharacterData_2eproto = nullptr;

const uint32_t TableStruct_CharacterData_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::CharacterData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::CharacterData, _impl_.level_),
  PROTOBUF_FIELD_OFFSET(::CharacterData, _impl_.exp_),
  PROTOBUF_FIELD_OFFSET(::CharacterData, _impl_.playername_),
  PROTOBUF_FIELD_OFFSET(::CharacterData, _impl_.gold_),
  PROTOBUF_FIELD_OFFSET(::CharacterData, _impl_.weaponsavedata_),
  PROTOBUF_FIELD_OFFSET(::CharacterData, _impl_.rifleammo_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::WeaponSaveData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::WeaponSaveData, _impl_.weaponlevel_),
  PROTOBUF_FIELD_OFFSET(::WeaponSaveData, _impl_.weaponenhancementlevel_),
  PROTOBUF_FIELD_OFFSET(::WeaponSaveData, _impl_.weapontype_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::CharacterData)},
  { 12, -1, -1, sizeof(::WeaponSaveData)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_CharacterData_default_instance_._instance,
  &::_WeaponSaveData_default_instance_._instance,
};

const char descriptor_table_protodef_CharacterData_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\023CharacterData.proto\"\211\001\n\rCharacterData\022"
  "\r\n\005level\030\001 \001(\005\022\013\n\003exp\030\002 \001(\005\022\022\n\nplayerNam"
  "e\030\003 \001(\t\022\014\n\004gold\030\004 \001(\005\022\'\n\016weaponSaveData\030"
  "\005 \001(\0132\017.WeaponSaveData\022\021\n\trifleAmmo\030\006 \001("
  "\005\"\263\001\n\016WeaponSaveData\022\023\n\013weaponLevel\030\001 \001("
  "\005\022\036\n\026weaponEnhancementLevel\030\002 \001(\005\022.\n\nwea"
  "ponType\030\003 \001(\0162\032.WeaponSaveData.WeaponTyp"
  "e\"<\n\nWeaponType\022\r\n\tEWT_RIFLE\020\000\022\016\n\nEWT_PI"
  "STOL\020\001\022\017\n\013EWT_SHOTGUN\020\002b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_CharacterData_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_CharacterData_2eproto = {
    false, false, 351, descriptor_table_protodef_CharacterData_2eproto,
    "CharacterData.proto",
    &descriptor_table_CharacterData_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_CharacterData_2eproto::offsets,
    file_level_metadata_CharacterData_2eproto, file_level_enum_descriptors_CharacterData_2eproto,
    file_level_service_descriptors_CharacterData_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_CharacterData_2eproto_getter() {
  return &descriptor_table_CharacterData_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_CharacterData_2eproto(&descriptor_table_CharacterData_2eproto);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* WeaponSaveData_WeaponType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_CharacterData_2eproto);
  return file_level_enum_descriptors_CharacterData_2eproto[0];
}
bool WeaponSaveData_WeaponType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
constexpr WeaponSaveData_WeaponType WeaponSaveData::EWT_RIFLE;
constexpr WeaponSaveData_WeaponType WeaponSaveData::EWT_PISTOL;
constexpr WeaponSaveData_WeaponType WeaponSaveData::EWT_SHOTGUN;
constexpr WeaponSaveData_WeaponType WeaponSaveData::WeaponType_MIN;
constexpr WeaponSaveData_WeaponType WeaponSaveData::WeaponType_MAX;
constexpr int WeaponSaveData::WeaponType_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))

// ===================================================================

class CharacterData::_Internal {
 public:
  static const ::WeaponSaveData& weaponsavedata(const CharacterData* msg);
};

const ::WeaponSaveData&
CharacterData::_Internal::weaponsavedata(const CharacterData* msg) {
  return *msg->_impl_.weaponsavedata_;
}
CharacterData::CharacterData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:CharacterData)
}
CharacterData::CharacterData(const CharacterData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  CharacterData* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.playername_){}
    , decltype(_impl_.weaponsavedata_){nullptr}
    , decltype(_impl_.level_){}
    , decltype(_impl_.exp_){}
    , decltype(_impl_.gold_){}
    , decltype(_impl_.rifleammo_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.playername_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.playername_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_playername().empty()) {
    _this->_impl_.playername_.Set(from._internal_playername(), 
      _this->GetArenaForAllocation());
  }
  if (from._internal_has_weaponsavedata()) {
    _this->_impl_.weaponsavedata_ = new ::WeaponSaveData(*from._impl_.weaponsavedata_);
  }
  ::memcpy(&_impl_.level_, &from._impl_.level_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.rifleammo_) -
    reinterpret_cast<char*>(&_impl_.level_)) + sizeof(_impl_.rifleammo_));
  // @@protoc_insertion_point(copy_constructor:CharacterData)
}

inline void CharacterData::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.playername_){}
    , decltype(_impl_.weaponsavedata_){nullptr}
    , decltype(_impl_.level_){0}
    , decltype(_impl_.exp_){0}
    , decltype(_impl_.gold_){0}
    , decltype(_impl_.rifleammo_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.playername_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.playername_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

CharacterData::~CharacterData() {
  // @@protoc_insertion_point(destructor:CharacterData)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void CharacterData::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.playername_.Destroy();
  if (this != internal_default_instance()) delete _impl_.weaponsavedata_;
}

void CharacterData::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void CharacterData::Clear() {
// @@protoc_insertion_point(message_clear_start:CharacterData)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.playername_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && _impl_.weaponsavedata_ != nullptr) {
    delete _impl_.weaponsavedata_;
  }
  _impl_.weaponsavedata_ = nullptr;
  ::memset(&_impl_.level_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.rifleammo_) -
      reinterpret_cast<char*>(&_impl_.level_)) + sizeof(_impl_.rifleammo_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* CharacterData::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 level = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.level_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 exp = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.exp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string playerName = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_playername();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "CharacterData.playerName"));
        } else
          goto handle_unusual;
        continue;
      // int32 gold = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.gold_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .WeaponSaveData weaponSaveData = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          ptr = ctx->ParseMessage(_internal_mutable_weaponsavedata(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 rifleAmmo = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _impl_.rifleammo_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* CharacterData::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:CharacterData)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 level = 1;
  if (this->_internal_level() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_level(), target);
  }

  // int32 exp = 2;
  if (this->_internal_exp() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_exp(), target);
  }

  // string playerName = 3;
  if (!this->_internal_playername().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_playername().data(), static_cast<int>(this->_internal_playername().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "CharacterData.playerName");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_playername(), target);
  }

  // int32 gold = 4;
  if (this->_internal_gold() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_gold(), target);
  }

  // .WeaponSaveData weaponSaveData = 5;
  if (this->_internal_has_weaponsavedata()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(5, _Internal::weaponsavedata(this),
        _Internal::weaponsavedata(this).GetCachedSize(), target, stream);
  }

  // int32 rifleAmmo = 6;
  if (this->_internal_rifleammo() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(6, this->_internal_rifleammo(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:CharacterData)
  return target;
}

size_t CharacterData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:CharacterData)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string playerName = 3;
  if (!this->_internal_playername().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_playername());
  }

  // .WeaponSaveData weaponSaveData = 5;
  if (this->_internal_has_weaponsavedata()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.weaponsavedata_);
  }

  // int32 level = 1;
  if (this->_internal_level() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_level());
  }

  // int32 exp = 2;
  if (this->_internal_exp() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_exp());
  }

  // int32 gold = 4;
  if (this->_internal_gold() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_gold());
  }

  // int32 rifleAmmo = 6;
  if (this->_internal_rifleammo() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_rifleammo());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData CharacterData::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    CharacterData::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*CharacterData::GetClassData() const { return &_class_data_; }


void CharacterData::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<CharacterData*>(&to_msg);
  auto& from = static_cast<const CharacterData&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:CharacterData)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_playername().empty()) {
    _this->_internal_set_playername(from._internal_playername());
  }
  if (from._internal_has_weaponsavedata()) {
    _this->_internal_mutable_weaponsavedata()->::WeaponSaveData::MergeFrom(
        from._internal_weaponsavedata());
  }
  if (from._internal_level() != 0) {
    _this->_internal_set_level(from._internal_level());
  }
  if (from._internal_exp() != 0) {
    _this->_internal_set_exp(from._internal_exp());
  }
  if (from._internal_gold() != 0) {
    _this->_internal_set_gold(from._internal_gold());
  }
  if (from._internal_rifleammo() != 0) {
    _this->_internal_set_rifleammo(from._internal_rifleammo());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void CharacterData::CopyFrom(const CharacterData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:CharacterData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CharacterData::IsInitialized() const {
  return true;
}

void CharacterData::InternalSwap(CharacterData* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.playername_, lhs_arena,
      &other->_impl_.playername_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(CharacterData, _impl_.rifleammo_)
      + sizeof(CharacterData::_impl_.rifleammo_)
      - PROTOBUF_FIELD_OFFSET(CharacterData, _impl_.weaponsavedata_)>(
          reinterpret_cast<char*>(&_impl_.weaponsavedata_),
          reinterpret_cast<char*>(&other->_impl_.weaponsavedata_));
}

::PROTOBUF_NAMESPACE_ID::Metadata CharacterData::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_CharacterData_2eproto_getter, &descriptor_table_CharacterData_2eproto_once,
      file_level_metadata_CharacterData_2eproto[0]);
}

// ===================================================================

class WeaponSaveData::_Internal {
 public:
};

WeaponSaveData::WeaponSaveData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:WeaponSaveData)
}
WeaponSaveData::WeaponSaveData(const WeaponSaveData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  WeaponSaveData* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.weaponlevel_){}
    , decltype(_impl_.weaponenhancementlevel_){}
    , decltype(_impl_.weapontype_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.weaponlevel_, &from._impl_.weaponlevel_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.weapontype_) -
    reinterpret_cast<char*>(&_impl_.weaponlevel_)) + sizeof(_impl_.weapontype_));
  // @@protoc_insertion_point(copy_constructor:WeaponSaveData)
}

inline void WeaponSaveData::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.weaponlevel_){0}
    , decltype(_impl_.weaponenhancementlevel_){0}
    , decltype(_impl_.weapontype_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

WeaponSaveData::~WeaponSaveData() {
  // @@protoc_insertion_point(destructor:WeaponSaveData)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void WeaponSaveData::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void WeaponSaveData::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void WeaponSaveData::Clear() {
// @@protoc_insertion_point(message_clear_start:WeaponSaveData)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.weaponlevel_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.weapontype_) -
      reinterpret_cast<char*>(&_impl_.weaponlevel_)) + sizeof(_impl_.weapontype_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* WeaponSaveData::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 weaponLevel = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.weaponlevel_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 weaponEnhancementLevel = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.weaponenhancementlevel_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .WeaponSaveData.WeaponType weaponType = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_weapontype(static_cast<::WeaponSaveData_WeaponType>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* WeaponSaveData::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:WeaponSaveData)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 weaponLevel = 1;
  if (this->_internal_weaponlevel() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_weaponlevel(), target);
  }

  // int32 weaponEnhancementLevel = 2;
  if (this->_internal_weaponenhancementlevel() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_weaponenhancementlevel(), target);
  }

  // .WeaponSaveData.WeaponType weaponType = 3;
  if (this->_internal_weapontype() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      3, this->_internal_weapontype(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WeaponSaveData)
  return target;
}

size_t WeaponSaveData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:WeaponSaveData)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 weaponLevel = 1;
  if (this->_internal_weaponlevel() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_weaponlevel());
  }

  // int32 weaponEnhancementLevel = 2;
  if (this->_internal_weaponenhancementlevel() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_weaponenhancementlevel());
  }

  // .WeaponSaveData.WeaponType weaponType = 3;
  if (this->_internal_weapontype() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_weapontype());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData WeaponSaveData::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    WeaponSaveData::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*WeaponSaveData::GetClassData() const { return &_class_data_; }


void WeaponSaveData::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<WeaponSaveData*>(&to_msg);
  auto& from = static_cast<const WeaponSaveData&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:WeaponSaveData)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_weaponlevel() != 0) {
    _this->_internal_set_weaponlevel(from._internal_weaponlevel());
  }
  if (from._internal_weaponenhancementlevel() != 0) {
    _this->_internal_set_weaponenhancementlevel(from._internal_weaponenhancementlevel());
  }
  if (from._internal_weapontype() != 0) {
    _this->_internal_set_weapontype(from._internal_weapontype());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void WeaponSaveData::CopyFrom(const WeaponSaveData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:WeaponSaveData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WeaponSaveData::IsInitialized() const {
  return true;
}

void WeaponSaveData::InternalSwap(WeaponSaveData* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(WeaponSaveData, _impl_.weapontype_)
      + sizeof(WeaponSaveData::_impl_.weapontype_)
      - PROTOBUF_FIELD_OFFSET(WeaponSaveData, _impl_.weaponlevel_)>(
          reinterpret_cast<char*>(&_impl_.weaponlevel_),
          reinterpret_cast<char*>(&other->_impl_.weaponlevel_));
}

::PROTOBUF_NAMESPACE_ID::Metadata WeaponSaveData::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_CharacterData_2eproto_getter, &descriptor_table_CharacterData_2eproto_once,
      file_level_metadata_CharacterData_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::CharacterData*
Arena::CreateMaybeMessage< ::CharacterData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::CharacterData >(arena);
}
template<> PROTOBUF_NOINLINE ::WeaponSaveData*
Arena::CreateMaybeMessage< ::WeaponSaveData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::WeaponSaveData >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
#ifdef _MSC_VER
#include "Windows/HideWindowsPlatformTypes.h"
#endif
