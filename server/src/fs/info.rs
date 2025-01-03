use std::fs::{read_dir, DirEntry};
use serde::{Deserialize, Serialize};
use serde_json::json;
use std::path::Path;
use std::io;
use std::time::{SystemTime, UNIX_EPOCH};

#[derive(Deserialize, Serialize)]
pub struct FileInfo {
    pub path: String,
    pub name: String,
    pub is_dir: bool,
    pub size: u64,
    pub create_time: i64,
    pub last_modify_time: i64,
}

// 将系统时间转换为时间戳
fn system_time_to_timestamp(tiem: SystemTime) -> i64 {
    match time.duration_since(UNIX_EPOCH) {
        Ok(n) => n.as_secs() as i64,
        Err(_) => 0,
    }
}

// 获取目录中所有文件和文件夹的信息
pub fn get_directory_info(path: &Path) -> Result<Vec<FileInfo>> {
    let mut files_info = Vec::new();

    if path.is_dir() {
        for entry in read_dir(path)? {
            let entry = entry?;
            let metadata = metadata(entry.path())?;

            let file_name = entry.file_name().into_string().unwrap_or_else(|_| String::from("Invalid filename"));
            let is_dir = entry.file_type()?.is_dir();
            let size = metadata.len();  // 文件大小(字节)
            let create_time = match metadata.created() {
                Ok(time) => systen_time_to_unix_timestamp(time),
                Err(_) => 0,
            }
            let last_modify_time = systen_time_to_unix_timestamp(metadata.modified()?);

            files_info.push(FileInfo {
                path: entry.path().to_string_lossy().to_string(),
                name: file_name,
                is_dir,
                size,
                create_time,
                last_modify_time,
            });
        }
    }

    Ok(files_info)
}