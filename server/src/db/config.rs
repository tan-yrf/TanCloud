use once_cell::sync::Lazy;
use sqlx::{sqlite::SqlitePool, Pool, Sqlite};
use std::env;
use std::path::PathBuf;
use tracing::info;

pub static DB_POOL: Lazy<Pool<Sqlite>> = Lazy::new(|| {
    let db_path = PathBuf::from(env::current_dir().unwrap()).join("tancloud.db");
    info!("db_path: {}", db_path);

    // 创建数据库连接池
    SqlitePool::connect_lazy(&format!("sqlite://{}",db_path.to_str().unwrap()))
        .expect("Failed to create database connection pool");
});

// 返回数据库连接池
pub async fn get_db_pool() -> &'static Pool<Sqlite> {
    &DB_POOL
}