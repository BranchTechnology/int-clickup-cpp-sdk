//
// Created by Jacques Perrault on 10/5/21.
//

#ifndef CLICKUP_SRC_CLICKUP_REQUESTS_H_
#define CLICKUP_SRC_CLICKUP_REQUESTS_H_

struct {
  [JsonProperty("name")]
  string Name{get; set;}

  [JsonProperty("description")]
  string Description{get; set;}

  [JsonProperty("content")]
  string Content{get; set;}

  [JsonProperty("assignees")]
  List<long> Assignees{get; set;}

  [JsonProperty("tags")]
  List<long> Tags{get; set;}

  [JsonProperty("status")]
  string Status{get; set;}

  [JsonProperty("priority")]
  TaskPriority? Priority {
    get;
    set;
  }

  [JsonProperty("due_date")]
  [
  JsonConverter(typeof(JsonConverterDateTimeMilliseconds))
  ]
  DateTime? DueDate {
    get;
    set;
  }

  [JsonProperty("due_date_time")]
  bool? DueDateTime {
    get;
    set;
  }

  [JsonProperty("time_estimate")]
  [
  JsonConverter(typeof(JsonConverterDateTimeMilliseconds))
  ]
  bool? TimeEstimate {
    get;
    set;
  }

  [JsonProperty("start_date")]
  [
  JsonConverter(typeof(JsonConverterDateTimeMilliseconds))
  ]
  bool? StartDate {
    get;
    set;
  }

  [JsonProperty("start_date_time")]
  bool? StartDateTime {
    get;
    set;
  }

  [JsonProperty("notify_all")]
  bool? NotifyAll {
    get;
    set;
  }

  [JsonProperty("check_required_custom_fields")]
  bool? CheckRequiredCustomFields {
    get;
    set;
  }
};

#endif //CLICKUP_SRC_CLICKUP_REQUESTS_H_
