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
    RenameFailed = 20002,           // 重命名失败
    RenameSuccess = 20003,          // 重命名成功
    CopyFailed = 20004,             // 复制失败
    PathExists = 20005,             // 路径已存在
    CreateDirFailed = 20006,        // 创建目录失败
    MoveFailed = 20007,             // 移动失败
    DeleteFailed = 20008,           // 删除失败
    ValidataName = 20009,           // 非法名称
    WriteFailed = 20010,            // 写入失败
    MissField = 20011,              // 缺失字段 
    OutSize = 20012,                // 文件大小超出限制
    FileOpenFaild = 20013,          // 文件打开失败
    NeedFileNotDir = 20014,         // 需要文件而不是文件夹
}

impl ErrorCode {
    pub fn message(&self) -> &str {
        match self {
            ErrorCode::Unknown => "未知错误",
            ErrorCode::Success => "成功",

            ErrorCode::UserNotExists => "用户不存在",
            ErrorCode::PasswordError => "密码错误",

            ErrorCode::InvalidPath => "无效路径",
            ErrorCode::RenameFailed => "重命名失败",
            ErrorCode::RenameSuccess => "重命名成功",
            ErrorCode::CopyFailed => "复制失败",
            ErrorCode::PathExists => "路径已存在",
            ErrorCode::CreateDirFailed => "创建目录失败",
            ErrorCode::MoveFailed => "移动失败",
            ErrorCode::DeleteFailed => "删除失败",
            ErrorCode::ValidataName => "非法名称",
            ErrorCode::WriteFailed => "写入失败",
            ErrorCode::MissField => "缺失字段",
            ErrorCode::OutSize => "文件大小超出限制",
            ErrorCode::FileOpenFaild => "文件打开失败",
            ErrorCode::NeedFileNotDir => "路径是文件而不是文件夹",
        }
    }
}