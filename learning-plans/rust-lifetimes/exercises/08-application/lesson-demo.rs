struct TextView<'data> {
    text: &'data str,
}

impl<'data> TextView<'data> {
    fn new(text: &'data str) -> Self {
        Self { text }
    }

    fn tied_to_self(&self) -> &str {
        self.text
    }

    fn tied_to_data(&self) -> &'data str {
        self.text
    }

    fn snapshot(&self) -> String {
        self.text.to_owned()
    }
}

fn default_text() -> &'static str {
    "default"
}

fn main() {
    let owner = String::from("rust");
    let external;
    let snapshot;
    {
        let view = TextView::new(owner.as_str());
        assert_eq!(view.tied_to_self(), "rust");
        external = view.tied_to_data();
        snapshot = view.snapshot();
    }
    assert_eq!(external, "rust");
    drop(owner);
    assert_eq!(snapshot, "rust");
    assert_eq!(default_text(), "default");
    println!("snapshot={snapshot}, default={}", default_text());
}
