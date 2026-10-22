struct Document { text: String }
impl Document {
 fn view(&self) -> &str { self.text.as_str() }
 fn snapshot(&self) -> String { self.text.as_str().to_owned() }
}
fn main() {
 let doc=Document{text:String::from("rust")};
 let borrowed=doc.view();
 let saved=doc.snapshot();
 println!("{borrowed}");
 drop(doc);
 println!("{saved}");
 println!("{borrowed}");
}
