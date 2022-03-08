mod material;
use crate::material::Texture;
use cgmath::Vector3;

pub trait Object{
    fn intersects(&self, origin: Vector3<f32>, dir: Vector3<f32>)->f32;
    fn get_mat(&self)-> Vec<Texture>;
    fn get_normale(&self, point: Vector3<f32>)->Vector3<f32>;
}

pub struct Sphere{
    pub pos: Vector3<f32>,
    pub rayon: f32,
    pub textures: Vec<Texture>
}

impl Object for Sphere{
    fn intersects(&self, origin: Vector3<f32>, dir: Vector3<f32>)->f32{
        // TODO
        return 0.0;
    }

    fn get_mat(&self)-> Vec<Texture>{
        return self.textures;
    }

    fn get_normale(&self, point: Vector3<f32>)->Vector3<f32>{
        return point - self.pos;
    }
}
