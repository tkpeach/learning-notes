fn forward<'src: 'out, 'out>(x: &'src str) -> &'out str {
    x
}

fn main() {
    let owner = String::from("rust");
    assert_eq!(forward(owner.as_str()), "rust");
}
