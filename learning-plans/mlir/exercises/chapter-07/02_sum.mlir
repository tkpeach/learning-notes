module {
  func.func @sum_five() -> i32 {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c5 = arith.constant 5 : index
    %sum_init = arith.constant 0 : i32

    %sum = scf.for %iv = %c0 to %c5 step %c1
        iter_args(%sum_it = %sum_init) -> (i32) {
      %iv_i32 = arith.index_cast %iv : index to i32
      %sum_next = arith.addi %sum_it, %iv_i32 : i32
      scf.yield %sum_next : i32
    }

    return %sum : i32
  }
}
