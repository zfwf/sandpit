use std::io;
use std::io::Write;
use std::cmp::Ordering;
use rand::Rng;


fn main() {
    println!("Guess a number!");

    let rand_number = rand::thread_rng().gen_range(1, 101);
    println!("Secret number is: {}", rand_number);

    print!("Please input your guess: ");
    io::stdout().flush().unwrap();
    let mut guess = String::new();
    io::stdin().read_line(&mut guess).expect("Fail to read line");
    let guess: u32 = guess.trim().parse().expect("Please enter a number");
    println!("You guessed {}", guess);

    match guess.cmp(&rand_number) {
        Ordering::Greater => println!("Too big"),
        Ordering::Less => println!("Too small"),
        Ordering::Equal => println!("Correct")
    }
}
