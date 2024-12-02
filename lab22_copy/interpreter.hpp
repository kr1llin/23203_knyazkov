// #include "Token.hpp"
// #include "expressions.hpp"


// //values are from interpreter
// class Interpreter : public Expr::Visitor {
// public:

//     std::shared_ptr<Object> visitNumberExpr(Number* expr) override {
//         return std::make_shared<Number>(expr->value);
//     }
    
//     std::shared_ptr<Object> visitLiteralExpr(Literal* expr) override {
//         return expr->value; // Return the value of the literal expression
//     }

//     // Implement other visit methods for different expression types
//     void interpret(Expr *expression) {
//       try {
//         std::shared_ptr<Object> value = evaluate(expression);
//         std::cout << stringify(value) << std::endl;
//       } catch (const RuntimeError &error) {
//         std::cerr << "Runtime Error: " << error.what() << std::endl;
//       }
//     }

//     std::string stringify(std::shared_ptr<Object> object) {
//         if (!object) return "nil"; // Check for nullptr

//         if (auto number = dynamic_cast<Number*>(object.get())) {
//             // Convert the number to a string
//             std::ostringstream oss;
//             oss << number->value;
//             return oss.str();
//         }

//         return object.toString; // Placeholder for other object types
//     }
//     // A method to evaluate an expression
//     std::shared_ptr<Object> evaluate(Expr* expr) {
//         return expr->accept(this);
//     }
//     std::shared_ptr<Object> visitBinaryExpr(Binary *expr) override {
//       auto left = evaluate(expr->left);
//       auto right = evaluate(expr->right);

//       // Assuming left and right are of type Number
//       double leftValue = dynamic_cast<Number *>(left.get())->value;
//       double rightValue = dynamic_cast<Number *>(right.get())->value;

//       if (expr->getOperatorToken().getLiteral() == "-") {
//         return std::make_shared<Number>(leftValue - rightValue);
//       } else if (expr->operatorType == "/") {
//         if (rightValue == 0) {
//           throw std::runtime_error("Division by zero");
//         }
//         return std::make_shared<Number>(leftValue / rightValue);
//       } else if (expr->operatorType == "*") {
//         return std::make_shared<Number>(leftValue * rightValue);
//       }

//       // Unreachable.
//       return nullptr;
//     }

//       std::shared_ptr<Object> evaluate(Expr *expr) {
//         return expr->accept(this);
//       }
// };
