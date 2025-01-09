use std::fs::metadata;
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
        target: WORK_DIR.join(user_id.clone()).join("root").join(path),
    };
    //println!("root {},  target {}", res.root_path.to_string_lossy(), res.target.to_string_lossy());
    if metadata(&res.target).is_ok() {
        Ok(res)
    } else {
        Err(())
    }
}

// 检查新名称是否包含非法字符,以及目标路径下是否存在同名文件
pub fn validate_new_name(target: &PathBuf, new_name: &String) -> Result<(), ()> {
    if new_name.is_empty() {
        return Err(());
    }
    
    if ILLEGAL_CHARS.iter().any(|&c| new_name.contains(c)) {
        return Err(());
    }

    let new_path = target.join(new_name);
    if metadata(&new_path).is_ok() {
        return Err(());
    }

    Ok(())
}