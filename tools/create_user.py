import sqlite3
import argparse
import shutil
import time  

# 设置命令行参数解析
parser = argparse.ArgumentParser(description="Create a new user in the database.")
parser.add_argument("db_path", help="Path to the SQLite database file")
args = parser.parse_args()

# 使用传入的数据库路径连接到 SQLite 数据库
conn = sqlite3.connect(args.db_path)
cursor = conn.cursor()

# 如果用户表不存在，就创建一个，id 字段将使用时间戳作为主键
cursor.execute(''' 
CREATE TABLE IF NOT EXISTS user (
    id INTEGER PRIMARY KEY,  
    name TEXT NOT NULL,
    password TEXT NOT NULL,
    space INTEGER NOT NULL
);
''')

# 获取当前系统可用空间（以 GB 为单位）
total, used, free = shutil.disk_usage("/")
free_gb = free // (2**30)  # 转换为 GB

print(f"Available space on the system: {free_gb} GB")

username = input("Enter your username: ")
password = input("Enter your password: ")
space = input("Enter your space (in GB, as an integer): ")

# 校验输入
if not username or not password:
    print("Username and password must be non-empty.")
    exit(1)

try:
    space = int(space)
    if space < 0:
        print("Please enter a positive value for cloud space.")
        exit(1)
    if space > free_gb:
        print(f"Cloud space cannot exceed available system space of {free_gb} GB.")
        exit(1)
except ValueError:
    print("Space must be an integer.")
    exit(1)

# 将 GB 转换为字节
space_byte = space * (2**30)

# 获取当前时间戳
timestamp = int(time.time())  

# 插入用户数据，使用时间戳作为 id
try:
    cursor.execute(''' 
    INSERT INTO user (id, name, password, space) VALUES (?, ?, ?, ?)
    ''', (timestamp, username, password, space_byte))  # 传入时间戳作为 id
    conn.commit()
    print(f"User '{username}' created successfully with cloud space of {space} GB.")
except sqlite3.Error as e:
    print(f"Error inserting user: {e}")

# 关闭连接
conn.close()
