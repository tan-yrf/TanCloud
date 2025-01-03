pub mod info;

use axum::{Router, routing::post};

pub fn fs_routes() -> Router {
    Router::new()
        .nest("/", info_routes())
}
pub fn info_routes() -> Router {
    Router::new()
        .route("/get_directory_info", post(info::handle_get_directory_info))   
}