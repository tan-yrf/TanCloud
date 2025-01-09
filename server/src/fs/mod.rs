mod tools;
mod info;
mod rename;
mod copy;
mod m_move;
mod delete;
mod create;
mod upload;

use axum::{
    Router, 
    routing::post,
    middleware::{from_extractor},
    extract::DefaultBodyLimit,
};
use crate::mid::RequireAuth;

pub fn fs_routes() -> Router {
    Router::new()
        .route("/get_directory_info", post(info::handle_get_directory_info)) 
        .route("/create_folder", post(create::handle_create))
        .route("/rename", post(rename::handle_rename))
        .route("/copy", post(copy::handle_copy))
        .route("/move", post(m_move::handle_move))
        .route("/delete", post(delete::handle_delete))
        .route("/upload", post(upload::handle_upload))
        .layer(from_extractor::<RequireAuth>())
        .layer(DefaultBodyLimit::max(10 * 1024 * 1024 * 1024))
}
