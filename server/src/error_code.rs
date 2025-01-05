use serde::Serialize;

#[derive(Serialize, Clone, Copy)]
#[allow(dead_code)]
pub enum ErrorCode {
    Unknown = -1,
    Success = 0,

    // 用户相关
    UserNotExists = 10001,          // 用户不存在
    PasswordError = 10002,          // 密码错误  

    // 文件相关
    InvalidPath = 20001,            // 无效路径
}

impl ErrorCode {
    pub fn message(&self) -> &str {
        match self {
            ErrorCode::Unknown => "未知错误",
            ErrorCode::Success => "成功",

            ErrorCode::UserNotExists => "用户不存在",
            ErrorCode::PasswordError => "密码错误",

            ErrorCode::InvalidPath => "无效路径",
        }
    }
}