use axum::{
    extract::{FromRequestParts},
    http::{header, StatusCode, request::Parts, Request},
};
use sqlx::FromRow;
use std::sync::Arc;
use crate::config::get_db_pool;

// 自定义 BearerToken 结构体
#[derive(Clone, FromRow)]
#[allow(dead_code)]
pub struct UserInfo {
    pub id: i64,
    pub name: String,
    pub space: i64,
}
impl UserInfo {
    pub fn new(id: i64, name: String, space: i64) -> Self {
        Self { id, name, space }
    }
}

// 中间件，用于验证 Token
pub struct RequireAuth;

impl<S> FromRequestParts<S> for RequireAuth
where
    S: Send + Sync,
{
    type Rejection = StatusCode;

    // 对token进行校验，校验成功后将对应用户的信息存入扩展中，给后续处理函数使用
    async fn from_request_parts(parts: &mut Parts, state: &S) -> Result<Self, Self::Rejection> {
        // 获取 Authorization 头
        let auth_header = parts
            .headers
            .get(header::AUTHORIZATION)
            .and_then(|value| value.to_str().ok());

        match auth_header {
            Some(auth_header) if auth_token(auth_header).await.is_ok() => {
                let userinfo = UserInfo::new(1, "test".to_string(), 1024);
    
                // 获取 Request 对象的 extensions，并将用户信息插入其中
                let mut req = Request::from_parts(parts.clone(), Arc::new(state));
                req.extensions_mut().insert(userinfo);

                Ok(Self)
            }
            _ => Err(StatusCode::UNAUTHORIZED),
        }
    }
}

// 校验token，现在token没有加密，就是用户id
async fn auth_token(token: &str) -> Result<UserInfo, ()> {
    let pool = get_db_pool();
    let res = sqlx::query_as::<_, UserInfo>(
        r#"SELECT * FROM user WHERE id = ?"#
    )
    .bind(token)
    .fetch_one(pool)
    .await;

    match res {
        Ok(userinfo) => Ok(userinfo),
        Err(_) => Err(()),
    }
}