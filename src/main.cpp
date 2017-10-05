#include <glog/logging.h>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <cstdio>
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


static
enum JobType {
    LOG2REQ, GEN_RULES, CLASSIFY, NOT_SPECIFIED
} g_eJobType = NOT_SPECIFIED;

static std::string      g_strLogFile;
static std::string      g_strRuleFile;
static std::string      g_strReqFile;
static std::string      g_strPrefix;


static
void log_2_req_json()
{
    cerr << "Convert log to request json..." << endl;
    if (g_strLogFile.empty())
        cerr << "logfile not specified, use stdin" << endl;
    if (g_strReqFile.empty())
        cerr << "reqfile not specified, use stdout" << endl;

    auto pInput = open_input(g_strLogFile);
    THROW_RUNTIME_ERROR_IF(!(*pInput), "log_2_req_json() cannot open log file \"" << g_strLogFile << "\" for reading!");
    auto pOutput = open_output(g_strReqFile);
    THROW_RUNTIME_ERROR_IF(!(*pOutput), "log_2_req_json() cannot open req file \"" << g_strReqFile << "\" for writting!");

    string      line;
    size_t      lineNO = 0;
    Json::Value root;
    std::shared_ptr<LogParser> parser = std::make_shared<QsLogParser>();
    while (getline(*pInput, line)) {
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

    *pOutput << Json::StyledWriter().write(root) << flush;
}


static
void gen_rules()
{
    cerr << "Generating classification rules..." << endl;
    if (g_strLogFile.empty())
        cerr << "logfile not specified, use stdin" << endl;
    if (g_strRuleFile.empty())
        cerr << "rule file not specified, use stdout" << endl;

    auto pInput = open_input(g_strLogFile);
    THROW_RUNTIME_ERROR_IF(!(*pInput), "gen_rules() cannot open log file \"" << g_strLogFile << "\" for reading!");
    auto pOutput = open_output(g_strRuleFile);
    THROW_RUNTIME_ERROR_IF(!(*pOutput), "gen_rules() cannot open rule file \"" << g_strRuleFile << "\" for writting!");

    string      line;
    size_t      lineNO = 0;

    std::shared_ptr<LogParser>  parser = std::make_shared<QsLogParser>();
    std::shared_ptr<LogReqCmp>  pLogCmp = std::make_shared<QsLogReqCmp>();
    LogReqClassifier            classifier(pLogCmp.get());

    while (getline(*pInput, line)) {
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
    // do {
        // Json::Value root;
        // for (auto pReq : classifier.classified()) {
            // Json::Value jsVal;
            // pReq->toJson(jsVal);
            // root.append(jsVal);
        // } // for
        // cout << Json::StyledWriter().write(root) << flush;
    // } while (0);
    
    do {
        auto pRule = std::make_shared<QsClassifyRule>();
        Json::Value root;
        classifier.toRules(pRule.get(), root);
        // cout << Json::StyledWriter().write(root) << flush;
        // cout << Json::FastWriter().write(root) << flush;
        for (auto &js : root)
            *pOutput << Json::FastWriter().write(js) << flush;
    } while (0);
}


static
void do_classify_log( const std::string &logFile,
            const std::string &ruleFile,
            const std::string &baseOutLogName = "")
{
    string      line;
    size_t      lineNO = 0;

    std::shared_ptr<LogReqCmp> pLogCmp = std::make_shared<QsLogReqCmp>();
    LogReqClassifier           classifier(pLogCmp.get());
    auto                       pRule = std::make_shared<QsClassifyRule>();
    Json::Reader               reader;

    // read rules
    cerr << "Loading rules..." << endl;
    auto pInput = open_input(ruleFile);
    THROW_RUNTIME_ERROR_IF(!(*pInput), "classify_log() cannot open \"" << ruleFile << "\" for reading!");
    while (getline(*pInput, line)) {
        ++lineNO;
        boost::trim(line);
        if (line.empty()) continue;
        Json::Value     jsVal;
        if (reader.parse(line, jsVal)) {
            auto pLogReq = std::make_shared<LogReq>();
            pRule->fromJson(*pLogReq, jsVal);
            classifier.addRule(pLogReq);
        } else {
            LOG(ERROR) << "Invalid json format in line " << lineNO << ", text: " << line;
            continue;
        } // if
    } // while
    pInput.reset();

    // classify log
    THROW_RUNTIME_ERROR_IF(!classifier.nRules(), "classify_log() No classify rules specified!");

    // init output files
    char buf[20];
    vector<std::shared_ptr<std::ostream> >     outFiles(classifier.nRules());
    for (int i = 0; (size_t)i < classifier.rules().size(); ++i) {
        snprintf(buf, 20, "%02d.log", (i + 1));
        string fname = baseOutLogName + buf;
        outFiles[i] = open_output(fname);
        THROW_RUNTIME_ERROR_IF(!(*outFiles[i]), "classifyLog cannot open \"" << fname << "\" for writting!");
    } // for i

    // read log and classify
    cerr << "classifying log..." << endl;
    std::shared_ptr<LogParser> parser = std::make_shared<QsLogParser>();
    pInput = open_input(logFile);
    THROW_RUNTIME_ERROR_IF(!(*pInput), "classify_log() cannot open \"" << logFile << "\" for reading!");

    lineNO = 0;
    while (getline(*pInput, line)) {
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
        
        // 没有重复 找到一条不再继续找
        // int idx = classifier.getRuleId(pReq);
        // if (-1 == idx) {
            // LOG(ERROR) << "Error in line " << lineNO << ", cannot get the class id of this log! text: " << line;
            // continue;
        // } // if
        // *outFiles[idx] << line << endl;
        
        // 可能有重复 找出全部的match
        bool found = false;
        for (size_t i = 0; i < classifier.nRules(); ++i) {
            if (pLogCmp->equals(pReq, classifier.rules()[i])) {
                found = true;
                *outFiles[i] << line << endl;
            } // if
        } // for
        if (!found) {
            LOG(ERROR) << "Error in line " << lineNO << ", cannot get the class id of this log! text: " << line;
        } // if
    } // while
    pInput.reset();
}


static
void classify_log()
{
    cerr << "Classify log..." << endl;

    if (g_strLogFile.empty())
        cerr << "logfile not specified, use stdin" << endl;

    if (g_strRuleFile.empty()) {
        cerr << "rule file not specified!" << endl;
        exit(-1);
    } // if

    do_classify_log(g_strLogFile, g_strRuleFile, g_strPrefix);
}


static
void parse_args(int argc, char **argv)
{
    namespace po = boost::program_options;

    po::options_description desc(
        BUILD_STRING("Example:\n" << 
            argv[0] << " --log2req --log-file $logfile --req-file $reqfile\n" <<
            argv[0] << " --gen-rules --log-file $logfile --rule-file $rulefile\n" <<
            argv[0] << " --classify --log-file $logfile --rule-file $rulefile --prefix $prefix\n" <<
            "\nOptions")
    );

    desc.add_options()
        ("log2req,Q", po::bool_switch()->
                notifier([&](bool flag){
                    if(flag) g_eJobType = LOG2REQ;
                }), "Convert log to online request (json)")
        ("gen-rules,R", po::bool_switch()->
                notifier([&](bool flag){
                    if(flag) g_eJobType = GEN_RULES;
                }), "generate rules that can classify log")
        ("classify,C", po::bool_switch()->
                notifier([&](bool flag){
                    if(flag) g_eJobType = CLASSIFY;
                }), "classify log based on rules")
        ("log-file,l", po::value<string>(&g_strLogFile), "log file")
        ("rule-file,r", po::value<string>(&g_strRuleFile), "json rules file")
        ("req-file,q", po::value<string>(&g_strReqFile), "requests in json file")
        ("prefix,p", po::value<string>(&g_strPrefix), "prefix file name for classification result files");

    if (argc <= 1) {
        cout << desc << endl;
        exit(0);
    } // if

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
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
    
    parse_args(argc, argv);

    if (g_eJobType >= NOT_SPECIFIED) {
        cerr << "No job specified" << endl;
        exit(-1);
    } // if

    typedef std::function<void(void)>   JobFunc;
    map<int, JobFunc>   jobs = {
        {LOG2REQ, log_2_req_json},
        {GEN_RULES, gen_rules},
        {CLASSIFY, classify_log}
    };

    auto pfn = jobs[g_eJobType];
    THROW_RUNTIME_ERROR_IF(!pfn, "Invalid job type!");
    pfn();

    return 0;

} catch (const std::exception &ex) {
    std::cerr << "Exception caught by main: " << ex.what() << std::endl;
    return -1;
}


