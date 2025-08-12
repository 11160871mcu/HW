# app/audio_utils.py 的完整程式碼
import os
import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
from scipy.io.wavfile import write
from datetime import datetime
from .ai_model import run_inference # <-- 導入 AI 推論函式

def process_audio_and_generate_spectrograms(filepath, result_dir, spec_type, segment_duration=2.0, overlap_ratio=0.5):
    # ... (此函式頂部內容不變) ...
    try:
        y, sr = librosa.load(filepath, sr=None)
    except Exception as e:
        print(f"Error loading audio file: {e}")
        return []

    results = []
    basename = f"{os.path.splitext(os.path.basename(filepath))[0]}_{datetime.now().strftime('%Y%m%d%H%M%S')}"

    frame_length = int(segment_duration * sr)
    hop_length = int(frame_length * (1 - overlap_ratio))
    
    if frame_length == 0 or hop_length == 0:
        return []

    y_frames = librosa.util.frame(y, frame_length=frame_length, hop_length=hop_length)

    for i, segment in enumerate(y_frames.T):
        audio_filename = f"{basename}_part{i}.wav"
        spec_filename = f"{basename}_spec{i}.png"
        
        audio_path = os.path.join(result_dir, audio_filename)
        spec_path = os.path.join(result_dir, spec_filename)
        
        segment_int16 = (segment * 32767).astype(np.int16)
        write(audio_path, sr, segment_int16)
        save_spectrogram(segment, sr, spec_path, spec_type)
        
        # 1. 暫時註解掉真正的 AI 推論
        # detections = run_inference(spec_path) 
        
        # 2. 建立一個假的偵測結果
        print("--- Generating FAKE detection data for testing! ---")
        fake_detections = [{
            "box": [50, 70, 250, 200],
            "label": "假偵測物件",
            "confidence": 0.99
        }]
        detections = fake_detections

        results.append({
            'audio': audio_filename,
            'spectrogram': spec_filename,
            'detections': detections # 確保這裡傳遞的是 fake_detections
        })

    return results

def save_spectrogram(y, sr, out_path, spec_type='mel'):
    # ... (此函式內容不變) ...
    plt.figure(figsize=(6, 4)) 
    if spec_type == 'mel':
        S = librosa.feature.melspectrogram(y=y, sr=sr, n_mels=128, fmax=sr/2)
        S_db = librosa.power_to_db(S, ref=np.max)
        librosa.display.specshow(S_db, sr=sr, x_axis='time', y_axis='mel', fmax=sr/2)
        plt.title('Mel Spectrogram')
    else: # stft
        D = librosa.stft(y)
        S_db = librosa.amplitude_to_db(np.abs(D), ref=np.max)
        librosa.display.specshow(S_db, sr=sr, x_axis='time', y_axis='hz')
        plt.title('STFT Spectrogram')
    plt.colorbar(format='%+2.0f dB')
    plt.tight_layout()
    plt.savefig(out_path)
    plt.close()