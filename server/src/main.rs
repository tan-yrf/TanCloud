use axum::{ routing::{post}, response::IntoResponse, Json, Router};
use tracing_subscriber;
use serde_json::json;
use std::env;
use std::path::PathBuf;
use once_cell::sync::Lazy;

mod error_code;
mod http_response;
mod mid;
mod config;
mod user;
mod fs;

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
    // todo: 后面把配置项通过配置文件来设置
    
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        std::process::exit(1);
    }
    let db_path = &args[1];

    // 初始化数据库和日志
    config::init_db(db_path).await;
    tracing_subscriber::fmt::init();

    let app = Router::new()
        .route("/TanCloud", post(root))
        .nest("/TanCloud/user", user::user_routes())
        .nest("/TanCloud/fs", fs::fs_routes());


    let listener = tokio::net::TcpListener::bind("0.0.0.0:52996")
        .await
        .unwrap();
    tracing::debug!("listening on {}", listener.local_addr().unwrap());
    axum::serve(listener, app).await.unwrap();
}

// 测试连通性用
async fn root() -> impl IntoResponse {
    Json(json!({ "message": "Ok" }))
}
