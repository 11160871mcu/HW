FROM python:3.9-slim

# 安裝所有 OpenCV 可能需要的底層系統依賴
RUN apt-get update && apt-get install -y \
    libgl1-mesa-glx \
    libglib2.0-0 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# 之後的步驟維持不變
WORKDIR /app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

COPY app/ .

CMD ["flask", "run", "--host=0.0.0.0"]