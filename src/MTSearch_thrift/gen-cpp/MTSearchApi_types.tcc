/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MTSearchApi_TYPES_TCC
#define MTSearchApi_TYPES_TCC

#include "MTSearchApi_types.h"



template <class Protocol_>
uint32_t SearchQueryReq::read(Protocol_* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_key_words = false;
  bool isset_city = false;
  bool isset_category = false;
  bool isset_cityid = false;
  bool isset_id = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->key_words);
          isset_key_words = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->city);
          isset_city = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->category);
          isset_category = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->cityid);
          isset_cityid = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->id);
          isset_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->offset);
          this->__isset.offset = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->limit);
          this->__isset.limit = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 8:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->location);
          this->__isset.location = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 9:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->orderby);
          this->__isset.orderby = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 10:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->filter.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _ktype1;
            ::apache::thrift::protocol::TType _vtype2;
            xfer += iprot->readMapBegin(_ktype1, _vtype2, _size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              std::string _key5;
              xfer += iprot->readString(_key5);
              std::string& _val6 = this->filter[_key5];
              xfer += iprot->readString(_val6);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.filter = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 11:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->counter.clear();
            uint32_t _size7;
            ::apache::thrift::protocol::TType _ktype8;
            ::apache::thrift::protocol::TType _vtype9;
            xfer += iprot->readMapBegin(_ktype8, _vtype9, _size7);
            uint32_t _i11;
            for (_i11 = 0; _i11 < _size7; ++_i11)
            {
              std::string _key12;
              xfer += iprot->readString(_key12);
              std::string& _val13 = this->counter[_key12];
              xfer += iprot->readString(_val13);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.counter = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 12:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->control.clear();
            uint32_t _size14;
            ::apache::thrift::protocol::TType _ktype15;
            ::apache::thrift::protocol::TType _vtype16;
            xfer += iprot->readMapBegin(_ktype15, _vtype16, _size14);
            uint32_t _i18;
            for (_i18 = 0; _i18 < _size14; ++_i18)
            {
              std::string _key19;
              xfer += iprot->readString(_key19);
              std::string& _val20 = this->control[_key19];
              xfer += iprot->readString(_val20);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.control = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 13:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->exdata.clear();
            uint32_t _size21;
            ::apache::thrift::protocol::TType _ktype22;
            ::apache::thrift::protocol::TType _vtype23;
            xfer += iprot->readMapBegin(_ktype22, _vtype23, _size21);
            uint32_t _i25;
            for (_i25 = 0; _i25 < _size21; ++_i25)
            {
              std::string _key26;
              xfer += iprot->readString(_key26);
              std::string& _val27 = this->exdata[_key26];
              xfer += iprot->readString(_val27);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.exdata = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 14:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->opt);
          this->__isset.opt = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_key_words)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_city)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_category)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_cityid)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_id)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

template <class Protocol_>
uint32_t SearchQueryReq::write(Protocol_* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("SearchQueryReq");

  xfer += oprot->writeFieldBegin("key_words", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->key_words);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("city", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->city);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("category", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->category);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("cityid", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->cityid);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("id", ::apache::thrift::protocol::T_I32, 5);
  xfer += oprot->writeI32(this->id);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.offset) {
    xfer += oprot->writeFieldBegin("offset", ::apache::thrift::protocol::T_I32, 6);
    xfer += oprot->writeI32(this->offset);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.limit) {
    xfer += oprot->writeFieldBegin("limit", ::apache::thrift::protocol::T_I32, 7);
    xfer += oprot->writeI32(this->limit);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.location) {
    xfer += oprot->writeFieldBegin("location", ::apache::thrift::protocol::T_STRING, 8);
    xfer += oprot->writeString(this->location);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.orderby) {
    xfer += oprot->writeFieldBegin("orderby", ::apache::thrift::protocol::T_STRING, 9);
    xfer += oprot->writeString(this->orderby);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.filter) {
    xfer += oprot->writeFieldBegin("filter", ::apache::thrift::protocol::T_MAP, 10);
    {
      xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->filter.size()));
      std::map<std::string, std::string> ::const_iterator _iter28;
      for (_iter28 = this->filter.begin(); _iter28 != this->filter.end(); ++_iter28)
      {
        xfer += oprot->writeString(_iter28->first);
        xfer += oprot->writeString(_iter28->second);
      }
      xfer += oprot->writeMapEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.counter) {
    xfer += oprot->writeFieldBegin("counter", ::apache::thrift::protocol::T_MAP, 11);
    {
      xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->counter.size()));
      std::map<std::string, std::string> ::const_iterator _iter29;
      for (_iter29 = this->counter.begin(); _iter29 != this->counter.end(); ++_iter29)
      {
        xfer += oprot->writeString(_iter29->first);
        xfer += oprot->writeString(_iter29->second);
      }
      xfer += oprot->writeMapEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.control) {
    xfer += oprot->writeFieldBegin("control", ::apache::thrift::protocol::T_MAP, 12);
    {
      xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->control.size()));
      std::map<std::string, std::string> ::const_iterator _iter30;
      for (_iter30 = this->control.begin(); _iter30 != this->control.end(); ++_iter30)
      {
        xfer += oprot->writeString(_iter30->first);
        xfer += oprot->writeString(_iter30->second);
      }
      xfer += oprot->writeMapEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.exdata) {
    xfer += oprot->writeFieldBegin("exdata", ::apache::thrift::protocol::T_MAP, 13);
    {
      xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->exdata.size()));
      std::map<std::string, std::string> ::const_iterator _iter31;
      for (_iter31 = this->exdata.begin(); _iter31 != this->exdata.end(); ++_iter31)
      {
        xfer += oprot->writeString(_iter31->first);
        xfer += oprot->writeString(_iter31->second);
      }
      xfer += oprot->writeMapEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.opt) {
    xfer += oprot->writeFieldBegin("opt", ::apache::thrift::protocol::T_I32, 14);
    xfer += oprot->writeI32(this->opt);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

template <class Protocol_>
uint32_t SearchMatchItem::read(Protocol_* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_id = false;
  bool isset_doc_info = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->id);
          isset_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->doc_info.clear();
            uint32_t _size36;
            ::apache::thrift::protocol::TType _ktype37;
            ::apache::thrift::protocol::TType _vtype38;
            xfer += iprot->readMapBegin(_ktype37, _vtype38, _size36);
            uint32_t _i40;
            for (_i40 = 0; _i40 < _size36; ++_i40)
            {
              std::string _key41;
              xfer += iprot->readString(_key41);
              std::string& _val42 = this->doc_info[_key41];
              xfer += iprot->readString(_val42);
            }
            xfer += iprot->readMapEnd();
          }
          isset_doc_info = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_id)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_doc_info)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

template <class Protocol_>
uint32_t SearchMatchItem::write(Protocol_* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("SearchMatchItem");

  xfer += oprot->writeFieldBegin("id", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("doc_info", ::apache::thrift::protocol::T_MAP, 2);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->doc_info.size()));
    std::map<std::string, std::string> ::const_iterator _iter43;
    for (_iter43 = this->doc_info.begin(); _iter43 != this->doc_info.end(); ++_iter43)
    {
      xfer += oprot->writeString(_iter43->first);
      xfer += oprot->writeString(_iter43->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

template <class Protocol_>
uint32_t SearchGroupRes::read(Protocol_* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_type = false;
  bool isset_info = false;
  bool isset_matches = false;
  bool isset_exinfo = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->type);
          isset_type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->info);
          isset_info = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->matches.clear();
            uint32_t _size48;
            ::apache::thrift::protocol::TType _etype51;
            xfer += iprot->readListBegin(_etype51, _size48);
            this->matches.resize(_size48);
            uint32_t _i52;
            for (_i52 = 0; _i52 < _size48; ++_i52)
            {
              xfer += this->matches[_i52].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          isset_matches = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->exinfo.clear();
            uint32_t _size53;
            ::apache::thrift::protocol::TType _ktype54;
            ::apache::thrift::protocol::TType _vtype55;
            xfer += iprot->readMapBegin(_ktype54, _vtype55, _size53);
            uint32_t _i57;
            for (_i57 = 0; _i57 < _size53; ++_i57)
            {
              std::string _key58;
              xfer += iprot->readString(_key58);
              std::string& _val59 = this->exinfo[_key58];
              xfer += iprot->readString(_val59);
            }
            xfer += iprot->readMapEnd();
          }
          isset_exinfo = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_type)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_info)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_matches)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_exinfo)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

template <class Protocol_>
uint32_t SearchGroupRes::write(Protocol_* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("SearchGroupRes");

  xfer += oprot->writeFieldBegin("type", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->type);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("info", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->info);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("matches", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->matches.size()));
    std::vector<SearchMatchItem> ::const_iterator _iter60;
    for (_iter60 = this->matches.begin(); _iter60 != this->matches.end(); ++_iter60)
    {
      xfer += (*_iter60).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("exinfo", ::apache::thrift::protocol::T_MAP, 4);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->exinfo.size()));
    std::map<std::string, std::string> ::const_iterator _iter61;
    for (_iter61 = this->exinfo.begin(); _iter61 != this->exinfo.end(); ++_iter61)
    {
      xfer += oprot->writeString(_iter61->first);
      xfer += oprot->writeString(_iter61->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

template <class Protocol_>
uint32_t SearchMultiRes::read(Protocol_* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_status = false;
  bool isset_error = false;
  bool isset_group_res = false;
  bool isset_exinfo = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->status);
          isset_status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->error);
          isset_error = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->group_res.clear();
            uint32_t _size66;
            ::apache::thrift::protocol::TType _etype69;
            xfer += iprot->readListBegin(_etype69, _size66);
            this->group_res.resize(_size66);
            uint32_t _i70;
            for (_i70 = 0; _i70 < _size66; ++_i70)
            {
              xfer += this->group_res[_i70].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          isset_group_res = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->exinfo.clear();
            uint32_t _size71;
            ::apache::thrift::protocol::TType _ktype72;
            ::apache::thrift::protocol::TType _vtype73;
            xfer += iprot->readMapBegin(_ktype72, _vtype73, _size71);
            uint32_t _i75;
            for (_i75 = 0; _i75 < _size71; ++_i75)
            {
              std::string _key76;
              xfer += iprot->readString(_key76);
              std::string& _val77 = this->exinfo[_key76];
              xfer += iprot->readString(_val77);
            }
            xfer += iprot->readMapEnd();
          }
          isset_exinfo = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_status)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_error)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_group_res)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_exinfo)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

template <class Protocol_>
uint32_t SearchMultiRes::write(Protocol_* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("SearchMultiRes");

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("error", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->error);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("group_res", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->group_res.size()));
    std::vector<SearchGroupRes> ::const_iterator _iter78;
    for (_iter78 = this->group_res.begin(); _iter78 != this->group_res.end(); ++_iter78)
    {
      xfer += (*_iter78).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("exinfo", ::apache::thrift::protocol::T_MAP, 4);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->exinfo.size()));
    std::map<std::string, std::string> ::const_iterator _iter79;
    for (_iter79 = this->exinfo.begin(); _iter79 != this->exinfo.end(); ++_iter79)
    {
      xfer += oprot->writeString(_iter79->first);
      xfer += oprot->writeString(_iter79->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}



#endif