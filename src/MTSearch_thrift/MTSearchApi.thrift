/*
 * thrift --gen cpp:templates,pure_enums,moveable_types,no_default_operators MTSearchApi.thrift
 */

struct SearchQueryReq{
	1: required string key_words = '',
	2: required string city = '',   
	3: required string category = '', 
	4: required i32 cityid,
	5: required i32 id,
	6: optional i32 offset = 0,   
	7: optional i32 limit = 1000,
	8: optional string location = '',  // "lat,lng"
	9: optional string orderby = '',
	10: optional map<string, string> filter,
	11: optional map<string, string> counter,
	12: optional map<string, string> control,
	13: optional map<string, string> exdata,
	14: optional i32 opt = 0,
}


struct SearchMatchItem{
	1: required i32 id,
	2: required map<string, string> doc_info
}

struct SearchGroupRes{
	1: required string type,
	2: required string info,
	3: required list<SearchMatchItem> matches,
	4: required map<string, string> exinfo
}

struct SearchMultiRes{
	1: required i32 status,
	2: required string error,
	3: required list<SearchGroupRes> group_res,
	4: required map<string, string> exinfo
}


service MTSearch{
	SearchMultiRes MTSearchDeal(1: SearchQueryReq query);
	SearchMultiRes MTSearchPoi(1: SearchQueryReq query);
	SearchMultiRes MTMultiSearch(1: SearchQueryReq query);
	SearchMultiRes AttributeFilter(1: SearchQueryReq query);
}
