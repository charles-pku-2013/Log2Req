#ifndef _LOG_REQ_H_
#define _LOG_REQ_H_

#include "MTSearch.h"
#include <memory>

#ifdef ONLINE
#include <jsoncpp/json/json.h>
#else
#include <json/json.h>
#endif


class LogReq {
public:
    typedef std::shared_ptr<LogReq>     pointer;

public:
    typedef void (SearchQueryReq::*StringSetter)(const std::string&);
    typedef void (SearchQueryReq::*IntSetter)(const int32_t);
    typedef void (SearchQueryReq::*DictSetter)(const std::map<std::string, std::string>&);

public:
    template<typename T>
    void setAttr(const std::string &key, const T &val)
    {
        if (!setSearchQueryReq(key, val))
            setAttrHelper(key, val);
    }

    std::string toJson(bool concise = false) const;
    void toJson(Json::Value &root) const;

    static void SearchQueryReq2Json(Json::Value &root, const SearchQueryReq &req);

    template<typename MapType>
    static Json::Value Map2Json(const MapType &dict)
    {
        Json::Value ret;
        for (const auto &kv : dict)
            ret[kv.first] = kv.second;
        return ret;
    }

public:
    bool setSearchQueryReq(const std::string &key, const std::string &val)
    {
        auto it = m_mapSearchReqSetterString.find(key);
        if (it == m_mapSearchReqSetterString.end())
            return false;
        (m_SearchQueryReq.*(it->second))(val);
        return true;
    }

    bool setSearchQueryReq(const std::string &key, const int32_t val)
    {
        auto it = m_mapSearchReqSetterInt.find(key);
        if (it == m_mapSearchReqSetterInt.end())
            return false;
        (m_SearchQueryReq.*(it->second))(val);
        return true;
    }

    bool setSearchQueryReq(const std::string &key, const std::map<std::string, std::string> &val)
    {
        auto it = m_mapSearchReqSetterDict.find(key);
        if (it == m_mapSearchReqSetterDict.end())
            return false;
        (m_SearchQueryReq.*(it->second))(val);
        return true;
    }

    // 除了string之外，都是空实现
    template<typename T>
    void setAttrHelper(const std::string &key, const T &val) {}

    // 特化模板，string类型特殊处理
    void setAttrHelper(const std::string &key, const std::string &val)
    {
        if ("if_name" == key)
            m_strIfName = val;
    }

    SearchQueryReq& query() { return m_SearchQueryReq; }
    const SearchQueryReq& query() const { return m_SearchQueryReq; }

    const std::string& ifName() const { return m_strIfName; }

    void setNO(std::size_t no)
    {m_nNO = no;}
    std::size_t logNO() const 
    { return m_nNO; }

public:
    std::size_t         m_nNO = 0;
    // 独有的成员
    std::string         m_strIfName;

    SearchQueryReq      m_SearchQueryReq;

    const std::map<std::string, StringSetter> m_mapSearchReqSetterString = {
        {"query", &SearchQueryReq::__set_key_words},
        {"city", &SearchQueryReq::__set_city},
        {"category", &SearchQueryReq::__set_category},
        {"location", &SearchQueryReq::__set_location},
        {"orderby", &SearchQueryReq::__set_orderby}
    };

    const std::map<std::string, IntSetter> m_mapSearchReqSetterInt = {
        {"cityid", &SearchQueryReq::__set_cityid},
        {"reqid", &SearchQueryReq::__set_id},
        {"offset", &SearchQueryReq::__set_offset},
        {"limit", &SearchQueryReq::__set_limit}
    };

    const std::map<std::string, DictSetter> m_mapSearchReqSetterDict = {
        {"filter", &SearchQueryReq::__set_filter},
        {"counter", &SearchQueryReq::__set_counter},
        {"control", &SearchQueryReq::__set_control},
        {"ext_data", &SearchQueryReq::__set_exdata}
    };
};



#endif /* _LOG_REQ_H_ */

