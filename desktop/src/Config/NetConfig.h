#ifndef NETCONFIG_H
#define NETCONFIG_H

#include <regex>
#include <string>

namespace NetConfig {
    static std::string request_protocol;                // 使用的请求协议,可用的有"http"和"https"
    static int protocol_version;                        // 使用的协议版本
    static std::string server_address;                  // 服务器地址
    static std::string port;                            // 使用的端口号,例如"80"
    static std::string base_path;                       // 基础地址方便后续使用

    inline bool set_net_config(std::string path) {
        if (path.empty())
            return false;

        std::regex regex(R"(^((http|https):\/\/)?([\w.-]+)(:\d+)?(\/.*)?$)");
        std::smatch match;

        if (std::regex_match(path, match, regex) == false)
            return false;

        base_path = path + "/TanCloud";
        request_protocol = match[2].str().empty()? "http" : match[2].str();
        server_address = match[3].str();
        port = match[5].str().empty() ? (request_protocol == "https" ? "443" : "80") : match[5].str();

        return true;
    }
}
#endif // NETCONFIG_H
