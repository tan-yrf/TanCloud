use serde::Serialize;

#[derive(Serialize, Clone, Copy)]
#[allow(dead_code)]
pub enum ErrorCode {
    Success = 0,

    // 用户相关
    UserCreatedScuccess = 10000,
    UserCreateFailed = 10001,
}

impl ErrorCode {
    pub fn message(&self) -> &str {
        match self {
            ErrorCode::Success => "成功",

            ErrorCode::UserCreatedScuccess => "用户创建成功",
            ErrorCode::UserCreateFailed => "用户创建失败",
        }
    }
}