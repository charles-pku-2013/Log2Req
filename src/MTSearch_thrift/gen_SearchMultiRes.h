#pragma once
#include "../include/MTSearch_thrift/gen-cpp/MTSearchApi_types.h"
#include "template.h"
#include "jsonEncode.h"
class SearchQueryReq;
class SearchMatchItem;
class SearchGroupRes;
class SearchMultiRes;
static inline void print(const SearchQueryReq& arg, const char* key=0){
	printf("SearchQueryReq={");
	print(arg.opt, "opt");
	print(arg.exdata, "exdata");
	print(arg.control, "control");
	print(arg.counter, "counter");
	print(arg.filter, "filter");
	print(arg.orderby, "orderby");
	print(arg.location, "location");
	print(arg.limit, "limit");
	print(arg.offset, "offset");
	print(arg.id, "id");
	print(arg.cityid, "cityid");
	print(arg.category, "category");
	print(arg.city, "city");
	print(arg.key_words, "key_words");
	printf("};");
}
static inline void sprint(string& dest, const SearchQueryReq& arg, const char* key=0){
	sprint(dest,"SearchQueryReq={");
	sprint(dest, arg.opt, "opt");
	sprint(dest, arg.exdata, "exdata");
	sprint(dest, arg.control, "control");
	sprint(dest, arg.counter, "counter");
	sprint(dest, arg.filter, "filter");
	sprint(dest, arg.orderby, "orderby");
	sprint(dest, arg.location, "location");
	sprint(dest, arg.limit, "limit");
	sprint(dest, arg.offset, "offset");
	sprint(dest, arg.id, "id");
	sprint(dest, arg.cityid, "cityid");
	sprint(dest, arg.category, "category");
	sprint(dest, arg.city, "city");
	sprint(dest, arg.key_words, "key_words");
	sprint(dest, "};");
}
static inline void jsonEncode(Json::Value& dest, const SearchQueryReq& arg, const char* key=0){
	jsonEncode(dest, arg.opt, "opt");
	jsonEncode(dest, arg.exdata, "exdata");
	jsonEncode(dest, arg.control, "control");
	jsonEncode(dest, arg.counter, "counter");
	jsonEncode(dest, arg.filter, "filter");
	jsonEncode(dest, arg.orderby, "orderby");
	jsonEncode(dest, arg.location, "location");
	jsonEncode(dest, arg.limit, "limit");
	jsonEncode(dest, arg.offset, "offset");
	jsonEncode(dest, arg.id, "id");
	jsonEncode(dest, arg.cityid, "cityid");
	jsonEncode(dest, arg.category, "category");
	jsonEncode(dest, arg.city, "city");
	jsonEncode(dest, arg.key_words, "key_words");
}
static inline void print(const SearchMatchItem& arg, const char* key=0){
	printf("SearchMatchItem={");
	print(arg.doc_info, "doc_info");
	print(arg.id, "id");
	printf("};");
}
static inline void sprint(string& dest, const SearchMatchItem& arg, const char* key=0){
	sprint(dest,"SearchMatchItem={");
	sprint(dest, arg.doc_info, "doc_info");
	sprint(dest, arg.id, "id");
	sprint(dest, "};");
}
static inline void jsonEncode(Json::Value& dest, const SearchMatchItem& arg, const char* key=0){
	jsonEncode(dest, arg.doc_info, "doc_info");
	jsonEncode(dest, arg.id, "id");
}
static inline void print(const SearchGroupRes& arg, const char* key=0){
	printf("SearchGroupRes={");
	print(arg.exinfo, "exinfo");
	print(arg.matches, "matches");
	print(arg.info, "info");
	print(arg.type, "type");
	printf("};");
}
static inline void sprint(string& dest, const SearchGroupRes& arg, const char* key=0){
	sprint(dest,"SearchGroupRes={");
	sprint(dest, arg.exinfo, "exinfo");
	sprint(dest, arg.matches, "matches");
	sprint(dest, arg.info, "info");
	sprint(dest, arg.type, "type");
	sprint(dest, "};");
}
static inline void jsonEncode(Json::Value& dest, const SearchGroupRes& arg, const char* key=0){
	jsonEncode(dest, arg.exinfo, "exinfo");
	jsonEncode(dest, arg.matches, "matches");
	jsonEncode(dest, arg.info, "info");
	jsonEncode(dest, arg.type, "type");
}
static inline void print(const SearchMultiRes& arg, const char* key=0){
	printf("SearchMultiRes={");
	print(arg.exinfo, "exinfo");
	print(arg.group_res, "group_res");
	print(arg.error, "error");
	print(arg.status, "status");
	printf("};");
}
static inline void sprint(string& dest, const SearchMultiRes& arg, const char* key=0){
	sprint(dest,"SearchMultiRes={");
	sprint(dest, arg.exinfo, "exinfo");
	sprint(dest, arg.group_res, "group_res");
	sprint(dest, arg.error, "error");
	sprint(dest, arg.status, "status");
	sprint(dest, "};");
}
static inline void jsonEncode(Json::Value& dest, const SearchMultiRes& arg, const char* key=0){
	jsonEncode(dest, arg.exinfo, "exinfo");
	jsonEncode(dest, arg.group_res, "group_res");
	jsonEncode(dest, arg.error, "error");
	jsonEncode(dest, arg.status, "status");
}

static inline bool serial(const SearchQueryReq& arg, string& dest){
	serial(arg.opt, dest);
	serial(arg.exdata, dest);
	serial(arg.control, dest);
	serial(arg.counter, dest);
	serial(arg.filter, dest);
	serial(arg.orderby, dest);
	serial(arg.location, dest);
	serial(arg.limit, dest);
	serial(arg.offset, dest);
	serial(arg.id, dest);
	serial(arg.cityid, dest);
	serial(arg.category, dest);
	serial(arg.city, dest);
	serial(arg.key_words, dest);
	return true;
}
static inline bool serial(const SearchMatchItem& arg, string& dest){
	serial(arg.doc_info, dest);
	serial(arg.id, dest);
	return true;
}
static inline bool serial(const SearchGroupRes& arg, string& dest){
	serial(arg.exinfo, dest);
	serial(arg.matches, dest);
	serial(arg.info, dest);
	serial(arg.type, dest);
	return true;
}
static inline bool serial(const SearchMultiRes& arg, string& dest){
	serial(arg.exinfo, dest);
	serial(arg.group_res, dest);
	serial(arg.error, dest);
	serial(arg.status, dest);
	return true;
}

static inline int unserial(const string& src, int loc, SearchQueryReq& arg){
	int cur_loc = loc;
	cur_loc += unserial(src, cur_loc, arg.opt);
	cur_loc += unserial(src, cur_loc, arg.exdata);
	cur_loc += unserial(src, cur_loc, arg.control);
	cur_loc += unserial(src, cur_loc, arg.counter);
	cur_loc += unserial(src, cur_loc, arg.filter);
	cur_loc += unserial(src, cur_loc, arg.orderby);
	cur_loc += unserial(src, cur_loc, arg.location);
	cur_loc += unserial(src, cur_loc, arg.limit);
	cur_loc += unserial(src, cur_loc, arg.offset);
	cur_loc += unserial(src, cur_loc, arg.id);
	cur_loc += unserial(src, cur_loc, arg.cityid);
	cur_loc += unserial(src, cur_loc, arg.category);
	cur_loc += unserial(src, cur_loc, arg.city);
	cur_loc += unserial(src, cur_loc, arg.key_words);
	return cur_loc-loc;
}
static inline int unserial(const string& src, int loc, SearchMatchItem& arg){
	int cur_loc = loc;
	cur_loc += unserial(src, cur_loc, arg.doc_info);
	cur_loc += unserial(src, cur_loc, arg.id);
	return cur_loc-loc;
}
static inline int unserial(const string& src, int loc, SearchGroupRes& arg){
	int cur_loc = loc;
	cur_loc += unserial(src, cur_loc, arg.exinfo);
	cur_loc += unserial(src, cur_loc, arg.matches);
	cur_loc += unserial(src, cur_loc, arg.info);
	cur_loc += unserial(src, cur_loc, arg.type);
	return cur_loc-loc;
}
static inline int unserial(const string& src, int loc, SearchMultiRes& arg){
	int cur_loc = loc;
	cur_loc += unserial(src, cur_loc, arg.exinfo);
	cur_loc += unserial(src, cur_loc, arg.group_res);
	cur_loc += unserial(src, cur_loc, arg.error);
	cur_loc += unserial(src, cur_loc, arg.status);
	return cur_loc-loc;
}

