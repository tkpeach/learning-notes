fn main() {
    let mut text = String::from("rust");
    text.push_str("!");
    let view = text.as_str();
    println!("{view}");
    println!("{text}");
    println!("{view}");
}
