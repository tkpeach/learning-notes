struct Document { text: String }
impl Document {
fn view(&self) -> &str { self.text.as_str() }
fn snapshot(&self) -> String { self.text.as_str().to_owned() }
fn into_text(self) -> String { self.text }
}
fn main() {
let doc=Document{text:String::from("rust")};
assert_eq!(doc.view(),"rust");
let snapshot=doc.snapshot();
assert_eq!(doc.view(),"rust");
let moved=doc.into_text();
assert_eq!(moved,"rust");
drop(moved);
assert_eq!(snapshot,"rust");
println!("{snapshot}");
}
