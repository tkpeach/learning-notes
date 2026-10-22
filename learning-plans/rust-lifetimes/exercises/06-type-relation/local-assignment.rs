fn local_assignment<'a, 'b>(x: &'a str) {
    let src: &'a str = x;
    let _dst: &'b str = src;
}

fn main() {}
