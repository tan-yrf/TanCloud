use once_cell::sync::OnceCell;
use sqlx::{sqlite::SqlitePool, Pool, Sqlite};
use std::path::PathBuf;
use tracing::info;

static DB_POOL: OnceCell<Pool<Sqlite>> = OnceCell::new();

// 返回数据库连接池
pub fn get_db_pool() -> &'static Pool<Sqlite> {
    DB_POOL.get().expect("db pool not initialized")
}


// 初始化数据库连接池
pub async fn init_db(db_path: &str) {
    let db_path = PathBuf::from(db_path);
    info!("Initializing database at: {}", db_path.display());

    let pool = SqlitePool::connect(&format!("sqlite://{}", db_path.display()))
        .await
        .unwrap_or_else(|_| panic!("Failed to create database connection pool"));

    // 确保池只初始化一次
    DB_POOL.set(pool).expect("Failed to initialize the database pool");

    let res = sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS user (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            password TEXT NOT NULL,
            space INTEGER NOT NULL
        );
        "#,
    )
    .execute(get_db_pool())
    .await;

    match res {
        Ok(_) => info!("Database and user table initialized successfully"),
        Err(e) => panic!("Failed to initialize database: {}", e),
    }
}