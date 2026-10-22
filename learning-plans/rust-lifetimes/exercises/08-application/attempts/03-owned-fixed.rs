fn greeting(name: &str) -> String { format!("Hello, {name}!") }
fn main() {
 let result;
 { let name = String::from("Rust"); result = greeting(name.as_str()); }
 assert_eq!(result, "Hello, Rust!"); println!("{result}");
}
