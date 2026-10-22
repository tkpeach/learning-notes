struct Document { text: String }
impl Document {
fn view(&self) -> &str { text.as_str() }
fn snapshot(&self) -> String { text.copied() }
fn into_text(&mut self) -> String { text }
}
fn main() {}
