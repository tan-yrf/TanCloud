use axum::{response::IntoResponse, Json, http::StatusCode, routing::post, Router};
use serde::{Deserialize, Serialize};
use serde_json::json;
use sqlx::{Error, FromRow};
use std::fs;

use crate::config::get_db_pool;
use crate::http_response::HttpResponse;
use crate::error_code::ErrorCode;
use crate::WORK_DIR;
use crate::fs::tools::calculate_dir_size;

pub fn user_routes() -> Router {
    Router::new()
        .route("/login", post(login))
}

#[derive(Deserialize, Serialize, FromRow)]
pub struct User {
    pub id: Option<i64>,
    pub name: String,
    pub password: String,
    pub space: Option<i64>, // 云空间大小
}

// 创建用户空间所需的文件夹
async fn create_user_folder(user_id: i64) {
    let user_dir = WORK_DIR.join(user_id.to_string());
    let trash_dir = user_dir.join("trash");
    let root_dir = user_dir.join("root");

    if !user_dir.exists() {
        fs::create_dir(&user_dir).unwrap_or_else(|e| {
            eprintln!("Failed to create user directory: {:?}", e);
        });
        fs::create_dir(&trash_dir).unwrap_or_else(|e| {
            eprintln!("Failed to create trash directory: {:?}", e);
        });
        fs::create_dir(&root_dir).unwrap_or_else(|e| {
            eprintln!("Failed to create root directory: {:?}", e);
        });
    }
}

// 用户登录
pub async fn login(user: Json<User>) -> impl IntoResponse {
    let pool = get_db_pool();
    let user = user.0;

    let res = sqlx::query_as::<_, User>(
        r#"
        SELECT * FROM user
        WHERE name = ?
        "#,
    )
    .bind(user.name)
    .fetch_one(pool)
    .await;

    // 用户名存在就验证密码，其他情况返回对应错误
    let response = match res {
        Ok(user_data) => {
            if user_data.password == user.password {
                // 校验通过，创建用户的目录结构
                if let Some(user_id) = user_data.id {
                    create_user_folder(user_id).await;
                    let user_dir = WORK_DIR.join(user_id.to_string());
                    let used = calculate_dir_size(&user_dir);
                    HttpResponse::new(ErrorCode::Success, json!({ 
                        "id": user_data.id.map(|id| id.to_string()).unwrap_or_default(), 
                        "name": user_data.name,
                        "space": user_data.space.map(|space| space.to_string()).unwrap_or_default(), 
                        "used": used.to_string(), 
                        "token": user_id.to_string() 
                    }))
                } else {
                    HttpResponse::new(ErrorCode::Unknown, json!({}))
                }
            } else {
                // 密码错误
                HttpResponse::new(ErrorCode::PasswordError, json!({}))
            }
        },
        Err(Error::RowNotFound) => {
            // 用户名不存在
            HttpResponse::new(ErrorCode::UserNotExists, json!({}))
        },
        Err(_e) => {
            // 其他数据库错误
            HttpResponse::new(ErrorCode::Unknown, json!({}))
        }
    };

    (StatusCode::OK, Json(response))
}
