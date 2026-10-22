struct OwnedView { text: String }
impl OwnedView { fn raw(&self) -> &str { self.text.as_str() } }
fn main() { let v = OwnedView { text: String::from("message") }; assert_eq!(v.raw(), "message"); }
