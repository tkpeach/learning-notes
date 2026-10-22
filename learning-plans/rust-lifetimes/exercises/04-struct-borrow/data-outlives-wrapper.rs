struct Excerpt<'a> {
    text: &'a str,
}

impl<'a> Excerpt<'a> {
    fn via_self(&self) -> &str {
        self.text
    }

    fn data(&self) -> &'a str {
        self.text
    }
}

fn main() {
    let owner = String::from("rust");
    let result;
    {
        let excerpt = Excerpt { text: owner.as_str() };
        assert_eq!(excerpt.via_self(), "rust");
        result = excerpt.data();
    }
    assert_eq!(result, "rust");
    println!("{result}");
}
