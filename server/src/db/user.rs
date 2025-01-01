use axum::{response::IntoResponse, Json, http::StatusCode};
use serde::{Deserialize, Serialize};

use crate::db::config::get_db_pool;
use crate::http_response::HttpResponse;

#[derive(Deserialize, Serialize)]
pub struct User {
    id: i32,
    name: String,
    password: String,
    space: i64,     // 云空间大小
}

// 创建用户
pub async fn create_user(user: Json<User>) -> impl IntoResponse {
    let pool = get_db_pool();
    let user = user.0;
    let res = sqlx::query(
        r#"
        INSERT INTO user (id, name, password, space)
        VALUES (?, ?, ?, ?)
        "#,
    )
    .bind(user.id).bind(user.name).bind(user.password).bind(user.space)
    .execute(pool)
    .await;

    let response = match res {
        Ok(_) => HttpResponse {
            code: 0,
            message: "创建用户成功".to_string(),
            body: (),
        },
        Err(e) => {
            eprintln!("创建用户失败: {:?}", e);
            HttpResponse {
                code: 1,
                message: "创建用户失败".to_string(),
                body: (),
            }
        }
    };

    (StatusCode::OK, Json(response))
}