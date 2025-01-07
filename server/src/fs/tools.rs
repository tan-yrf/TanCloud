use std::fs;
use std::path::PathBuf;
use crate::WORK_DIR;


// 非法字符集合
pub const ILLEGAL_CHARS: &[char] = &['\\', ':', '*', '?', '"', '<', '>', '|'];

pub struct VerifyResult {
    pub root_path: PathBuf,
    pub target: PathBuf,
}

// 校验路径(路径是否合法,路径对应的资源是否存在),成功返回完整目标路径,失败返回响应结构体
pub fn verify_path(path: &String, user_id: &String) -> Result<VerifyResult, ()> {
    if path.contains("..") || ILLEGAL_CHARS.iter().any(|&c| path.contains(c)) {
        return Err(());
    }

    let res = VerifyResult {
        root_path: WORK_DIR.join(user_id.clone()).join("root"),
        target: WORK_DIR.join(user_id).join("root").join(path),
    };
    if fs::metadata(&res.target).is_ok() {
        Ok(res)
    } else {
        Err(())
    }
}