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
    paths: Vec<String>,
}

// 处理删除请求
pub async fn handle_delete (
    Extension(user_info): Extension<UserInfo>,
    Json(request_delete): Json<RequestDelete>
 ) -> impl IntoResponse {
    let mut results = Vec::new();
    
    for path in request_delete.paths {
        let verify_res = match verify_path(&path, &user_info.id.to_string()) {
            Ok(res) => res,
            Err(_) => {
                let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
                return (StatusCode::OK, Json(response));
            }
        };
        let target_path = verify_res.root_path.join(&path);

        match delete_resource(target_path) {
            Ok(_) => results.push((path.clone(), true, "Success".to_string())),
            Err(err) if err.kind() == ErrorKind::NotFound => {
                results.push((path.clone(), false, "Path not found".to_string()));
            }
            Err(_) => {
                results.push((path.clone(), false, "Delete failed".to_string()));
            }
        }
    }
    
    let all_success = results.iter().all(|(_, success, _)| *success);

    if all_success {
        let response = HttpResponse::new(ErrorCode::Success, json!({ "results": results }));
        (StatusCode::OK, Json(response))
    } else {
        let response = HttpResponse::new(ErrorCode::DeleteFailed, json!({ "results": results }));
        (StatusCode::OK, Json(response))
    }
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