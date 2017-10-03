#include "LogParser.h"
#include "CommDef.h"
#include <cctype>
#include <boost/algorithm/string.hpp>
#include <glog/logging.h>

using namespace std;


void DictItemParser::setAttr(const std::string &strKey, const std::string &strVal, LogReq &req)
{
    map<string, string> val;
    LogParser::parse_dict(strVal, val);
    req.setAttr(strKey, val);
}

void ControlItemParser::setAttr(const std::string &strKey, const std::string &strVal, LogReq &req)
{
    static const set<string> specialControlKeys = {"hasGroup", "results", "static"};
    // 以下划线打头的key都不要
    map<string, string> val;
    LogParser::parse_dict(strVal, val);

    for (auto it = val.begin(); it != val.end();) {
        // if (it->first.empty() || it->first[0] == '_')
        if (!specialControlKeys.count(it->first))
            it = val.erase(it);
        else
            ++it;
    } // for it

    req.setAttr(strKey, val);
}

void ExtDataItemParser::setAttr(const std::string &strKey, const std::string &strVal, LogReq &req)
{
    static const set<string> specialExtDataKeys = {"request_source", "sort_type"};

    map<string, string> val;
    LogParser::parse_dict(strVal, val);

    for (auto it = val.begin(); it != val.end();) {
        if (!specialExtDataKeys.count(it->first))
            it = val.erase(it);
        else
            ++it;
    } // for it

    req.setAttr(strKey, val);
}

void LogParser::parse_dict(const std::string &text, std::map<std::string, std::string> &result)
{
    if (text.empty()) return;

    string key, value;
    result.clear();

    string::size_type prev = (string::size_type)(-1);
    for (string::size_type cur = text.find_first_of(",:"); cur != string::npos; 
                cur = text.find_first_of(",:", cur + 1)) {
        // check if key
        if (text[cur] == ':' && (prev == (string::size_type)(-1) || text[prev] == ',')) {
            if (!key.empty()) {
                boost::trim_right_if(value, boost::is_any_of(","));
                result[key] = value;
                value.clear();
            } // if
            key = string(text.c_str() + prev + 1, text.c_str() + cur);
        } else {
            value.append(text.c_str() + prev + 1, text.c_str() + cur + 1);
        } // if
        prev = cur;
    } // for

    if (!key.empty()) {
        value.append(text.c_str() + prev + 1);
        boost::trim_right_if(value, boost::is_any_of(","));
        result[key] = value;
    } // if
}

QsLogParser::QsLogParser()
{
    m_dictItemParser["query"] = std::make_shared<ItemParser>();
    m_dictItemParser["category"] = std::make_shared<ItemParser>();
    m_dictItemParser["location"] = std::make_shared<ItemParser>();
    m_dictItemParser["orderby"] = std::make_shared<ItemParser>();
    m_dictItemParser["if_name"] = std::make_shared<ItemParser>();
    m_dictItemParser["reqid"] = std::make_shared<IntItemParser>();
    m_dictItemParser["cityid"] = std::make_shared<IntItemParser>();
    m_dictItemParser["offset"] = std::make_shared<IntItemParser>();
    m_dictItemParser["limit"] = std::make_shared<IntItemParser>();
    m_dictItemParser["filter"] = std::make_shared<DictItemParser>();
    m_dictItemParser["counter"] = std::make_shared<DictItemParser>();
    m_dictItemParser["control"] = std::make_shared<ControlItemParser>();
    m_dictItemParser["ext_data"] = std::make_shared<ExtDataItemParser>();
}

// #if 0
void QsLogParser::parse(const std::string &line, LogReq &req)
{
    string::size_type prev = line.find_first_of(']');
    THROW_RUNTIME_ERROR_IF(string::npos == prev, "Invalid log");
    ++prev;

    string key, value;
    for (string::size_type cur = line.find_first_of("=" SPACES, prev + 1); cur != string::npos;
                cur = line.find_first_of("=" SPACES, cur + 1)) {
        // check if key
        if (line[cur] == '=' && isspace(line[prev])) {
            if (!key.empty()) {
                boost::trim_right_if(value, boost::is_any_of(SPACES));
                auto it = m_dictItemParser.find(key);
                if (it != m_dictItemParser.end())
                    it->second->setAttr(key, value, req);
                value.clear();
            } // if
            key = string(line.c_str() + prev + 1, line.c_str() + cur);
        } else {
            value.append(line.c_str() + prev + 1, line.c_str() + cur + 1);
        } // if
        prev = cur;
    } // for

    if (!key.empty()) {
        value.append(line.c_str() + prev + 1);
        boost::trim_right_if(value, boost::is_any_of(SPACES));
        auto it = m_dictItemParser.find(key);
        if (it != m_dictItemParser.end())
            it->second->setAttr(key, value, req);
    } // if
}
// #endif

#if 0
void QsLogParser::parse(const std::string &line, LogReq &req)
{
    string::size_type posStart = line.find_first_of(']');
    THROW_RUNTIME_ERROR_IF(string::npos == posStart, "Invalid log");
    posStart += 2;

    istringstream iss(string(line, posStart));
    string item;

    while (iss >> item) {
        string::size_type sep = item.find_first_of('=');
        THROW_RUNTIME_ERROR_IF(string::npos == sep, 
                "no \"=\" found in item \"" << item << "\", log text: " << line);

        string key(item, 0, sep);
        string val(item, sep + 1);

        auto it = m_dictItemParser.find(key);
        if (it != m_dictItemParser.end())
            it->second->setAttr(key, val, req);
    } // while
}
#endif



