# app/main.py 的完整程式碼

from flask import current_app, render_template, request, redirect, url_for
from werkzeug.utils import secure_filename
import os
import json
import shutil
from . import db
from .models import Upload, Result
from .audio_utils import process_audio_and_generate_spectrograms
from flask import Blueprint

main_bp = Blueprint('main', __name__)

@main_bp.route('/')
def index():
    return render_template('index.html')

# --- ▼▼▼ 修改這個 /history 路由 ▼▼▼ ---
@main_bp.route('/history')
def history():
    # 1. 從 URL 參數中獲取排序指令，預設為 'desc' (新到舊)
    sort_order = request.args.get('sort', 'desc')

    # 2. 建立基礎查詢
    query = Upload.query

    # 3. 根據排序指令決定排序方式
    if sort_order == 'asc':
        all_uploads = query.order_by(Upload.upload_timestamp.asc()).all()
    else:
        all_uploads = query.order_by(Upload.upload_timestamp.desc()).all()

    # 4. 將排序結果和當前的排序狀態傳給模板
    return render_template('history.html', uploads=all_uploads, current_sort=sort_order)
# --- ▲▲▲ 修改這個 /history 路由 ▲▲▲ ---


@main_bp.route('/upload', methods=['POST'])
def upload():
    # ... (此函式內容不變) ...
    if 'file' not in request.files:
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)
    try:
        spec_type = request.form['spec_type']
        segment_duration = float(request.form['segment_duration'])
        overlap = float(request.form['overlap'])
        params_dict = {
            'spec_type': spec_type,
            'segment_duration': segment_duration,
            'overlap': overlap
        }
    except (KeyError, ValueError):
        return "Invalid parameters provided.", 400
    if file:
        filename = secure_filename(file.filename)
        new_upload = Upload(
            original_filename=filename,
            result_path="pending",
            params=json.dumps(params_dict)
        )
        db.session.add(new_upload)
        db.session.commit()
        upload_id = new_upload.id
        result_dir_name = os.path.join(current_app.config['RESULT_FOLDER'], str(upload_id))
        os.makedirs(result_dir_name, exist_ok=True)
        new_upload.result_path = os.path.join('results', str(upload_id))
        db.session.commit()
        upload_path = os.path.join(current_app.config['UPLOAD_FOLDER'], filename)
        file.save(upload_path)
        results_data = process_audio_and_generate_spectrograms(
            filepath=upload_path, 
            result_dir=result_dir_name, 
            spec_type=spec_type,
            segment_duration=segment_duration,
            overlap_ratio=overlap
        )
        for res_item in results_data:
            new_result = Result(
                upload_id=upload_id,
                audio_filename=res_item['audio'],
                spectrogram_filename=res_item['spectrogram'],
                # --- ▼▼▼ 新增這一行 ▼▼▼ ---
                detections=json.dumps(res_item['detections']) # 將 list/dict 轉為 JSON 字串
            )
            db.session.add(new_result)
        db.session.commit()
        return redirect(url_for('main.results', upload_id=upload_id))
    return redirect(url_for('main.index'))

@main_bp.route('/results/<int:upload_id>')
def results(upload_id):
    upload_record = Upload.query.get_or_404(upload_id)
    return render_template('result.html', upload=upload_record)

@main_bp.route('/delete/<int:upload_id>', methods=['POST'])
def delete_upload(upload_id):
    upload_to_delete = Upload.query.get_or_404(upload_id)
    physical_path = os.path.join(current_app.root_path, 'static', upload_to_delete.result_path)
    try:
        if os.path.exists(physical_path):
            shutil.rmtree(physical_path)
            print(f"Successfully deleted folder: {physical_path}")
    except OSError as e:
        print(f"Error deleting folder {physical_path}: {e.strerror}")
    db.session.delete(upload_to_delete)
    db.session.commit()
    return redirect(url_for('main.history'))