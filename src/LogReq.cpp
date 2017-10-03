#include "LogReq.h"


void LogReq::SearchQueryReq2Json(Json::Value &root, const SearchQueryReq &req)
{
    root["key_words"] = req.key_words;
    root["city"] = req.city;
    root["category"] = req.category;
    root["cityid"] = req.cityid;
    root["id"] = req.id;
    root["offset"] = req.offset;
    root["limit"] = req.limit;
    root["location"] = req.location;
    root["orderby"] = req.orderby;
    root["opt"] = req.opt;
    root["filter"] = std::move(Map2Json(req.filter));
    root["counter"] = std::move(Map2Json(req.counter));
    root["control"] = std::move(Map2Json(req.control));
    root["exdata"] = std::move(Map2Json(req.exdata));
}

void LogReq::toJson(Json::Value &root) const
{
    root.clear();
    root["LogNO"] = m_nNO;
    SearchQueryReq2Json(root, m_SearchQueryReq);
    root["if_name"] = m_strIfName;
}

std::string LogReq::toJson(bool concise) const
{
    Json::Value  root;
    toJson(root);
    if (concise)
        return Json::FastWriter().write(root);
    return Json::StyledWriter().write(root);
}

