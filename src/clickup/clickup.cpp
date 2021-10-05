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

struct RequestException : public exception {
  string message;
  int code;
  RequestException(string iMessage, int iCode=400){
    message=iMessage;
    code=iCode;
  }
  [[nodiscard]] const char * what () const noexcept {
    return message.c_str();
  }

  void printError () const noexcept {
    cout << " - message: " + message + "\n- code: " + to_string(code);
  }
};


clickup::clickup(const std::string &userToken) {
  accessToken=userToken;
}
nlohmann::json clickup::GetFolderlessList(const string &id) {

  try {

    Response r = Get(Url{baseUrl+"space/" + id + "/list"},
                               Header{{"authorization", accessToken}});

    if(r.status_code != 200){
      throw RequestException(r.error.message, r.status_code);
    }
    return nlohmann::json::parse(r.text);
  }
  catch(RequestException &e) {
    e.printError();
    throw e;
  }
  catch(std::exception& e) {
    cout << "unknown exception" << endl;
    throw e;
  }

}

nlohmann::json clickup::GetFolders(const string &id) {

  try {

    Response r = Get(Url{baseUrl+"space/" + id + "/folder"},
                     Header{{"authorization", accessToken}});

    if(r.status_code != 200){
      throw RequestException(r.text, r.status_code);
    }
    return nlohmann::json::parse(r.text);
  }
  catch(RequestException &e) {
    e.printError();
    throw e;
  }
  catch(std::exception& e) {
    cout << "unknown exception" << endl;
    throw e;
  }
}

