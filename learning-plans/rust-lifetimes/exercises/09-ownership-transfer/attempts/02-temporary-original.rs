fn label(input: &str) -> &str { input.trim() }
fn main() { let result=label(String::from("  rust  ").as_str()); println!("{result}"); }
