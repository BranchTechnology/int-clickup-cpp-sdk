#include <clickup/clickup.h>
#include <config_clickup.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <cpr/api.h>

using namespace std;

static inline std::string GetEnvVal(const std::string &var, std::string def) {
  auto val = std::getenv(var.c_str());
//        cout << val << endl;
  if (val == nullptr) {
    return def;
  } else {
    return std::string(val);
  }
}

class ClickUpFixture {
 private:

 public:
  clickup clickup;

  static std::string connect() {
    return GetEnvVal("ACCESS_TOKEN", "null");

  }
  ClickUpFixture() : clickup(connect()) {}
};

TEST_CASE_METHOD(ClickUpFixture, "test getting a folderless list", "[clickup.cpp]")
{
  auto o = clickup.GetFolderlessList("54005663");
  cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test getting folders", "[clickup.cpp]")
{
  auto o = clickup.GetFolders("54005663");
  cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test getting tasks", "[clickup.cpp]")

{
  auto o = clickup.GetTasksByListId("54005663", GetTasksByListIdOptions());
  cout << o << endl;
}

TEST_CASE_METHOD(ClickUpFixture, "test creating a task in list", "[clickup.cpp]")
{

  auto t = R"({
    "name": "sdf"
  })";
  auto j = nlohmann::json::parse(t);

  auto o = clickup.CreateTaskInList("54005663", j);
  cout << o << endl;
}
