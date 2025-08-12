from . import db
from datetime import datetime
import json

class Upload(db.Model):
    __tablename__ = 'uploads'
    id = db.Column(db.Integer, primary_key=True)
    original_filename = db.Column(db.String(255), nullable=False)
    upload_timestamp = db.Column(db.DateTime, default=datetime.utcnow)
    result_path = db.Column(db.String(255), nullable=False, unique=True)
    params = db.Column(db.Text, nullable=False)
    results = db.relationship('Result', backref='upload', lazy=True, cascade="all, delete-orphan")

    def get_params(self):
        return json.loads(self.params)

class Result(db.Model):
    __tablename__ = 'results'
    id = db.Column(db.Integer, primary_key=True)
    upload_id = db.Column(db.Integer, db.ForeignKey('uploads.id'), nullable=False)
    audio_filename = db.Column(db.String(255), nullable=False)
    spectrogram_filename = db.Column(db.String(255), nullable=False)
    # --- ▼▼▼ 新增這個欄位來儲存 AI 分析結果 ▼▼▼ ---
    detections = db.Column(db.Text, nullable=True) # 儲存 JSON 字串

    @property
    def audio_url(self):
        return f"{self.upload.result_path}/{self.audio_filename}"

    @property
    def spectrogram_url(self):
        return f"{self.upload.result_path}/{self.spectrogram_filename}"

    # --- ▼▼▼ 新增這個函式來解析 JSON ▼▼▼ ---
    def get_detections(self):
        if self.detections:
            return json.loads(self.detections)
        return []