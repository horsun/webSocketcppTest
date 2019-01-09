#include "json/json.h"
#include <iostream>
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include <stdio.h>
#include <list>

using namespace std;


class MyJson {
public:

    void writeJson() {
        // key & value
        // type list
        Json::Value root;
        Json::Value arrayObj;
        Json::Value item;

        item["cpp"] = "jsoncpp";
        item["java"] = "jsoninjava";
        item["php"] = "support";
        arrayObj.append(item);

        root["name"] = "json";
        root["array"] = arrayObj;
/*
		root.toStyledString();
		string out = root.toStyledString();*/
        cout <<   root << endl;
    };
    void addObj() {

    };
    void toString() {

    };
    void jsonStrReader(string jsonStr) {
        cout << "收到的string是：" << jsonStr << endl;
        Json::Value newJson;
        Json::CharReaderBuilder builder;
        builder["collectiComments"] = false;
        JSONCPP_STRING errs;
        Json::CharReader* reader = builder.newCharReader();
        if (!reader->parse(jsonStr.data(), jsonStr.data() + jsonStr.size(), &newJson, &errs))//从jsonStr中读取数据到newJson
        {
            return;
        };
        jsonStr.clear();
        cout <<"解析后的json：\n"<< newJson << endl;
        cout << "json 的uploadid 是：" << newJson["uploadid"] << endl;
        cout << ">>>>>>>>>>>>>>>" << endl;
    };
};


typedef websocketpp::server<websocketpp::config::asio>server;
void on_message(websocketpp::connection_hdl hadl, server::message_ptr msg) {
    string jsonStr = msg->get_payload();
    MyJson testJSon;
    testJSon.jsonStrReader(jsonStr);
};




void main() {
    MyJson json;
    json.jsonStrReader("{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}");
    json.writeJson();
    cout << "服务正在启动 ws://127.0.0.1:9002" << endl;
    server print_sever;
    print_sever.set_message_handler(&on_message);
    print_sever.init_asio();
    print_sever.listen(9002);
    print_sever.start_accept();
    print_sever.run();
}
