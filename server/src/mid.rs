use axum::{
    http::{Request, StatusCode},
    middleware::Next,
    response::{IntoResponse, Response},
    body::Body,
};
use std::net::SocketAddr;

#[allow(dead_code)]
pub async fn restrict_to_localhost(req: Request<Body>, next: Next) -> Response {
    if let Some(addr) = req.extensions().get::<SocketAddr>() {
        if addr.ip().is_loopback() {
            return next.run(req).await;
        }
    }
    (StatusCode::FORBIDDEN, "Forbidden").into_response()
}