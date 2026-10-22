fn keep_first<'a>(x: &'a str, note: &str) -> &'a str {
    println!("{note}");
    x
}

fn main() {
    let text = String::from("rust");
    let result;
    {
        let note = String::from("只是一条备注");
        result = keep_first(text.as_str(), note.as_str());
    }
    println!("{result}");
}
