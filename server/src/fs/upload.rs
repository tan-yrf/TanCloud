use axum::{
    extract::{Json, Multipart},
    extract::{Extension},
    response::IntoResponse,
    http::StatusCode,
};
use walkdir::WalkDir;
use serde_json::json;
use std::{
    fs,
    fs::OpenOptions,
    io::Write,
    path::PathBuf,
};
use crate::{
    http_response::HttpResponse,
    error_code::ErrorCode,
    mid::UserInfo,
    fs::tools::{verify_path, validate_new_name},
};

pub async fn handle_upload (
    Extension(user_info): Extension<UserInfo>,
    mut multipart: Multipart,
) -> impl IntoResponse {
    let mut target: String = String::from("?");
    let mut name: String = String::from("?");
    let mut size: i64 = i64::MAX;
    let mut file_path: Option<PathBuf> = None;
    let mut written_size: i64 = 0;

    while let Some(mut field) = multipart.next_field().await.unwrap() {
        match field.name() {
            Some("target") => target = field.text().await.unwrap(),
            Some("name") => name = field.text().await.unwrap(),
            Some("size") => size = field.text().await.unwrap().parse().unwrap_or(i64::MAX),
            Some("file") => {
                // 校验路径是否存在
                let verify_path_res = match verify_path(&target, &user_info.id.to_string()) {
                    Ok(res) => res,
                    Err(_) => {
                        let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
                        return (StatusCode::OK, Json(response));
                    }
                };

                // 校验文件名是否合法
                if let Err(_) = validate_new_name(&verify_path_res.target, &name) {
                    let response = HttpResponse::new(ErrorCode::ValidataName, json!({}));
                    return (StatusCode::OK, Json(response));
                }

                // 校验上传的文件大小是否超出限制
                let available_size = user_info.space - calculate_dir_size(&verify_path_res.root_path);
                if size > available_size {
                    let response = HttpResponse::new(ErrorCode::OutSize, json!({}));
                    return (StatusCode::OK, Json(response));
                }

                // 上传文件
                let path = verify_path_res.target.clone().join(name.clone());
                file_path = Some(path.clone());
                let mut file = match OpenOptions::new().create(true).write(true).open(file_path.as_ref().unwrap()) {
                    Ok(f) => f,
                    Err(_) => {
                        let response = HttpResponse::new(ErrorCode::WriteFailed, json!({}));
                        return (StatusCode::OK, Json(response));
                    }
                };

                const MAX_CHUNK_SIZE: usize = 4 * 1024 * 1024; // 4 MB
                let mut buffer: Vec<u8> = Vec::with_capacity(MAX_CHUNK_SIZE);

                // 分块写入
                while let Some(chunk) = field.chunk().await.unwrap() {
                    buffer.extend_from_slice(&chunk);
                    if buffer.len() >= MAX_CHUNK_SIZE {
                        if let Err(_) = file.write_all(&buffer) {
                            let response = HttpResponse::new(ErrorCode::WriteFailed, json!({}));
                            return (StatusCode::OK, Json(response));
                        }
                        written_size += buffer.len() as i64;
                        buffer.clear();
                    }
                }

                // 如果最后还有剩余的数据，写入文件
                if buffer.is_empty() == false {
                    if let Err(_) = file.write_all(&buffer) {
                        let response = HttpResponse::new(ErrorCode::WriteFailed, json!({}));
                        return (StatusCode::OK, Json(response));
                    }
                    written_size += buffer.len() as i64;
                }
            }
            _ => {}
        }
    }

    if name.is_empty() || size == i64::MAX || size != written_size {
        if let Some(path) = file_path {
            let _ = fs::remove_file(path);
        }
        let response = HttpResponse::new(ErrorCode::MissField, json!({}));
        return (StatusCode::OK, Json(response));
    }

    let response = HttpResponse::new(ErrorCode::Success, json!({}));
    (StatusCode::OK, Json(response))
}

fn calculate_dir_size(path: &PathBuf) -> i64 {
    WalkDir::new(path)
        .into_iter() 
        .filter_map(|entry| entry.ok()) 
        .filter_map(|entry| fs::metadata(entry.path()).ok()) 
        .filter(|metadata| metadata.is_file()) // 仅计算文件
        .map(|metadata| metadata.len() as i64) 
        .sum() 
}