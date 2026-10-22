struct View<'a> { text: &'a str }
fn build<'a>(text: &'a str, _note: &str) -> View<'a> { View { text } }
fn main() {
 let view;
 { let owner = String::from("message"); view = build(owner.as_str(), "note"); }
 println!("{}", view.text);
}
