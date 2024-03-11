#ifndef _BRACKETSHANDLER_H_
#define _BRACKETSHANDLER_H_

#include "ExpressionHandler.h"

namespace s21 {
class BracketsHandler : public ExpressionHandler {
public:
    HandleStatus handle(const std::string& expression, size_t& index, std::list<ExpressionToken>& stack) override;
    void clean() override;

private:
    bool checkBracketsBalance();

    size_t left_bracket_counter_;
    size_t right_bracket_counter_;

    size_t last_index_of_left_bracket_;
    size_t last_index_of_right_bracket_;
};
}

#endif  // _BRACKETSHANDLER_H_
