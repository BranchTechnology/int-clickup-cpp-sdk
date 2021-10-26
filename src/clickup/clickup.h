//
// Created by Jacques Perrault on 10/5/21.
//

#ifndef CLICKUP_SRC_CLICKUP_CLICKUP_H_
#define CLICKUP_SRC_CLICKUP_CLICKUP_H_

#include <nlohmann/json.hpp>
#include <future>
#include <string>
#include "params.h"

class clickup
{
private:
public:
    std::string accessToken;
    std::string baseUrl = "https://api.clickup.com/api/v2/";
    clickup();
    explicit clickup(const std::string &userToken);
    void getToken(const std::string &userToken = "ACCESS_TOKEN");
    nlohmann::json GetFolderlessList(const std::string &id);
    std::future<nlohmann::json> AsyncGetFolderlessList(const std::string &id);
    nlohmann::json GetFolders(const std::string &id);
    nlohmann::json GetTasksByListId(const std::string &id,
                                    GetTasksByListIdOptions paramsGetTasksByListId = GetTasksByListIdOptions());
    nlohmann::json CreateTaskInList(const std::string &id, nlohmann::json body);
    nlohmann::json AddTaskToList(const string &listId, const string &taskId);
    nlohmann::json GetListCustomFields(const string &listId);
    nlohmann::json GetTaskById(const string &taskId);
};

#endif  // CLICKUP_SRC_CLICKUP_CLICKUP_H_
