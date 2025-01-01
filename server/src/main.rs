use axum::{
    http::StatusCode,
    response::IntoResponse,
    routing::{get, post},
    Json, Router,
};
use serde::{Deserialize, Serialize};
use sqlx::sqlite::SqlitePool;
use once_cell::sync::OnceCell;
use std::env;
use std::path::PathBuf;

#[tokio::main]
async fn main() {
    // match env::current_dir() {
    //     Ok(cur_dir) => {
    //         let db_path = cur_dir.join("tancloud.db");
    //         let conn = Connection::open(db_path);
    //         // 在这里处理数据库连接
    //     }
    //     Err(e) => eprintln!("无法获取当前的工作目录路径: {}", e),
    // }

    
    // 初始化 tracing 用于记录日志
    tracing_subscriber::fmt::init();

    // 设置路由
    let app = Router::new()
        .route("/TanCloud", get(root))
        .route("/TanCloud", post(root));

    // 使用 hyper
    let listener = tokio::net::TcpListener::bind("0.0.0.0:52996")
        .await
        .unwrap();

    tracing::debug!("listening on {}", listener.local_addr().unwrap());
    axum::serve(listener, app).await.unwrap();
}

async fn root() -> & 'static str {
    "你好个p"
}