/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MTSearchApi_TYPES_H
#define MTSearchApi_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




class SearchQueryReq;

class SearchMatchItem;

class SearchGroupRes;

class SearchMultiRes;

typedef struct _SearchQueryReq__isset {
  _SearchQueryReq__isset() : offset(true), limit(true), location(true), orderby(true), filter(false), counter(false), control(false), exdata(false), opt(true) {}
  bool offset :1;
  bool limit :1;
  bool location :1;
  bool orderby :1;
  bool filter :1;
  bool counter :1;
  bool control :1;
  bool exdata :1;
  bool opt :1;
} _SearchQueryReq__isset;

class SearchQueryReq {
 public:

  SearchQueryReq(const SearchQueryReq&);
  SearchQueryReq(SearchQueryReq&&);
  SearchQueryReq& operator=(const SearchQueryReq&);
  SearchQueryReq& operator=(SearchQueryReq&&);
  SearchQueryReq() : key_words(""), city(""), category(""), cityid(0), id(0), offset(0), limit(1000), location(""), orderby(""), opt(0) {
  }

  virtual ~SearchQueryReq() throw();
  std::string key_words;
  std::string city;
  std::string category;
  int32_t cityid;
  int32_t id;
  int32_t offset;
  int32_t limit;
  std::string location;
  std::string orderby;
  std::map<std::string, std::string>  filter;
  std::map<std::string, std::string>  counter;
  std::map<std::string, std::string>  control;
  std::map<std::string, std::string>  exdata;
  int32_t opt;

  _SearchQueryReq__isset __isset;

  void __set_key_words(const std::string& val);

  void __set_city(const std::string& val);

  void __set_category(const std::string& val);

  void __set_cityid(const int32_t val);

  void __set_id(const int32_t val);

  void __set_offset(const int32_t val);

  void __set_limit(const int32_t val);

  void __set_location(const std::string& val);

  void __set_orderby(const std::string& val);

  void __set_filter(const std::map<std::string, std::string> & val);

  void __set_counter(const std::map<std::string, std::string> & val);

  void __set_control(const std::map<std::string, std::string> & val);

  void __set_exdata(const std::map<std::string, std::string> & val);

  void __set_opt(const int32_t val);

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(SearchQueryReq &a, SearchQueryReq &b);

inline std::ostream& operator<<(std::ostream& out, const SearchQueryReq& obj)
{
  obj.printTo(out);
  return out;
}


class SearchMatchItem {
 public:

  SearchMatchItem(const SearchMatchItem&);
  SearchMatchItem(SearchMatchItem&&);
  SearchMatchItem& operator=(const SearchMatchItem&);
  SearchMatchItem& operator=(SearchMatchItem&&);
  SearchMatchItem() : id(0) {
  }

  virtual ~SearchMatchItem() throw();
  int32_t id;
  std::map<std::string, std::string>  doc_info;

  void __set_id(const int32_t val);

  void __set_doc_info(const std::map<std::string, std::string> & val);

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(SearchMatchItem &a, SearchMatchItem &b);

inline std::ostream& operator<<(std::ostream& out, const SearchMatchItem& obj)
{
  obj.printTo(out);
  return out;
}


class SearchGroupRes {
 public:

  SearchGroupRes(const SearchGroupRes&);
  SearchGroupRes(SearchGroupRes&&);
  SearchGroupRes& operator=(const SearchGroupRes&);
  SearchGroupRes& operator=(SearchGroupRes&&);
  SearchGroupRes() : type(), info() {
  }

  virtual ~SearchGroupRes() throw();
  std::string type;
  std::string info;
  std::vector<SearchMatchItem>  matches;
  std::map<std::string, std::string>  exinfo;

  void __set_type(const std::string& val);

  void __set_info(const std::string& val);

  void __set_matches(const std::vector<SearchMatchItem> & val);

  void __set_exinfo(const std::map<std::string, std::string> & val);

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(SearchGroupRes &a, SearchGroupRes &b);

inline std::ostream& operator<<(std::ostream& out, const SearchGroupRes& obj)
{
  obj.printTo(out);
  return out;
}


class SearchMultiRes {
 public:

  SearchMultiRes(const SearchMultiRes&);
  SearchMultiRes(SearchMultiRes&&);
  SearchMultiRes& operator=(const SearchMultiRes&);
  SearchMultiRes& operator=(SearchMultiRes&&);
  SearchMultiRes() : status(0), error() {
  }

  virtual ~SearchMultiRes() throw();
  int32_t status;
  std::string error;
  std::vector<SearchGroupRes>  group_res;
  std::map<std::string, std::string>  exinfo;

  void __set_status(const int32_t val);

  void __set_error(const std::string& val);

  void __set_group_res(const std::vector<SearchGroupRes> & val);

  void __set_exinfo(const std::map<std::string, std::string> & val);

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(SearchMultiRes &a, SearchMultiRes &b);

inline std::ostream& operator<<(std::ostream& out, const SearchMultiRes& obj)
{
  obj.printTo(out);
  return out;
}



#include "MTSearchApi_types.tcc"

#endif
