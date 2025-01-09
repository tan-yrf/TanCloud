use axum::{
    extract::{Json, Extension},
    response::{IntoResponse, Response},
    http::{StatusCode, header},
    body::Body
};
use serde::Deserialize;
use crate::{
    error_code::ErrorCode,
    mid::UserInfo,
    fs::tools::{verify_path},
};

#[derive(Deserialize)]
pub struct RequestDownload {
    pub path: String,
}

pub async fn handle_download(
    Extension(user_info): Extension<UserInfo>,
    Json(request_download): Json<RequestDownload>,
) -> impl IntoResponse {
    let verify_path = match verify_path(&request_download.path, &user_info.id.to_string()) {
        Ok(res) => res,
        Err(_) => {
            return ErrorCode::InvalidPath.message().into_response();
        }
    };

    if verify_path.target.is_dir() {
        return ErrorCode::NeedFileNotDir.message().into_response();
    }

    let file = match tokio::fs::File::open(&verify_path.target).await {
        Ok(f) => f,
        Err(_) => {
            return ErrorCode::FileOpenFaild.message().into_response();
        }
    };

    let stream = tokio_util::io::ReaderStream::new(file);
    let body = Body::from_stream(stream);
    let response = Response::builder()
    .status(StatusCode::OK)
    .header(header::CONTENT_TYPE, "text/plain; charset=utf-8")
    .header(header::CONTENT_DISPOSITION, format!("attachment; filename=\"{}\"", verify_path.target.file_name().unwrap().to_str().unwrap()))
    .body(body)
    .unwrap();

    // 返回最终的响应
    response.into_response()
}