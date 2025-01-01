use once_cell::sync::Lazy;
use sqlx::{sqlite::SqlitePool, Pool, Sqlite};
use std::env;
use std::path::PathBuf;
use tracing::info;

pub static DB_POOL: Lazy<Pool<Sqlite>> = Lazy::new(|| {
    let db_path = PathBuf::from(env::current_dir().unwrap()).join("tancloud.db");
    info!("db_path: {}", db_path.display());
    println!("Database path: {}", db_path.display());

    // 创建数据库连接池
    SqlitePool::connect_lazy(&format!("sqlite://{}", db_path.to_str().unwrap()))
        .unwrap_or_else(|_| panic!("Failed to create database connection pool"))
});

// 返回数据库连接池
pub fn get_db_pool() -> &'static Pool<Sqlite> {
    &DB_POOL
}

// 初始化数据库，检查数据库和表是否存在，不存在就创建
pub async fn init_db() {
    let pool = get_db_pool();

    let res = sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS user (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            password TEXT NOT NULL,
            space INTEGER NOT NULL
        );
        "#
    )
    .execute(pool)
    .await;

    match res {
        Ok(_) => info!("create table user success"),
        Err(e) => panic!("create table user failed: {}", e),
    }
}