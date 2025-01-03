mod error_code;
mod http_response;
mod mid;
mod config;
mod user;


use axum::{ routing::{post}, response::IntoResponse, Json, Router};
use tracing_subscriber;
use serde_json::json;
use std::env;
use std::path::PathBuf;
use once_cell::sync::Lazy;

// 用来存储工作目录
pub static WORK_DIR: Lazy<PathBuf> = Lazy::new(|| {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        std::process::exit(1);
    }
    PathBuf::from(&args[2])
});

#[tokio::main]
async fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        std::process::exit(1);
    }
    let db_path = &args[1];

    // 初始化数据库
    config::init_db(db_path).await;

    // 初始化 tracing 用来记录日志
    tracing_subscriber::fmt::init();

    // 构建路由
    let app = Router::new()
        .route("/TanCloud", post(root))
        .nest("/TanCloud/user", user::user_routes());

    // 使用 hyper 运行服务
    let listener = tokio::net::TcpListener::bind("0.0.0.0:52996")
        .await
        .unwrap();
    tracing::debug!("listening on {}", listener.local_addr().unwrap());
    axum::serve(listener, app).await.unwrap();
}

async fn root() -> impl IntoResponse {
    Json(json!({ "message": "Ok" }))
}
