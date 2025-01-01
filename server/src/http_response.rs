use serde::Serialize;
use crate::error_code::ErrorCode;

#[derive(Serialize)]
pub struct HttpResponse<T>{
    pub code: i32,
    pub message: String,
    pub body: T,
}

#[allow(dead_code)]
impl<T> HttpResponse<T> {
    pub fn new(code: ErrorCode, body: T) -> Self {
        HttpResponse::<T>{
            code: code as i32,
            message: code.message().to_string(),
            body,
        }
    }
}