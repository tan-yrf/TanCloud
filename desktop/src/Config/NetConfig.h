#ifndef NETCONFIG_H
#define NETCONFIG_H

#include <string>

struct NetConfig {
    static std::string request_protocol;                // 使用的请求协议,可用的有"http"和"https"
    static int protocol_version;                        // 使用的协议版本
    static std::string server_address;                  // 服务器地址
    static std::string port;                            // 使用的端口号,例如"80"
    static std::string base_path;                       // 基础地址方便后续使用

    static bool set_net_config(std::string path);
};
#endif // NETCONFIG_H
