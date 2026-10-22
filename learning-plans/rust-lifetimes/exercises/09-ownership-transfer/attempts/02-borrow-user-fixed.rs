fn label(input: &str) -> &str { input.trim() }
fn main() { let ori=String::from("  rust  "); let result=label(ori.as_str()); assert_eq!(result,"rust"); println!("{result}"); }
