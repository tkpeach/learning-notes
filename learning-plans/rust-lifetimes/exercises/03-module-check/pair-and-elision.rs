fn pair<'a, 'b>(x: &'a str, y: &'b str) -> (&'a str, &'b str) { (x, y) }
fn trim(s: &str) -> &str { s.trim() }
fn select<'a>(x: &'a str, y: &'a str, take_x: bool) -> &'a str { if take_x { x } else { y } }
fn count(x: &str, y: &str) -> usize { x.len() + y.len() }
struct Label { text: String }
impl Label { fn label(&self, _fallback: &str) -> &str { self.text.as_str() } }
fn main() {
 let (x, y) = pair(" x ", "y");
 assert_eq!(trim(x), "x");
 assert_eq!(select(x, y, false), "y");
 assert_eq!(count(x, y), 4);
 let owner = Label { text: String::from("label") };
 assert_eq!(owner.label("fallback"), "label");
}
