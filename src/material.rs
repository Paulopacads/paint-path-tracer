use cgmath::Vector3;

#[derive(Clone, Debug)]
pub enum TextureType {
    REFR,
    DIFF,
    SPEC,
    EMIS,
}

#[derive(Clone, Debug)]
pub struct Texture {
    pub weight: u32,
    pub t_type: TextureType,
    pub color: Vector3<f32>,
}
