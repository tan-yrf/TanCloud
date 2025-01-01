use serde::Serialize;

#[derive(Serialize)]
pub struct Response {
    pub code: i32,
    pub message: String,
    pub body: T,
}