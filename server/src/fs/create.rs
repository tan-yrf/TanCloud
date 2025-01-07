use axum::{
    extract::{Json, Extension},
    response::IntoResponse,
    http::StatusCode,
};
use serde::Deserialize;
use serde_json::json;
use std::fs::create_dir;

use crate::http_response::HttpResponse;
use crate::error_code::ErrorCode;
use crate::mid::UserInfo;
use crate::fs::tools::{verify_path, validate_new_name};

#[derive(Deserialize)]
pub struct RequestCreate {
    path: String,
    name: String
}

// 处理创建文件夹请求，在制定文件夹下创建一个文件夹
pub async fn handle_create (
    Extension(user_info): Extension<UserInfo>,
    Json(request_create): Json<RequestCreate>
) -> impl IntoResponse {
    let verify_res = match verify_path(&request_create.path, &user_info.id.to_string()) {
        Ok(res) => res,
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
            return (StatusCode::OK, Json(response));
        }
    };

    // 检查新名称的有效性
    if let Err(_) = validate_new_name(&verify_res.target, &request_create.name) {
        let response = HttpResponse::new(ErrorCode::ValidataName, json!({}));
        return (StatusCode::OK, Json(response));
    }

    let new_folder_path = verify_res.target.join(&request_create.name);
    
    if new_folder_path.exists() {
        let response = HttpResponse::new(ErrorCode::PathExists, json!({}));
        return (StatusCode::OK, Json(response));
    }

    match create_dir(&new_folder_path) {
        Ok(_) => {
            let response = HttpResponse::new(ErrorCode::Success, json!({}));
            (StatusCode::OK, Json(response))
        }
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::CreateDirFailed, json!({}));
            (StatusCode::OK, Json(response))
        }
    }
}
