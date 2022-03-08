pub mod object;
pub mod material;
use crate::object::*;

use cgmath::Vector3;

fn main() {
    let sphere = Sphere{pos: Vector3::new(0.0, 0.0, 0.0), rayon: 0.0, textures: Vec::new()};
    println!("Hello, world!");
}
