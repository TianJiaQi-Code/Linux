#pragma once

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

const std::string blank_space_sep = " ";
const std::string protocol_sep = "\n";

std::string Encode(std::string &content)
{
    std::string package = std::to_string(content.size());
    package += protocol_sep;
    package += content;
    package += protocol_sep;
    return package;
}

bool Decode(std::string &package, std::string *content)
{
    std::size_t pos = package.find(protocol_sep);
    if (pos == std::string::npos)
        return false;
    std::string len_str = package.substr(0, pos);
    std::size_t len = std::stoi(len_str);
    std::size_t total_len = len_str.size() + len + 2;
    if (package.size() < total_len)
        return false;

    *content = package.substr(pos + 1, len);
    package.erase(0, total_len);

    return true;
}

class Request
{
public:
    Request()
    {
    }
    Request(int data1, int data2, char oper)
        : x(data1), y(data2), op(oper)
    {
    }
    ~Request()
    {
    }

public:
    bool Serialize(std::string *out)
    {
        Json::Value root;
        root["x"] = x;
        root["y"] = y;
        root["op"] = op;
        Json::StyledWriter w;
        *out = w.write(root);
        return true;
    }
    bool Deserialize(const std::string &in)
    {
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);

        x = root["x"].asInt();
        y = root["y"].asInt();
        op = root["op"].asInt();
        return true;
    }
    void DebugPrint()
    {
        std::cout << "新请求构建完成: " << x << op << y << "=?" << std::endl;
    }

public:
    int x;
    int y;
    char op; // + - * / %
};

class Response
{
public:
    Response(int res, int c)
        : result(res), code(c)
    {
    }
    ~Response()
    {
    }

public:
    bool Serialize(std::string *out)
    {
        Json::Value root;
        root["result"] = result;
        root["code"] = code;
        Json::StyledWriter w;
        *out = w.write(root);
        return true;
    }
    bool Deserialize(const std::string &in)
    {
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);

        result = root["result"].asInt();
        code = root["code"].asInt();
        return true;
    }
    void DebugPrint()
    {
        std::cout << "结果响应完成, result: " << result << ", code: " << code << std::endl;
    }

public:
    int result;
    int code;
};