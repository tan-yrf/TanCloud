use axum::{
    extract::{Json, Extension},
    response::IntoResponse,
    http::StatusCode,
};
use serde::Deserialize;
use serde_json::json;
use std::path::PathBuf;
use std::fs::{metadata, remove_dir_all, remove_file};
use std::io::{self, ErrorKind};

use crate::http_response::HttpResponse;
use crate::error_code::ErrorCode;
use crate::mid::UserInfo;
use crate::fs::tools::verify_path;

#[derive(Deserialize)]
pub struct RequestDelete {
    path: String
}

// 处理删除请求
pub async fn handle_delete (
    Extension(user_info): Extension<UserInfo>,
    Json(request_delete): Json<RequestDelete>
 ) -> impl IntoResponse {
    // 待移动的资源存在
    let verify_res = match verify_path(&request_delete.path, &user_info.id.to_string()) {
        Ok(res) => res,
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
            return (StatusCode::OK, Json(response));
        }
    };

    let target_path = verify_res.root_path.join(&request_delete.path);

    // 检查路径是否存在并尝试删除
    let response = match delete_resource(target_path) {
        Ok(_) => HttpResponse::new(ErrorCode::Success, json!({})),
        Err(err) if err.kind() == ErrorKind::NotFound => HttpResponse::new(ErrorCode::InvalidPath, json!({})),
        Err(_) =>  HttpResponse::new(ErrorCode::DeleteFailed, json!({}))
    };

    (StatusCode::OK, Json(response))
}

fn delete_resource(path: PathBuf) -> io::Result<()> {
    let metadata = metadata(&path)?;
    if metadata.is_file() {
        remove_file(path)?; // 删除文件
    } else if metadata.is_dir() {
        remove_dir_all(path)?; // 递归删除文件夹及其内容
    }
    Ok(())
}