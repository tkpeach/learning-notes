fn first<'a>(x: &'a str, _y: &'a str) -> &'a str { x }
fn main() {
let outside = String::from("outside");
let r;
{
let inside = String::from("inside");
r = first(outside.as_str(), inside.as_str());
}
println!("{r}");
}
