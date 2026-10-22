struct View<'a> { text: &'a str }
fn build<'a>(text: &'a str, _note: &'a str) -> View<'a> { View { text } }
fn main() {
 let owner = String::from("message"); let view;
 { let note = String::from("temporary note"); view = build(owner.as_str(), note.as_str()); }
 println!("{}", view.text);
}
