fn greeting<'a>(name: &'a str) -> &'a str {
 let message = format!("Hello, {name}!");
 message.as_str()
}
fn main() {}
