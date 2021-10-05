#include <clickup/clickup.h>
#include <config_clickup.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <cpr/api.h>


using namespace std;

static inline std::string GetEnvVal(const std::string &var, std::string def)
{
  auto val = std::getenv(var.c_str());
//        cout << val << endl;
  if (val == nullptr) {
    return def;
  } else {
    return std::string(val);
  }
}

class ClickUpFixture
{
private:


public:
    clickup clickup;

    static std::string connect()
    {
        return GetEnvVal("ACCESS_TOKEN", "null");

    }
    ClickUpFixture() : clickup(connect()) {}
};

TEST_CASE_METHOD(ClickUpFixture, "Test_creating a bucket", "[clickup.cpp]")
{
    auto j = clickup.GetFolderlessList("54005663");
    cout << j << endl;
}