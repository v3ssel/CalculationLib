#ifndef _BASECALCULATIONALGORITHM_H_
#define _BASECALCULATIONALGORITHM_H_

#include <string>

namespace s21 {
class BaseCalculationAlgorithm {
public:
    virtual ~BaseCalculationAlgorithm() = default;

    double calculate(const std::string& exp);
    const std::string& getExpression() const;

protected:
    virtual void parseExpression() = 0;
    virtual void calculation() = 0;
    virtual double getResult() = 0;

    std::string expression_;
};
}

#endif  // _BASECALCULATIONALGORITHM_H_
