struct Document { text: String }
impl Document { fn snapshot(&self) -> String { self.text.copied() } }
fn main() {}
