use axum::{
    extract::{Json, Extension},
    response::{IntoResponse},
    http::StatusCode,
};
use serde::{Deserialize, Serialize};
use serde_json::json;
use std::path::{PathBuf};
use std::fs::{read_dir, metadata};
use crate::mid::UserInfo;

#[derive(Deserialize)]
struct RequestRename {
    pub path: String,
    pub new_name: String
}

pub async fn hadnle_rename(
    Extension(user_info): Extension<UserInfo>,
    Json(request_rename): Json<RequestRename>
) -> impl IntoResponse {
    // 校验路径中是否有不合法字符

    // 校验目标路径是否存在
}