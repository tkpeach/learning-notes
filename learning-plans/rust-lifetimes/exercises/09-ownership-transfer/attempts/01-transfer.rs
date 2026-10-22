fn transfer(s: String) -> String { s }
fn main() { let first=String::from("rust"); let second=transfer(first); assert_eq!(second,"rust"); }
