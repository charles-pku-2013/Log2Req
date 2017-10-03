#include "LogReqClassifier.h"
#include <glog/logging.h>

/*
 * 不需要的字段在读入log时已经去除了，这里只比较需要的字段
 */

using namespace std;

int LogReqCmp::cmp_string_map(const QsLogReqCmp::StringMap &lhs, const QsLogReqCmp::StringMap &rhs)
{
    int retval = 0;
    auto it1 = lhs.begin();
    auto it2 = rhs.begin();

    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        // compare key
        retval = it1->first.compare(it2->first);
        if (retval) { // key not equal
            return retval;
        } else { // key equals, compare value
            retval = it1->second.compare(it2->second);
            if (retval) 
                return retval;
        } // if retval
    } // for

    if (it1 != lhs.end())
        retval = 1;
    else if (it2 != rhs.end())
        retval = -1;

    return retval;
}

int LogReqCmp::cmp_string_map_key_only(const QsLogReqCmp::StringMap &lhs, const QsLogReqCmp::StringMap &rhs)
{
    int retval = 0;
    auto it1 = lhs.begin();
    auto it2 = rhs.begin();

    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        // compare key
        retval = it1->first.compare(it2->first);
        if (retval) return retval;
    } // for

    if (it1 != lhs.end())
        retval = 1;
    else if (it2 != rhs.end())
        retval = -1;

    return retval;
}

int QsLogReqCmp::compare(const LogReq::pointer &lhs, const LogReq::pointer &rhs) const
{
    int retval = 0;
    
    retval = cmpSearchQueryReq(lhs->query(), rhs->query());
    if (retval) return retval;

    // 除了SearchQueryReq之外的log字段
    retval = lhs->ifName().compare(rhs->ifName());

    return retval;
}

int QsLogReqCmp::cmpSearchQueryReq(const SearchQueryReq &lhs, const SearchQueryReq &rhs) const
{
    int retval = 0;

    // first cmp id
    if ((retval = lhs.id - rhs.id))
        return retval;

    // cmp orderby
    if ((retval = lhs.orderby.compare(rhs.orderby)))
        return retval;

    // filter, counter only cmp key
    retval = cmp_string_map_key_only(lhs.filter, rhs.filter);
    if (retval) return retval;
    retval = cmp_string_map_key_only(lhs.counter, rhs.counter);
    if (retval) return retval;

    // control, exdata cmp key and value
    retval = cmp_string_map(lhs.control, rhs.control);
    if (retval) return retval;
    retval = cmp_string_map(lhs.exdata, rhs.exdata);
    if (retval) return retval;

    return retval;
}


void LogReqClassifier::toRules(const ClassifyRule *pRule, Json::Value &root) const
{
    root.clear();

    for (auto pReq : m_setClassified) {
        Json::Value jsVal;
        pRule->toJson(pReq, jsVal);
        root.append(jsVal);
    } // for
}


void QsClassifyRule::toJson(const LogReq::pointer &pReq, Json::Value &js) const
{
    js.clear();

    js["if_name"] = pReq->ifName();
    js["id"] = pReq->query().id;
    js["orderby"] = pReq->query().orderby;

    // filter, counter only cmp key
    if (!pReq->query().filter.empty()) {
        for (auto &kv : pReq->query().filter)
            js["filter"].append(kv.first);
    } // if
    if (!pReq->query().counter.empty()) {
        for (auto &kv : pReq->query().counter)
            js["counter"].append(kv.first);
    } // if

    // control, exdata cmp key and value
    if (!pReq->query().control.empty()) {
        auto &jsControl = js["control"];
        for (auto &kv : pReq->query().control)
            jsControl[kv.first] = kv.second;
    } // if
    if (!pReq->query().exdata.empty()) {
        auto &jsExData = js["exdata"];
        for (auto &kv : pReq->query().exdata)
            jsExData[kv.first] = kv.second;
    } // if
}

void QsClassifyRule::fromJson(LogReq &logReq, const Json::Value &js) const
{
    logReq.setAttr("if_name", js["if_name"].asString());
    logReq.setAttr("reqid", js["id"].asInt());
    logReq.setAttr("orderby", js["orderby"].asString());

    // filter, counter only key
    auto &jsFilter = js["filter"];
    if (!!jsFilter) {
        map<string, string>     dict;
        for (Json::ArrayIndex i = 0; i < jsFilter.size(); ++i) {
            dict[jsFilter[i].asString()] = "";
        } // for
        logReq.setAttr("filter", dict);
    } // if
    auto &jsCounter = js["counter"];
    if (!!jsCounter) {
        map<string, string>     dict;
        for (Json::ArrayIndex i = 0; i < jsCounter.size(); ++i) {
            dict[jsCounter[i].asString()] = "";
        } // for
        logReq.setAttr("counter", dict);
    } // if

    // control, exdata cmp key and value
    auto &jsControl = js["control"];
    if (!!jsControl) {
        map<string, string>     dict;
        for (auto it = jsControl.begin(); it != jsControl.end(); ++it) {
            dict[it.key().asString()] = it->asString();
        } // for
        logReq.setAttr("control", dict);
    } // if
    auto &jsExData = js["exdata"];
    if (!!jsExData) {
        map<string, string>     dict;
        for (auto it = jsExData.begin(); it != jsExData.end(); ++it) {
            dict[it.key().asString()] = it->asString();
        } // for
        logReq.setAttr("ext_data", dict);
    } // if

    // LOG(INFO) << logReq.toJson(true);
}


int LogReqClassifier::getRuleId(const LogReq::pointer &pLogReq)
{
    auto cmp = m_setClassified.key_comp().getLogReqCmp();

    for (int i = 0; (size_t)i < m_vecRules.size(); ++i) {
        if (cmp->equals(pLogReq, m_vecRules[i]))
            return i;
    } // for

    return -1;
}

#if 0
void LogReqClassifier::classifyLog(const std::string &baseName)
{
    if (m_vecRules.empty()) return;

    char buf[20];

    vector<std::shared_ptr<std::ofstream> >     outFiles(m_vecRules.size());
    
    for (int i = 0; (size_t)i < m_vecRules.size(); ++i) {
        snprintf(buf, 20, "%02d.log", (i + 1));
        string fname = baseName + buf;
        outFiles[i].reset(new ofstream(fname));
        THROW_RUNTIME_ERROR_IF(!(*outFiles[i]), "classifyLog cannot open \"" << fname << "\" for writting!");
    } // for i
}
#endif

