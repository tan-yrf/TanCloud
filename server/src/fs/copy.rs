use axum::{
    extract::{Json, Extension},
    response::{IntoResponse},
    http::StatusCode,
};
use serde::{Deserialize};
use serde_json::json;
use std::path::PathBuf;
use std::fs::{metadata, copy, create_dir_all, read_dir};
use std::io::{self, Error, ErrorKind};

use crate::http_response::HttpResponse;
use crate::error_code::ErrorCode;
use crate::mid::UserInfo;
use crate::fs::tools::{verify_path};

#[derive(Deserialize)]
pub struct RequestCopy {
    original: String,
    target: String
}

// 处理拷贝请求
pub async fn handle_copy(
    Extension(user_info): Extension<UserInfo>,
    Json(request_copy): Json<RequestCopy>
) -> impl IntoResponse {
    // 待拷贝的原始路径要求资源存在
    let verify_org_res = match verify_path(&request_copy.original, &user_info.id.to_string()) {
        Ok(res) => res,
        Err(_) => {
            let response = HttpResponse::new(ErrorCode::InvalidPath, json!({}));
            return (StatusCode::OK, Json(response));
        }
    };

    // 待拷贝的目标路径要求是一个文件夹，并且该文件夹中不能存在与原始路径同名的文件或文件夹
    let target_path = verify_org_res.root_path.join(request_copy.target);
    match metadata(&target_path) {
        Ok(metadata) if metadata.is_dir() => {
            let target_name = request_copy.original.split('/').last().unwrap();
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

    let org_path = verify_org_res.target;
    let response = match m_copy(org_path, target_path) {
        Ok(_) => HttpResponse::new(ErrorCode::Success, json!({})),
        Err(_) => HttpResponse::new(ErrorCode::CopyFailed, json!({})),
    };
    
    (StatusCode::OK, Json(response))
}

fn m_copy(source: PathBuf, target: PathBuf) -> io::Result<()> {
    if source.is_dir() {
        let target_folder = target.join(source.file_name().unwrap());
        if target_folder.exists() == false {
            create_dir_all(&target_folder)?;
        }
        // 调用递归拷贝函数进行复制
        copy_recursively(source, target_folder)?;
    } else {
        let target_file_path = target.join(source.file_name().unwrap());
        copy(&source, target_file_path)?;
    }

    Ok(())
}

// 拷贝资源(文件或者文件夹)到目标文件夹下
fn copy_recursively(source: PathBuf, destination: PathBuf) -> io::Result<()> {
    if source.exists() == false {
        return Err(Error::new(ErrorKind::NotFound, "Source path not found"));
    }

    // 如果目标路径不存在，创建目标路径
    if destination.exists() == false {
        create_dir_all(&destination)?;
    }

    // 如果源路径是文件，则直接拷贝到目标路径
    if source.is_file() {
        let target_file_path = destination.join(source.file_name().unwrap());
        copy(&source, target_file_path)?;
    } else if source.is_dir() {
        // 遍历源目录中的每个条目，递归拷贝文件或子目录
        for entry in read_dir(&source)? {
            let entry = entry?;
            let entry_path = entry.path();
            let mut destination_path = destination.clone();
            destination_path.push(entry.file_name());

            if entry_path.is_dir() {
                // 递归拷贝子目录
                copy_recursively(entry_path, destination_path)?;
            } else {
                // 拷贝文件
                copy(&entry_path, &destination_path)?;
            }
        }
    }

    Ok(())
}