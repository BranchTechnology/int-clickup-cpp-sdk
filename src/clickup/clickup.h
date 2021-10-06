//
// Created by Jacques Perrault on 10/5/21.
//

#ifndef CLICKUP_SRC_CLICKUP_CLICKUP_H_
#define CLICKUP_SRC_CLICKUP_CLICKUP_H_

//#include <nlohmann/json.hpp>
#include <string>
#include "params.h"

class clickup
{
private:
public:
    std::string accessToken;
    std::string baseUrl = "https://api.clickup.com/api/v2/";

    explicit clickup(const std::string &region);

    void GetFolderlessList(const std::string &id);
    void GetFolders(const std::string &id);
    void GetTasksByListId(const std::string &id,
                                    GetTasksByListIdOptions paramsGetTasksByListId = GetTasksByListIdOptions());
//    void CreateTaskInList(const std::string &id, void body);
    void AddTaskToList(const string &listId, const string &taskId);
    void GetListCustomFields(const string &listId);
    void GetTaskById(const string &taskId);
};

#endif  // CLICKUP_SRC_CLICKUP_CLICKUP_H_
