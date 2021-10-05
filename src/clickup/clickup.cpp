//
// Created by Jacques Perrault on 10/5/21.
//
#include <iostream>
#include <cpr/response.h>
#include <cpr/api.h>
#include "clickup.h"

using namespace std;
using namespace cpr;

clickup::clickup(const std::string &userToken) {
  accessToken=userToken;
}
nlohmann::json clickup::GetFolderlessList(const std::string &id) {

  try {

    Response r = Get(Url{baseUrl+"space/" + id + "/list"},
                               Header{{"authorization", accessToken}});

    if(r.status_code != 200){
      throw runtime_error(r.error.message);
    }
    return nlohmann::json::parse(r.text);
  }
  catch(exception &e) {
    throw(e);
  }


}
