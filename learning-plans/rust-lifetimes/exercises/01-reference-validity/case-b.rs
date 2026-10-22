fn main() {
    let view;
    {
        let text = String::from("rust");
        view = text.as_str();
    }
    println!("{view}");
}
