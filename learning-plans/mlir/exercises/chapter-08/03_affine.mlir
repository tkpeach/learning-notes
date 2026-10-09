module {
  func.func @affine_index(%i: index, %j: index, %N: index) -> index {
    %index = affine.apply affine_map<(d0, d1)[s0] -> (d0 + d1 * 4 + s0)>
        (%i, %j)[%N]
    return %index : index
  }
}
