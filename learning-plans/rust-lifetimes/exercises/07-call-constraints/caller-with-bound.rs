fn forward<'a: 'b, 'b>(x: &'a str) -> &'b str {
    x
}

pub fn caller<'p: 'q, 'q>(s: &'p str) -> &'q str {
    forward(s)
}
