fn main() {
    let mut text = String::from("rust");
    let view = text.as_str();
    println!("{view}");
    text.push_str("!");
    println!("{text}");
    println!("{view}");
}
