#include <regex>

#include "NetConfig.h"

std::string NetConfig::request_protocol;
int NetConfig::protocol_version;
std::string NetConfig::server_address;
std::string NetConfig::port;
std::string NetConfig::base_path;

bool NetConfig::set_net_config(std::string path) {
    if (path.empty())
        return false;

    std::regex regex(R"(^((http|https):\/\/)?([\w.-]+)(:(\d+))?(\/.*)?$)");
    std::smatch match;

    if (std::regex_match(path, match, regex) == false)
        return false;

    base_path = path + "/TanCloud";
    request_protocol = match[2].str().empty()? "http" : match[2].str();
    protocol_version = 11;
    server_address = match[3].str();
    port = match[5].str().empty() ? (request_protocol == "https" ? "443" : "80") : match[5].str();

    return true;
}
