mod info;
mod rename;
mod copy;
mod m_move;
mod tools;

use axum::{
    Router, 
    routing::post,
    middleware::from_extractor,
};
use crate::mid::RequireAuth;

pub fn fs_routes() -> Router {
    Router::new()
        .route("/get_directory_info", post(info::handle_get_directory_info)) 
        .route("/rename", post(rename::handle_rename))
        .route("/copy", post(copy::handle_copy))
        .route("/move", post(m_move::handle_move))
        .route_layer(from_extractor::<RequireAuth>())
}
