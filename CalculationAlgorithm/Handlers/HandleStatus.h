#ifndef _HANDLESTATUS_H_
#define _HANDLESTATUS_H_

#include <string>

namespace s21 {
struct HandleStatus {
  bool is_error;
  std::string error_message;
};
}

#endif  // _HANDLESTATUS_H_
