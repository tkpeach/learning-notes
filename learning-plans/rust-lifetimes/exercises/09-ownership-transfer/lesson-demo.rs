fn read(s: &str) -> &str {
    s
}

fn take(s: String) -> String {
    s
}

fn make(name: &str) -> String {
    format!("Hello, {name}!")
}

fn main() {
    let owner = String::from("rust");
    assert_eq!(read(owner.as_str()), "rust");
    assert_eq!(owner, "rust");
    let moved = take(owner);
    assert_eq!(moved, "rust");

    let output = {
        let local = String::from("block result");
        local
    };
    assert_eq!(output, "block result");

    let greeting;
    {
        let name = String::from("Rust");
        greeting = make(name.as_str());
    }
    assert_eq!(greeting, "Hello, Rust!");
    println!("{moved}; {output}; {greeting}");
}
