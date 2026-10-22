fn pass<'a>(s: &'a str) -> &'a str { s }
fn main() { let owner=String::from("rust"); assert_eq!(pass(owner.as_str()),"rust"); }
