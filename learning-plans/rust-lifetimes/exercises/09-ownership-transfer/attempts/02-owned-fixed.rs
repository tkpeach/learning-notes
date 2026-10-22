fn label(input: String) -> String { input.trim().to_owned() }
fn main() { let result=label(String::from("  rust  ")); assert_eq!(result,"rust"); println!("{result}"); }
