#ifndef _CREDITLIB_H_
#define _CREDITLIB_H_

#include <memory>

#include "../Deposit/DepositCalculator.h"

namespace s21 {
    class DepositLib {
    public:
        static DepositLib& Instance();

        DepositResult calculate(const DepositParams& params);
    private:
        DepositLib();
        DepositLib(DepositLib const&) = delete;
        DepositLib& operator=(DepositLib const&) = delete;

        std::unique_ptr<DepositCalculator> m_deposit_;
    };
}

#endif  // _CREDITLIB_H_
