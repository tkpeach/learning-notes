module {
  func.func @choose(%cond: i1) -> i32 {
    %chosen = scf.if %cond -> (i32) {
      %seven = arith.constant 7 : i32
      scf.yield %seven : i32
    } else {
      %nine = arith.constant 9 : i32
      scf.yield %nine : i32
    }
    return %chosen : i32
  }
}
