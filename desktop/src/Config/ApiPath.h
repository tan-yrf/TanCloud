#ifndef APIPATH_H
#define APIPATH_H

#include <string>

namespace ApiPath {
    inline const std::string c_login = "/user/login";
    inline const std::string c_get_dir_info = "/fs/get_directory_info";
    inline const std::string c_create_folder = "/fs/create_folder";
    inline const std::string c_delete_complete = "/fs/delete";
}
#endif // APIPATH_H
