# app/__init__.py

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import os

db = SQLAlchemy()

def create_app():
    app = Flask(__name__)

    # --- 資料庫設定 ---
    app.config['SQLALCHEMY_DATABASE_URI'] = os.environ.get('DATABASE_URL')
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

    # --- 檔案路徑設定 ---
    app.config['UPLOAD_FOLDER'] = 'static/uploads'
    app.config['RESULT_FOLDER'] = 'static/results'

    os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
    os.makedirs(app.config['RESULT_FOLDER'], exist_ok=True)
    
    db.init_app(app)

    with app.app_context():
        # --- ▼▼▼ 新增這兩行 ▼▼▼ ---
        # 讓 Flask 知道我們的路由在哪裡
        from . import main
        # 將 main.py 中的路由藍圖註冊到 app
        app.register_blueprint(main.main_bp)
        # --- ▲▲▲ 新增這兩行 ▲▲▲ ---

        # 建立所有資料庫表格
        db.create_all()
        return app