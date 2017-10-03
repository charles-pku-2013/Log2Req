#ifndef _LOG_REQ_CLASSIFIER_H_
#define _LOG_REQ_CLASSIFIER_H_

#include "LogReq.h"
#include <set>
#include <map>


class LogReqCmp {
public:
    typedef std::map<std::string, std::string>      StringMap;
public:
    virtual int compare(const LogReq::pointer &lhs, const LogReq::pointer &rhs) const = 0;
    
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


class LogReqClassifier {
public:
    struct Comparator {
        explicit Comparator(const LogReqCmp *pCmp) : cmp_(pCmp) {}

        bool operator()(const LogReq::pointer &lhs, const LogReq::pointer &rhs)
        { return (cmp_->compare(lhs, rhs) < 0); }

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

    std::set<LogReq::pointer, Comparator>& classified()
    { return m_setClassified; }
    const std::set<LogReq::pointer, Comparator>& classified() const
    { return m_setClassified; }

private:
    std::set<LogReq::pointer, Comparator>   m_setClassified;
};



#endif /* _LOG_REQ_CLASSIFIER_H_ */

