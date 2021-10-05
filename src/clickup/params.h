//
// Created by Jacques Perrault on 10/5/21.
//

#ifndef CLICKUP_SRC_CLICKUP_PARAMS_H_
#define CLICKUP_SRC_CLICKUP_PARAMS_H_

using namespace std;

struct GetTasksByListIdOptions{
  bool Archived;
  int Page;
  bool IncludeClosed;

  GetTasksByListIdOptions(bool iArchive =false, int iPage =-1, bool iIncludeClosed=false){
    Archived=iArchive;
    Page=iPage;
    IncludeClosed=iIncludeClosed;
  }
};



#endif //CLICKUP_SRC_CLICKUP_PARAMS_H_
