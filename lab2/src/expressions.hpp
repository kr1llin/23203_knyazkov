#pragma once

#include "ExecutionContext.hpp"
#include "Token.hpp"
#include "factory.hpp"
#include <memory>
#include <vector>


///==== COMMANDS ====///

//ABC
class Expr{
public:
    Expr() = default;
    virtual ~Expr() = default;
    virtual void execute(ExecutionContext* context) = 0;
private:
};

class PushNumberExpr : public Expr{
public:
  PushNumberExpr() = default;
  void execute(ExecutionContext* context) override;
private:
};

class DupExpr : public Expr {
public:
    void execute(ExecutionContext* context) override;
private:
};

class DropExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override ;
  private:
    // bool regDrop =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "drop", []() { return std::make_unique<DropExpr>(); });
};

class SumExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regSum = Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "+", []() { return std::make_unique<SumExpr>(); });
};

class SubsExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regSubs =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "-", [](int) { return std::make_unique<SubsExpr>(); });
};

class ModExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
};

class SlashExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regSlash =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "/", []() { return std::make_unique<SlashExpr>(); });
};

class MultExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
};

class EmitExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regEmit =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "emit", [](int) { return std::make_unique<EmitExpr>(); });
};

class DotExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regDot = Factory<std::string, Expr>::getInstance()->registerCreator(
    // ".", [](int) { return std::make_unique<DotExpr>(); });
};

class SwapExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
};

class OverExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regOver =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "over", [](int) { return std::make_unique<OverExpr>(); });
};

class CrExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regCr = Factory<std::string, Expr>::getInstance()->registerCreator(
    // "cr", []() { return std::make_unique<CrExpr>(); });
};

class RotExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
};

class LogicExpr : public Expr{
  public:
    void execute(ExecutionContext* context) override;
};


class LessExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regLess =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "<", [](int) { return std::make_unique<LessExpr>(); });
};

class GreaterExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;

  private:
    // bool regGreater =
    //     Factory<std::string, Expr>::getInstance()->registerCreator(
    //         ">", [](int) { return std::make_unique<GreaterExpr>(); });
};

class EqualExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regEqual =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "=", [](int) { return std::make_unique<EqualExpr>(); });
};

class IExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regI = Factory<std::string, Expr>::getInstance()->registerCreator(
    // "i", [](int) { return std::make_unique<IExpr>(); });
};

class PrintStrExpr : public Expr {
  public:
    void execute(ExecutionContext* context) override;
  private:
    // bool regStringOutput =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     ".\"", []() {
    //       return std::make_unique<PrintStrExpr>();
    //     });
};

class ConditionalExpr : public Expr {
public:
  void execute(ExecutionContext* context) override;
  private:
    // bool regConditional =
    // Factory<std::string, Expr>::getInstance()->registerCreator(
    //     "if", [](int) { return std::make_unique<ConditionalExpr>(); });
};

class CycleExpr : public Expr {
public:
  void execute(ExecutionContext* context) override;

private:
// bool regCycle =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "do", [](int) { return std::make_unique<CycleExpr>(); });
};

namespace {
const Creator<TokenType, PushNumberExpr> regNum{TokenType::NUMBER};
const Creator<std::string, OverExpr> regOver{"over"};
const Creator<std::string, DropExpr> regDrop{"drop"};
const Creator<std::string, CycleExpr> regCycle{"do"};
const Creator<std::string, RotExpr> regRot{"rot"};
const Creator<std::string, DupExpr> regDup{"dup"};
const Creator<std::string, SumExpr> regSum{"+"};
const Creator<std::string, SubsExpr> regSub{"-"};
const Creator<std::string, MultExpr> regMul{"*"};
const Creator<std::string, ModExpr> regMod{"mod"};
const Creator<std::string, ConditionalExpr> regIf{"if"};
const Creator<std::string, CrExpr> regCr{"cr"};

const Creator<std::string, DotExpr> regDot{"."};
const Creator<std::string, PrintStrExpr> regStringOut{".\""};
const Creator<std::string, IExpr> regI{"i"};
const Creator<std::string, EmitExpr> regEmit{"emit"};
const Creator<std::string, LessExpr> regLess{"<"};
const Creator<std::string, GreaterExpr> regGreater{">"};
const Creator<std::string, EqualExpr> regEqual{"="};
const Creator<std::string, SwapExpr> regSwap{"swap"};

};




// template <class Key, class Product>
// class RegisterInFactory
// {
// protected:
//     static bool s_registered;
// };

// template <class Key, class Product>
// bool RegisterInFactory<Key, Product>::s_registered =
//     Factory<Key, Product>::getInstance()->registerCreator(
//         Product::getFactoryName(),
//         []() { return std::make_unique<Product>(); });

  // static TokenType getFactoryName() { return TokenType::NUMBER; }





//===

// template <class Key, class Product>
// class Registrator {
//  public:
//   Registrator(
//       Key key, Product product){
//     Factory<Key, Product>::getInstance()->registerCreator(
//         Product::getFactoryName(),
//         []() { return std::make_unique<Product>(); });
//   }
// };


// template <class Key, class Product>
// class Registrator {
// public:
//     static bool registered;
//     static void registerProduct() {
//         if (!registered) {
//             Factory<Key, Product>::getInstance()->registerCreator(
//                 Product::getFactoryName(),
//                 []() { return std::make_unique<Product>(); });
//             registered = true; // Mark as registered
//         }
//     }
// };

// template <class Key, class Product>
// bool Registrator<Key, Product>::registered = []() {
//     Registrator<Key, Product>::registerProduct();
//     return true;
// }();



// namespace {
// static bool regSum = Factory<std::string, Expr>::getInstance()->registerCreator(
//     "+", []() { return std::make_unique<SumExpr>(); });

// // static bool regNumber =
// //     Factory<TokenType, Expr>::getInstance()->registerCreator(
// //         TokenType::NUMBER, []() {
// //           return std::make_unique<PushNumberExpr>();
// //         });

// static bool regDup = Factory<std::string, Expr>::getInstance()->registerCreator(
//     "dup", []() { return std::make_unique<DupExpr>(); });

// static bool regCr = Factory<std::string, Expr>::getInstance()->registerCreator(
//     "cr", []() { return std::make_unique<CrExpr>(); });

// static bool regStringOutput =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         ".\"", []() {
//           return std::make_unique<PrintStrExpr>();
//         });

// static bool regSlash =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "/", []() { return std::make_unique<SlashExpr>(); });

// static bool regDrop =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "drop", []() { return std::make_unique<DropExpr>(); });

// static bool regSubs =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "-", []() { return std::make_unique<SubsExpr>(); });

// static bool regEmit =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "emit", []() { return std::make_unique<EmitExpr>(); });

// static bool regLess =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "<", []() { return std::make_unique<LessExpr>(); });

// static bool regGreater =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         ">", []() { return std::make_unique<GreaterExpr>(); });

// static bool regEqual =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "=", []() { return std::make_unique<EqualExpr>(); });

// static bool regConditional =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "if", []() { return std::make_unique<ConditionalExpr>(); });

// static bool regCycle =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "do", []() { return std::make_unique<CycleExpr>(); });

// static bool regI = Factory<std::string, Expr>::getInstance()->registerCreator(
//     "i", []() { return std::make_unique<IExpr>(); });

// static bool regRot = Factory<std::string, Expr>::getInstance()->registerCreator(
//     "rot", []() { return std::make_unique<RotExpr>(); });

// static bool regDot = Factory<std::string, Expr>::getInstance()->registerCreator(
//     ".", []() { return std::make_unique<DotExpr>(); });

// static bool regOver =
//     Factory<std::string, Expr>::getInstance()->registerCreator(
//         "over", []() { return std::make_unique<OverExpr>(); });
// } 

//=============DUMPSTERRR!!!==================//

