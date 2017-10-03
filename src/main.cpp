#include <string>
#include <map>
#include <glog/logging.h>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include "CommDef.h"
#include "LogParser.h"
#include "LogReqClassifier.h"

using namespace std;

namespace Test {
void test()
{
    // LogParser     LogParser;
    // LogParser.log2Json("");
    // LogParser.writeJson("");
    
#if 0
    // cout << "Json test" << endl;
    // cout << LogParser.jsonLog().size() << endl;
    for (Json::ArrayIndex i = 0; i < LogParser.jsonLog().size(); ++i) {
        Json::Value &item = LogParser.jsonLog()[i];
        for (Json::Value::iterator it = item.begin(); it != item.end(); ++it) {
            if (it->isObject())
                cout << it.key() << " is object" << endl;
            else
                cout << it.key() << " is not object" << endl;
            // cout << boost::format("%s = %s") % it.key().asString() % it->asString() << endl;
            // cout << it.key() << endl;
        } // for
        // for (const auto &key : item.getMemberNames()) {
            // cout << key << endl;
        // } // for key
    } // for i
    
    // for (const auto &key : LogParser.jsonLog().getMemberNames())
        // cout << key << endl;
        // cout << boost::format("%s = %s") % key % LogParser.jsonLog().get(key, Json::Value()) << endl;
#endif
}

// Thrift's json not readable

void test_log_request()
{
    LogReq logReq;
    logReq.setAttr("query", "美食");
    logReq.setAttr("orderby", "@asc");
    logReq.setAttr("cityid", 1234);
    logReq.setAttr("reqid", 10020);
    cout << logReq.m_SearchQueryReq << endl;
}

void test_map2json()
{
    map<string, string> dict;
    dict["key_words"] = "美食";
    dict["location"] = "123.15,255,45";

    Json::Value val = std::move(LogReq::Map2Json(dict));
    cout << Json::StyledWriter().write(val) << endl;
}

void test_parse_map()
{
    std::shared_ptr<LogParser> parser = std::make_shared<QsLogParser>();
    map<string, string> result;
    string text = "hasGroup:1,results:1";
    parser->parse_dict(text, result);

    for (const auto &kv : result)
        cout << kv.first << " = " << kv.second << endl;
}

void test_cmp_string_map()
{
    LogReqCmp::StringMap m1, m2;
    m1["a"] = "1";
    m1["b"] = "2";
    m1["c"] = "3";
    m2["a"] = "1";
    m2["b"] = "3";
    m2["c"] = "3";
    // m2["d"] = "4";

    cout << LogReqCmp::cmp_string_map(m1, m2) << endl;
    cout << LogReqCmp::cmp_string_map_key_only(m1, m2) << endl;
}
} // namespace Test

void log_2_req_json()
{
    string      line;
    size_t      lineNO = 0;
    Json::Value root;
    std::shared_ptr<LogParser> parser = std::make_shared<QsLogParser>();
    while (getline(cin, line)) {
        ++lineNO;
        boost::trim(line);
        if (line.empty()) continue;
        LogReq      req;
        Json::Value jsVal;
        try {
            parser->parse(line, req);
        } catch (const std::exception &ex) {
            LOG(ERROR) << "Error in line " << lineNO << "! " << ex.what();
            continue;
        } // try
        // cout << req.query() << endl << endl;;
        // cout << req.toJson() << endl;
        req.setNO(lineNO);
        req.toJson(jsVal);
        root.append(jsVal);
    } // while

    cout << Json::StyledWriter().write(root) << flush;
}


void log_classify()
{
    string      line;
    size_t      lineNO = 0;

    std::shared_ptr<LogParser>  parser = std::make_shared<QsLogParser>();
    std::shared_ptr<LogReqCmp>  pLogCmp = std::make_shared<QsLogReqCmp>();
    LogReqClassifier            classifier(pLogCmp.get());

    while (getline(cin, line)) {
        ++lineNO;
        boost::trim(line);
        if (line.empty()) continue;
        auto pReq = std::make_shared<LogReq>();
        try {
            parser->parse(line, *pReq);
        } catch (const std::exception &ex) {
            LOG(ERROR) << "Error in line " << lineNO << "! " << ex.what();
            continue;
        } // try
        pReq->setNO(lineNO);
        classifier.addItem(pReq);
    } // while

    LOG(INFO) << classifier.classified().size() << " classified requests.";
    Json::Value root;
    for (auto pReq : classifier.classified()) {
        Json::Value jsVal;
        pReq->toJson(jsVal);
        root.append(jsVal);
    } // for
    cout << Json::StyledWriter().write(root) << flush;
}

int main(int argc, char **argv)
try {
    google::InitGoogleLogging(argv[0]);

    // Test::test();
    // Test::test_serialize();
    // Test::test_log_request();
    // Test::test_map2json();
    // Test::test_parse_map();
    // Test::test_cmp_string_map();
    // exit(0);
    // log_2_req_json();
    log_classify();

    return 0;

} catch (const std::exception &ex) {
    std::cerr << "Exception caught by main: " << ex.what() << std::endl;
    return -1;
}


