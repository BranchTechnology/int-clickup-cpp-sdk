//
// Created by Jacques Perrault on 10/5/21.
//
#include <iostream>
#include <cpr/response.h>
#include <cpr/api.h>
#include "clickup.h"

#include <exception>

using namespace std;
using namespace cpr;

struct RequestException : public exception
{
    string message;
    int code;
    RequestException(string iMessage, int iCode = 400)
    {
        message = iMessage;
        code = iCode;
    }
    [[nodiscard]] const char *what() const noexcept { return message.c_str(); }

    void printError() const noexcept { cout << " - message: " + message + "\n- code: " + to_string(code); }
};

clickup::clickup(const std::string &userToken)
{
    accessToken = userToken;
}
nlohmann::json clickup::GetFolderlessList(const string &id)
{
    try {
        Response r = Get(Url{baseUrl + "space/" + id + "/list"}, Header{{"authorization", accessToken}});

        if (r.status_code != 200) {
            throw RequestException(r.error.message, r.status_code);
        }
        return nlohmann::json::parse(r.text);
    } catch (RequestException &e) {
        e.printError();
        throw e;
    } catch (std::exception &e) {
        cout << "unknown exception: " << e.what() << endl;
        throw e;
    }
}

nlohmann::json clickup::GetFolders(const string &id)
{
    try {
        Response r = Get(Url{baseUrl + "space/" + id + "/folder"}, Header{{"authorization", accessToken}});

        if (r.status_code != 200) {
            throw RequestException(r.text, r.status_code);
        }
        return nlohmann::json::parse(r.text);
    } catch (RequestException &e) {
        e.printError();
        throw e;
    } catch (std::exception &e) {
        cout << "unknown exception: " << e.what() << endl;
        throw e;
    }
}

nlohmann::json clickup::GetListCustomFields(const string &listId)
{
    try {
        Response r = Get(Url{baseUrl + "list/" + listId + "/field"}, Header{{"authorization", accessToken}});

        if (r.status_code != 200) {
            throw RequestException(r.text, r.status_code);
        }
        return nlohmann::json::parse(r.text);
    } catch (RequestException &e) {
        e.printError();
        throw e;
    } catch (std::exception &e) {
        cout << "unknown exception: " << e.what() << endl;
        throw e;
    }
}

nlohmann::json clickup::GetTaskById(const string &taskId)
{
    try {
        Response r = Get(Url{baseUrl + "task/" + taskId}, Header{{"authorization", accessToken}});

        if (r.status_code != 200) {
            throw RequestException(r.text, r.status_code);
        }
        return nlohmann::json::parse(r.text);
    } catch (RequestException &e) {
        e.printError();
        throw e;
    } catch (std::exception &e) {
        cout << "unknown exception: " << e.what() << endl;
        throw e;
    }
}

nlohmann::json clickup::GetTasksByListId(const string &id, GetTasksByListIdOptions paramsGetTasksByListId)
{
    try {
        string requestResource = "list/{paramsGetTasksByListId.ListId}/task";
        bool addedParams = false;
        if (paramsGetTasksByListId.Archived) {
            if (!addedParams) {
                requestResource += "?";
                addedParams = true;
            }
            requestResource += "archived={paramsGetTasksByListId.Archived}";
        }
        if (paramsGetTasksByListId.Page > 0) {
            if (!addedParams) {
                requestResource += "?";
                addedParams = true;
            } else {
                requestResource += "&";
            }
            requestResource += "page={paramsGetTasksByListId.Page}";
        }
        if (paramsGetTasksByListId.IncludeClosed) {
            if (!addedParams) {
                requestResource += "?";
                addedParams = true;
            } else {
                requestResource += "&";
            }
            requestResource += "include_closed={paramsGetTasksByListId.IncludeClosed}";
        }

        Response r = Get(Url{baseUrl + "space/" + id + "/folder"}, Header{{"authorization", accessToken}});

        if (r.status_code != 200) {
            throw RequestException(r.text, r.status_code);
        }
        return nlohmann::json::parse(r.text);
    } catch (RequestException &e) {
        e.printError();
        throw e;
    } catch (std::exception &e) {
        cout << "unknown exception: " << e.what() << endl;
        throw e;
    }
}

nlohmann::json clickup::CreateTaskInList(const string &id, nlohmann::json body)
{
    try {
        Response r =
            Post(Url{baseUrl + "list/" + id + "/task"},
                 Header{{"authorization", accessToken}, {"Content-Type", "application/json"}}, Body{to_string(body)});

        if (r.status_code != 200) {
            throw RequestException(r.text, r.status_code);
        }
        return nlohmann::json::parse(r.text);
    } catch (RequestException &e) {
        e.printError();
        throw e;
    } catch (std::exception &e) {
        cout << "unknown exception: " << e.what() << endl;
        throw e;
    }
}

nlohmann::json clickup::AddTaskToList(const string &listId, const string &taskId)
{
    try {
        Response r = Post(Url{baseUrl + "list/" + listId + "/task/" + taskId}, Header{{"authorization", accessToken}});

        if (r.status_code != 200) {
            throw RequestException(r.text, r.status_code);
        }
        return nlohmann::json::parse(r.text);
    } catch (RequestException &e) {
        e.printError();
        throw e;
    } catch (std::exception &e) {
        cout << "unknown exception: " << e.what() << endl;
        throw e;
    }
}
