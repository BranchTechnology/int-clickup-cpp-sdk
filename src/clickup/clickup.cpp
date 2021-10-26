//
// Created by Jacques Perrault on 10/5/21.
//
#include <iostream>
#include <cpr/response.h>
#include <cpr/api.h>
#include "clickup.h"
#include <future>
//#include <experiemental/future>
#include <exception>
#include <utility>

using namespace std;
using namespace cpr;

struct RequestException : public exception {
  string message;
  int code;
  RequestException(string iMessage, int iCode = 400) {
    message = std::move(iMessage);
    code = iCode;
  }
  [[nodiscard]] const char *what() const noexcept { return message.c_str(); }

  void printError() const noexcept { cout << " - message: " + message + "\n- code: " + to_string(code); }
};

clickup::clickup(const std::string &userToken) {
  accessToken = userToken;
}

clickup::clickup() = default;

void clickup::getToken(const std::string &userToken) {
  try {
    auto val = std::getenv(userToken.c_str());
    if (val == nullptr) {
      throw logic_error("failed to get ACCESS_TOKEN from env");
    } else {
      accessToken = string(val);
    }
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}

nlohmann::json parseResponse(const Response& f,  const  string& url) {
  if (f.status_code != 200) {
    throw RequestException(f.error.message, f.status_code);
  }
  auto resp = nlohmann::json::parse(f.text);
  resp["respUrl"] = url;
  return resp;
}


nlohmann::json clickup::GetFolderlessList(const string &id) {
  try {
    auto url = baseUrl + "space/" + id + "/list";
    Response r = Get(Url{url}, Header{{"authorization", accessToken}});
    return parseResponse(r, url);
  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}


future<nlohmann::json> clickup::AsyncGetFolderlessList(const string &id) {
  try {
    return std::async( [&]() {
      return this->GetFolderlessList(id);
    });

  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}
nlohmann::json clickup::GetFolders(const string &id) {
  try {
    auto url = baseUrl + "space/" + id + "/folder";
    Response r = Get(Url{url}, Header{{"authorization", accessToken}});
    return parseResponse(r, url);
  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}

nlohmann::json clickup::GetListCustomFields(const string &listId) {
  try {
    auto url = baseUrl + "list/" + listId + "/field";
    Response r = Get(Url{url}, Header{{"authorization", accessToken}});
    return parseResponse(r, url);

  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}

nlohmann::json clickup::GetTaskById(const string &taskId) {
  try {
    auto url = baseUrl + "task/" + taskId;
    Response r = Get(Url{url}, Header{{"authorization", accessToken}});
    return parseResponse(r, url);
  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}

nlohmann::json clickup::GetTasksByListId(const string &id, GetTasksByListIdOptions paramsGetTasksByListId) {
  try {

    ostringstream requestResource;
    requestResource << baseUrl << "list/"+id+"/task";

//    string requestResource = "list/"+id+"/task";
    bool addedParams = false;
    if (paramsGetTasksByListId.Archived) {
      addedParams = true;
      requestResource << "?archived=" << boolalpha <<  paramsGetTasksByListId.Archived;
    }
    if (paramsGetTasksByListId.Page > -1) {
      if (!addedParams) {
        requestResource << "?";
        addedParams = true;
      } else {
        requestResource << "&";
      }
      requestResource << "page=" << paramsGetTasksByListId.Page;
    }
    if (paramsGetTasksByListId.IncludeClosed) {
      if (!addedParams) {
        requestResource << "?";
      } else {
        requestResource << "&";
      }
      requestResource << "include_closed="<< boolalpha << paramsGetTasksByListId.IncludeClosed;

    }
    auto url = requestResource.str();
    Response r = Get(Url{url}, Header{{"authorization", accessToken}});
    return parseResponse(r, url);
  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}

nlohmann::json clickup::CreateTaskInList(const string &id, nlohmann::json body) {
  try {
    auto url = baseUrl + "list/" + id + "/task";
    Response r = Post(Url{url},Header{{"authorization", accessToken}, {"Content-Type", "application/json"}}, Body{to_string(body)});
    return parseResponse(r, url);
  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}

nlohmann::json clickup::AddTaskToList(const string &listId, const string &taskId) {
  try {
    auto url = baseUrl + "list/" + listId + "/task/" + taskId;
    Response r = Post(Url{url}, Header{{"authorization", accessToken}});
    return parseResponse(r, url);
  } catch (RequestException &e) {
    e.printError();
    throw e;
  } catch (std::exception &e) {
    cout << "unknown exception: " << e.what() << endl;
    throw e;
  }
}
