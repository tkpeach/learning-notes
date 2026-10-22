#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Verifier.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"
#include "llvm/Support/raw_ostream.h"

#include <string>

namespace {

constexpr char kInput[] = R"mlir(
module {
  func.func @mix(%a: i32, %b: i32, %c: i32) -> i32 {
    %sum0 = arith.addi %a, %b : i32
    %scaled = arith.muli %sum0, %c : i32
    %sum1 = arith.addi %scaled, %a : i32
    return %sum1 : i32
  }

  func.func @difference(%lhs: i32, %rhs: i32) -> i32 {
    %delta = arith.subi %lhs, %rhs : i32
    return %delta : i32
  }
}
)mlir";

struct OpCounts {
  unsigned addi = 0;
  unsigned muli = 0;
};

OpCounts countTargetOps(mlir::ModuleOp module) {
  OpCounts counts;

  // TODO 1: 遍历 module 中的 Operation。
  // 只统计 arith::AddIOp 和 arith::MulIOp；不要把 subi 或 func.return 算进去。
  for (auto op : module.operations) {
    if (op.kind == arith::AddIOp || op.kind == arith::MulIOp) {
      counts++;
    }
  }

  return counts;
}

mlir::OwningOpRef<mlir::ModuleOp> buildAddOne(mlir::MLIRContext &context) {
  mlir::OpBuilder builder(&context);
  mlir::Location loc = builder.getUnknownLoc();
  mlir::ModuleOp module = mlir::ModuleOp::create(loc);

  // TODO 2: 在 module body 插入一个 func.func @add_one(i32) -> i32。
  // 为函数创建 entry block；在 block 中构造常量 1、参数 + 1 和 func.return。
  // 可使用 builder.getFunctionType、func::FuncOp::addEntryBlock、
  // arith::ConstantIntOp、arith::AddIOp 和 func::ReturnOp。
  build.setInsertionPointToStart(module.body);
  auto f = builder.

  return mlir::OwningOpRef<mlir::ModuleOp>(module);
}

} // namespace

int main(int argc, char **argv) {
  if (argc != 2 || (std::string(argv[1]) != "count" &&
                    std::string(argv[1]) != "build")) {
    llvm::errs() << "usage: chapter09_exercises <count|build>\n";
    return 2;
  }

  mlir::DialectRegistry registry;
  registry.insert<mlir::arith::ArithDialect, mlir::func::FuncDialect>();
  mlir::MLIRContext context(registry);
  context.loadAllAvailableDialects();

  if (std::string(argv[1]) == "count") {
    auto module = mlir::parseSourceString<mlir::ModuleOp>(
        kInput, mlir::ParserConfig(&context), "chapter09-count-input");
    if (!module) {
      llvm::errs() << "could not parse the embedded MLIR input\n";
      return 1;
    }

    OpCounts counts = countTargetOps(*module);
    llvm::outs() << "arith.addi=" << counts.addi
                 << " arith.muli=" << counts.muli << "\n";
    return 0;
  }

  auto module = buildAddOne(context);
  if (mlir::failed(mlir::verify(module->getOperation()))) {
    llvm::errs() << "generated module did not pass verification\n";
    return 1;
  }
  module->print(llvm::outs());
  llvm::outs() << "\n";
  return 0;
}
