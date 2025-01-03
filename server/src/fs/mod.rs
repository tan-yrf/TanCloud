pub mod info;

use axum::{routing::post, Router};

pub fn info_routes() -> Router {
    Router::new()
        .route("/get_directory_info", post(info::get_directory_info))   
}