#include "json/json.h"
#include <iostream>
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include <stdio.h>
using namespace std;

typedef websocketpp::server<websocketpp::config::asio>server;
void on_message(websocketpp::connection_hdl hadl,server::message_ptr msg) {
	string jsonStr = msg->get_payload();
	cout << "�յ���string�ǣ�" << jsonStr << endl;
	Json::Value newJson;
	Json::CharReaderBuilder builder;
	builder["collectiComments"] = false;
	JSONCPP_STRING errs;
	Json::CharReader* reader = builder.newCharReader();
	if (!reader->parse(jsonStr.data(), jsonStr.data() + jsonStr.size(), &newJson, &errs))//��jsonStr�ж�ȡ���ݵ�newJson
	{
		cout << "error" << endl;
		return;
	};
	cout << newJson << std::endl;
	cout << "json ��code �ǣ�" << newJson["code"] << endl;

	/*printf("msg:",msg->get_payload());
	std::cout << msg->get_payload() << std::endl;*/
	return;
};

void jsonStrReader(string jsonStr) {
	cout << "�յ���string�ǣ�" << jsonStr << endl;
	Json::Value newJson;
	Json::CharReaderBuilder builder;
	builder["collectiComments"] = false;
	JSONCPP_STRING errs;
	Json::CharReader* reader = builder.newCharReader();
	if (!reader->parse(jsonStr.data(), jsonStr.data() + jsonStr.size(), &newJson, &errs))//��jsonStr�ж�ȡ���ݵ�newJson
	{
		return;
	};
	jsonStr.clear();
	cout << newJson << endl;
	cout << "json ��uploadid �ǣ�" << newJson["uploadid"] << endl;
	system("pause");

};

void main() {
	jsonStrReader("{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}");
	server print_sever;
	print_sever.set_message_handler(&on_message);
	print_sever.init_asio();
	print_sever.listen(9002);
	print_sever.start_accept();
	print_sever.run();
}