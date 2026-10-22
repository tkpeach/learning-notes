struct View<'a> { text: &'a str }
fn main() {
 let mut owner = String::from("rust");
 let view = View { text: owner.as_str() };
 println!("{}", view.text);
 owner.push_str("!");
 println!("{owner}");
 println!("{}", view.text);
}
