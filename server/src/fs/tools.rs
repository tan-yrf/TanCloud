use axum::{
    extract::Json,
    response::IntoResponse,
    http::StatusCode,
};
use serde_json::json;
use std::fs;
use std::path::PathBuf;
use crate::error_code::ErrorCode;
use crate::WORK_DIR;
use crate::http_response::HttpResponse;


// 非法字符集合
const ILLEGAL_CHARS: &[char] = &['\\', '/', ':', '*', '?', '"', '<', '>', '|'];

pub struct VerifyResult {
    pub root_path: PathBuf,
    pub target: PathBuf,
}

// 校验路径,成功返回完整目标路径,失败返回响应结构体
pub fn verify_path(path: String, user_id: String) -> Result<VerifyResult, ()> {
    let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
    
    if path.contains("..") || ILLEGAL_CHARS.iter().any(|&c| path.contains(c)) {
        return Err(());
    }

    let res = VerifyResult {
        root_path: WORK_DIR.join(user_id.clone()).join("root"),
        target: WORK_DIR.join(user_id).join("root").join(path),
    };
    if fs::metadata(&res.target).is_ok() {
        Ok(res)
    } else {
        Err(())
    }
}