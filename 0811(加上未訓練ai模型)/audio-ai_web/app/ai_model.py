# app/ai_model.py (新增檔案)

from ultralytics import YOLO
import torch
import os

# 偵測是否有可用的 GPU，否則使用 CPU
DEVICE = "cuda" if torch.cuda.is_available() else "cpu"
print(f"AI Model using device: {DEVICE}")

# 建立模型檔案的路徑
# current_path -> /app
# model_path -> /app/models/best.pt
current_path = os.path.dirname(os.path.abspath(__file__))
model_path = os.path.join(current_path, "models", "best.pt")

# 載入模型。這段程式碼只會在服務啟動時執行一次，避免重複載入
try:
    model = YOLO(model_path)
    model.to(DEVICE)
    print("AI model loaded successfully.")
except Exception as e:
    print(f"Error loading AI model: {e}")
    # 如果模型載入失敗，建立一個假的 model 物件，讓程式不至於崩潰
    model = None

def run_inference(image_path):
    """
    對指定的圖片執行 YOLO 推論，並回傳格式化的結果。
    """
    if model is None:
        print("AI model is not available, skipping inference.")
        return []

    try:
        results = model(image_path)
        processed_results = []
        
        # 解析 YOLO 的回傳結果
        for result in results:
            boxes = result.boxes
            for box in boxes:
                # 獲取座標、信心度、和類別
                xyxy = box.xyxy[0].tolist()
                conf = box.conf[0].item()
                cls = int(box.cls[0].item())
                label = model.names[cls]
                
                processed_results.append({
                    "box": [round(coord) for coord in xyxy], # 座標取整數
                    "label": label,
                    "confidence": round(conf, 2) # 信心度取到小數點後兩位
                })
        return processed_results
    except Exception as e:
        print(f"Error during AI inference: {e}")
        return []