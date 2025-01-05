pub mod info;
pub mod rename;
pub mod tools;

use axum::{
    Router, 
    routing::post,
    middleware::from_extractor,
};
use crate::mid::RequireAuth;

pub fn fs_routes() -> Router {
    Router::new()
        .route("/get_directory_info", post(info::handle_get_directory_info)) 
        .route_layer(from_extractor::<RequireAuth>())
}
