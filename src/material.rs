use cgmath::Vector3;

#[derive(Debug)]
pub enum TextureType {
    REFRACT,
    DIFFUSE,
    SPECULR,
}

#[derive(Debug)]
pub struct Texture {
    pub weight: u32,
    pub t_type: TextureType,
    pub color: Vector3<f32>,
}

#[derive(Debug)]
pub struct Material {
    pub textures: Vec<Texture>,
}
