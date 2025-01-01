use axum::{
    routing::{get, post},
    response::IntoResponse,
    Json,
    Router,
    middleware,
};

use tracing_subscriber;
use serde_json::json;

mod db;
mod error_code;
mod http_response;
mod mid;


#[tokio::main]
async fn main() {
    // 初始化数据库
    db::config::init_db().await;

    // 初始化 tracing 用来记录日志
    tracing_subscriber::fmt::init();

    // 构建路由
    //let user_routes = Router::new();

    let app = Router::new()
        .route("/TanCloud", post(root))
        .nest("/TanCloud/user", user_routes);

    // 使用 hyper 运行服务
    let listener = tokio::net::TcpListener::bind("0.0.0.0:52996")
        .await
        .unwrap();
    tracing::debug!("listening on {}", listener.local_addr().unwrap());
    axum::serve(listener, app).await.unwrap();
}

async fn root() -> impl IntoResponse {
    Json(json!({ "message": "你好个p" }))
}
