#include "LogReqClassifier.h"
#include <glog/logging.h>

/*
 * 不需要的字段在读入log时已经去除了，这里只比较需要的字段
 */

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


