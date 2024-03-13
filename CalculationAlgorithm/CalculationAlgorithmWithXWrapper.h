#ifndef _CALCULATIONALGORITHMWITHXWRAPPER_H_
#define _CALCULATIONALGORITHMWITHXWRAPPER_H_

#include <memory>
#include "BaseCalculationAlgorithm.h"
#include "ExpressionPreparator.h"

namespace s21 {
    class CalculationAlgorithmWithXWrapper {
    public:
        CalculationAlgorithmWithXWrapper(BaseCalculationAlgorithm* algorithm,
                                         ExpressionPreparator* preparator);

        virtual double calculate(const std::string &expression, const std::string &x = "");

    protected:
        std::unique_ptr<BaseCalculationAlgorithm> m_algorithm_;
        std::unique_ptr<ExpressionPreparator> m_preparator_;
    };
}

#endif  // _CALCULATIONALGORITHMWITHXWRAPPER_H_
