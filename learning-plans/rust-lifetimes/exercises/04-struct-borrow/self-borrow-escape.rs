struct Excerpt<'a> {
    text: &'a str,
}

impl<'a> Excerpt<'a> {
    fn via_self(&self) -> &str {
        self.text
    }
}

fn main() {
    let owner = String::from("rust");
    let result;
    {
        let excerpt = Excerpt { text: owner.as_str() };
        result = excerpt.via_self();
    }
    println!("{result}");
}
