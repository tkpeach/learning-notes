module {
  func.func @memref_update() -> i32 {
    %m = memref.alloc() : memref<2xi32>
    %i0 = arith.constant 0 : index
    %i1 = arith.constant 1 : index
    %c1 = arith.constant 1 : i32
    %c2 = arith.constant 2 : i32
    %c9 = arith.constant 9 : i32

    memref.store %c1, %m[%i0] : memref<2xi32>
    memref.store %c2, %m[%i1] : memref<2xi32>
    memref.store %c9, %m[%i0] : memref<2xi32>
    %value = memref.load %m[%i0] : memref<2xi32>
    memref.dealloc %m : memref<2xi32>
    return %value : i32
  }
}
