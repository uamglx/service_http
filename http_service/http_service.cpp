// http_service.cpp: 定义应用程序的入口点。
//

#include "http_service.h"
#include "../json/include/nlohmann/json.hpp"
#include <iostream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

void string2num(string str, double &num)
{
	stringstream ss;
	ss << str;
	ss >> num;
}

int main(void)
{
	using namespace httplib;
	Server svr;
	svr.set_base_dir("../../http_service");
	svr.Post("/add", [](const Request& req, Response& res) {
		json j;
		int ans = atof(req.get_param_value("a").c_str())*atof(req.get_param_value("b").c_str());
		j["ans"] = ans;
		res.set_content(j.dump(), "text/plain");
		//res.set_content_provider();
	});
	svr.Get("/add", [](const Request& req, Response& res) {
		json j;
		double a, b;
		string2num(req.get_param_value("a").c_str(), a);
		string2num(req.get_param_value("b").c_str(), b);
		double ans = a + b;
		j["ans"] = ans;
		res.set_content(j.dump(), "text/plain");
		//res.set_content_provider();
	});
	svr.Get("/selectAllBook", [](const Request& req, Response& res) {
		int ans = atoi(req.get_param_value("a").c_str())*atoi(req.get_param_value("b").c_str());
		json j;
		j["id"] = 123;
		j["bookName"] = "234";
		j["bookPrice"] = "345";
		res.set_content(j.dump(), "text/plain");
		//res.set_content_provider();
	});
	svr.Get("/users.json", [](const Request& req, Response& res) {
		int ans = atoi(req.get_param_value("a").c_str())*atoi(req.get_param_value("b").c_str());
		json j,c;
		
		j["id"] = "123";
		j["sex"] = "234";
		j["height"] = "345";
		c.emplace_back(j);
		c.emplace_back(j);
		cout << c.dump() << endl;
		res.set_content(c.dump(), "text/plain");;
	});
	svr.listen("localhost", 3333);
}