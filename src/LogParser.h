#ifndef _LOG_PARSER_H_
#define _LOG_PARSER_H_

#include <iostream>
#include <set>
#include <memory>
#include <boost/lexical_cast.hpp>
#include "LogReq.h"


struct ItemParser {
    virtual void setAttr(const std::string &strKey, const std::string &strVal, LogReq &req)
    { req.setAttr(strKey, strVal); }
};

struct IntItemParser : ItemParser {
    void setAttr(const std::string &strKey, const std::string &strVal, LogReq &req) override
    { 
        int val = boost::lexical_cast<int32_t>(strVal);
        req.setAttr(strKey, val); 
    }
};

struct DictItemParser : ItemParser {
    void setAttr(const std::string &strKey, const std::string &strVal, LogReq &req) override;
};

struct ControlItemParser : DictItemParser {
    void setAttr(const std::string &strKey, const std::string &strVal, LogReq &req) override;
};

struct ExtDataItemParser : DictItemParser {
    void setAttr(const std::string &strKey, const std::string &strVal, LogReq &req) override;
};


class LogParser {
public:
    typedef std::map<std::string, std::shared_ptr<ItemParser> >     ItemParserDict;

public:
    virtual void parse(const std::string &line, LogReq &req) = 0;
    static void parse_dict(const std::string &text, std::map<std::string, std::string> &result);

protected:
    ItemParserDict    m_dictItemParser;
};

/*
 * query 词可能包含空格，暂不支持解析这样的log
 */
class QsLogParser : public LogParser {
public:
    QsLogParser();
    void parse(const std::string &line, LogReq &req) override;
};

#if 0
class LogParser {
public:
    void log2Json(const std::string &fname);
    void writeJson(const std::string &fname);
    void loadJson(const std::string &fname);
    Json::Value& jsonLog() { return m_jsonLog; }

public:
    bool toJson_helper(const std::string &line, Json::Value &jsLog, std::size_t lineNO);
    void parseMulti(const std::string &text, Json::Value &result, std::size_t lineNO);

public:
    Json::Value         m_jsonLog;

    const std::set<std::string>     m_UsefulAttrs = 
                {"query", "city", "category", "cityid", "reqid",
                 "offset", "limit", "location", "orderby", "filter",
                 "counter", "control", "ext_data", "if_name"};
    const std::map<std::string, std::string>    m_LogReqKeyDict = 
                {{"query", "key_words"},
                 {"reqid", "id"},
                 {"ext_data", "exdata"}};
    const std::set<std::string>     m_MultiKeys = {"filter", "counter", "control", "ext_data"};
};
#endif


#endif /* _LOG_PARSER_H_ */
