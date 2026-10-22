struct View<'a> { text: &'a str }
impl<'a> View<'a> { fn raw(&self) -> &'a str { self.text } }
fn main() {
 let owner = String::from("message"); let result;
 { let view = View { text: owner.as_str() }; result = view.raw(); }
 assert_eq!(result, "message");
}
