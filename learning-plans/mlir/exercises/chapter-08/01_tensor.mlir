module {
  func.func @tensor_update() -> (i32, i32) {
    %c1 = arith.constant 1 : i32
    %c2 = arith.constant 2 : i32
    %c9 = arith.constant 9 : i32
    %i0 = arith.constant 0 : index

    %t = tensor.from_elements %c1, %c2 : tensor<2xi32>
    %t2 = tensor.insert %c9 into %t[%i0] : tensor<2xi32>
    %old = tensor.extract %t[%i0] : tensor<2xi32>
    %new = tensor.extract %t2[%i0] : tensor<2xi32>
    return %old, %new : i32, i32
  }
}
