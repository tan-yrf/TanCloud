use axum::{
    extract::{Json, Extension},
    response::{IntoResponse},
    http::StatusCode,
};

use serde::{Deserialize, Serialize};
use serde_json::json;
use std::path::Path;
use std::fs::{read_dir, metadata};
use std::io;
use std::time::{SystemTime, UNIX_EPOCH};

use crate::http_response::HttpResponse;
use crate::error_code::ErrorCode;
use crate::mid::UserInfo;

#[derive(Deserialize, Serialize)]
pub struct FileInfo {
    pub path: String,
    pub name: String,
    pub is_dir: bool,
    pub size: u64,
    pub create_time: i64,
    pub last_modify_time: i64,
}


pub async fn handle_get_directory_info(
    Extension(user_info): Extension<UserInfo>,
    Json(path_str): Json<String>
) -> impl IntoResponse {

    let path = Path::new(&path_str);
    let response = match get_directory_info(path) {
        Ok(files_info) => HttpResponse::new(ErrorCode::Success, json!(files_info)),
        Err(_) => HttpResponse::new(ErrorCode::Unknown, json!({})),
    };

    (StatusCode::OK, Json(response))
}


// 将系统时间转换为时间戳
fn system_time_to_timestamp(time: SystemTime) -> i64 {
    match time.duration_since(UNIX_EPOCH) {
        Ok(duration) => duration.as_secs() as i64,
        Err(_) => 0,
    }
}

// 获取目录中所有文件和文件夹的信息
fn get_directory_info(path: &Path) -> io::Result<Vec<FileInfo>> {
    let mut files_info = Vec::new();

    if path.is_dir() {
        for entry in read_dir(path)? {
            let entry = entry?;
            let metadata = metadata(entry.path())?;

            let file_name = entry.file_name().into_string().unwrap_or_else(|_| String::from("Invalid filename"));
            let is_dir = entry.file_type()?.is_dir();
            let size = metadata.len();  // 文件大小(字节)
            let create_time = match metadata.created() {
                Ok(time) => system_time_to_timestamp(time),
                Err(_) => 0,
            };
            let last_modify_time = system_time_to_timestamp(metadata.modified()?);

            files_info.push(FileInfo {
                path: entry.path().to_string_lossy().to_string(),
                name: file_name,
                is_dir,
                size,
                create_time,
                last_modify_time,
            });
        }
    }

    Ok(files_info)
}

