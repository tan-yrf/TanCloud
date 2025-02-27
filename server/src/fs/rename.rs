use axum::{
    extract::{Json, Extension},
    response::{IntoResponse},
    http::StatusCode,
};
use serde::{Deserialize};
use serde_json::json;
use std::path::{PathBuf};
use std::fs::rename;

use crate::http_response::HttpResponse;
use crate::error_code::ErrorCode;
use crate::mid::UserInfo;
use crate::fs::tools::{verify_path, validate_new_name};

#[derive(Deserialize)]
pub struct RequestRename {
    path: String,
    new_name: String
}

// 处理重命名请求
pub async fn handle_rename(
    Extension(user_info): Extension<UserInfo>,
    Json(request_rename): Json<RequestRename>
) -> impl IntoResponse {
    let verify_res = match verify_path(&request_rename.path, &user_info.id.to_string()) {
        Ok(res) => res,
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
            return (StatusCode::OK, Json(response));
        }
    };

    // 检查新名称的有效性
    if let Err(_) = validate_new_name(&verify_res.target, &request_rename.new_name) {
        let response = HttpResponse::new(ErrorCode::RenameFailed, json!({}));
        return (StatusCode::OK, Json(response));
    }

    // 执行重命名操作
    match rename_file(verify_res.target, request_rename.new_name).await {
        Ok(_) => {
            let response = HttpResponse::new(ErrorCode::Success, json!({}));
            (StatusCode::OK, Json(response))
        },
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::RenameFailed, json!({}));
            (StatusCode::OK, Json(response))
        }
    }
}


// 重命名文件
async fn rename_file(target: PathBuf, new_name: String) -> Result<(), ()> {
    let parent = target.parent().unwrap_or_else(|| &target);
    let new_path = parent.join(new_name);

    match rename(&target, &new_path) {
        Ok(_) => Ok(()),
        Err(_) => Err(()), 
    }
}
