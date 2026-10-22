fn main() {
 let text: &str = "rust";
 let a: String = text.to_owned();
 let mut b: String = a.clone();
 b.push('!');
 assert_eq!(a, "rust"); assert_eq!(b, "rust!");
 let slice: &[i32] = &[1, 2];
 let owned: Vec<i32> = slice.to_owned(); assert_eq!(owned, vec![1, 2]);
 let copied: Vec<i32> = owned.iter().copied().collect(); assert_eq!(copied, vec![1, 2]);
 let words = vec![String::from("rust")];
 let cloned: Vec<String> = words.iter().cloned().collect();
 drop(words); assert_eq!(cloned[0], "rust");
 let n = 7;
 let optional: Option<&i32> = Some(&n);
 let copied_option: Option<i32> = optional.copied(); assert_eq!(copied_option, Some(7));
 let name = String::from("rust");
 let name_option: Option<String> = Some(&name).cloned();
 drop(name); assert_eq!(name_option.as_deref(), Some("rust"));
 let ref_copy: &str = <&str as Clone>::clone(&text); assert_eq!(ref_copy, "rust");
 println!("to_owned/clone/copied/cloned assertions passed");
}
