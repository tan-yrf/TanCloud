use axum::{response::IntoResponse, Json, http::StatusCode};
use serde::{Deserialize, Serialize};
use sqlx::SqlitePool;
use crate::db::config::get_db_pool;
use crate::response::Response;

#[derive(Deserialize, Serialize)]
struct User {
    id: i32,
    name: String,
    space: i64,     // 云空间大小
}

// 创建用户
pub async fn create_user(user: Json<User>) -> impl IntoResponse {
    let pool = get_db_pool().await;
    let user = user.into_inner();
    let res = sqlx::query!(
        r#"
        INSERT INTO user (id, name, space)
        VALUES (?, ?, ?)
        "#,
        user.id,
        user.name,
        user.space
    )
    .execute(&pool)
    .await;

    let response = match res {
        Ok(_) => ApiResponse {
            code: 0,
            message: "创建用户成功".to_string(),
            body: user,
        },
        Err(e) => {
            eprintln!("创建用户失败: {:?}", e);
            ApiResponse {
                code: 1,
                message: "创建用户失败".to_string(),
                body: user,
            }
        }
    };

    (StatusCode::OK, Json(response))
}