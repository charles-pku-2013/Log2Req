#ifndef _LOG_REQ_CLASSIFIER_H_
#define _LOG_REQ_CLASSIFIER_H_

#include "LogReq.h"
#include <set>
#include <map>
#include <vector>


class LogReqCmp {
public:
    typedef std::map<std::string, std::string>      StringMap;
public:
    virtual int compare(const LogReq::pointer &lhs, const LogReq::pointer &rhs) const = 0;

    virtual int equals(const LogReq::pointer &lhs, const LogReq::pointer &rhs) const
    { return (!(compare(lhs, rhs) < 0) && !(compare(rhs, lhs) < 0)); }
    
    // compare key and value
    static int cmp_string_map(const StringMap &lhs, const StringMap &rhs);
    // only compare key
    static int cmp_string_map_key_only(const StringMap &lhs, const StringMap &rhs);
};


// TODO 业务相关
class QsLogReqCmp : public LogReqCmp {
public:
    int compare(const LogReq::pointer &lhs, const LogReq::pointer &rhs) const override;
private:
    int cmpSearchQueryReq(const SearchQueryReq &lhs, const SearchQueryReq &rhs) const;
};


class ClassifyRule {
public:
    virtual void toJson(const LogReq::pointer &pReq, Json::Value &js) const = 0;
    virtual void fromJson(LogReq &logReq, const Json::Value &js) const = 0;
};

// TODO 业务相关
class QsClassifyRule : public ClassifyRule {
public:
    void toJson(const LogReq::pointer &pReq, Json::Value &js) const override;
    void fromJson(LogReq &logReq, const Json::Value &js) const override;
};


class LogReqClassifier {
public:
    struct Comparator {
        explicit Comparator(const LogReqCmp *pCmp) : cmp_(pCmp) {}

        bool operator()(const LogReq::pointer &lhs, const LogReq::pointer &rhs)
        { return (cmp_->compare(lhs, rhs) < 0); }

        const LogReqCmp* getLogReqCmp() const { return cmp_; }

        const LogReqCmp *cmp_;
    };

public:
    explicit LogReqClassifier(const LogReqCmp *pCmp)
            : m_setClassified(Comparator(pCmp)) {}

    bool addItem(const LogReq::pointer &pItem)
    {
        auto ret = m_setClassified.insert(pItem);
        return ret.second;
    }

    void toRules(const ClassifyRule *pRule, Json::Value &root) const;

    void addRule(const LogReq::pointer &pReq)
    { m_vecRules.push_back(pReq); }

    std::set<LogReq::pointer, Comparator>& classified()
    { return m_setClassified; }
    const std::set<LogReq::pointer, Comparator>& classified() const
    { return m_setClassified; }

    int getRuleId(const LogReq::pointer &pLogReq);

    std::vector<LogReq::pointer>& rules() { return m_vecRules; }
    const std::vector<LogReq::pointer>& rules() const { return m_vecRules; }
    std::size_t nRules() const { return m_vecRules.size(); }

private:
    std::set<LogReq::pointer, Comparator>   m_setClassified;
    std::vector<LogReq::pointer>            m_vecRules;
};



#endif /* _LOG_REQ_CLASSIFIER_H_ */

