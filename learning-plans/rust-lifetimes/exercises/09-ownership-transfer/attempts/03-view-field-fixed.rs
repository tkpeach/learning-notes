struct Document { text: String }
impl Document { fn view(&self) -> &str { self.text.as_str() } }
fn main() { let d=Document{text:String::from("rust")}; assert_eq!(d.view(),"rust"); }
