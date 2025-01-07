use axum::{
    extract::{Json, Extension},
    response::IntoResponse,
    http::StatusCode,
};
use serde::Deserialize;
use serde_json::json;
use std::path::PathBuf;
use std::fs::{metadata};
use std::io::{self, Error, ErrorKind};

use crate::http_response::HttpResponse;
use crate::error_code::ErrorCode;
use crate::mid::UserInfo;s
use crate::fs::tools::{verify_path};

#[derive(Deserialize)]
pub struct RequestMove {
    original: String,
    target: String,
}

// 处理移动请求
pub async fn handle_move (
    Extension(user_info): Extension<UserInfo>,
    Json(request_move): Json<RequestMove>,
) -> impl IntoResponse {
    // 待移动的资源存在
    let verify_org_res = match verify_path(&request_move.original, &user_info.id.to_string()) {
        Ok(res) => res,
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
            return (StatusCode::OK, Json(response));
        }
    };

    // 待移动的目标路径要求是一个文件夹，并且该文件夹中不能存在与原始路径同名的文件或文件夹
    let target_path = verify_org_res.root_path.join(request_move.target);
    match metadata(&target_path) {
        Ok(metadata) if metadata.is_dir() => {
            let target_name = request_move.original.split('/').last().unwrap();
            let target_file_path = target_path.join(target_name);
            if target_file_path.exists() {
                let response = HttpResponse::new(ErrorCode::PathExists, json!({}));
                return (StatusCode::OK, Json(response));
            }
        },
        Ok(_) => {
            let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
            return (StatusCode::OK, Json(response));
        },
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
            return (StatusCode::OK, Json(response));
        }
    }

    let response = match m_move(verify_org_res.target, target_path) {
        Ok(_) => HttpResponse::new(ErrorCode::Success, json!({})),
        Err(_) => HttpResponse::new(ErrorCode::MoveFailed, json!({})),
    };

    (StatusCode::OK, Json(response))
}   

fn m_move(source: PathBuf, target: PathBuf) -> io::Result<()> {
    if source.exists() == false {
        return Err(Error::new(ErrorKind::NotFound, "source not found"));
    }

    if target.exists() == false {
        create_dir_all(&target)?;
    }

    let item_name = match source.file_name() {
        Some(name) => name,
        None => return Err(Error::new(ErrorKind::InvalidInput, "Invalid source path")),
    };

    let destination = target.join(item_name);
    rename(source, destination)?;

    Ok(())
}