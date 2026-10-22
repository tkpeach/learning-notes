struct View<'a> { text: &'a str }
impl<'a> View<'a> { fn raw(&self) -> &str { text } }
fn main() {}
